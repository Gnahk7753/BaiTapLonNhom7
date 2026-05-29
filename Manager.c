//Thư viện sử dụng
#include <stdio.h>      
#include <string.h>     
#include <ctype.h>      
#include <stdlib.h>     
#include <dirent.h>     
#include <direct.h>     
#include <windows.h>  

//Định nghĩa cấu trúc cư dân
typedef struct {
    char fullName[64];
    char cccd[20];
    char birthYear[10];
    char gender[10];
    char hometown[64];
    char phone[15];
} Manager;

Manager manager;
char currentPassword[32], currentAccountPath[256];

// Thiết lập tiếng Việt cho Console
void setupVietnamese() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
}

// Xóa ký tự xuống dòng '\n' do fgets tạo ra
void trimNewline(char *str) {
    str[strcspn(str, "\r\n")] = '\0';
}

// Hàm lưu dữ liệu vào file 
int saveManagerData() {
    FILE *file = fopen(currentAccountPath, "w");
    if (file == NULL) {
        printf("\nKhông mở được file để ghi dữ liệu!\n");
        return 0;
    }
    fprintf(file, "%s\n", currentPassword);
    fprintf(file, "%s\n", manager.fullName);
    fprintf(file, "%s\n", manager.cccd);
    fprintf(file, "%s\n", manager.birthYear);
    fprintf(file, "%s\n", manager.gender);
    fprintf(file, "%s\n", manager.hometown);
    fprintf(file, "%s\n", manager.phone);
    fclose(file);
    return 1;
}

// Đăng nhập hệ thống
int login() {
    char username[32], password[32], path[256], filePassword[32];
    FILE *file;

    printf("=============== ĐĂNG NHẬP ===============\n");
    printf("Nhập tên tài khoản: ");
    fgets(username, sizeof(username), stdin);
    trimNewline(username);

    sprintf(path, "Data/Account/Manage/%s.txt", username);
    file = fopen(path, "r");
    if (file == NULL) {
        printf("\nKhông tìm thấy tài khoản!\n");
        return 0;
    }

    // Đọc mật khẩu từ file
    fgets(filePassword, sizeof(filePassword), file);
    trimNewline(filePassword);

	// Kiểm tra mật khẩu, sai thì nhập lại
	do {
        printf("Nhập mật khẩu: ");
        fgets(password, sizeof(password), stdin);
        trimNewline(password);

        if (strcmp(password, filePassword) != 0) {
            printf("=> Sai mật khẩu! Vui lòng thử lại.\n\n");
        }
    } while (strcmp(password, filePassword) != 0);
    
    // Lưu thông tin trạng thái đăng nhập toàn cục
    strcpy(currentPassword, password);
    strcpy(currentAccountPath, path);

    // Đọc toàn bộ thông tin quản lý còn lại
    fgets(manager.fullName, sizeof(manager.fullName), file);
    fgets(manager.cccd, sizeof(manager.cccd), file);
    fgets(manager.birthYear, sizeof(manager.birthYear), file);
    fgets(manager.gender, sizeof(manager.gender), file);
    fgets(manager.hometown, sizeof(manager.hometown), file);
    fgets(manager.phone, sizeof(manager.phone), file);

    // Xóa ký tự xuống dòng hàng loạt
    trimNewline(manager.fullName);
    trimNewline(manager.cccd);
    trimNewline(manager.birthYear);
    trimNewline(manager.gender);
    trimNewline(manager.hometown);
    trimNewline(manager.phone);

    fclose(file);
    printf("\nĐăng nhập thành công!\n");
    return 1;
}

// Hiển thị thông tin quản lý
void showManagerInfo() {
    printf("\n========== THÔNG TIN QUẢN LÝ ==========\n");
    printf("Họ tên        : %s\n", manager.fullName);
    printf("CCCD          : %s\n", manager.cccd);
    printf("Năm sinh      : %s\n", manager.birthYear);
    printf("Giới tính     : %s\n", manager.gender);
    printf("Quê quán      : %s\n", manager.hometown);
    printf("Số điện thoại : %s\n", manager.phone);
}

