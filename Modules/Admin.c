//Thư viện sử dụng
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <windows.h>
#include "Admin.h"
#include "Utils.h"

typedef struct {
    char password[50];
    char fullName[100];
    char cccd[20];
    char birthYear[10];
    char gender[16];
    char hometown[100];
    char phone[20];
} AccountProfile;

// Xóa ký tự xuống dòng và CRLF ở cuối chuỗi
static void trimNewline(char *str) {
    if (str == NULL) return;
    size_t len = strlen(str);
    while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r')) {
        str[len - 1] = '\0';
        len--;
    }
}

// In ra chuỗi với độ rộng cố định để căn hàng đẹp
static void printPadded(const char *str, int width) {
    int chars = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0) - 1;
    if (chars < 0) chars = 0;
    printf("%s", str);
    for (int i = chars; i < width; i++) {
        printf(" ");
    }
}

// Lấy năm sinh và giới tính tự động từ số CCCD
static void deriveFieldsFromCCCD(const char *cccd, char *birthYear, size_t birthYearSize, char *gender, size_t genderSize) {
    if (birthYearSize > 0) birthYear[0] = '\0';
    if (genderSize > 0) gender[0] = '\0';

    if (cccd == NULL) {
        return;
    }

    size_t len = strlen(cccd);
    if (len >= 1) {
        char last = cccd[len - 1];
        if (isdigit((unsigned char)last)) {
            int digit = last - '0';
            if (digit % 2 == 0) {
                strncpy(gender, "Nữ", genderSize);
            } else {
                strncpy(gender, "Nam", genderSize);
            }
        }
    }

    if (len == 12) {
        char yearDigits[3] = {0};
        yearDigits[0] = cccd[6];
        yearDigits[1] = cccd[7];
        if (isdigit((unsigned char)yearDigits[0]) && isdigit((unsigned char)yearDigits[1])) {
            int year = (yearDigits[0] - '0') * 10 + (yearDigits[1] - '0');
            int currentYear = 2026;
            if (year <= currentYear % 100) {
                year += 2000;
            } else {
                year += 1900;
            }
            snprintf(birthYear, birthYearSize, "%d", year);
        }
    }
}

// Đọc toàn bộ thông tin tài khoản từ file vào cấu trúc profile
static int loadAccountProfile(const char *directory, const char *username, AccountProfile *profile) {
    if (directory == NULL || username == NULL || profile == NULL) {
        return 0;
    }

    char path[256];
    snprintf(path, sizeof(path), "%s/%s.txt", directory, username);
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        return 0;
    }

    profile->password[0] = '\0';
    profile->fullName[0] = '\0';
    profile->cccd[0] = '\0';
    profile->birthYear[0] = '\0';
    profile->gender[0] = '\0';
    profile->hometown[0] = '\0';
    profile->phone[0] = '\0';

    if (fgets(profile->password, sizeof(profile->password), f) == NULL) {
        fclose(f);
        return 0;
    }
    trimNewline(profile->password);
    fgets(profile->fullName, sizeof(profile->fullName), f);
    trimNewline(profile->fullName);
    fgets(profile->cccd, sizeof(profile->cccd), f);
    trimNewline(profile->cccd);
    fgets(profile->birthYear, sizeof(profile->birthYear), f);
    trimNewline(profile->birthYear);
    fgets(profile->gender, sizeof(profile->gender), f);
    trimNewline(profile->gender);
    fgets(profile->hometown, sizeof(profile->hometown), f);
    trimNewline(profile->hometown);
    fgets(profile->phone, sizeof(profile->phone), f);
    trimNewline(profile->phone);
    fclose(f);
    return 1;
}

// Lưu thông tin tài khoản từ cấu trúc profile vào file
static int saveAccountProfile(const char *directory, const char *username, const AccountProfile *profile) {
    if (directory == NULL || username == NULL || profile == NULL) {
        return 0;
    }

    char path[256];
    snprintf(path, sizeof(path), "%s/%s.txt", directory, username);
    FILE *f = fopen(path, "w");
    if (f == NULL) {
        return 0;
    }

    fprintf(f, "%s\n", profile->password);
    fprintf(f, "%s\n", profile->fullName);
    fprintf(f, "%s\n", profile->cccd);
    fprintf(f, "%s\n", profile->birthYear);
    fprintf(f, "%s\n", profile->gender);
    fprintf(f, "%s\n", profile->hometown);
    fprintf(f, "%s\n", profile->phone);
    fclose(f);
    return 1;
}

