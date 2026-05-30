//Thư viện sử dụng
#include "Utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <dirent.h>
#include <windows.h>
#include <direct.h>
#include <time.h>
#include <conio.h>

#define ENTER 13
#define ESC 27

//Hàm di chuyển con trỏ
void gotoxy(int x, int y) {

    COORD c;

    c.X = x;
    c.Y = y;

    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        c
    );
}

//Tạo nơi chứa dữ liệu tỉnh thành
void createProvinceFolder() {

    //Tạo thư mục Province nếu chưa tồn tại
    DIR *dp = opendir("Data/Province");
    if (dp == NULL) {
        _mkdir("Data/Province");
    } else {
        closedir(dp);
    }

    //Danh sách mã tỉnh và tên tỉnh
    struct Province {
        int code;
        char name[64];
    };

    //Danh sách đầy đủ mã tỉnh và tên tỉnh
    struct Province provinces[] = {
        {1, "Hà Nội"},
        {2, "Hà Giang"},
        {4, "Cao Bằng"},
        {6, "Bắc Kạn"},
        {8, "Tuyên Quang"},
        {10, "Lào Cai"},
        {11, "Điện Biên"},
        {12, "Lai Châu"},
        {14, "Sơn La"},
        {15, "Yên Bái"},
        {17, "Hòa Bình"},
        {19, "Thái Nguyên"},
        {20, "Lạng Sơn"},
        {22, "Quảng Ninh"},
        {24, "Bắc Giang"},
        {25, "Phú Thọ"},
        {26, "Vĩnh Phúc"},
        {27, "Bắc Ninh"},
        {30, "Hải Dương"},
        {31, "Hải Phòng"},
        {33, "Hưng Yên"},
        {34, "Thái Bình"},
        {35, "Hà Nam"},
        {36, "Nam Định"},
        {37, "Ninh Bình"},
        {38, "Thanh Hóa"},
        {40, "Nghệ An"},
        {42, "Hà Tĩnh"},
        {44, "Quảng Bình"},
        {45, "Quảng Trị"},
        {46, "Thừa Thiên Huế"},
        {48, "Đà Nẵng"},
        {49, "Quảng Nam"},
        {51, "Quảng Ngãi"},
        {52, "Bình Định"},
        {54, "Phú Yên"},
        {56, "Khánh Hòa"},
        {58, "Ninh Thuận"},
        {60, "Bình Thuận"},
        {62, "Kon Tum"},
        {64, "Gia Lai"},
        {66, "Đắk Lắk"},
        {67, "Đắk Nông"},
        {68, "Lâm Đồng"},
        {70, "Bình Phước"},
        {72, "Tây Ninh"},
        {74, "Bình Dương"},
        {75, "Đồng Nai"},
        {77, "Bà Rịa - Vũng Tàu"},
        {79, "Hồ Chí Minh"},
        {80, "Long An"},
        {82, "Tiền Giang"},
        {83, "Bến Tre"},
        {84, "Trà Vinh"},
        {86, "Vĩnh Long"},
        {87, "Đồng Tháp"},
        {89, "An Giang"},
        {91, "Kiên Giang"},
        {92, "Cần Thơ"},
        {93, "Hậu Giang"},
        {94, "Sóc Trăng"},
        {95, "Bạc Liêu"},
        {96, "Cà Mau"}
    };

    //Lấy số lượng phần tử trong mảng provinces
    int n = sizeof(provinces) / sizeof(provinces[0]);

    //Tạo file cho từng tỉnh
    for (int i = 0; i < n; i++) {

        char path[256];

        //Tạo địa chỉ để đến nơi chứa File
        sprintf(path, "Data/Province/%03d.txt", provinces[i].code);

        //Kiểm tra file tồn tại chưa
        FILE *f = fopen(path, "r");

        //Nếu chưa tồn tại thì tạo file
        if (f == NULL) {

            f = fopen(path, "w");

            if (f != NULL) {
                fprintf(f, "%s", provinces[i].name);
                fclose(f);
            }
        } else {
            fclose(f);
        }
    }
}