// Chỉnh sửa tài khoản quản lý
void editManagerAccount() {
    int choice;
    char oldPassword[32], newPassword[32], newPhone[12];

    printf("\n========== CHỈNH SỬA TÀI KHOẢN ==========\n");
    printf("1. Thay đổi số điện thoại\n");
    printf("2. Thay đổi mật khẩu\n");
    printf("3. Thay đổi thông tin khác\n");
    printf("\nNhập lựa chọn: ");
    
    if (scanf("%d", &choice) != 1) {
        while (getchar() != '\n'); // Xóa bộ nhớ đệm nếu nhập chữ
        printf("\nLựa chọn không hợp lệ!\n");
        return;
    }
    getchar(); // Xóa ký tự thừa

    switch(choice) {
        case 1:
            printf("\nNhập số điện thoại mới: ");
            fgets(newPhone, sizeof(newPhone), stdin);
            trimNewline(newPhone);

            strcpy(manager.phone, newPhone);
            if (saveManagerData()) {
                printf("\nĐổi số điện thoại thành công!\n");
            }
            break;

        case 2:
            printf("\nNhập mật khẩu cũ: ");
            fgets(oldPassword, sizeof(oldPassword), stdin);
            trimNewline(oldPassword);

            if (strcmp(oldPassword, currentPassword) != 0) {
                printf("\nMật khẩu cũ không đúng!\n");
                return;
            }

            printf("Nhập mật khẩu mới: ");
            fgets(newPassword, sizeof(newPassword), stdin);
            trimNewline(newPassword);

            strcpy(currentPassword, newPassword);
            if (saveManagerData()) {
                printf("\nĐổi mật khẩu thành công!\n");
            }
            break;

        case 3:
            printf("\nVui lòng báo với admin để được hỗ trợ.\n");
            break;

        default:
            printf("\nLựa chọn không hợp lệ!\n");
    }
}

// Định nghĩa struct
typedef struct {
    char username[64];
    char password[64];
    char fullName[64];
    char cccd[32];     
    char phone[20];
    char year[10];
    char gender[10];
    char province[64];
} ResidentAccount;

// CÁC HÀM KIỂM TRA CCCD

// Kiểm tra toàn số
int isAllDigits(char *s) {
    for (int i = 0; s[i]; i++) {
        if (!isdigit((unsigned char)s[i])) return 0;
    }
    return 1;
}

// Kiểm tra mã tỉnh hợp lệ
int validProvince(int CCCD) {
    int provinces[] = {
        1, 2, 4, 6, 8, 10, 11, 12, 14, 15, 17, 19, 20, 22, 24, 25, 26, 27, 30,
        31, 33, 34, 35, 36, 37, 38, 40, 42, 44, 45, 46, 48, 49, 51, 52, 54, 56,
        58, 60, 62, 64, 66, 67, 68, 70, 72, 74, 75, 77, 79, 80, 82, 83, 84, 86,
        87, 89, 91, 92, 93, 94, 95, 96
    };
    int n = sizeof(provinces) / sizeof(provinces[0]);
    for (int i = 0; i < n; i++) {
        if (CCCD == provinces[i]) return 1;
    }
    return 0;
}

// Kiểm tra trùng CCCD (Đã sửa từ mảng [13] thành [20] để không bị kẹt dấu \n)
int checkDuplicates(char CCCD[]) {
    FILE *f = fopen("Data/cccd.txt", "r");
    if (f == NULL) {
        return 1; // Chưa có file dữ liệu thì coi như không trùng
    }
    char cccdInFile[20]; 
    while (fgets(cccdInFile, sizeof(cccdInFile), f) != NULL) {
        cccdInFile[strcspn(cccdInFile, "\r\n")] = '\0';
        if (strcmp(CCCD, cccdInFile) == 0) {
            fclose(f);
            return 0; // Trùng lặp!
        }
    }
    fclose(f);
    return 1; // Hợp lệ, không trùng
}