// Kiểm tra xem file tài khoản có tồn tại trong thư mục tương ứng không
static int accountExists(const char *directory, const char *username) {
    char path[256];
    snprintf(path, sizeof(path), "%s/%s.txt", directory, username);
    FILE *f = fopen(path, "r");
    if (f != NULL) {
        fclose(f);
        return 1;
    }
    return 0;
}

// Hiển thị menu chức năng admin cho người dùng
static void printAdminMenu() {
    printf("\n========== MENU ADMIN ==========");
    printf("\n1. Hiển thị thông tin admin");
    printf("\n2. Chỉnh sửa thông tin admin");
    printf("\n3. Tạo tài khoản quản lý");
    printf("\n4. Chỉnh sửa tài khoản quản lý");
    printf("\n5. Xóa tài khoản quản lý");
    printf("\n6. Xem danh sách quản lý");
    printf("\n7. Xem danh sách các phòng trống / có người ở");
    printf("\n8. Xem danh sách cư dân theo tầng");
    printf("\n9. Tìm cư dân");
    printf("\n10. Xem hóa đơn theo tháng");
    printf("\n0. Đăng xuất\n");
    printf("Chọn chức năng: ");
}

// Hiển thị thông tin chi tiết của admin đang đăng nhập
static void displayAdminInfo(const char *adminUsername) {
    AccountProfile profile;
    if (!loadAccountProfile("Data/Account/Admin", adminUsername, &profile)) {
        printf("\nKhông thể đọc thông tin Admin.\n");
        return;
    }

    printf("\n========== THÔNG TIN ADMIN ==========");
    printf("\nTên đăng nhập: %s", adminUsername);
    printf("\nTên: %s", profile.fullName[0] ? profile.fullName : "(chưa có)");
    printf("\nCCCD: %s", profile.cccd[0] ? profile.cccd : "(chưa có)");
    printf("\nNăm sinh: %s", profile.birthYear[0] ? profile.birthYear : "(chưa có)");
    printf("\nGiới tính: %s", profile.gender[0] ? profile.gender : "(chưa có)");
    printf("\nQuê quán: %s", profile.hometown[0] ? profile.hometown : "(chưa có)");
    printf("\nSố điện thoại: %s\n", profile.phone[0] ? profile.phone : "(chưa có)");
}

