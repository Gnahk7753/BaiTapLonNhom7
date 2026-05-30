//Thư viện sử dụng
#include "Login.h"
#include "Utils.h"
#include "Admin.h"
#include "Manage.h"
#include "Resident.h"
#include <stdio.h>      // printf
#include <stdlib.h>     // system("cls")
#include <conio.h>      // getch()
#include <windows.h>    // SetConsoleTextAttribute
#include <string.h>     // strlen nếu cần
#include <locale.h>     // UTF-8 tiếng Việt

#define KEY_UP 72
#define KEY_DOWN 80
#define BACKSPACE 8
#define ENTER 13
#define ESC 27

//In chữ LOGIN ADMIN
void printAdminBanner() {
    printf("\n");
    printf("██╗      ██████╗  ██████╗ ██╗███╗   ██╗     █████╗ ██████╗ ███╗   ███╗██╗███╗   ██╗\n");
    printf("██║     ██╔═══██╗██╔════╝ ██║████╗  ██║    ██╔══██╗██╔══██╗████╗ ████║██║████╗  ██║\n");
    printf("██║     ██║   ██║██║  ███╗██║██╔██╗ ██║    ███████║██║  ██║██╔████╔██║██║██╔██╗ ██║\n");
    printf("██║     ██║   ██║██║   ██║██║██║╚██╗██║    ██╔══██║██║  ██║██║╚██╔╝██║██║██║╚██╗██║\n");
    printf("███████╗╚██████╔╝╚██████╔╝██║██║ ╚████║    ██║  ██║██████╔╝██║ ╚═╝ ██║██║██║ ╚████║\n");
    printf("╚══════╝ ╚═════╝  ╚═════╝ ╚═╝╚═╝  ╚═══╝    ╚═╝  ╚═╝╚═════╝ ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝\n\n\n");
}

//In chữ LOGIN MANAGE
void printManageBanner() {
    printf("\n");
    printf("██╗      ██████╗  ██████╗ ██╗███╗   ██╗    ███╗   ███╗ █████╗ ███╗   ██╗ █████╗  ██████╗ ███████╗\n");
    printf("██║     ██╔═══██╗██╔════╝ ██║████╗  ██║    ████╗ ████║██╔══██╗████╗  ██║██╔══██╗██╔════╝ ██╔════╝\n");
    printf("██║     ██║   ██║██║  ███╗██║██╔██╗ ██║    ██╔████╔██║███████║██╔██╗ ██║███████║██║  ███╗█████╗  \n");
    printf("██║     ██║   ██║██║   ██║██║██║╚██╗██║    ██║╚██╔╝██║██╔══██║██║╚██╗██║██╔══██║██║   ██║██╔══╝  \n");
    printf("███████╗╚██████╔╝╚██████╔╝██║██║ ╚████║    ██║ ╚═╝ ██║██║  ██║██║ ╚████║██║  ██║╚██████╔╝███████╗\n");
    printf("╚══════╝ ╚═════╝  ╚═════╝ ╚═╝╚═╝  ╚═══╝    ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝\n\n\n");
}

//In chữ LOGIN RESIDENT
void printResidentBanner() {
    printf("\n");
    printf("██╗      ██████╗  ██████╗ ██╗███╗   ██╗    ██████╗ ███████╗███████╗██╗██████╗ ███████╗███╗   ██╗████████╗\n");
    printf("██║     ██╔═══██╗██╔════╝ ██║████╗  ██║    ██╔══██╗██╔════╝██╔════╝██║██╔══██╗██╔════╝████╗  ██║╚══██╔══╝\n");
    printf("██║     ██║   ██║██║  ███╗██║██╔██╗ ██║    ██████╔╝█████╗  ███████╗██║██║  ██║█████╗  ██╔██╗ ██║   ██║   \n");
    printf("██║     ██║   ██║██║   ██║██║██║╚██╗██║    ██╔══██╗██╔══╝  ╚════██║██║██║  ██║██╔══╝  ██║╚██╗██║   ██║   \n");
    printf("███████╗╚██████╔╝╚██████╔╝██║██║ ╚████║    ██║  ██║███████╗███████║██║██████╔╝███████╗██║ ╚████║   ██║   \n");
    printf("╚══════╝ ╚═════╝  ╚═════╝ ╚═╝╚═╝  ╚═══╝    ╚═╝  ╚═╝╚══════╝╚══════╝╚═╝╚═════╝ ╚══════╝╚═╝  ╚═══╝   ╚═╝   \n\n\n");
}

