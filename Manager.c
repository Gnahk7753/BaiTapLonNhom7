//Thư viện sử dụng
#include <stdio.h>      
#include <string.h>     
#include <ctype.h>      
#include <stdlib.h>     
#include <dirent.h>     
#include <direct.h>     
#include <windows.h>  
#include <time.h>

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
        trimNewline(line);
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
    
    fprintf(f1, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n", acc.password, acc.fullName, acc.cccd, acc.year, acc.gender, acc.province, acc.phone);
    fclose(f1);

    // 2. Ghi FILE vị trí phòng ở cư dân
    char path2[256];
    sprintf(path2, "FloorList/Floor%s/P%s0%s/%s.txt", tang, tang, phong, acc.cccd);
    FILE *f2 = fopen(path2, "w");
    if (f2 == NULL) return 0;
    
    fprintf(f2, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n", acc.password, acc.fullName, acc.cccd, acc.year, acc.gender, acc.province, acc.phone);
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
	trimNewline(acc.username);
	
	printf("-> Nhập mật khẩu: "); 
	fgets(acc.password, sizeof(acc.password), stdin); 
	trimNewline(acc.password);
    
	printf("-> Nhập họ và tên: "); 
	fgets(acc.fullName, sizeof(acc.fullName), stdin); 
	trimNewline(acc.fullName);
    normalizeName(acc.fullName); 
    
	printf("-> Nhập số điện thoại (Bấm Enter nếu bỏ qua): "); 
	fgets(acc.phone, sizeof(acc.phone), stdin); 
	trimNewline(acc.phone);
    
	printf("-> Nhập tầng đang ở: "); 
	fgets(tang, sizeof(tang), stdin); 
	trimNewline(tang);
    
	printf("-> Nhập phòng đang ở: "); 
	fgets(phong, sizeof(phong), stdin); 
	trimNewline(phong);

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
void editResidentAccount() {
    char old_tang[10], old_phong[10];
    char new_tang[10], new_phong[10];

    ResidentAccount old_acc;
    ResidentAccount new_acc;

    printf("\n================ CHỈNH SỬA TÀI KHOẢN CƯ DÂN ================\n");
    printf("-> Nhập TÊN TÀI KHOẢN cư dân muốn sửa: "); 
    fgets(old_acc.username, sizeof(old_acc.username), stdin); 
    trimNewline(old_acc.username);

    printf("-> Nhập TẦNG hiện tại của cư dân này: "); 
    fgets(old_tang, sizeof(old_tang), stdin); 
    trimNewline(old_tang);

    printf("-> Nhập PHÒNG hiện tại của cư dân này: "); 
    fgets(old_phong, sizeof(old_phong), stdin); 
    trimNewline(old_phong);

    // 1. Check thư mục phòng cũ
    char check_dir_path[256];
    sprintf(check_dir_path, "FloorList/Floor%s/P%s0%s", old_tang, old_tang, old_phong);
    DIR *dir = opendir(check_dir_path);
    if (dir == NULL) {
        printf("\n[Lỗi]. Thư mục phòng ở '%s' không tồn tại!\n", check_dir_path);
        return;
    }
    closedir(dir);

    // 2. Kiểm tra file tài khoản
    char old_path1[256];
    sprintf(old_path1, "Data/Account/Resident/%s.txt", old_acc.username);
    FILE *f_read = fopen(old_path1, "r");
    if (f_read == NULL) {
        printf("\n[Lỗi]. Không tìm thấy file tài khoản cư dân '%s'!\n", old_acc.username);
        return;
    }

    // Đọc dữ liệu cũ
    fgets(old_acc.password, sizeof(old_acc.password), f_read);   
	trimNewline(old_acc.password);
    
	fgets(old_acc.fullName, sizeof(old_acc.fullName), f_read);   
	trimNewline(old_acc.fullName);
    
	fgets(old_acc.cccd, sizeof(old_acc.cccd), f_read);           
	trimNewline(old_acc.cccd);
    
	fgets(old_acc.year, sizeof(old_acc.year), f_read);           
	trimNewline(old_acc.year);
    
	fgets(old_acc.gender, sizeof(old_acc.gender), f_read);       
	trimNewline(old_acc.gender);
    
	fgets(old_acc.province, sizeof(old_acc.province), f_read);   
	trimNewline(old_acc.province);
    
	fgets(old_acc.phone, sizeof(old_acc.phone), f_read);         
	trimNewline(old_acc.phone);
    
	fclose(f_read);

    // Kiểm tra xem file cư dân có đúng ở phòng cũ không
    char old_path2[256];
    sprintf(old_path2, "FloorList/Floor%s/P%s0%s/%s.txt", old_tang, old_tang, old_phong, old_acc.cccd);
    FILE *f_check_res = fopen(old_path2, "r");
    if (f_check_res == NULL) {
        printf("\n[Lỗi]. Cư dân không có trong phòng P%s0%s!\n", old_tang, old_phong);
        return;
    }
    fclose(f_check_res);

    // Tạm nhấc CCCD cũ ra để tránh báo trùng khi validate
    removeCCCDFromFile(old_acc.cccd);

    printf("\n--- NHẬP THÔNG TIN CHỈNH SỬA MỚI ---\n");
    printf("-> Nhập tên tài khoản MỚI: "); 
    fgets(new_acc.username, sizeof(new_acc.username), stdin); 
    trimNewline(new_acc.username);

    printf("-> Nhập họ và tên MỚI: "); 
    fgets(new_acc.fullName, sizeof(new_acc.fullName), stdin); 
    trimNewline(new_acc.fullName);
    normalizeName(new_acc.fullName); 

    // Nhập và kiểm tra phòng mới
    while (1) {
        printf("-> Nhập tầng MỚI: "); 
        fgets(new_tang, sizeof(new_tang), stdin); 
        trimNewline(new_tang);

        printf("-> Nhập phòng MỚI: "); 
        fgets(new_phong, sizeof(new_phong), stdin); 
        trimNewline(new_phong);

        char new_dir_path[256];
        sprintf(new_dir_path, "FloorList/Floor%s/P%s0%s", new_tang, new_tang, new_phong);
        
        DIR *dir_new = opendir(new_dir_path);
        if (dir_new != NULL) {
            closedir(dir_new);
            break; 
        }
        printf("[Lỗi]. Phòng mới không tồn tại! Vui lòng nhập lại.\n\n");
    }

    // Nhập và kiểm tra CCCD mới
    inputAndValidateCCCD(&new_acc);

    // Kế thừa dữ liệu
    strcpy(new_acc.password, old_acc.password);
    strcpy(new_acc.phone, old_acc.phone);

    // CHỈ XÓA FILE CŨ KHI MỌI THỨ ĐÃ HỢP LỆ
    remove(old_path1);
    remove(old_path2);

    // Ghi dữ liệu mới vào phòng mới (Không ảnh hưởng đến file cư dân khác)
    if (!saveResidentData(new_acc.username, new_tang, new_phong, new_acc)) {
        printf("[Lỗi]. Không thể ghi file dữ liệu mới!\n");
        return;
    }

    // Ghi nhận CCCD mới vào file tổng
    FILE *f3 = fopen("Data/cccd.txt", "a");
    if (f3 != NULL) { 
        fprintf(f3, "%s\n", new_acc.cccd); 
        fclose(f3); 
    }

    printf("\n[Thành công]. Đã chuyển phòng và cập nhật thông tin!\n");
}

// Hàm xóa tài khoản cư dân
void deleteResidentAccount() {
	
    char input_username[64];
    char input_cccd[32];
    char confirm; 
    
    ResidentAccount file_acc; // Dùng struct đồng bộ với chức năng 3 và 4
    char tang[10], phong[10]; // Biến vị trí phòng tách riêng theo yêu cầu

    printf("\n================ XÓA TÀI KHOẢN CƯ DÂN ================\n");
    
    printf("-> Nhập TÊN TÀI KHOẢN muốn xóa: ");
    fgets(input_username, sizeof(input_username), stdin);
    trimNewline(input_username);

    printf("-> Nhập số CCCD để xác nhận: ");
    fgets(input_cccd, sizeof(input_cccd), stdin);
    trimNewline(input_cccd);

    printf("-> Nhập TẦNG hiện tại của cư dân: ");
    fgets(tang, sizeof(tang), stdin);
    trimNewline(tang);

    printf("-> Nhập PHÒNG hiện tại của cư dân: ");
    fgets(phong, sizeof(phong), stdin);
    trimNewline(phong);

    // Tạo đường dẫn file tài khoản (File 1)
    char path1[256];
    sprintf(path1, "Data/Account/Resident/%s.txt", input_username);
    
    FILE *f = fopen(path1, "r");
    if (f == NULL) {
        printf("\n[Lỗi]. Không tìm thấy tên tài khoản '%s' trên hệ thống!\n", input_username);
        return;
    }

    // Đọc dữ liệu từ file để lấy số CCCD gốc đối chiếu nhằm bảo mật thông tin
    fgets(file_acc.password, sizeof(file_acc.password), f); 
    fgets(file_acc.fullName, sizeof(file_acc.fullName), f); 
    fgets(file_acc.cccd, sizeof(file_acc.cccd), f); // Số CCCD nằm ở dòng thứ 3 của file
    fclose(f); // Đóng file ngay lập tức để hệ thống giải phóng file, lát nữa mới xóa được

    // Xóa ký tự xuống dòng của số CCCD vừa đọc từ file
   trimNewline(file_acc.cccd);

    // Kiểm tra tính khớp nhau giữa dữ liệu nhập vào và dữ liệu lưu trong file
    if (strcmp(input_cccd, file_acc.cccd) != 0) {
        printf("\n[Thất bại]. CCCD không có trong tài khoản! Hủy bỏ lệnh xóa.\n");
        return; 
    }

    // Bước hỏi xác nhận trước khi tiến hành xóa vĩnh viễn
    printf("\nCẢNH BÁO: Bạn có chắc chắn muốn xóa vĩnh viễn tài khoản cư dân này không?\n");
    printf("Bấm (y/Y) để ĐỒNG Ý xóa, hoặc bấm phím bất kỳ khác để HỦY: ");
    scanf("%c", &confirm);
    getchar(); // Xóa ký tự thừa '\n' tránh bị trôi lệnh ở các menu sau

    if (confirm != 'y' && confirm != 'Y') {
        printf("\n[Đã hủy]. Hệ thống đã hủy bỏ lệnh xóa tài khoản an toàn.\n");
        return; 
    }

    // BẮT ĐẦU QUÁ TRÌNH XÓA FILE KHI ĐÃ XÁC NHẬN Y/Y:
    
    // Tạo đường dẫn File 2 (File đặt trong sơ đồ phòng) dựa trên vị trí phòng và số CCCD trong struct
    char path2[256];
    sprintf(path2, "FloorList/Floor%s/P%s0%s/%s.txt", tang, tang, phong, file_acc.cccd);

    // Thực thi lệnh xóa file vĩnh viễn trên máy tính
    int res1 = remove(path1); // Xóa file tài khoản cư dân
    int res2 = remove(path2); // Xóa file thông tin nằm trong phòng ở

    // Gọi hàm dùng chung để xóa số CCCD khỏi danh sách tổng Data/cccd.txt
    removeCCCDFromFile(file_acc.cccd);

    // In thông báo kết quả cho quản lý dễ theo dõi
    if (res1 == 0 && res2 == 0) {
        printf("\n[Thành công]. Đã xóa hoàn toàn tài khoản '%s' và file phòng ở ra khỏi hệ thống!\n", input_username);
    } else if (res1 == 0 && res2 != 0) {
        printf("\n[Cảnh báo]. Đã xóa file tài khoản thành công và dọn dẹp CCCD tổng.\n");
        printf("Tuy nhiên không tìm thấy file phòng để xóa (có thể điền sai thông tin tầng/phòng cũ).\n");
    } else {
        printf("\n[Lỗi]. Không thể thực hiện lệnh xóa file. Vui lòng kiểm tra lại quyền truy cập!\n");
    }
}

// Hàm bổ trợ in chuỗi UTF-8 kèm khoảng trắng chuẩn visual (Chống lệch hàng khi có dấu tiếng Việt)
void printPadded(const char *str, int width) {
    int chars = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0) - 1;
    if (chars < 0) chars = 0;
    printf("%s", str);
    for (int i = 0; i < width - chars; i++) {
        printf(" ");
    }
}

// Hàm xem danh sách các phòng
void displayRoomOccupantsByFloor() {
    char input_tang[10];
    char room_dir_path[256];
    char file_path[256];
    char room_name[10];
    
    ResidentAccount occupant; 
    struct dirent *entry;
    DIR *dir;

    printf("\n================ XEM DANH SÁCH CÁC PHÒNG ================\n");
    printf("-> Chọn tầng muốn hiển thị danh sách phòng: ");
    fgets(input_tang, sizeof(input_tang), stdin);
    trimNewline(input_tang);

    printf("\nTầng %s\n", input_tang);
    printf("-------------------------------------------------------------------------------------------\n");
    printPadded("Phòng", 7); printf(" ");
    printPadded("Họ và tên", 25); printf(" ");
    printPadded("CCCD", 15); printf(" ");
    printPadded("Năm sinh", 10); printf(" ");
    printPadded("Giới tính", 10); printf(" ");
    printPadded("Số điện thoại", 15); printf("\n");
    printf("-------------------------------------------------------------------------------------------\n");

    for (int p = 1; p <= 5; p++) {
        sprintf(room_dir_path, "FloorList/Floor%s/P%s0%d", input_tang, input_tang, p);

        dir = opendir(room_dir_path);
        if (dir == NULL) {
            continue; 
        }

        int has_occupant = 0; 
        sprintf(room_name, "%s0%d", input_tang, p);

        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }

            sprintf(file_path, "%s/%s", room_dir_path, entry->d_name);
            
            FILE *f = fopen(file_path, "r");
            if (f != NULL) {
                fgets(occupant.password, sizeof(occupant.password), f); 
				trimNewline(occupant.password);
                
				fgets(occupant.fullName, sizeof(occupant.fullName), f); 
				trimNewline(occupant.fullName);
                
				fgets(occupant.cccd, sizeof(occupant.cccd), f);         
				trimNewline(occupant.cccd);
                
				fgets(occupant.year, sizeof(occupant.year), f);         
				trimNewline(occupant.year);
                
				fgets(occupant.gender, sizeof(occupant.gender), f);     
				trimNewline(occupant.gender);
                
				fgets(occupant.province, sizeof(occupant.province), f); 
				trimNewline(occupant.province);
                
				fgets(occupant.phone, sizeof(occupant.phone), f);       
				trimNewline(occupant.phone);
                
				fclose(f);

                if (strlen(occupant.phone) == 0) {
                    strcpy(occupant.phone, "Không có");
                }

                if (has_occupant == 0) {
                    printPadded(room_name, 7); printf(" ");
                    printPadded(occupant.fullName, 25); printf(" ");
                    printPadded(occupant.cccd, 15); printf(" ");
                    printPadded(occupant.year, 10); printf(" ");
                    printPadded(occupant.gender, 10); printf(" ");
                    printPadded(occupant.phone, 15); printf("\n");
                    has_occupant = 1; 
                } else {
                    printPadded("", 7); printf(" ");
                    printPadded(occupant.fullName, 25); printf(" ");
                    printPadded(occupant.cccd, 15); printf(" ");
                    printPadded(occupant.year, 10); printf(" ");
                    printPadded(occupant.gender, 10); printf(" ");
                    printPadded(occupant.phone, 15); printf("\n");
                }
            }
        }
        closedir(dir); 

        if (has_occupant == 1) {
            printf("....... ......................... ............... .......... .......... ...............\n");
        }
    }
    printf("-------------------------------------------------------------------------------------------\n");
}