// Cho phép admin chỉnh sửa thông tin cá nhân và mật khẩu
static void editAdminAccount(char *adminUsername) {
    AccountProfile profile;
    if (!loadAccountProfile("Data/Account/Admin", adminUsername, &profile)) {
        printf("\nKhông thể tải thông tin Admin để chỉnh sửa.\n");
        return;
    }

    int choice = -1;
    char input[128];

    do {
        printf("\n========== CHỈNH SỬA ADMIN ==========");
        printf("\n1. Thay đổi tên tài khoản");
        printf("\n2. Thay đổi tên thật");
        printf("\n3. Thay đổi mật khẩu");
        printf("\n4. Sửa tất cả thông tin cá nhân");
        printf("\n0. Quay lại\n");
        printf("Chọn chức năng: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = -1;
        }
        getchar();

        switch (choice) {
            case 1:
                printf("Nhập tên tài khoản mới: ");
                fgets(input, sizeof(input), stdin);
                trimNewline(input);
                if (strlen(input) == 0) {
                    printf("Tên tài khoản không được để trống.\n");
                    break;
                }
                if (accountExists("Data/Account/Admin", input)) {
                    printf("Tên tài khoản đã tồn tại.\n");
                    break;
                }
                {
                    char oldPath[256];
                    char newPath[256];
                    snprintf(oldPath, sizeof(oldPath), "Data/Account/Admin/%s.txt", adminUsername);
                    snprintf(newPath, sizeof(newPath), "Data/Account/Admin/%s.txt", input);
                    if (rename(oldPath, newPath) == 0) {
                        strcpy(adminUsername, input);
                        printf("Đã đổi tên tài khoản thành công.\n");
                    } else {
                        printf("Không thể đổi tên tài khoản.\n");
                    }
                }
                break;
            case 2:
                printf("Nhập tên thật mới: ");
                fgets(profile.fullName, sizeof(profile.fullName), stdin);
                trimNewline(profile.fullName);
                if (saveAccountProfile("Data/Account/Admin", adminUsername, &profile)) {
                    printf("Đã cập nhật tên thật.\n");
                } else {
                    printf("Lưu thất bại.\n");
                }
                break;
            case 3:
                printf("Nhập mật khẩu mới: ");
                fgets(profile.password, sizeof(profile.password), stdin);
                trimNewline(profile.password);
                if (saveAccountProfile("Data/Account/Admin", adminUsername, &profile)) {
                    printf("Đã đổi mật khẩu.\n");
                } else {
                    printf("Lưu thất bại.\n");
                }
                break;
            case 4:
                printf("Nhập họ và tên: ");
                fgets(profile.fullName, sizeof(profile.fullName), stdin);
                trimNewline(profile.fullName);
                printf("Nhập CCCD: ");
                fgets(profile.cccd, sizeof(profile.cccd), stdin);
                trimNewline(profile.cccd);
                deriveFieldsFromCCCD(profile.cccd, profile.birthYear, sizeof(profile.birthYear), profile.gender, sizeof(profile.gender));
                printf("Nhập quê quán: ");
                fgets(profile.hometown, sizeof(profile.hometown), stdin);
                trimNewline(profile.hometown);
                printf("Nhập số điện thoại: ");
                fgets(profile.phone, sizeof(profile.phone), stdin);
                trimNewline(profile.phone);
                if (saveAccountProfile("Data/Account/Admin", adminUsername, &profile)) {
                    printf("Đã cập nhật thông tin Admin.\n");
                } else {
                    printf("Lưu thất bại.\n");
                }
                break;
            case 0:
                break;
            default:
                printf("Lựa chọn không hợp lệ.\n");
                break;
        }
    } while (choice != 0);
}

// Tạo một tài khoản quản lý mới và lưu vào thư mục Manage
static void createManagerAccount() {
    AccountProfile profile;
    char username[64];

    printf("\n========== TẠO TÀI KHOẢN QUẢN LÝ ==========");
    printf("\nNhập tên tài khoản quản lý: ");
    fgets(username, sizeof(username), stdin);
    trimNewline(username);
    if (strlen(username) == 0) {
        printf("Tên tài khoản không được để trống.\n");
        return;
    }
    if (accountExists("Data/Account/Manage", username)) {
        printf("Tài khoản quản lý đã tồn tại.\n");
        return;
    }

    printf("Nhập mật khẩu: ");
    fgets(profile.password, sizeof(profile.password), stdin);
    trimNewline(profile.password);
    printf("Nhập tên thật quản lý: ");
    fgets(profile.fullName, sizeof(profile.fullName), stdin);
    trimNewline(profile.fullName);
    printf("Nhập CCCD: ");
    fgets(profile.cccd, sizeof(profile.cccd), stdin);
    trimNewline(profile.cccd);
    deriveFieldsFromCCCD(profile.cccd, profile.birthYear, sizeof(profile.birthYear), profile.gender, sizeof(profile.gender));
    printf("Nhập số điện thoại: ");
    fgets(profile.phone, sizeof(profile.phone), stdin);
    trimNewline(profile.phone);
    strncpy(profile.hometown, "(chưa có)", sizeof(profile.hometown));

    if (saveAccountProfile("Data/Account/Manage", username, &profile)) {
        printf("Đã tạo tài khoản quản lý thành công.\n");
    } else {
        printf("Tạo tài khoản quản lý thất bại.\n");
    }
}