//Tạo nơi chứa tài khoản admin và quản lý
void createAccountFolder() {

    //Tạo thư mục Account nếu chưa tồn tại
    DIR *dp1 = opendir("Data/Account");
    if (dp1 == NULL) {
        _mkdir("Data/Account");
    } else {
        closedir(dp1);
    }

    //Tạo thư mục Admin nếu chưa tồn tại
    DIR *dp2 = opendir("Data/Account/Admin");
    if (dp2 == NULL) {
        _mkdir("Data/Account/Admin");
    } else {
        closedir(dp2);
    }

    //Tạo thư mục Manage nếu chưa tồn tại
    DIR *dp3 = opendir("Data/Account/Manage");
    if (dp3 == NULL) {
        _mkdir("Data/Account/Manage");
    } else {
        closedir(dp3);
    }
}

//Tạo nơi chứa FloorList
void createFloorList() {

    //Tạo thư mục gốc
    _mkdir("FloorList");

    for (int floor = 1; floor <= 5; floor++) {
        char floorName[50];
        sprintf(floorName, "FloorList/Floor%d", floor);

        //Tạo Floor1, Floor2,...
        _mkdir(floorName);

        for (int room = 1; room <= 5; room++) {
            char roomName[60];
            sprintf(roomName, "FloorList/Floor%d/P%d%02d", floor, floor, room);

            //Tạo P101, P102,...
            _mkdir(roomName);
        }
    }
}

//Tạo nơi chứa Bill
void createBill() {

    //Tạo folder Bill
    _mkdir("Data/Bill");

    for (int floor = 1; floor <= 5; floor++) {
        char floorPath[100];
        sprintf(floorPath, "Data/Bill/Floor%d", floor);

        //Tạo Floor1, Floor2,...
        _mkdir(floorPath);

        for (int room = 1; room <= 5; room++) {
            char roomPath[150];
            sprintf(roomPath, "Data/Bill/Floor%d/P%d%02d", floor, floor, room);

            //Tạo P101, P102,...
            _mkdir(roomPath);
        }
    }
}

//Kiểm tra thư mục Data có tồn tại không, nếu không thì tạo
void createDataFolder() {

    //Kiểm tra thư mục Data có tồn tại chưa
    DIR *dp = opendir("Data");

    //Nếu chưa tồn tại thì tạo thư mục
    if (dp == NULL) {
        _mkdir("Data");
    } else {
        closedir(dp);
    }

    //Tạo folder chứa Province
    createProvinceFolder();

    //Tạo folder chứa Account
    createAccountFolder();

    //Tạo folder Bill
    createBill();

    //Tạo folder FloorList
    createFloorList();
}