// Hàm tìm kiếm cư dân
void searchResident() {
    char choice[10];
    char input_search[64];
    int found = 0;

    DIR *dir_floorlist = opendir("FloorList");
    if (dir_floorlist == NULL) {
        printf("[Lỗi]. Thư mục FloorList không tồn tại trên hệ thống!\n");
        return;
    }

    // Vòng lặp yêu cầu nhập lại nếu chọn sai
    while (1) {
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
            break; // Nhập đúng thì thoát vòng lặp để xuống bước tìm kiếm
        } else if (strcmp(choice, "2") == 0) {
            printf("-> Nhập Họ và tên cần tìm: ");
            fgets(input_search, sizeof(input_search), stdin);
            trimNewline(input_search);
            normalizeName(input_search); 
            break; // Nhập đúng thì thoát vòng lặp để xuống bước tìm kiếm
        } else {
            printf("[Lỗi]. Lựa chọn không hợp lệ! Vui lòng chọn lại (1 hoặc 2).\n");
        }
    }

    struct dirent *ent_floorlist;
    while ((ent_floorlist = readdir(dir_floorlist)) != NULL) {
        if (strcmp(ent_floorlist->d_name, ".") == 0 || strcmp(ent_floorlist->d_name, "..") == 0) {
            continue;
        }

        char path_floor[512];
        sprintf(path_floor, "FloorList/%s", ent_floorlist->d_name);
        
        DIR *dir_floor = opendir(path_floor);
        if (dir_floor == NULL) continue;

        struct dirent *ent_floor;
        while ((ent_floor = readdir(dir_floor)) != NULL) {
            if (strcmp(ent_floor->d_name, ".") == 0 || strcmp(ent_floor->d_name, "..") == 0) {
                continue;
            }

            char path_room[512];
            sprintf(path_room, "%s/%s", path_floor, ent_floor->d_name);

            DIR *dir_room = opendir(path_room);
            if (dir_room == NULL) continue;

            struct dirent *ent_room;
            while ((ent_room = readdir(dir_room)) != NULL) {
                if (strcmp(ent_room->d_name, ".") == 0 || strcmp(ent_room->d_name, "..") == 0) {
                    continue;
                }

                char path_file[512];
                sprintf(path_file, "%s/%s", path_room, ent_room->d_name);

                if (strcmp(choice, "1") == 0) {
                    char cccd_from_filename[32];
                    strcpy(cccd_from_filename, ent_room->d_name);
                    
                    char *dot = strrchr(cccd_from_filename, '.');
                    if (dot != NULL) *dot = '\0';

                    if (strcmp(input_search, cccd_from_filename) == 0) {
                        ResidentAccount temp_acc;
                        FILE *f_read = fopen(path_file, "r");
                        if (f_read != NULL) {
                            fgets(temp_acc.password, sizeof(temp_acc.password), f_read);
                            fgets(temp_acc.fullName, sizeof(temp_acc.fullName), f_read);
                            trimNewline(temp_acc.fullName);
                            fclose(f_read);
                        }

                        printf("\n[Tìm thấy]. Cư dân: %s\n", temp_acc.fullName);
                        printf("-> Vị trí: %s\n", ent_floor->d_name);
                        found = 1;
                        break; 
                    }
                }
                else if (strcmp(choice, "2") == 0) {
                    FILE *f = fopen(path_file, "r");
                    if (f != NULL) {
                        ResidentAccount temp_acc;
                        fgets(temp_acc.password, sizeof(temp_acc.password), f); 
                        fgets(temp_acc.fullName, sizeof(temp_acc.fullName), f); 
                        fgets(temp_acc.cccd, sizeof(temp_acc.cccd), f);
                        fclose(f);

                        trimNewline(temp_acc.fullName);
                        trimNewline(temp_acc.cccd);

                        if (strcmp(input_search, temp_acc.fullName) == 0) {
                            printf("\n[Tìm thấy]. Cư dân: %s (CCCD: %s)\n", temp_acc.fullName, temp_acc.cccd);
                            printf("-> Vị trí: %s\n", ent_floor->d_name);
                            found = 1;
                        }
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
			case 5: 
				deleteResidentAccount();
				break;
			case 6:
				displayRoomOccupantsByFloor();
				break;
			case 7: 
				searchResident();
				break;
			case 8: case 9:
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