static void editManagerAccount() {
    AccountProfile profile;
    char username[64];
    char input[128];
    int choice = -1;

    printf("\n========== CHỈNH SỬA TÀI KHOẢN QUẢN LÝ ==========");
    printf("\nNhập tên tài khoản quản lý cần chỉnh sửa: ");
    fgets(username, sizeof(username), stdin);
    trimNewline(username);
    if (!loadAccountProfile("Data/Account/Manage", username, &profile)) {
        printf("Không tìm thấy tài khoản quản lý.\n");
        return;
    }

    do {
        printf("\n1. Thay đổi tên tài khoản");
        printf("\n2. Thay đổi tên thật");
        printf("\n3. Thay đổi CCCD");
        printf("\n4. Thay đổi số điện thoại");
        printf("\n0. Quay lại\n");
        printf("Chọn: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = -1;
        }
        getchar();

        switch (choice) {
            case 1:
                printf("Tên tài khoản mới: ");
                fgets(input, sizeof(input), stdin);
                trimNewline(input);
                if (strlen(input) == 0) {
                    printf("Tên tài khoản không được để trống.\n");
                    break;
                }
                if (accountExists("Data/Account/Manage", input)) {
                    printf("Tên tài khoản đã tồn tại.\n");
                    break;
                }
                {
                    char oldPath[256];
                    char newPath[256];
                    snprintf(oldPath, sizeof(oldPath), "Data/Account/Manage/%s.txt", username);
                    snprintf(newPath, sizeof(newPath), "Data/Account/Manage/%s.txt", input);
                    if (rename(oldPath, newPath) == 0) {
                        strcpy(username, input);
                        printf("Đổi tên tài khoản quản lý thành công.\n");
                    } else {
                        printf("Không thể đổi tên tài khoản quản lý.\n");
                    }
                }
                break;
            case 2:
                printf("Tên thật mới: ");
                fgets(profile.fullName, sizeof(profile.fullName), stdin);
                trimNewline(profile.fullName);
                if (saveAccountProfile("Data/Account/Manage", username, &profile)) {
                    printf("Đã cập nhật tên thật.\n");
                }
                break;
            case 3:
                printf("CCCD mới: ");
                fgets(profile.cccd, sizeof(profile.cccd), stdin);
                trimNewline(profile.cccd);
                deriveFieldsFromCCCD(profile.cccd, profile.birthYear, sizeof(profile.birthYear), profile.gender, sizeof(profile.gender));
                if (saveAccountProfile("Data/Account/Manage", username, &profile)) {
                    printf("Đã cập nhật CCCD và tự động thay đổi năm sinh/giới tính.\n");
                }
                break;
            case 4:
                printf("Số điện thoại mới: ");
                fgets(profile.phone, sizeof(profile.phone), stdin);
                trimNewline(profile.phone);
                if (saveAccountProfile("Data/Account/Manage", username, &profile)) {
                    printf("Đã cập nhật số điện thoại.\n");
                }
                break;
            case 0:
                break;
            default:
                printf("Lựa chọn không hợp lệ.\n");
                break;
        }
    } while (choice != 0);
}

// Xóa một tài khoản quản lý sau khi xác nhận với người dùng
static void deleteManagerAccount() {
    char username[64];
    char confirm[10];

    printf("\n========== XÓA TÀI KHOẢN QUẢN LÝ ==========");
    printf("\nNhập tên tài khoản quản lý cần xóa: ");
    fgets(username, sizeof(username), stdin);
    trimNewline(username);
    if (!accountExists("Data/Account/Manage", username)) {
        printf("Tài khoản quản lý không tồn tại.\n");
        return;
    }

    printf("Bạn có chắc chắn muốn xóa tài khoản '%s'? (y/N): ", username);
    fgets(confirm, sizeof(confirm), stdin);
    trimNewline(confirm);
    if (strcmp(confirm, "y") != 0 && strcmp(confirm, "Y") != 0) {
        printf("Đã hủy xóa.\n");
        return;
    }

    char path[256];
    snprintf(path, sizeof(path), "Data/Account/Manage/%s.txt", username);
    if (remove(path) == 0) {
        printf("Đã xóa tài khoản quản lý '%s'.\n", username);
    } else {
        printf("Xóa tài khoản thất bại.\n");
    }
}