//In chữ HELLO ADMIN
void helloAdmin() {
    printf("\n");
    printf("██╗  ██╗███████╗██╗     ██╗      ██████╗      █████╗ ██████╗ ███╗   ███╗██╗███╗   ██╗\n");
    printf("██║  ██║██╔════╝██║     ██║     ██╔═══██╗    ██╔══██╗██╔══██╗████╗ ████║██║████╗  ██║\n");
    printf("███████║█████╗  ██║     ██║     ██║   ██║    ███████║██║  ██║██╔████╔██║██║██╔██╗ ██║\n");
    printf("██╔══██║██╔══╝  ██║     ██║     ██║   ██║    ██╔══██║██║  ██║██║╚██╔╝██║██║██║╚██╗██║\n");
    printf("██║  ██║███████╗███████╗███████╗╚██████╔╝    ██║  ██║██████╔╝██║ ╚═╝ ██║██║██║ ╚████║\n");
    printf("╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝ ╚═════╝     ╚═╝  ╚═╝╚═════╝ ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝\n\n\n");
}

//In chữ HELLO MANAGE
void printHelloManage() {
    printf("\n");
    printf("██╗  ██╗███████╗██╗     ██╗      ██████╗     ███╗   ███╗ █████╗ ███╗   ██╗ █████╗  ██████╗ ███████╗\n");
    printf("██║  ██║██╔════╝██║     ██║     ██╔═══██╗    ████╗ ████║██╔══██╗████╗  ██║██╔══██╗██╔════╝ ██╔════╝\n");
    printf("███████║█████╗  ██║     ██║     ██║   ██║    ██╔████╔██║███████║██╔██╗ ██║███████║██║  ███╗█████╗  \n");
    printf("██╔══██║██╔══╝  ██║     ██║     ██║   ██║    ██║╚██╔╝██║██╔══██║██║╚██╗██║██╔══██║██║   ██║██╔══╝  \n");
    printf("██║  ██║███████╗███████╗███████╗╚██████╔╝    ██║ ╚═╝ ██║██║  ██║██║ ╚████║██║  ██║╚██████╔╝███████╗\n");
    printf("╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝ ╚═════╝     ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝\n\n\n");
}

//In chữ HELLO RESIDENT
void printHelloResident() {
    printf("\n");
    printf("██╗  ██╗███████╗██╗     ██╗      ██████╗     ██████╗ ███████╗███████╗██╗██████╗ ███████╗███╗   ██╗████████╗\n");
    printf("██║  ██║██╔════╝██║     ██║     ██╔═══██╗    ██╔══██╗██╔════╝██╔════╝██║██╔══██╗██╔════╝████╗  ██║╚══██╔══╝\n");
    printf("███████║█████╗  ██║     ██║     ██║   ██║    ██████╔╝█████╗  ███████╗██║██║  ██║█████╗  ██╔██╗ ██║   ██║   \n");
    printf("██╔══██║██╔══╝  ██║     ██║     ██║   ██║    ██╔══██╗██╔══╝  ╚════██║██║██║  ██║██╔══╝  ██║╚██╗██║   ██║   \n");
    printf("██║  ██║███████╗███████╗███████╗╚██████╔╝    ██║  ██║███████╗███████║██║██████╔╝███████╗██║ ╚████║   ██║   \n");
    printf("╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝ ╚═════╝     ╚═╝  ╚═╝╚══════╝╚══════╝╚═╝╚═════╝ ╚══════╝╚═╝  ╚═══╝   ╚═╝   \n\n\n");
}

//Hàm vẽ giao diện đăng nhập
void printLoginForm(char username[], char password[], int currentField, int *fail) {

    //Ô tài khoản
    if(currentField == 0) {
        setColor(11);
        printf("   >> Tài Khoản: %s\n", username);
        setColor(7);
    } else {
        printf("       Tài Khoản: %s\n", username);
    }

    //Ô mật khẩu
    if(currentField == 1) {
        setColor(11);
        printf("   >> Mật khẩu : %s\n", password);
        setColor(7);
    } else {
        printf("       Mật khẩu : %s\n", password);
    }

    //Ô đăng nhập
    if(*fail) {
        setColor(12);
        printf("   >> Sai tài khoản hoặc mật khẩu\n");
        setColor(7);
        *fail = 0; // Reset trạng thái thất bại sau khi hiển thị
    }else if(currentField == 2) {
        setColor(11);
        printf("   >> Đăng nhập\n");
        setColor(7);
    } else {
        printf("       Đăng nhập\n");
    }

    //Hướng dẫn
    printf("\nNhấn ▲ ▼ để di chuyển\n");
    printf("Nhấn Enter xác nhận\n");
    printf("Nhấn Esc để thoát\n");

    //Đưa con trỏ tới vị trí nhập
    if(currentField == 0) {
        gotoxy(17 + strlen(username), 9);
    }
    else {
        gotoxy(17 + strlen(password), 10);
    }
}