// Hàm cốt lõi kiểm tra CCCD và tự động bóc tách thông tin cá nhân
int checkCCCD(char year[], char province[], char CCCD[], char gender[]) {
    if (strlen(CCCD) != 12) {
        printf("[Lỗi] -> Nhập lại CCCD phải có đủ 12 số: ");
        return 0;
    }
    if (!isAllDigits(CCCD)) {
        printf("[Lỗi] -> Nhập lại CCCD chỉ toàn là số: ");
        return 0;
    }
    if (!checkDuplicates(CCCD)) {
        printf("[Lỗi] -> Nhập lại CCCD vì đã bị trùng với số đã có trong dữ liệu tổng: ");
        return 0;
    }

    int Province = (CCCD[0] - '0') * 100 + (CCCD[1] - '0') * 10 + (CCCD[2] - '0');
    if (!validProvince(Province)) {
        printf("[Lỗi] -> Mã tỉnh không hợp lệ. Nhập lại CCCD: ");
        return 0;
    }

    // Đọc quê quán từ file tỉnh thành của bạn
    char path[256];
    sprintf(path, "Data/Province/%03d.txt", Province);
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        strcpy(province, "Không tìm thấy quê quán");
    } else {
        fgets(province, 64, f);
        province[strcspn(province, "\r\n")] = '\0';
        fclose(f);
    }

    // Xác định giới tính
    int Gender = CCCD[3] - '0';
    if (Gender < 0 || Gender > 3) {
        printf("[Lỗi] -> Ký tự giới tính không hợp lệ. Nhập lại CCCD: ");
        return 0;
    }
    if (Gender % 2 == 0) strcpy(gender, "Nam");
    else strcpy(gender, "Nữ");

    // Xác định năm sinh
    int Year = (CCCD[4] - '0') * 10 + (CCCD[5] - '0');
    if (Gender == 0 || Gender == 1) sprintf(year, "19%02d", Year);
    if (Gender == 2 || Gender == 3) sprintf(year, "20%02d", Year);

    return 1;
}

// Chuẩn hóa viết hoa chữ cái đầu
void normalizeName(char name[]) {
    for (int i = 0; name[i]; i++)
        name[i] = tolower((unsigned char)name[i]);
    if (name[0] != '\0')
        name[0] = toupper((unsigned char)name[0]);
    for (int i = 1; name[i]; i++)
        if (name[i-1] == ' ' && name[i] != ' ')
            name[i] = toupper((unsigned char)name[i]);
}

// Hàm xóa một số CCCD khỏi file Data/cccd.txt để phục vụ sửa/xóa tài khoản
void removeCCCDFromFile(char cccd[]) {
    FILE *f = fopen("Data/cccd.txt", "r");
    if (f == NULL) return;

    FILE *temp = fopen("Data/cccd_temp.txt", "w");
    if (temp == NULL) {
        fclose(f);
        return;
    }

    char line[32];
    while (fgets(line, sizeof(line), f) != NULL) {
        line[strcspn(line, "\r\n")] = '\0';
        if (strcmp(line, cccd) != 0 && strlen(line) > 0) {
            fprintf(temp, "%s\n", line);
        }
    }
    fclose(f);
    fclose(temp);

    remove("Data/cccd.txt");               
    rename("Data/cccd_temp.txt", "Data/cccd.txt"); 
}
// Hàm kiểm tra CCCD dùng chung cho chức năng 3, 4, 5
void inputAndValidateCCCD(ResidentAccount *acc) {
    printf("-> Nhập số CCCD: ");
    while (1) {
        fgets(acc->cccd, sizeof(acc->cccd), stdin);
        acc->cccd[strcspn(acc->cccd, "\r\n")] = '\0';

        // Gọi hàm checkCCCD gốc để tự kiểm tra trùng lặp và tách thông tin
        if (checkCCCD(acc->year, acc->province, acc->cccd, acc->gender)) {
            break; // Khi hợp lệ thì tự động thoát vòng lặp
        }
    }
}