// Liệt kê tất cả tài khoản quản lý hiện có và thông tin cơ bản
static void listManagerAccounts() {
    DIR *dir = opendir("Data/Account/Manage");
    if (dir == NULL) {
        printf("\nKhông thể mở thư mục tài khoản quản lý. Vui lòng kiểm tra đường dẫn.\n");
        return;
    }

    printf("\n===== DANH SÁCH QUẢN LÝ =====\n");
    struct dirent *entry;
    int count = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') {
            continue;
        }
        const char *ext = strrchr(entry->d_name, '.');
        if (ext == NULL || strcmp(ext, ".txt") != 0) {
            continue;
        }

        char username[64];
        size_t len = ext - entry->d_name;
        if (len >= sizeof(username)) {
            len = sizeof(username) - 1;
        }
        strncpy(username, entry->d_name, len);
        username[len] = '\0';

        AccountProfile profile;
        if (!loadAccountProfile("Data/Account/Manage", username, &profile)) {
            continue;
        }

        printf("\nQuản lý %d:\n", ++count);
        printf("- Tên đăng nhập: %s\n", username);
        printf("- Tên thật: %s\n", profile.fullName[0] ? profile.fullName : "(chưa có)");
        printf("- CCCD: %s\n", profile.cccd[0] ? profile.cccd : "(chưa có)");
        printf("- Giới tính: %s\n", profile.gender[0] ? profile.gender : "(chưa có)");
        printf("- Năm sinh: %s\n", profile.birthYear[0] ? profile.birthYear : "(chưa có)");
    }

    if (count == 0) {
        printf("Chưa có tài khoản quản lý nào.\n");
    }
    closedir(dir);
}

// Hiển thị phòng trống và phòng đã có người ở theo tầng nhập vào
static void listRoomsByOccupancy() {
    char floorInput[10];
    printf("\n========== PHÒNG TRỐNG / PHÒNG CÓ NGƯỜI Ở ==========");
    printf("\nNhập tầng muốn xem: ");
    fgets(floorInput, sizeof(floorInput), stdin);
    trimNewline(floorInput);

    char occupied[512] = "";
    char emptyRooms[512] = "";
    int roomCount = 0;

    for (int room = 1; room <= 5; room++) {
        char roomDir[256];
        char roomName[16];
        snprintf(roomName, sizeof(roomName), "%s%02d", floorInput, room);
        snprintf(roomDir, sizeof(roomDir), "FloorList/Floor%s/P%s", floorInput, roomName);

        DIR *dir = opendir(roomDir);
        if (dir == NULL) {
            continue;
        }

        struct dirent *entry;
        int hasResident = 0;
        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }
            hasResident = 1;
            break;
        }
        closedir(dir);

        if (hasResident) {
            if (strlen(occupied) > 0) {
                strncat(occupied, ", ", sizeof(occupied) - strlen(occupied) - 1);
            }
            strncat(occupied, roomName, sizeof(occupied) - strlen(occupied) - 1);
        } else {
            if (strlen(emptyRooms) > 0) {
                strncat(emptyRooms, ", ", sizeof(emptyRooms) - strlen(emptyRooms) - 1);
            }
            strncat(emptyRooms, roomName, sizeof(emptyRooms) - strlen(emptyRooms) - 1);
        }
        roomCount++;
    }

    if (roomCount == 0) {
        printf("Không tìm thấy tầng %s hoặc tầng không tồn tại.\n", floorInput);
        return;
    }

    printf("\nPhòng có người ở: %s\n", occupied[0] ? occupied : "Không có phòng nào có người ở");
    printf("Phòng trống: %s\n", emptyRooms[0] ? emptyRooms : "Không có phòng trống");
}