//Hàm đổi màu chữ
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//Ẩn con trỏ
void hideCursor() {

    CONSOLE_CURSOR_INFO cursorInfo;

    // Lấy thông tin con trỏ hiện tại
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    // Tắt hiển thị con trỏ
    cursorInfo.bVisible = FALSE;

    // Cập nhật lại
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

//Hiện con trỏ
void showCursor() {

    CONSOLE_CURSOR_INFO cursorInfo;

    // Lấy thông tin hiện tại của con trỏ (kích thước + trạng thái)
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    // Bật hiển thị con trỏ (TRUE = hiện, FALSE = ẩn)
    cursorInfo.bVisible = TRUE;

    // Cập nhật lại cấu hình con trỏ vào console
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

//Lưu lịch sử thay đổi
void saveHistory(char role[], char status[], char action[], char target[]) {

    //Mở file lịch sử và kiểm tra
    FILE *f = fopen ("Data/History.txt", "a");
    if (f == NULL) {
        setColor(12);
        printf("[Lỗi]. Không mở được file History.txt.");
        setColor(7);
        return;
    }

    //Lấy thời gian hiện tại
    time_t t;
    struct tm *now;

    time (&t);
    now = localtime(&t);

    //Ghi vào file
    fprintf(f, "[%s][%s][%02d/%02d/%04d %02d:%02d:%02d] %s: %s\n", role, status, now->tm_mday, now->tm_mon + 1, now->tm_year + 1900, now->tm_hour, now->tm_min, now->tm_sec, action, target);

    //Đóng file
    fclose (f);
}

//Đếm ký tự UTF-8 gần đúng
int utf8len(const char *s) {
    int len = 0;
    while (*s) {
        //Byte không phải continuation byte
        if ((*s & 0xC0) != 0x80) {
            len++;
        }
        s++;
    }
    return len;
}

//Hàm in nội dung
void printContent(char content[], int num, int choice) {

    if (num == choice) {
        setColor(11);
        printf("   >> [%d]. %s\n", num, content);
        setColor(7);
    } else {
        printf("       [%d]. %s\n", num, content);
    }
}

//Kiểm tra username có hợp lệ không
int checkUsername(char username[]) {

    //Duyệt từng ký tự trong chuỗi
    for (int i = 0; i < strlen(username); i++) {
        // Nếu ký tự không phải chữ hoặc số
        if (!isalnum(username[i])) {
            return 0;
        }
    }
    return 1;
}

//Kiểm tra username có trùng không
int checkDuplicateUsername(char newUsername[], char path[]) {

    //Mở file chứa danh sách username
    FILE *f = fopen(path, "r");

    //Nếu file không tồn tại
    if (f == NULL) {
        return 0;
    }
    return 1;
}

//Hàm kiểm tra chuỗi chỉ chứa chữ cái và khoảng trắng
int isOnlyLetter(char str[]) {

    int i = 0;
    while (str[i] != '\0') {
        unsigned char c = str[i];

        //Cho phép khoảng trắng
        if (c == ' ') {
            i++;
        }

        //Chữ cái tiếng Anh
        else if ((c >= 'A' && c <= 'Z') ||
                 (c >= 'a' && c <= 'z')) {
            i++;
        }

        //Ký tự UTF-8 tiếng Việt
        else if (c >= 128) {
            //UTF-8 tiếng Việt thường dài 2 hoặc 3 byte
            if ((c & 0xE0) == 0xC0) {
                i += 2;
            }
            else if ((c & 0xF0) == 0xE0) {
                i += 3;
            }
            else {
                return 0;
            }
        }
        //Ký tự không hợp lệ
        else {
            return 0;
        }
    }
    return 1;
}

//Hàm kiểm tra tính hợp lệ của mật khẩu
int checkPassword(char password[]) {
    int length = strlen(password);
    
    //Mật khẩu phải có ít nhất 8 ký tự
    if (length < 8) {
        return 0;
    }

    //Mật khẩu phải chứa ít nhất một chữ cái viết hoa, một chữ cái viết thường, một số và một ký tự đặc biệt
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;
    for (int i = 0; i < length; i++) {
        if (password[i] >= 'A' && password[i] <= 'Z') {
            hasUpper = 1;
        } else if (password[i] >= 'a' && password[i] <= 'z') {
            hasLower = 1;
        } else if (password[i] >= '0' && password[i] <= '9') {
            hasDigit = 1;
        } else {
            hasSpecial = 1;
        }
    }
    return hasUpper && hasLower && hasDigit && hasSpecial;
}

//Kiểm tra Số điện thoại
int checkPhoneNumber(char phone[]) {
    int length = strlen(phone);
    
    //Số điện thoại phải có 10 chữ số và bắt đầu bằng số 0
    if (length != 10) {
        return 0;
    }
    if (phone[0] != '0') {
        return 0;
    }

    //Kiểm tra tất cả ký tự phải là số
    for (int i = 0; i < length; i++) {
        if (phone[i] < '0' || phone[i] > '9') {
            return 0;
        }
    }
    return 1;
}

//Kiểm tra có phải toàn số không
int isAllDigits(char *s) {
    //Chuỗi rỗng
    if(strlen(s) == 0) {
        return 0;
    }
    //Kiểm tra từng ký tự
    for(int i = 0; s[i]; i++) {
        if(!isdigit(s[i])) {
            return 0;
        }
    }
    //Toàn số
    return 1;
}

//Kiểm tra mã tỉnh
int validProvince(int CCCD) {

    //Mã tỉnh hợp lệ
    int provinces[] = {
        1, 2, 4, 6, 8, 10, 11, 12, 14, 15,
        17, 19, 20, 22, 24, 25, 26, 27, 30,
        31, 33, 34, 35, 36, 37, 38, 40, 42,
        44, 45, 46, 48, 49, 51, 52, 54, 56,
        58, 60, 62, 64, 66, 67, 68, 70, 72,
        74, 75, 77, 79, 80, 82, 83, 84, 86,
        87, 89, 91, 92, 93, 94, 95, 96
    };

    //Lấy số lượng mã tỉnh
    int n = sizeof (provinces)/sizeof(provinces[0]);

    //Kiểm tra mã có hợp lệ không
    for (int i = 0; i < n; i++) {
        if (CCCD == provinces[i]) return 1;
    }
    return 0;
}

//Kiểm tra CCCD có bị trùng hay không
int checkDuplicateCCCD(char CCCD[]) {

    //Khai báo biến cần thiết
    FILE *f;
    DIR *dir;

    struct dirent *entry;

    char path[256];

    char password[100];
    char name[100];
    char fileCCCD[30];

    //================ ADMIN ================

    //Mở folder Admin
    dir = opendir("Data/Account/Admin");

    //Nếu mở được folder
    if(dir != NULL) {

        //Đọc từng file
        while((entry = readdir(dir)) != NULL) {

            //Kiểm tra file txt
            if(strstr(entry->d_name, ".txt") != NULL) {

                //Tạo đường dẫn file
                sprintf(path, "Data/Account/Admin/%s", entry->d_name);

                //Mở file
                f = fopen(path, "r");

                //Nếu mở được file
                if(f != NULL) {

                    //Đọc dữ liệu
                    fgets(password, sizeof(password), f);
                    fgets(name, sizeof(name), f);
                    fgets(fileCCCD, sizeof(fileCCCD), f);

                    //Xóa xuống dòng
                    fileCCCD[strcspn(fileCCCD, "\n")] = '\0';

                    //So sánh CCCD
                    if(strcmp(CCCD, fileCCCD) == 0) {

                        fclose(f);

                        closedir(dir);

                        return 1;
                    }

                    fclose(f);
                }
            }
        }

        closedir(dir);
    }

    //================ MANAGE ================

    //Mở folder Manage
    dir = opendir("Data/Account/Manage");

    //Nếu mở được folder
    if(dir != NULL) {

        //Đọc từng file
        while((entry = readdir(dir)) != NULL) {

            //Kiểm tra file txt
            if(strstr(entry->d_name, ".txt") != NULL) {

                //Tạo đường dẫn file
                sprintf(path, "Data/Account/Manage/%s", entry->d_name);

                //Mở file
                f = fopen(path, "r");

                //Nếu mở được file
                if(f != NULL) {

                    //Đọc dữ liệu
                    fgets(password, sizeof(password), f);
                    fgets(name, sizeof(name), f);
                    fgets(fileCCCD, sizeof(fileCCCD), f);

                    //Xóa xuống dòng
                    fileCCCD[strcspn(fileCCCD, "\n")] = '\0';

                    //So sánh CCCD
                    if(strcmp(CCCD, fileCCCD) == 0) {

                        fclose(f);

                        closedir(dir);

                        return 1;
                    }

                    fclose(f);
                }
            }
        }

        closedir(dir);
    }

    //================ RESIDENT ================

    //Duyệt từng tầng
    for(int floor = 1; floor <= 5; floor++) {

        //Duyệt từng phòng
        for(int room = 1; room <= 5; room++) {

            //Tạo path folder phòng
            sprintf(path, "FloorList/Floor%d/P%d%02d", floor, floor, room);

            //Mở folder phòng
            dir = opendir(path);

            //Nếu mở được folder
            if(dir != NULL) {

                //Đọc từng file trong phòng
                while((entry = readdir(dir)) != NULL) {

                    //Kiểm tra file txt
                    if(strstr(entry->d_name, ".txt") != NULL) {

                        //Tạo full path
                        char residentPath[300];
                        
                        sprintf(residentPath, "%s/%s", path, entry->d_name);

                        //Mở file
                        f = fopen(residentPath, "r");

                        //Nếu mở được file
                        if(f != NULL) {

                            //Đọc dữ liệu
                            fgets(password, sizeof(password), f);
                            fgets(name, sizeof(name), f);
                            fgets(fileCCCD, sizeof(fileCCCD), f);

                            //Xóa xuống dòng
                            fileCCCD[strcspn(fileCCCD, "\n")] = '\0';

                            //So sánh CCCD
                            if(strcmp(CCCD, fileCCCD) == 0) {

                                fclose(f);
                                closedir(dir);

                                return 1;
                            }

                            fclose(f);
                        }
                    }
                }

                closedir(dir);
            }
        }
    }

    //Không trùng
    return 0;
}

//Kiểm tra căn cước công dân có hợp lệ không
int checkCCCD(char year[], char province[], char CCCD[], char gender[]) {

    //Kiểm tra có đủ 12 ký tự không
    if (strlen(CCCD) != 12) {
        return 0;
    }
    //Kiểm tra có phải tất cả là số không
    if (!isAllDigits(CCCD)) {
        return 0;
    }

    //Kiểm tra CCCD có trùng với ai không
    if (checkDuplicateCCCD(CCCD)) {
        return 0;
    }

    //Kiểm tra mã tỉnh
    int Province = (CCCD[0] - '0') * 100 + (CCCD[1] - '0') * 10 + (CCCD[2] - '0');
    if (!validProvince(Province)) {
        return 0;
    }
    //Lưu quê quán
    char path[256];
    sprintf(path, "Data/Province/%03d.txt", Province);
    FILE *f = fopen (path, "r");
    if (f == NULL) {
        strcpy(province, "Không tìm thấy quê quán");
    } else {
        fgets(province, 32, f);
        province[strcspn(province, "\n")] = '\0';
        fclose(f);
    }

    //Kiểm tra giới tính
    int Gender = CCCD[3] - '0';
    if (Gender < 0 || Gender > 3) {
        return 0;
    }
    if (Gender % 2 == 0) strcpy(gender, "Nam");
    else strcpy(gender, "Nữ");

    //Kiểm tra năm sinh
    int Year = (CCCD[4] - '0') * 10 + (CCCD[5] - '0');
    if (Gender == 0 || Gender == 1) sprintf(year, "19%02d", Year);
    if (Gender == 2 || Gender == 3) sprintf(year, "20%02d", Year);

    return 1;
}

//Validate CCCD thuần — không check duplicate
int checkCCCDOnly(char year[], char province[], char CCCD[], char gender[]) {

    if(strlen(CCCD) != 12) return 0;

    if(!isAllDigits(CCCD)) return 0;

    // BỎ DÒNG NÀY so với checkCCCD gốc
    // if(checkDuplicateCCCD(CCCD)) return 0;

    int Province = (CCCD[0] - '0') * 100 + (CCCD[1] - '0') * 10 + (CCCD[2] - '0');
    if(!validProvince(Province)) return 0;

    char path[256];
    sprintf(path, "Data/Province/%03d.txt", Province);
    FILE *f = fopen(path, "r");
    if(f == NULL) {
        strcpy(province, "Không tìm thấy quê quán");
    } else {
        fgets(province, 32, f);
        province[strcspn(province, "\n")] = '\0';
        fclose(f);
    }

    int Gender = CCCD[3] - '0';
    if(Gender < 0 || Gender > 3) return 0;
    if(Gender % 2 == 0) strcpy(gender, "Nam");
    else strcpy(gender, "Nữ");

    int Year = (CCCD[4] - '0') * 10 + (CCCD[5] - '0');
    if(Gender == 0 || Gender == 1) sprintf(year, "19%02d", Year);
    if(Gender == 2 || Gender == 3) sprintf(year, "20%02d", Year);

    return 1;
}

//Kiểm tra username có trùng không
int checkDuplicateUsernameForResident(char username[]) {

    char path[300];

    for (int floor = 1; floor <= 5; floor++) {
        for (int room = 1; room <= 5; room++) {

            sprintf(path, "FloorList/Floor%d/P%d%02d/%s.txt", floor, floor, room, username);

            FILE *f = fopen(path, "r");

            if (f != NULL) {
                fclose(f);
                return 1;
            }
        }
    }

    return 0;
}

//Đăng xuất
void logout() {

    //Làm sạch màn hình
    system("cls");

    //In chữ LOGOUT
    printf("\n");
    printf("██╗      ██████╗  ██████╗  ██████╗ ██╗   ██╗████████╗\n");
    printf("██║     ██╔═══██╗██╔════╝ ██╔═══██╗██║   ██║╚══██╔══╝\n");
    printf("██║     ██║   ██║██║  ███╗██║   ██║██║   ██║   ██║   \n");
    printf("██║     ██║   ██║██║   ██║██║   ██║██║   ██║   ██║   \n");
    printf("███████╗╚██████╔╝╚██████╔╝╚██████╔╝╚██████╔╝   ██║   \n");
    printf("╚══════╝ ╚═════╝  ╚═════╝  ╚═════╝  ╚═════╝    ╚═╝   \n\n\n");

    //In thông báo
    setColor(10);
    printf("       Đăng xuất thành công!\n");
    setColor(7);

    //Đợi người dùng nhấn Enter hoặc Esc
    printf("\nNhấn Enter hoặc Esc để thoát\n");
    int key = getch();
    while (key != ENTER && key != ESC) {
        key = getch();
    }
}