// Hàm ghi dữ liệu đồng bộ xuống dòng vào cả 2 file dùng chung cho chức năng 3, 4, 5
int saveResidentData(const char *username, const char *tang, const char *phong, ResidentAccount acc) {
    // 1. Ghi FILE tài khoản cư dân
    char path1[256];
    sprintf(path1, "Data/Account/Resident/%s.txt", username);
    FILE *f1 = fopen(path1, "w");
    if (f1 == NULL) return 0;
    
    fprintf(f1, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n", 
            acc.password, acc.fullName, acc.cccd, acc.year, acc.gender, acc.province, acc.phone);
    fclose(f1);

    // 2. Ghi FILE vị trí phòng ở cư dân
    char path2[256];
    sprintf(path2, "FloorList/Floor%s/P%s0%s/%s.txt", tang, tang, phong, acc.cccd);
    FILE *f2 = fopen(path2, "w");
    if (f2 == NULL) return 0;
    
    fprintf(f2, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n", 
            acc.password, acc.fullName, acc.cccd, acc.year, acc.gender, acc.province, acc.phone);
    fclose(f2);

    return 1; // Lưu thành công cả 2 file
}

// Hàm tạo tài khoản cư dân
void createResidentAccount() {
    ResidentAccount acc; 
    char tang[10], phong[10];

    printf("\n================ TẠO TÀI KHOẢN CƯ DÂN ================\n");
    printf("-> Nhập tên tài khoản: "); 
	fgets(acc.username, sizeof(acc.username), stdin); 
	acc.username[strcspn(acc.username, "\r\n")] = '\0';
    
	printf("-> Nhập mật khẩu: "); 
	fgets(acc.password, sizeof(acc.password), stdin); 
	acc.password[strcspn(acc.password, "\r\n")] = '\0';
    
	printf("-> Nhập họ và tên: "); 
	fgets(acc.fullName, sizeof(acc.fullName), stdin); 
	acc.fullName[strcspn(acc.fullName, "\r\n")] = '\0';
    normalizeName(acc.fullName); 
    
	printf("-> Nhập số điện thoại (Bấm Enter nếu bỏ qua): "); 
	fgets(acc.phone, sizeof(acc.phone), stdin); 
	acc.phone[strcspn(acc.phone, "\r\n")] = '\0';
    
	printf("-> Nhập tầng đang ở: "); 
	fgets(tang, sizeof(tang), stdin); 
	tang[strcspn(tang, "\r\n")] = '\0';
    
	printf("-> Nhập phòng đang ở: "); 
	fgets(phong, sizeof(phong), stdin); 
	phong[strcspn(phong, "\r\n")] = '\0';

    // Gọi hàm dùng chung để nhập và kiểm tra CCCD
    inputAndValidateCCCD(&acc);

    // Gọi hàm dùng chung để ghi đè 2 file cùng lúc
    if (!saveResidentData(acc.username, tang, phong, acc)) {
        printf("[Lỗi]. Không thể tạo các file lưu trữ dữ liệu cư dân!\n");
        return;
    }

    // Cập nhật CCCD mới vào file danh sách tổng
    FILE *f3 = fopen("Data/cccd.txt", "a");
    if (f3 != NULL) { fprintf(f3, "%s\n", acc.cccd); fclose(f3); }

    printf("\n[Thành công] Đã tạo tài khoản và phân phòng cư dân hoàn tất!\n");
}

// Hàm chỉnh sửa tài khoản cư dân
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h> // Bắt buộc phải có thư viện này để dùng DIR và opendir