// Hiển thị danh sách cư dân theo từng phòng trong tầng nhập vào
static void displayRoomOccupantsByFloor() {
    char input_floor[10];
    char room_dir_path[256];
    char file_path[256];
    char room_name[10];
    struct dirent *entry;

    printf("\n================ XEM DANH SÁCH CÁC PHÒNG ================\n");
    printf("-> Chọn tầng muốn hiển thị danh sách phòng: ");
    fgets(input_floor, sizeof(input_floor), stdin);
    trimNewline(input_floor);

    printf("\nTầng %s\n", input_floor);
    printf("+---------+---------------------------+-----------------+------------+------------+-----------------+\n");
    printf("| "); printPadded("Phòng", 7);
    printf(" | "); printPadded("Họ và tên", 25);
    printf(" | "); printPadded("CCCD", 15);
    printf(" | "); printPadded("Năm sinh", 10);
    printf(" | "); printPadded("Giới tính", 10);
    printf(" | "); printPadded("Số điện thoại", 15);
    printf(" |\n");
    printf("+---------+---------------------------+-----------------+------------+------------+-----------------+\n");

    int printedAny = 0;
    for (int room = 1; room <= 5; room++) {
        snprintf(room_dir_path, sizeof(room_dir_path), "FloorList/Floor%s/P%s%02d", input_floor, input_floor, room);
        DIR *dir = opendir(room_dir_path);
        if (dir == NULL) {
            continue;
        }

        int firstPrinted = 0;
        snprintf(room_name, sizeof(room_name), "%s%02d", input_floor, room);

        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }

            snprintf(file_path, sizeof(file_path), "%s/%s", room_dir_path, entry->d_name);
            FILE *fp = fopen(file_path, "r");
            if (fp == NULL) {
                continue;
            }

            char password[100] = "";
            char fullName[100] = "";
            char cccd[50] = "";
            char year[20] = "";
            char gender[20] = "";
            char province[100] = "";
            char phone[50] = "";

            fgets(password, sizeof(password), fp);
            fgets(fullName, sizeof(fullName), fp);
            fgets(cccd, sizeof(cccd), fp);
            fgets(year, sizeof(year), fp);
            fgets(gender, sizeof(gender), fp);
            fgets(province, sizeof(province), fp);
            fgets(phone, sizeof(phone), fp);
            trimNewline(fullName);
            trimNewline(cccd);
            trimNewline(year);
            trimNewline(gender);
            trimNewline(province);
            trimNewline(phone);
            fclose(fp);

            if (strlen(phone) == 0) {
                strcpy(phone, "Không có");
            }

            if (!firstPrinted) {
                printf("| "); printPadded(room_name, 7);
                printf(" | "); printPadded(fullName, 25);
                printf(" | "); printPadded(cccd, 15);
                printf(" | "); printPadded(year, 10);
                printf(" | "); printPadded(gender, 10);
                printf(" | "); printPadded(phone, 15);
                printf(" |\n");
                firstPrinted = 1;
            } else {
                printf("| "); printPadded("", 7);
                printf(" | "); printPadded(fullName, 25);
                printf(" | "); printPadded(cccd, 15);
                printf(" | "); printPadded(year, 10);
                printf(" | "); printPadded(gender, 10);
                printf(" | "); printPadded(phone, 15);
                printf(" |\n");
            }
            printedAny = 1;
        }
        closedir(dir);
        if (firstPrinted) {
            printf("+---------+---------------------------+-----------------+------------+------------+-----------------+\n");
        }
    }

    if (!printedAny) {
        printf("Không tìm thấy phòng nào có cư dân trên tầng %s.\n", input_floor);
    }
}