//Hàm kiểm tra tài khoản và mật khẩu Admin trả về 1 nếu đúng và 0 nếu sai
int checkLoginAdmin(char username[], char password[]) {

    //Tạo đường dẫn đầy đủ đến file tài khoản Admin
    char path[100];
    sprintf(path, "Data/Account/Admin/%s.txt", username);

    //Mở file
    FILE *f = fopen(path, "r");

    //Nếu file không tồn tại
    if(f == NULL) {
        return 0;
    }

    //Đọc mật khẩu dòng đầu tiên
    char filePassword[50];
    fgets(filePassword, sizeof(filePassword), f);

    //Xóa ký tự xuống dòng '\n'
    filePassword[strcspn(filePassword, "\n")] = '\0';

    //Đóng file
    fclose(f);

    //So sánh mật khẩu
    if(strcmp(password, filePassword) == 0) {
        return 1;
    }
    return 0;
}

//Hàm kiểm tra tài khoản và mật khẩu Manage trả về 1 nếu đúng và 0 nếu sai
int checkLoginManage(char username[], char password[]) {

    //Tạo đường dẫn đầy đủ đến file tài khoản Manage
    char path[100];
    sprintf(path, "Data/Account/Manage/%s.txt", username);

    //Mở file
    FILE *f = fopen(path, "r");

    //Nếu file không tồn tại
    if(f == NULL) {
        return 0;
    }

    //Đọc mật khẩu dòng đầu tiên
    char filePassword[50];
    fgets(filePassword, sizeof(filePassword), f);

    //Xóa ký tự xuống dòng '\n'
    filePassword[strcspn(filePassword, "\n")] = '\0';

    //Đóng file
    fclose(f);

    //So sánh mật khẩu
    if(strcmp(password, filePassword) == 0) {
        return 1;
    }
    return 0;
}

//Hàm kiểm tra tài khoản và mật khẩu Resident trả về 1 nếu đúng và 0 nếu sai
int checkLoginResident(char username[], char password[]) {
    char path[256];
    char floorPath[256];
    char roomPath[256];
    char filePath[256];
    char storedPass[50];

    //Duyệt Floor1 -> Floor5
    for (int floor = 1; floor <= 5; floor++) {
        sprintf(floorPath, "FloorList/Floor%d", floor);

        //Duyệt P101 -> P110
        for (int room = 1; room <= 10; room++) {
            int roomNumber = floor * 100 + room;
            sprintf(roomPath, "%s/P%d", floorPath, roomNumber);

            //File username.txt
            sprintf(filePath, "%s/%s.txt", roomPath, username);

            FILE *f = fopen(filePath, "r");
            if (f != NULL) {
                //Đọc mật khẩu dòng đầu
                if (fgets(storedPass, sizeof(storedPass), f) != NULL) {
                    //xoá \n nếu có
                    storedPass[strcspn(storedPass, "\n")] = '\0';

                    fclose(f);

                    //So sánh mật khẩu
                    if (strcmp(storedPass, password) == 0) {
                        return 1;
                    } else {
                        return 0;
                    }
                }

                fclose(f);
            }
        }
    }

    return 0;
}