// ====================================================================
// CHỨC NĂNG 4: CHỈNH SỬA TÀI KHOẢN CƯ DÂN (Đã thêm check thư mục phòng)
// ====================================================================
void editResidentAccount() {
    char old_tang[10], old_phong[10];
    char new_tang[10], new_phong[10];

    ResidentAccount old_acc;
    ResidentAccount new_acc;

    printf("\n================ CHỈNH SỬA TÀI KHOẢN CƯ DÂN ================\n");
    printf("-> Nhập TÊN TÀI KHOẢN cư dân muốn sửa: "); 
    fgets(old_acc.username, sizeof(old_acc.username), stdin); 
    old_acc.username[strcspn(old_acc.username, "\r\n")] = '\0';

    printf("-> Nhập TẦNG hiện tại của cư dân này: "); 
    fgets(old_tang, sizeof(old_tang), stdin); 
    old_tang[strcspn(old_tang, "\r\n")] = '\0';

    printf("-> Nhập PHÒNG hiện tại của cư dân này: "); 
    fgets(old_phong, sizeof(old_phong), stdin); 
    old_phong[strcspn(old_phong, "\r\n")] = '\0';

    // BƯỚC KIỂM TRA ĐƯỜNG DẪN PHÒNG CŨ CÓ TỒN TẠI KHÔNG
    char check_dir_path[256];
    sprintf(check_dir_path, "FloorList/Floor%s/P%s0%s", old_tang, old_tang, old_phong);
    
    DIR *dir = opendir(check_dir_path);
    if (dir == NULL) {
        printf("\n[Lỗi]. Thư mục phòng ở '%s' không tồn tại trên hệ thống!\n", check_dir_path);
        printf("Vui lòng kiểm tra lại số tầng và số phòng đã nhập.\n");
        return; // Thoát hàm luôn, không cho chạy tiếp xuống dưới
    }
    closedir(dir); // Mở được thì phải đóng lại để giải phóng bộ nhớ

    // Tạo đường dẫn tìm file tài khoản cũ
    char old_path1[256];
    sprintf(old_path1, "Data/Account/Resident/%s.txt", old_acc.username);
    FILE *f_read = fopen(old_path1, "r");
    if (f_read == NULL) {
        printf("\n[Lỗi]. Không tìm thấy file tài khoản cư dân '%s' trong hệ thống Data/Account/Resident/!\n", old_acc.username);
        return;
    }

    // Đọc TOÀN BỘ dữ liệu từ file cũ đổ vào struct old_acc
    fgets(old_acc.password, sizeof(old_acc.password), f_read);   
	old_acc.password[strcspn(old_acc.password, "\r\n")] = '\0';
    
	fgets(old_acc.fullName, sizeof(old_acc.fullName), f_read);   
	old_acc.fullName[strcspn(old_acc.fullName, "\r\n")] = '\0';
    
	fgets(old_acc.cccd, sizeof(old_acc.cccd), f_read);           
	old_acc.cccd[strcspn(old_acc.cccd, "\r\n")] = '\0';
    
	fgets(old_acc.year, sizeof(old_acc.year), f_read);           
	old_acc.year[strcspn(old_acc.year, "\r\n")] = '\0';
    
	fgets(old_acc.gender, sizeof(old_acc.gender), f_read);       
	old_acc.gender[strcspn(old_acc.gender, "\r\n")] = '\0';
    
	fgets(old_acc.province, sizeof(old_acc.province), f_read);   
	old_acc.province[strcspn(old_acc.province, "\r\n")] = '\0';
    
	fgets(old_acc.phone, sizeof(old_acc.phone), f_read);         
	old_acc.phone[strcspn(old_acc.phone, "\r\n")] = '\0';
    
	fclose(f_read);

    // Xác định đường dẫn file phòng ở cũ (dùng cấu trúc FloorList/Floor%s/P%s0%s/[số cccd].txt)
    char old_path2[256];
    sprintf(old_path2, "FloorList/Floor%s/P%s0%s/%s.txt", old_tang, old_tang, old_phong, old_acc.cccd);

    // Kiểm tra xem file .txt của cư dân đó có thực sự nằm trong phòng đó không
    FILE *f_check_res = fopen(old_path2, "r");
    if (f_check_res == NULL) {
        printf("\n[Lỗi]. Không tìm thấy file dữ liệu cư dân '%s.txt' tại phòng đã nhập!\n", old_acc.cccd);
        return;
    }
    fclose(f_check_res);

    // Tạm thời nhấc CCCD cũ ra khỏi danh sách tổng để phục vụ kiểm tra trùng lặp
    removeCCCDFromFile(old_acc.cccd);

    printf("\n--- NHẬP THÔNG TIN CHỈNH SỬA MỚI ---\n");
    printf("-> Nhập tên tài khoản MỚI: "); 
    fgets(new_acc.username, sizeof(new_acc.username), stdin); 
    new_acc.username[strcspn(new_acc.username, "\r\n")] = '\0';

    printf("-> Nhập họ và tên MỚI: "); 
    fgets(new_acc.fullName, sizeof(new_acc.fullName), stdin); 
    new_acc.fullName[strcspn(new_acc.fullName, "\r\n")] = '\0';
    normalizeName(new_acc.fullName); 

    // Nhập vị trí mới và tiến hành kiểm tra thư mục phòng mới luôn
    while (1) {
        printf("-> Nhập tầng MỚI: "); 
        fgets(new_tang, sizeof(new_tang), stdin); 
        new_tang[strcspn(new_tang, "\r\n")] = '\0';

        printf("-> Nhập phòng MỚI: "); 
        fgets(new_phong, sizeof(new_phong), stdin); 
        new_phong[strcspn(new_phong, "\r\n")] = '\0';

        // Check xem phòng mới nhập có tồn tại trên hệ thống để chuyển cư dân vào không
        char new_dir_path[256];
        sprintf(new_dir_path, "FloorList/Floor%s/P%s0%s", new_tang, new_tang, new_phong);
        
        DIR *dir_new = opendir(new_dir_path);
        if (dir_new != NULL) {
            closedir(dir_new);
            break; // Phòng mới hợp lệ thì thoát vòng lặp nhập phòng
        }
        printf("[Lỗi]. Phòng mới '%s' không tồn tại trên hệ thống! Vui lòng nhập lại.\n\n", new_dir_path);
    }

    // Tái sử dụng hàm dùng chung 1: Nhập và kiểm tra CCCD mới
    inputAndValidateCCCD(&new_acc);

    // Kế thừa dữ liệu cũ không sửa
    strcpy(new_acc.password, old_acc.password);
    strcpy(new_acc.phone, old_acc.phone);

    // Xóa bỏ hoàn toàn 2 file cũ sau khi mọi thông tin kiểm tra đã chắc chắn đúng
    remove(old_path1);
    remove(old_path2);

    // Tái sử dụng hàm dùng chung 2: Ghi dữ liệu mới vào hệ thống file mới
    if (!saveResidentData(new_acc.username, new_tang, new_phong, new_acc)) {
        printf("[Lỗi]. Không thể ghi đè hệ thống file mới!\n");
        FILE *f_back = fopen("Data/cccd.txt", "a");
        if (f_back != NULL) { fprintf(f_back, "%s\n", old_acc.cccd); fclose(f_back); }
        return;
    }

    // Cập nhật số CCCD mới vào danh sách tổng
    FILE *f3 = fopen("Data/cccd.txt", "a");
    if (f3 != NULL) { 
        fprintf(f3, "%s\n", new_acc.cccd); 
        fclose(f3); 
    }

    printf("\n[Thành công]. Toàn bộ thông tin cư dân và vị trí phòng ở đã được cập nhật!\n");
}