// Tìm cư dân theo CCCD hoặc họ tên trong toàn bộ FloorList
static void searchResident() {
    char choice[10];
    char input_search[128];
    int found = 0;

    printf("\n================ TÌM KIẾM CƯ DÂN ================\n");
    printf("1. Tìm kiếm bằng số CCCD\n");
    printf("2. Tìm kiếm bằng Họ và tên\n");
    printf("-> Nhập lựa chọn của bạn (1 hoặc 2): ");
    fgets(choice, sizeof(choice), stdin);
    trimNewline(choice);

    if (strcmp(choice, "1") == 0) {
        printf("-> Nhập số CCCD cần tìm: ");
        fgets(input_search, sizeof(input_search), stdin);
        trimNewline(input_search);
    } else if (strcmp(choice, "2") == 0) {
        printf("-> Nhập Họ và tên cần tìm: ");
        fgets(input_search, sizeof(input_search), stdin);
        trimNewline(input_search);
        for (size_t i = 0; i < strlen(input_search); ++i) {
            input_search[i] = (char)tolower((unsigned char)input_search[i]);
        }
    } else {
        printf("[Lỗi]. Lựa chọn không hợp lệ!\n");
        return;
    }

    DIR *dir_floorlist = opendir("FloorList");
    if (dir_floorlist == NULL) {
        printf("[Lỗi]. Thư mục FloorList không tồn tại trên hệ thống!\n");
        return;
    }

    struct dirent *ent_floorlist;
    while ((ent_floorlist = readdir(dir_floorlist)) != NULL) {
        if (strcmp(ent_floorlist->d_name, ".") == 0 || strcmp(ent_floorlist->d_name, "..") == 0) {
            continue;
        }

        char path_floor[512];
        snprintf(path_floor, sizeof(path_floor), "FloorList/%s", ent_floorlist->d_name);
        DIR *dir_floor = opendir(path_floor);
        if (dir_floor == NULL) continue;

        struct dirent *ent_floor;
        while ((ent_floor = readdir(dir_floor)) != NULL) {
            if (strcmp(ent_floor->d_name, ".") == 0 || strcmp(ent_floor->d_name, "..") == 0) {
                continue;
            }

            char path_room[512];
            snprintf(path_room, sizeof(path_room), "%s/%s", path_floor, ent_floor->d_name);
            DIR *dir_room = opendir(path_room);
            if (dir_room == NULL) continue;

            struct dirent *ent_room;
            while ((ent_room = readdir(dir_room)) != NULL) {
                if (strcmp(ent_room->d_name, ".") == 0 || strcmp(ent_room->d_name, "..") == 0) {
                    continue;
                }

                char path_file[512];
                snprintf(path_file, sizeof(path_file), "%s/%s", path_room, ent_room->d_name);
                FILE *fp = fopen(path_file, "r");
                if (fp == NULL) {
                    continue;
                }

                char password[100] = "";
                char fullName[100] = "";
                char cccd[50] = "";
                fgets(password, sizeof(password), fp);
                fgets(fullName, sizeof(fullName), fp);
                fgets(cccd, sizeof(cccd), fp);
                trimNewline(fullName);
                trimNewline(cccd);
                fclose(fp);

                if (strcmp(choice, "1") == 0) {
                    char search_cccd[50];
                    strncpy(search_cccd, ent_room->d_name, sizeof(search_cccd) - 1);
                    search_cccd[sizeof(search_cccd) - 1] = '\0';
                    char *dot = strrchr(search_cccd, '.');
                    if (dot) *dot = '\0';

                    if (strcmp(input_search, search_cccd) == 0) {
                        printf("\n[Tìm thấy]. Cư dân: %s\n", fullName);
                        printf("-> Vị trí: %s/%s\n", ent_floor->d_name, ent_room->d_name);
                        found = 1;
                        closedir(dir_room);
                        break;
                    }
                } else {
                    char lower_name[100];
                    strncpy(lower_name, fullName, sizeof(lower_name) - 1);
                    lower_name[sizeof(lower_name) - 1] = '\0';
                    for (size_t i = 0; i < strlen(lower_name); ++i) {
                        lower_name[i] = (char)tolower((unsigned char)lower_name[i]);
                    }
                    if (strcmp(lower_name, input_search) == 0) {
                        printf("\n[Tìm thấy]. Cư dân: %s (CCCD: %s)\n", fullName, cccd);
                        printf("-> Vị trí: %s/%s\n", ent_floor->d_name, ent_room->d_name);
                        found = 1;
                    }
                }
            }
            closedir(dir_room);
            if (found && strcmp(choice, "1") == 0) break;
        }
        closedir(dir_floor);
        if (found && strcmp(choice, "1") == 0) break;
    }
    closedir(dir_floorlist);

    if (!found) {
        printf("\n[Kết quả]. Không tìm thấy cư dân nào khớp với thông tin đã nhập trên hệ thống!\n");
    }
}