//Hàm đăng nhập
void login(int select) {
    
    char path[256];
    char username[50] = "", password[50] = "";
    int usernameLength = 0, passwordLength = 0;
    int currentField = 0, key;
    int fail = 0;

    //Đặt con trỏ mặc định tại chỗ nhập tài khoản
    gotoxy(17, 8);

    //Dùng vòng lặp để đăng nhập
    while (1) {

        //Làm sạch màn hình
        system("cls");

        //Vẽ giao diện theo lựa chọn đăng nhập
        switch (select) {
            case 0:
                printAdminBanner();
                break;
            case 1:
                printManageBanner();
                break;
            case 2:
                printResidentBanner();
                break;
        }

        //In form đăng nhập
        printLoginForm(username, password, currentField, &fail);

        //Điều hướng mũi tên
        key = getch();

        if (key == 224) {
            key = getch();

            //Lên
            if (key == KEY_UP) {
                currentField--;
                if (currentField < 0) {
                    currentField = 2;
                }
            }
            //Xuống
            else if (key == KEY_DOWN) {
                currentField++;
                if (currentField > 2) {
                    currentField = 0;
                }
            }
        }

        //Enter để hoàn tất
        else if(key == ENTER) {

            //Nếu đang chọn đăng nhập
            if(currentField == 2) {

                //Nếu đã nhập đủ
                if(strlen(username) > 0 && strlen(password) > 7) {

                    //Kiểm tra mật khẩu theo giao diện đăng nhập
                    switch (select) {
                        case 0:
                            //Đúng tài khoản và mật khẩu
                            if (checkLoginAdmin(username, password) == 1) {
                                //Tạo path để lưu lịch sử đăng nhập
                                sprintf(path, "Admin with the name '%s' has successfully logged in.", username);
                                saveHistory("ADMIN", "SUCCESS", "LOGIN", path);

                                //Chuyển sang các tính năng của admin
                                AdminLogin(username);
                                return;
                            } 
                            //Nếu sai tài khoản hoặc mật khẩu
                            else {
                                //Tạo path để lưu lịch sử đăng nhập
                                sprintf(path, "The Admin with the name '%s' attempted to log in with the password '%s'.", username, password);
                                saveHistory("ADMIN", "ERROR", "LOGIN", path);

                                //In thông báo đăng nhập thất bại
                                fail = 1;
                            } 
                            break;
                        case 1:
                            //Đúng tài khoản và mật khẩu
                            if (checkLoginManage(username, password) == 1) {
                                //Tạo path để lưu lịch sử đăng nhập
                                sprintf(path, "Manage with the name '%s' has successfully logged in.", username);
                                saveHistory("MANAGE", "SUCCESS", "LOGIN", path);

                                //Chuyển sang các tính năng của quản lý
                                ManageLogin(username);
                                return;
                            }
                            //Nếu sai tài khoản hoặc mật khẩu
                            else {
                                //Tạo path để lưu lịch sử đăng nhập
                                sprintf(path, "The Manage with the name '%s' attempted to log in with the password '%s'.", username, password);
                                saveHistory("MANAGE", "ERROR", "LOGIN", path);

                                //In thông báo đăng nhập thất bại
                                fail = 1;
                            }
                            break;
                        case 2:
                            //Đúng tài khoản và mật khẩu
                            if (checkLoginResident(username, password) == 1) {
                                //Tạo path để lưu lịch sử đăng nhập
                                sprintf(path, "Resident with the name '%s' has successfully logged in.", username);
                                saveHistory("RESIDENT", "SUCCESS", "LOGIN", path);

                                //Chuyển sang các tính năng của cư dân
                                ResidentLogin(username);
                                return;
                            }
                            //Nếu sai tài khoản hoặc mật khẩu
                            else {
                                //Tạo path để lưu lịch sử đăng nhập
                                sprintf(path, "The Resident with the name '%s' attempted to log in with the password '%s'.", username, password);
                                saveHistory("RESIDENT", "ERROR", "LOGIN", path);
                                
                                //In thông báo đăng nhập thất bại
                                fail = 1;
                            }
                            break;
                    }
                }
            }
        }

        //Backspace để xóa từ ký tự
        else if(key == BACKSPACE) {

            // Xóa tài khoản
            if(currentField == 0 && usernameLength > 0) {

                usernameLength--;
                username[usernameLength] = '\0';
            }

            // Xóa mật khẩu
            else if(currentField == 1 && passwordLength > 0) {

                passwordLength--;
                password[passwordLength] = '\0';
            }
        } 

        //Esc
        else if(key == ESC) {
            break;
        }

        //Nhập ký tự thường
        else {

            //Nhập tài khoản
            if(currentField == 0 && usernameLength < 49) {
                username[usernameLength++] = key;
                username[usernameLength] = '\0';
            }

            //Nhập mật khẩu
            else if(currentField == 1 && passwordLength < 49) {
                password[passwordLength++] = key;
                password[passwordLength] = '\0';
            }
        }
    }
}

//Hàm hiển thị menu và điều hướng mũi tên để chọn
int menuLogin(char *items[], int size) {
    int choice = 0;
    int key;

    //Tạo vòng lặp để tạo bảng và lựa chọn
    while (1) {

        //Làm sạch màn hình
        system("cls");

        //In tiêu đề đăng nhập
        printf("\n");
        printf("██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗\n");
        printf("██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝\n");
        printf("██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗  \n");
        printf("██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝  \n");
        printf("╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗\n");
        printf(" ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝\n\n\n");

        //In các lựa chọn có thể chọn
        for (int i = 0; i < size; i++) {
            if (i == choice) {
                //Vẽ nội dung
                setColor(11);
                printf("   >> [%d]. %s\n", i + 1, items[i]);
                setColor(7);
            } else {
                //Vẽ nội dung
                printf("       [%d]. %s\n", i + 1, items[i]);
            }
        }

        //Hướng dẫn
        printf("\nNhấn ▲ ▼ để di chuyển\n");
        printf("Nhấn Enter để chọn\n");

        //Điều hướng mũi tên
        key = getch();

        if (key == 224) {
            key = getch();

            //Lên
            if (key == KEY_UP) {
                choice--;
                if (choice < 0) {
                    choice = size - 1;
                }
            }
            //Xuống
            else if (key == KEY_DOWN) {
                choice++;
                if (choice >= size) {
                    choice = 0;
                }
            }
        }

        //Enter
        else if (key == ENTER) {
            return choice;
        }
    }
}