// Menu quản lý chính
void managerMenu() {
    int choice;
    do {
        system("cls");
        printf("\n=========================================\n");
        printf("               QUẢN LÝ\n");
        printf("=========================================\n");
        printf("1. Hiển thị thông tin quản lý\n");
        printf("2. Chỉnh sửa thông tin tài khoản quản lý\n");
        printf("3. Tạo tài khoản cho cư dân\n");
        printf("4. Chỉnh sửa thông tin tài khoản cư dân\n");
        printf("5. Xóa tài khoản cư dân\n");
        printf("6. Xem danh sách các phòng\n");
        printf("7. Tìm kiếm cư dân\n");
        printf("8. Nhập thông tin số điện, số nước\n");
        printf("9. Xem danh sách hóa đơn theo tháng\n");
        printf("0. Thoát\n");
        printf("=========================================\n");
        printf("Nhập lựa chọn: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // Chống vòng lặp vô hạn khi nhập chữ
            choice = -1; 
        } else {
            getchar(); // Xóa ký tự thừa
        }

        switch(choice) {
            case 1: 
				showManagerInfo(); 
				break;
            case 2: 
				editManagerAccount(); 
				break;
            case 3: 
            	createResidentAccount();
            	break;
			case 4: 
				editResidentAccount();
				break;
			case 5: case 6: case 7: case 8: case 9:
                printf("\nChưa code chức năng này.\n"); 
                break;
            case 0: printf("\nThoát chương trình.\n"); break;
            default: printf("\nLựa chọn không hợp lệ!\n");
        }
        if (choice != 0) {
            printf("\nNhấn Enter để tiếp tục...");
            getchar();
        }

    } while(choice != 0);
}

int main() {
    setupVietnamese();
    if (login()) {
        managerMenu();
    }
    return 0;
}