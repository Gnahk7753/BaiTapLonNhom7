//Thư viện sử dụng
#include <stdio.h>
#include <windows.h>
#include "Modules/Utils.h"
#include "Modules/Login.h"

//Hàm main
int main () {

    //Chỉnh sửa lỗi front chữ Tiếng Việt
	SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    //Kiểm tra File Data
    createDataFolder();

    //Tạo vòng lặp
    char *mainMenu[] = {
        "Đăng nhập với tư cách: Admin", 
        "Đăng nhập với tư cách: Quản lý", 
        "Đăng nhập với tư cách: Cư dân", 
        "Thoát",
    };

    //Lấy số lượng phần tử trong mảng mainMenu
    int size = sizeof(mainMenu) / sizeof(mainMenu[0]);

    //Vòng lặp chính
    while (1) {
        
        //Lựa chọn loại tài khoản muốn đăng nhập
        hideCursor();
        int selected = menuLogin(mainMenu, size);

        //Dùng switch case cho từng trường hợp đặng nhập
        switch (selected) {
            
            //Đăng nhập với tư cách Admin
            case 0:
                login(0);
                break;
            case 1:
                login(1);
                break;
            case 2:
                login(2);
                break;
            case 3:
                return 0;
        }
    }
}