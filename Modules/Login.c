//Thư viện sử dụng
#include "Login.h"
#include "Utils.h"
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

//In chữ HELLO ADMIN
void helloAdmin() {
    printf("██╗  ██╗███████╗██╗     ██╗      ██████╗      █████╗ ██████╗ ███╗   ███╗██╗███╗   ██╗\n");
    printf("██║  ██║██╔════╝██║     ██║     ██╔═══██╗    ██╔══██╗██╔══██╗████╗ ████║██║████╗  ██║\n");
    printf("███████║█████╗  ██║     ██║     ██║   ██║    ███████║██║  ██║██╔████╔██║██║██╔██╗ ██║\n");
    printf("██╔══██║██╔══╝  ██║     ██║     ██║   ██║    ██╔══██║██║  ██║██║╚██╔╝██║██║██║╚██╗██║\n");
    printf("██║  ██║███████╗███████╗███████╗╚██████╔╝    ██║  ██║██████╔╝██║ ╚═╝ ██║██║██║ ╚████║\n");
    printf("╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝ ╚═════╝     ╚═╝  ╚═╝╚═════╝ ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝\n\n\n");
}

//Hàm vẽ giao diện login
void printLoginForm(char username[], char password[], int currentField) {

    /// Ô tài khoản
    if(currentField == 0) {
        setColor(11);
        printf("   >> Tài Khoản: %s\n", username);
        setColor(7);
    } else {
        printf("      Tài Khoản: %s\n", username);
    }

    /// Ô mật khẩu
    if(currentField == 1) {
        setColor(11);
        printf("   >> Mật khẩu : %s\n", password);
        setColor(7);
    } else {
        printf("      Mật khẩu : %s\n", password);
    }

    //Hướng dẫn
    printf("\nMũi tên LÊN/XUỐNG để di chuyển\n");

    //Đưa con trỏ tới vị trí nhập
    if(currentField == 0) {
        gotoxy(17 + strlen(username), 9);
    }
    else {
        gotoxy(17 + strlen(password), 10);
    }
}

//Hàm kiểm tra tài khoản và mật khẩu trả về 1 nếu đúng và 0 nếu sai
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

//Đăng nhập với tư cách Admin
void loginAdmin() {
    
    char username[50] = "", password[50] = "";
    int usernameLength = 0, passwordLength = 0;
    int currentField = 0, key;

    //Đặt con trỏ mặc định tại chỗ nhập tài khoản
    gotoxy(17, 8);

    //Dùng vòng lặp để đăng nhập
    while (1) {

        //Làm sạch màn hình
        system("cls");

        //Vẽ giao diện
        printAdminBanner();

        //In form đăng nhập
        printLoginForm(username, password, currentField);

        //Điều hướng mũi tên
        key = getch();

        if (key == 224) {
            key = getch();

            //Lên
            if (key == KEY_UP) {
                currentField--;
                if (currentField < 0) {
                    currentField = 1;
                }
            }
            //Xuống
            else if (key == KEY_DOWN) {
                currentField++;
                if (currentField > 1) {
                    currentField = 0;
                }
            }
        }

        //Enter để hoàn tất
        else if(key == ENTER) {
            // Nếu đã nhập đủ
            if(strlen(username) > 0 && strlen(password) > 7) {

                //Nếu đúng tài khoản và mật khẩu
                if (checkLoginAdmin(username, password) == 1) {

                    //Tạo path để lưu lịch sử đăng nhập
                    char path[256];
                    sprintf(path, "Admin with the name '%s' has successfully logged in.", username);
                    saveHistory("ADMIN", "SUCCESS", "LOGIN", path);
                    printf("        Đăng nhập thành công");
                    scanf("%s", &username);
                } 

                //Nếu sai tài khoản và mật khẩu
                else {

                    //Tạo path để lưu lịch sử đăng nhập
                    char path[256];
                    sprintf(path, "The user with the name '%s' attempted to log in with the password '%s'.", username, password);
                    saveHistory("ADMIN", "ERROR", "LOGIN", path);

                    printf("        Sai tài khoản hoặc mật khẩu");
                    scanf("%s", &username);
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
    int width = 57;

    //Tạo vòng lặp để tạo bảng và lựa chọn
    while (1) {

        //Làm sạch màn hình
        system("cls");

        //In tiêu đề đăng nhập
        printf("+-------------------------------------------------------+\n");
        printf("|                  CHỌN LOẠI TÀI KHOẢN                  |\n");
        printf("+-------------------------------------------------------+\n");

        //In các lựa chọn có thể chọn
        for (int i = 0; i < size; i++) {

            //Đếm số từ trong nội dung in
            int count = utf8len (items[i]);
            if (i == choice) {

                //Vẽ nội dung
                printf("|");
                setColor(11);
                printf("   >> [%d]. %s", i + 1, items[i]);
                setColor(7);

                //Vẽ khoảng trắng và | ở cuối hàng
                for (int i = 0; i < width - count - 13; i++) {
                    printf(" ");
                }
                printf("|\n");
            } else {

                //Vẽ nội dung
                printf("|      [%d]. %s", i + 1, items[i]);

                //Vẽ khoảng trắng và | ở cuối hàng
                for (int i = 0; i < width - count - 13; i++) {
                    printf(" ");
                }
                printf("|\n");
            }
        }

        //In cuối bảng
        printf("+-------------------------------------------------------+\n\n");

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
