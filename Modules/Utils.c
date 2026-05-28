//Thư viện sử dụng
#include "Utils.h"
#include <stdio.h>      // fopen, fclose, fprintf, sprintf, FILE
#include <dirent.h>     // DIR, opendir, closedir
#include <windows.h>    // SetConsoleTextAttribute, GetStdHandle
#include <direct.h>     // _mkdir
#include <time.h>       //time_t
#include <conio.h>

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