// Hiển thị danh sách hóa đơn theo tháng cho một tầng cụ thể
static void displayFloorBillsByMonth() {
    char input_tang[10];
    char input_thang[10];
    char input_nam[10];
    char file_name[32];
    char path_file[512];
    char room_name[10];
    int has_any_bill = 0;

    char border[] = "+---------+-------------------+-----------+--------------------+-----------+--------------------+--------------------+";

    printf("\n================ XEM HÓA ĐƠN THEO TẦNG ================\n");
    printf("-> Nhập tầng muốn xem: ");
    fgets(input_tang, sizeof(input_tang), stdin);
    trimNewline(input_tang);
    printf("-> Nhập tháng: ");
    fgets(input_thang, sizeof(input_thang), stdin);
    trimNewline(input_thang);
    printf("-> Nhập năm: ");
    fgets(input_nam, sizeof(input_nam), stdin);
    trimNewline(input_nam);

    sprintf(file_name, "%02d%04d.txt", atoi(input_thang), atoi(input_nam));

    printf("\nTầng %s:\n", input_tang);
    printf("%s\n", border);
    printf("| "); printPadded("Phòng", 7);
    printf(" | "); printPadded("Tiền phòng(VNĐ)", 17);
    printf(" | "); printPadded("Số điện", 9);
    printf(" | "); printPadded("Tiền điện(VNĐ)", 18);
    printf(" | "); printPadded("Số nước", 9);
    printf(" | "); printPadded("Tiền nước(VNĐ)", 18);
    printf(" | "); printPadded("Tổng hóa đơn(VNĐ)", 18);
    printf(" |\n");
    printf("%s\n", border);

    for (int p = 1; p <= 5; p++) {
        sprintf(room_name, "%s%02d", input_tang, p);
        sprintf(path_file, "Data/Bill/Floor%s/P%s/%s", input_tang, room_name, file_name);

        FILE *f = fopen(path_file, "r");
        if (f == NULL) {
            continue;
        }

        float roomPrice = 0;
        float electricityNumber = 0;
        float electricityPrice = 0;
        float waterNumber = 0;
        float waterPrice = 0;

        fscanf(f, "%f", &roomPrice);
        fscanf(f, "%f", &electricityNumber);
        fscanf(f, "%f", &electricityPrice);
        fscanf(f, "%f", &waterNumber);
        fscanf(f, "%f", &waterPrice);
        fclose(f);

        float totalBill = roomPrice + electricityPrice + waterPrice;
        has_any_bill = 1;

        char str_roomPrice[32];
        char str_electricityNumber[32];
        char str_electricityPrice[32];
        char str_waterNumber[32];
        char str_waterPrice[32];
        char str_totalBill[32];

        sprintf(str_roomPrice, "%.0f", roomPrice);
        sprintf(str_electricityNumber, "%.0f", electricityNumber);
        sprintf(str_electricityPrice, "%.0f", electricityPrice);
        sprintf(str_waterNumber, "%.0f", waterNumber);
        sprintf(str_waterPrice, "%.0f", waterPrice);
        sprintf(str_totalBill, "%.0f", totalBill);

        printf("| "); printPadded(room_name, 7);
        printf(" | "); printPadded(str_roomPrice, 17);
        printf(" | "); printPadded(str_electricityNumber, 9);
        printf(" | "); printPadded(str_electricityPrice, 18);
        printf(" | "); printPadded(str_waterNumber, 9);
        printf(" | "); printPadded(str_waterPrice, 18);
        printf(" | "); printPadded(str_totalBill, 18);
        printf(" |\n");
        printf("%s\n", border);
    }

    if (has_any_bill == 0) {
        printf("       Không có hóa đơn nào trong tháng %02d/%04d tại tầng này.\n", atoi(input_thang), atoi(input_nam));
    }
}

// Hàm điều khiển menu chính của admin và chuyển hướng tới chức năng tương ứng
void adminMenu(const char *adminUsername) {
    if (adminUsername == NULL) {
        return;
    }

    char currentAdmin[64];
    strncpy(currentAdmin, adminUsername, sizeof(currentAdmin) - 1);
    currentAdmin[sizeof(currentAdmin) - 1] = '\0';

    int choice = -1;

    do {
        printAdminMenu();
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = -1;
        }
        getchar();

        switch (choice) {
            case 1:
                displayAdminInfo(currentAdmin);
                break;
            case 2:
                editAdminAccount(currentAdmin);
                break;
            case 3:
                createManagerAccount();
                break;
            case 4:
                editManagerAccount();
                break;
            case 5:
                deleteManagerAccount();
                break;
            case 6:
                listManagerAccounts();
                break;
            case 7:
                listRoomsByOccupancy();
                break;
            case 8:
                displayRoomOccupantsByFloor();
                break;
            case 9:
                searchResident();
                break;
            case 10:
                displayFloorBillsByMonth();
                break;
            case 0:
                printf("\nĐã đăng xuất khỏi Admin.\n");
                break;
            default:
                printf("\nLựa chọn không hợp lệ, hãy thử lại.\n");
                break;
        }
        if (choice != 0) {
            printf("\nNhấn Enter để tiếp tục...");
            getchar();
        }
    } while (choice != 0);
}
