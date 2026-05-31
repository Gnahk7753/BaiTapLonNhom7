//Thư viện
#include "Manage.h"
#include "Utils.h"
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

#define KEY_UP    72
#define KEY_DOWN  80
#define BACKSPACE  8
#define ENTER     13
#define ESC       27

typedef struct Manage {
    char username[50];
    char password[50];
    char name[50];
    char CCCD[20];
    char year[10];
    char gender[10];
    char province[50];
    char phone[20];
} Manage;

/*
    Hiển thị thông tin tài khoản quản lý
                                          */
void printManageInfo(Manage manage) {

    //Làm sạch màn hình
    system("cls");

    //In chữ INFORMATION
    printf("\n");
    printf("██╗███╗   ██╗███████╗ ██████╗ ██████╗ ███╗   ███╗ █████╗ ████████╗██╗ ██████╗ ███╗   ██╗\n");
    printf("██║████╗  ██║██╔════╝██╔═══██╗██╔══██╗████╗ ████║██╔══██╗╚══██╔══╝██║██╔═══██╗████╗  ██║\n");
    printf("██║██╔██╗ ██║█████╗  ██║   ██║██████╔╝██╔████╔██║███████║   ██║   ██║██║   ██║██╔██╗ ██║\n");
    printf("██║██║╚██╗██║██╔══╝  ██║   ██║██╔══██╗██║╚██╔╝██║██╔══██║   ██║   ██║██║   ██║██║╚██╗██║\n");
    printf("██║██║ ╚████║██║     ╚██████╔╝██║  ██║██║ ╚═╝ ██║██║  ██║   ██║   ██║╚██████╔╝██║ ╚████║\n");
    printf("╚═╝╚═╝  ╚═══╝╚═╝      ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝\n\n\n");

    printf("       Username       : %s\n", manage.username);
    printf("       Tên            : %s\n", manage.name);
    printf("       CCCD           : %s\n", manage.CCCD);
    printf("       Năm sinh       : %s\n", manage.year);
    printf("       Giới tính      : %s\n", manage.gender);
    printf("       Quê quán       : %s\n", manage.province);
    printf("       Số điện thoại  : %s\n", manage.phone);

    //Nhấn enter hoặc esc để quay lại
    printf("\nNhấn Enter hoặc Esc để quay lại\n");

    //Nhận phím từ người dùng
    int key = getch();
    while (key != ENTER && key != ESC) {
        key = getch();
    }
}

/*
    Chỉnh sửa thông tin quản lý
                                 */

//Đổi username
void editManageUsername(char username[]) {

    //Khai báo biến cần thiết
    char newUsername[50] = "";
    int choice = 1;
    int key;
    int fail = 0;

    //Tạo vòng lặp
    while (1) {

        //Làm sạch màn hình
        system("cls");

        //In chữ EDIT USERNAME
        printf("\n");
        printf("███████╗██████╗ ██╗████████╗    ██╗   ██╗███████╗███████╗██████╗ ███╗   ██╗ █████╗ ███╗   ███╗███████╗\n");
        printf("██╔════╝██╔══██╗██║╚══██╔══╝    ██║   ██║██╔════╝██╔════╝██╔══██╗████╗  ██║██╔══██╗████╗ ████║██╔════╝\n");
        printf("█████╗  ██║  ██║██║   ██║       ██║   ██║███████╗█████╗  ██████╔╝██╔██╗ ██║███████║██╔████╔██║█████╗  \n");
        printf("██╔══╝  ██║  ██║██║   ██║       ██║   ██║╚════██║██╔══╝  ██╔══██╗██║╚██╗██║██╔══██║██║╚██╔╝██║██╔══╝  \n");
        printf("███████╗██████╔╝██║   ██║       ╚██████╔╝███████║███████╗██║  ██║██║ ╚████║██║  ██║██║ ╚═╝ ██║███████╗\n");
        printf("╚══════╝╚═════╝ ╚═╝   ╚═╝        ╚═════╝ ╚══════╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝\n\n\n");

        //In chỗ nhập username mới
        if (choice == 1) {
            setColor(11);
            printf("   >> Nhập Username mới: %s\n", newUsername);
            setColor(7);
        } else {
            printf("       Nhập Username mới: %s\n", newUsername);
        }

        //In chỗ xác nhận
        if (fail == 1) {
            setColor(12);
            printf("   >> [Fail]. Username không hợp lệ\n");
            setColor(7);
            fail = 0;
        } else if (fail == 2) {
            setColor(12);
            printf("   >> [Fail]. Username đã tồn tại\n");
            setColor(7);
            fail = 0;
        } else if (choice == 2) {
            setColor(11);
            printf("   >> Xác nhận\n");
            setColor(7);
        } else {
            printf("       Xác nhận\n");
        }

        //In hướng dẫn
        printf("\nNhấn ▲ ▼ để di chuyển\n");
        printf("Nhấn Enter xác nhận\n");
        printf("Nhấn Esc để thoát\n");

        //Di chuyển con trỏ đến vị trí nhập username
        gotoxy(24 + strlen(newUsername) + 1, 9);

        //Nhận phím
        key = getch();

        //Điều hướng mũi tên
        if (key == 224) {
            key = getch();

            //Lên
            if (key == KEY_UP) {
                choice--;
                if (choice < 1) {
                    choice = 2;
                }
            }
            //Xuống
            else if (key == KEY_DOWN) {
                choice++;
                if (choice > 2) {
                    choice = 1;
                }
            }
        }

        //Esc để thoát
        else if (key == ESC) {
            return;
        }

        //Backspace để xóa ký tự
        else if (key == BACKSPACE) {
            if (choice == 1 && strlen(newUsername) > 0) {
                newUsername[strlen(newUsername) - 1] = '\0';
            }
        }

        //Enter để xác nhận
        else if (key == ENTER) {

            //Nếu đang chọn xác nhận
            if (choice == 2) {

                if (checkUsername(newUsername) == 0 || strlen(newUsername) < 3) {
                    //In thông báo username không hợp lệ
                    fail = 1;
                    continue;
                }

                //Tạo path đầy đủ
                char oldPath[100];
                char newPath[100];

                sprintf(oldPath, "Data/Account/Manage/%s.txt", username);
                sprintf(newPath, "Data/Account/Manage/%s.txt", newUsername);

                if (checkDuplicateUsername(newUsername, newPath) == 1) {
                    //In thông báo username đã tồn tại
                    fail = 2;
                    continue;
                }

                //Rename username
                if (rename(oldPath, newPath) == 0) {

                    //In thông báo đổi username thành công
                    setColor(10);
                    printf("\n       Đổi Username thành công!\n");
                    setColor(7);
                    printf("\nNhấn Enter hoặc Esc để thoát\n                                       \n                                   ");

                    //Lưu lịch sử
                    char history[256];
                    sprintf(history, "Quản lý '%s' đã đổi username của bản thân thành '%s'.", username, newUsername);
                    saveHistory("QUẢN LÝ", "THÀNH CÔNG", "Đổi username", history);

                    strcpy(username, newUsername);
                } else {

                    //In thông báo đổi username thất bại
                    setColor(12);
                    printf("\n       Đổi Username thất bại!\n");
                    setColor(7);
                    printf("\nNhấn Enter hoặc Esc để thoát\n                                       \n                                   ");

                    //Lưu lịch sử
                    char history[256];
                    sprintf(history, "Quản lý '%s' đã cố gắn đổi username của bản thân thành '%s'.", username, newUsername);
                    saveHistory("QUẢN LÝ", "THẤT BẠI", "Đổi username", history);
                }

                //Đợi người dùng nhấn Enter hoặc Esc
                while (1) {
                    key = getch();
                    if (key == ENTER || key == ESC) {
                        return;
                    }
                }
            }
        }

        //Nhập ký tự thường
        else {
            if (choice == 1 && strlen(newUsername) < 49) {

                //Chỉ nhận chữ và số
                if (
                    (key >= 'a' && key <= 'z') ||
                    (key >= 'A' && key <= 'Z') ||
                    (key >= '0' && key <= '9')
                ) {
                    int len = strlen(newUsername);
                    newUsername[len] = (char)key;
                    newUsername[len + 1] = '\0';
                }
            }
        }
    }
}

//Đổi tên
void editManageName(Manage *manage) {

    //Khai báo biến cần thiết
    char newName[50] = "";
    int choice = 1;
    int key;
    int fail = 0;

    //Tạo vòng lặp
    while (1) {

        //Làm sạch màn hình
        system("cls");

        //In chữ CHANGE NAME
        printf("\n");
        printf(" ██████╗██╗  ██╗ █████╗ ███╗   ██╗ ██████╗ ███████╗    ███╗   ██╗ █████╗ ███╗   ███╗███████╗\n");
        printf("██╔════╝██║  ██║██╔══██╗████╗  ██║██╔════╝ ██╔════╝    ████╗  ██║██╔══██╗████╗ ████║██╔════╝\n");
        printf("██║     ███████║███████║██╔██╗ ██║██║  ███╗█████╗      ██╔██╗ ██║███████║██╔████╔██║█████╗  \n");
        printf("██║     ██╔══██║██╔══██║██║╚██╗██║██║   ██║██╔══╝      ██║╚██╗██║██╔══██║██║╚██╔╝██║██╔══╝  \n");
        printf("╚██████╗██║  ██║██║  ██║██║ ╚████║╚██████╔╝███████╗    ██║ ╚████║██║  ██║██║ ╚═╝ ██║███████╗\n");
        printf(" ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝ ╚═════╝ ╚══════╝    ╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝\n\n\n");

        //In chỗ nhập tên
        if (choice == 1) {
            setColor(11);
            printf("   >> Nhập tên mới: %s\n", newName);
            setColor(7);
        } else {
            printf("       Nhập tên mới: %s\n", newName);
        }

        //In chỗ xác nhận
        if (fail) {
            setColor(12);
            printf("   >> Tên không hợp lệ\n");
            setColor(7);
            fail = 0;
        } else if (choice == 2) {
            setColor(11);
            printf("   >> Xác nhận\n");
            setColor(7);
        } else {
            printf("       Xác nhận\n");
        }

        //In hướng dẫn
        printf("\nNhấn ▲ ▼ để di chuyển\n");
        printf("Nhấn Enter xác nhận\n");
        printf("Nhấn Esc để thoát\n");

        //Di chuyển con trỏ đến vị trí nhập tên
        gotoxy(20 + strlen(newName), 9);

        //Nhận phím
        key = getch();

        //Điều hướng mũi tên
        if (key == 224) {
            key = getch();

            //Lên
            if (key == KEY_UP) {
                choice--;
                if (choice < 1) {
                    choice = 2;
                }
            }
            //Xuống
            else if (key == KEY_DOWN) {
                choice++;
                if (choice > 2) {
                    choice = 1;
                }
            }
        }

        //Esc để thoát
        else if (key == ESC) {
            return;
        }

        //Backspace để xóa ký tự
        else if (key == BACKSPACE) {
            if (choice == 1 && strlen(newName) > 0) {
                newName[strlen(newName) - 1] = '\0';
            }
        }

        //Enter để xác nhận
        else if (key == ENTER) {

            //Nếu đang chọn xác nhận
            if (choice == 2) {

                if (isOnlyLetter(newName) == 0 || strlen(newName) == 0) {
                    fail = 1;
                    continue;
                }

                //Lưu tên cũ
                char oldName[50];
                strncpy(oldName, manage->name, sizeof(oldName) - 1);             oldName[sizeof(oldName) - 1] = '\0';

                //Cập nhật tên mới vào struct manage
                strncpy(manage->name, newName, sizeof(manage->name) - 1);
                manage->name[sizeof(manage->name) - 1] = '\0';

                //Cập nhật tên mới vào file
                char path[256];
                sprintf(path, "Data/Account/Manage/%s.txt", manage->username);
                FILE *f = fopen(path, "w");
                if (f != NULL) {

                    //Ghi lại toàn bộ thông tin cá nhân vào file với tên mới
                    fprintf(f, "%s\n", manage->password);
                    fprintf(f, "%s\n", manage->name);
                    fprintf(f, "%s\n", manage->CCCD);
                    fprintf(f, "%s\n", manage->year);
                    fprintf(f, "%s\n", manage->gender);
                    fprintf(f, "%s\n", manage->province);
                    fprintf(f, "%s\n", manage->phone);
                    fclose(f);

                    //In thông báo đổi tên thành công
                    setColor(10);
                    printf("\n       Đổi tên thành công!\n");
                    setColor(7);
                    printf("\nNhấn Enter hoặc Esc để thoát\n                                       \n                                   ");

                    //Lưu lịch sử
                    char history[256];
                    sprintf(history, "Quản lý '%s' đã đổi tên bản thân từ '%s' thành '%s'", manage->username, oldName, manage->name);
                    saveHistory("QUẢN LÝ", "THÀNH CÔNG", "Đổi tên", history);
                } else {

                    //In thông báo đổi username thất bại
                    setColor(12);
                    printf("\n       Đổi tên thất bại!\n");
                    setColor(7);
                    printf("\nNhấn Enter hoặc Esc để thoát\n                                       \n                                   ");

                    //Lưu lịch sử
                    char history[256];
                    sprintf(history, "Quản lý '%s' đã cố gắn đổi tên bản thân từ '%s' thành '%s'.", manage->username, oldName, manage->name);
                    saveHistory("QUẢN LÝ", "THẤT BẠI", "Đổi tên", history); 
                }

                //Đợi người dùng nhấn Enter hoặc Esc
                while (1) {
                    key = getch();
                    if (key == ENTER || key == ESC) {
                        return;
                    }
                }
            }
        }

        //Nhập ký tự thường
        else {
            int len = strlen(newName);
            newName[len] = (char)key;
            newName[len + 1] = '\0';
        }
    }
}

//Đổi mật khẩu
void editManagePassword(Manage *manage) {

    //Khai báo biến cần thiết
    char oldPassword[50] = "";
    char newPassword[50] = "";
    int choice = 1;
    int key;
    int fail = 0;

    //Tạo vòng lặp
    while (1) {

        //Làm sạch màn hình
        system("cls");

        //In chữ CHANGE PASSWORD
        printf("\n");
        printf(" ██████╗██╗  ██╗ █████╗ ███╗   ██╗ ██████╗ ███████╗    ██████╗  █████╗ ███████╗███████╗██╗    ██╗ ██████╗ ██████╗ ██████╗ \n");
        printf("██╔════╝██║  ██║██╔══██╗████╗  ██║██╔════╝ ██╔════╝    ██╔══██╗██╔══██╗██╔════╝██╔════╝██║    ██║██╔═══██╗██╔══██╗██╔══██╗\n");
        printf("██║     ███████║███████║██╔██╗ ██║██║  ███╗█████╗      ██████╔╝███████║███████╗███████╗██║ █╗ ██║██║   ██║██████╔╝██║  ██║\n");
        printf("██║     ██╔══██║██╔══██║██║╚██╗██║██║   ██║██╔══╝      ██╔═══╝ ██╔══██║╚════██║╚════██║██║███╗██║██║   ██║██╔══██╗██║  ██║\n");
        printf("╚██████╗██║  ██║██║  ██║██║ ╚████║╚██████╔╝███████╗    ██║     ██║  ██║███████║███████║╚███╔███╔╝╚██████╔╝██║  ██║██████╔╝\n");
        printf(" ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝ ╚═════╝ ╚══════╝    ╚═╝     ╚═╝  ╚═╝╚══════╝╚══════╝ ╚══╝╚══╝  ╚═════╝ ╚═╝  ╚═╝╚═════╝ \n\n\n");

        //In chỗ nhập mật khẩu cũ
        if (choice == 1) {
            setColor(11);
            printf("   >> Nhập mật khẩu cũ: ");
            for (int i = 0; i < (int)strlen(oldPassword); i++) {
                printf("*");
            }
            printf("\n");
            setColor(7);
        } else {
            printf("       Nhập mật khẩu cũ: ");
            for (int i = 0; i < (int)strlen(oldPassword); i++) {
                printf("*");
            }
            printf("\n");
        }

        //In chỗ nhập mật khẩu mới
        if (choice == 2) {
            setColor(11);
            printf("   >> Nhập mật khẩu mới: ");
            for (int i = 0; i < (int)strlen(newPassword); i++) {
                printf("*");
            }
            printf("\n");
            setColor(7);
        } else {
            printf("       Nhập mật khẩu mới: ");
            for (int i = 0; i < (int)strlen(newPassword); i++) {
                printf("*");
            }
            printf("\n");
        }

        //In chỗ xác nhận
        if (fail == 1) {
            setColor(12);
            printf("   >> [Fail]. Mật khẩu mới không hợp lệ\n");
            setColor(7);
            fail = 0;
        } else if (fail == 2) {
            setColor(12);
            printf("   >> [Fail]. Mật khẩu cũ không đúng\n");
            setColor(7);
            fail = 0;
        } else if (choice == 3) {
            setColor(11);
            printf("   >> Xác nhận\n");
            setColor(7);
        } else {
            printf("       Xác nhận\n");
        }

        //In hướng dẫn
        printf("\nNhấn ▲ ▼ để di chuyển\n");
        printf("Nhấn Enter xác nhận\n");
        printf("Nhấn Esc để thoát\n");

        //Di chuyển con trỏ
        if (choice == 1) {
            gotoxy(23 + strlen(oldPassword) + 1, 9);
        } else if (choice == 2) {
            gotoxy(24 + strlen(newPassword) + 1, 10);
        }

        //Nhận phím
        key = getch();

        //Điều hướng mũi tên
        if (key == 224) {
            key = getch();

            //Lên
            if (key == KEY_UP) {
                choice--;
                if (choice < 1) {
                    choice = 3;
                }
            }
            //Xuống
            else if (key == KEY_DOWN) {
                choice++;
                if (choice > 3) {
                    choice = 1;
                }
            }
        }

        //Esc để thoát
        else if (key == ESC) {
            return;
        }

        //Backspace để xóa ký tự
        else if (key == BACKSPACE) {
            if (choice == 1 && strlen(oldPassword) > 0) {
                oldPassword[strlen(oldPassword) - 1] = '\0';
            }
            else if (choice == 2 && strlen(newPassword) > 0) {
                newPassword[strlen(newPassword) - 1] = '\0';
            }
        }

        //Enter để xác nhận
        else if (key == ENTER) {

            //Nếu đang chọn xác nhận
            if (choice == 3) {

                //Kiểm tra mật khẩu mới có hợp lệ hay không
                if (checkPassword(newPassword) == 0) {
                    fail = 1;
                    continue;
                }

                //Kiểm tra mật khẩu cũ có đúng hay không
                if (strcmp(oldPassword, manage->password) != 0) {
                    fail = 2;
                    continue;
                }

                //Lưu mật khẩu cũ
                char oldPass[50];
                strncpy(oldPass, manage->password, sizeof(oldPass) - 1);                     oldPass[sizeof(oldPass) - 1] = '\0';

                //Cập nhật mật khẩu mới vào struct manage
                strncpy(manage->password, newPassword, sizeof(manage->password) - 1);
                manage->password[sizeof(manage->password) - 1] = '\0';

                //Cập nhật mật khẩu mới vào file
                char path[256];
                sprintf(path, "Data/Account/Manage/%s.txt", manage->username);
                FILE *f = fopen(path, "w");
                if (f != NULL) {

                    //Ghi lại toàn bộ thông tin cá nhân vào file với mật khẩu mới
                    fprintf(f, "%s\n", manage->password);
                    fprintf(f, "%s\n", manage->name);
                    fprintf(f, "%s\n", manage->CCCD);
                    fprintf(f, "%s\n", manage->year);
                    fprintf(f, "%s\n", manage->gender);
                    fprintf(f, "%s\n", manage->province);
                    fprintf(f, "%s\n", manage->phone);
                    fclose(f);

                    //In thông báo đổi mật khẩu thành công
                    gotoxy(0 ,11);
                    setColor(10);
                    printf("       Đổi mật khẩu thành công!\n");
                    setColor(7);
                    printf("\nNhấn Enter hoặc Esc để thoát\n                                       \n                                   ");

                    //Lưu lịch sử
                    char history[256];
                    sprintf(history, "Quản lý '%s' đã đổi mật khẩu từ '%s' thành '%s'", manage->username, oldPass, manage->password);
                    saveHistory("QUẢN LÝ", "THÀNH CÔNG", "Đổi mật khẩu", history);
                } else {

                    //In thông báo đổi mật khẩu thất bại
                    gotoxy(7, 10);
                    setColor(12);
                    printf("\n       Đổi mật khẩu thất bại!\n");
                    setColor(7);
                    printf("\nNhấn Enter hoặc Esc để thoát\n                                       \n                                   ");

                    //Lưu lịch sử
                    char history[256];
                    sprintf(history, "Quản lý '%s' đã cố gắn đổi mật khẩu bản thân từ '%s' thành '%s'.", manage->username, oldPass, manage->password);
                    saveHistory("QUẢN LÝ", "THẤT BẠI", "Đổi mật khẩu", history); 
                }
                
                //Đợi người dùng nhấn Enter hoặc Esc
                while (1) {
                    key = getch();
                    if (key == ENTER || key == ESC) {
                        return;
                    }
                }
            }
        }

        //Nhập ký tự thường
        else {
            if (choice == 1 && strlen(oldPassword) < 49) {
                int len = strlen(oldPassword);
                oldPassword[len] = key;
                oldPassword[len + 1] = '\0';
            }
            else if (choice == 2 && strlen(newPassword) < 49) {
                int len = strlen(newPassword);
                newPassword[len] = key;
                newPassword[len + 1] = '\0';
            }
        }
    }
}

//Đổi số điện thoại
void editManagePhone(Manage *manage) {

    //Khai báo biến cần thiết
    char newPhone[20] = "";
    int choice = 1;
    int key;
    int fail = 0;

    //Tạo vòng lặp
    while (1) {

        //Làm sạch màn hình
        system("cls");

        //In chữ CHANGE PHONE NUMBER
        printf("\n");
        printf(" ██████╗██╗  ██╗ █████╗ ███╗   ██╗ ██████╗ ███████╗    ██████╗ ██╗  ██╗ ██████╗ ███╗   ██╗███████╗    ███╗   ██╗██╗   ██╗███╗   ███╗██████╗ ███████╗██████╗ \n");
        printf("██╔════╝██║  ██║██╔══██╗████╗  ██║██╔════╝ ██╔════╝    ██╔══██╗██║  ██║██╔═══██╗████╗  ██║██╔════╝    ████╗  ██║██║   ██║████╗ ████║██╔══██╗██╔════╝██╔══██╗\n");
        printf("██║     ███████║███████║██╔██╗ ██║██║  ███╗█████╗      ██████╔╝███████║██║   ██║██╔██╗ ██║█████╗      ██╔██╗ ██║██║   ██║██╔████╔██║██████╔╝█████╗  ██████╔╝\n");
        printf("██║     ██╔══██║██╔══██║██║╚██╗██║██║   ██║██╔══╝      ██╔═══╝ ██╔══██║██║   ██║██║╚██╗██║██╔══╝      ██║╚██╗██║██║   ██║██║╚██╔╝██║██╔══██╗██╔══╝  ██╔══██╗\n");
        printf("╚██████╗██║  ██║██║  ██║██║ ╚████║╚██████╔╝███████╗    ██║     ██║  ██║╚██████╔╝██║ ╚████║███████╗    ██║ ╚████║╚██████╔╝██║ ╚═╝ ██║██████╔╝███████╗██║  ██║\n");
        printf(" ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝ ╚═════╝ ╚══════╝    ╚═╝     ╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝    ╚═╝  ╚═══╝ ╚═════╝ ╚═╝     ╚═╝╚═════╝ ╚══════╝╚═╝  ╚═╝\n\n\n");

        //In chỗ nhập số điện thoại mới
        if (choice == 1) {
            setColor(11);
            printf("   >> Nhập số điện thoại mới: %s\n", newPhone);
            setColor(7);
        } else {
            printf("       Nhập số điện thoại mới: %s\n", newPhone);
        }

        //In chỗ xác nhận
        if (fail) {
            setColor(12);
            printf("   >> [Fail]. Số điện thoại không hợp lệ\n");
            setColor(7);
            fail = 0;
        } else if (choice == 2) {
            setColor(11);
            printf("   >> Xác nhận\n");
            setColor(7);
        } else {
            printf("       Xác nhận\n");
        }

        //In hướng dẫn
        printf("\nNhấn ▲ ▼ để di chuyển\n");
        printf("Nhấn Enter xác nhận\n");
        printf("Nhấn Esc để thoát\n");

        //Di chuyển con trỏ đến vị trí nhập số điện thoại
        gotoxy(29 + strlen(newPhone) + 1, 9);

        //Nhận phím
        key = getch();

        //Điều hướng mũi tên
        if (key == 224) {
            key = getch();

            //Lên
            if (key == KEY_UP) {
                choice--;
                if (choice < 1) {
                    choice = 2;
                }
            }
            //Xuống
            else if (key == KEY_DOWN) {
                choice++;
                if (choice > 2) {
                    choice = 1;
                }
            }
        }

        //Esc để thoát
        else if (key == ESC) {
            return;
        }

        //Backspace để xóa ký tự
        else if (key == BACKSPACE) {
            if (choice == 1 && strlen(newPhone) > 0) {
                newPhone[strlen(newPhone) - 1] = '\0';
            }
        }

        //Enter để xác nhận
        else if (key == ENTER) {

            //Nếu đang chọn xác nhận
            if (choice == 2) {

                if (checkPhoneNumber(newPhone) == 0) {
                    //In thông báo số điện thoại không hợp lệ
                    fail = 1;
                    continue;
                }

                //Lưu số cũ
                char oldphone[50];
                strncpy(oldphone, manage->phone, sizeof(oldphone) - 1);             oldphone[sizeof(oldphone) - 1] = '\0';

                //Cập nhật số điện thoại mới vào struct manage
                strncpy(manage->phone, newPhone, sizeof(manage->phone) - 1);
                manage->phone[sizeof(manage->phone) - 1] = '\0';

                //Cập nhật số điện thoại mới vào file
                char path[256];
                sprintf(path, "Data/Account/Manage/%s.txt", manage->username);
                FILE *f = fopen(path, "w");
                if (f != NULL) {

                    //Ghi lại toàn bộ thông tin cá nhân vào file với số điện thoại mới
                    fprintf(f, "%s\n", manage->password);
                    fprintf(f, "%s\n", manage->name);
                    fprintf(f, "%s\n", manage->CCCD);
                    fprintf(f, "%s\n", manage->year);
                    fprintf(f, "%s\n", manage->gender);
                    fprintf(f, "%s\n", manage->province);
                    fprintf(f, "%s\n", manage->phone);
                    fclose(f);

                    //In thông báo đổi số điện thoại thành công
                    setColor(10);
                    printf("\n       Đổi số điện thoại thành công!\n");
                    setColor(7);
                    printf("\nNhấn Enter hoặc Esc để thoát\n                                       \n                                   ");

                    //Lưu lịch sử
                    char history[256];
                    sprintf(history, "Quản lý '%s' đã đổi số điện thoại bản thân từ '%s' thành '%s'", manage->username, oldphone, manage->phone);
                    saveHistory("QUẢN LÝ", "THÀNH CÔNG", "Đổi số điện thoại", history);
                } else {

                    //In thông báo đổi số điện thoại thất bại
                    setColor(12);
                    printf("\n       Đổi số điện thoại thất bại!\n");
                    setColor(7);
                    printf("\nNhấn Enter hoặc Esc để thoát\n                                       \n                                   ");

                    //Lưu lịch sử
                    char history[256];
                    sprintf(history, "Quản lý '%s' đã cố gắn đổi số điện thoại bản thân từ '%s' thành '%s'.", manage->username, oldphone, manage->phone);
                    saveHistory("QUẢN LÝ", "THẤT BẠI", "Đổi số điện thoại", history);  
                }

                //Đợi người dùng nhấn Enter hoặc Esc
                while (1) {
                    key = getch();
                    if (key == ENTER || key == ESC) {
                        return;
                    }
                }
            }
        }

        //Nhập ký tự thường
        else {
            if (choice == 1 && strlen(newPhone) < 19 && key >= '0' && key <= '9') {
                int len = strlen(newPhone);
                newPhone[len] = key;
                newPhone[len + 1] = '\0';
            }
        }
    }
}

/*
    Chỉnh sửa thông tin cá nhân của Manage
                                             */
void editManageSelfInfo(Manage *manage) {

    //Khai báo hàm cần thiết
    int choice = 1;
    int key;
    char *options[] = {
        "Sửa tên tài khoản",
        "Sửa tên",
        "Đổi mật khẩu",
        "Đổi số điện thoại",
        "Thoát",
    };

    //Lấy số lượng phần tử trong mảng options
    int numOptions = sizeof(options) / sizeof(options[0]);

    //Tạo vòng lặp
    while (1) {

        //Làm sạch màn hình
        system("cls");

        //In chữ EDIT INFO
        printf("\n");
        printf("███████╗██████╗ ██╗████████╗    ██╗███╗   ██╗███████╗ ██████╗ \n");
        printf("██╔════╝██╔══██╗██║╚══██╔══╝    ██║████╗  ██║██╔════╝██╔═══██╗\n");
        printf("█████╗  ██║  ██║██║   ██║       ██║██╔██╗ ██║█████╗  ██║   ██║\n");
        printf("██╔══╝  ██║  ██║██║   ██║       ██║██║╚██╗██║██╔══╝  ██║   ██║\n");
        printf("███████╗██████╔╝██║   ██║       ██║██║ ╚████║██║     ╚██████╔╝\n");
        printf("╚══════╝╚═════╝ ╚═╝   ╚═╝       ╚═╝╚═╝  ╚═══╝╚═╝      ╚═════╝ \n\n\n");

        //In nội dung lựa chọn
        for (int i = 0; i < numOptions; i++) {
            printContent(options[i], i + 1, choice);
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
                if (choice < 1) {
                    choice = numOptions;
                }
            }
            //Xuống
            else if (key == KEY_DOWN) {
                choice++;
                if (choice > numOptions) {
                    choice = 1;
                }
            }
        }

        //Enter
        else if (key == ENTER) {
            switch (choice) {
                case 1:
                    editManageUsername(manage->username);
                    break;
                case 2:
                    editManageName(manage);
                    break;
                case 3:
                    editManagePassword(manage);
                    break;
                case 4:
                    editManagePhone(manage);
                    break;
                case 5:
                    return;
            }
        }
    }
}

//Lấy thông tin Manage từ file
void getManageInfo(Manage *manage) {

    //Tạo đường dẫn đầy đủ đến file tài khoản Manage
    char path[256];
    sprintf(path, "Data/Account/Manage/%s.txt", manage->username);

    //Mở file
    FILE *f = fopen(path, "r");

    //Nếu file không tồn tại
    if (f == NULL) {
        return;
    }

    //Đọc thông tin cá nhân từ file
    fgets(manage->password, sizeof(manage->password), f);  manage->password[strcspn(manage->password, "\n")] = '\0';
    fgets(manage->name,     sizeof(manage->name),     f);  manage->name[strcspn(manage->name, "\n")]         = '\0';
    fgets(manage->CCCD,     sizeof(manage->CCCD),     f);  manage->CCCD[strcspn(manage->CCCD, "\n")]         = '\0';
    fgets(manage->year,     sizeof(manage->year),     f);  manage->year[strcspn(manage->year, "\n")]         = '\0';
    fgets(manage->gender,   sizeof(manage->gender),   f);  manage->gender[strcspn(manage->gender, "\n")]     = '\0';
    fgets(manage->province, sizeof(manage->province), f);  manage->province[strcspn(manage->province, "\n")] = '\0';
    fgets(manage->phone,    sizeof(manage->phone),    f);  manage->phone[strcspn(manage->phone, "\n")]       = '\0';

    //Đóng file
    fclose(f);
}

/*
    Tạo tài khoản cư dân
                          */
void createResidentAccount(char manage[]) {

    //Khai báo biến cần thiết
    int choice = 1;
    int key;
    int fail = 0;

    char username[50]  = "";
    char name[100]     = "";
    char password[50]  = "";
    char CCCD[20]      = "";
    char year[10]      = "";
    char gender[10]    = "";
    char province[50]  = "";
    char phone[20]     = "";
    char roomInput[10] = "";

    char *contents[] = {
        "Nhập username       : ",
        "Nhập tên thật       : ",
        "Nhập mật khẩu       : ",
        "Nhập CCCD           : ",
        "Nhập SĐT            : ",
        "Nhập phòng (VD 101) : ",
        "Xác nhận",
    };

    //Tạo vòng lặp
    while (1) {

        //Làm sạch màn hình
        system("cls");

        //In chữ CREATE RESIDENT
        printf("\n");
        printf(" ██████╗██████╗ ███████╗ █████╗ ████████╗███████╗    ██████╗ ███████╗███████╗██╗██████╗ ███████╗███╗   ██╗████████╗\n");
        printf("██╔════╝██╔══██╗██╔════╝██╔══██╗╚══██╔══╝██╔════╝    ██╔══██╗██╔════╝██╔════╝██║██╔══██╗██╔════╝████╗  ██║╚══██╔══╝\n");
        printf("██║     ██████╔╝█████╗  ███████║   ██║   █████╗      ██████╔╝█████╗  ███████╗██║██║  ██║█████╗  ██╔██╗ ██║   ██║   \n");
        printf("██║     ██╔══██╗██╔══╝  ██╔══██║   ██║   ██╔══╝      ██╔══██╗██╔══╝  ╚════██║██║██║  ██║██╔══╝  ██║╚██╗██║   ██║   \n");
        printf("╚██████╗██║  ██║███████╗██║  ██║   ██║   ███████╗    ██║  ██║███████╗███████║██║██████╔╝███████╗██║ ╚████║   ██║   \n");
        printf(" ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝    ╚═╝  ╚═╝╚══════╝╚══════╝╚═╝╚═════╝ ╚══════╝╚═╝  ╚═══╝   ╚═╝   \n\n\n");

        //In username
        if (choice == 1) {
            setColor(11);
            printf("   >> %s%s\n", contents[0], username);
            setColor(7);
        } else {
            printf("       %s%s\n", contents[0], username);
        }

        //In tên thật
        if (choice == 2) {
            setColor(11);
            printf("   >> %s%s\n", contents[1], name);
            setColor(7);
        } else {
            printf("       %s%s\n", contents[1], name);
        }

        //In mật khẩu
        if (choice == 3) {
            setColor(11);
            printf("   >> %s", contents[2]);
            for (int i = 0; i < (int)strlen(password); i++) {
                printf("*");
            }
            printf("\n");
            setColor(7);
        } else {
            printf("       %s", contents[2]);
            for (int i = 0; i < (int)strlen(password); i++) {
                printf("*");
            }
            printf("\n");
        }

        //In CCCD
        if (choice == 4) {
            setColor(11);
            printf("   >> %s%s\n", contents[3], CCCD);
            setColor(7);
        } else {
            printf("       %s%s\n", contents[3], CCCD);
        }

        //In số điện thoại
        if (choice == 5) {
            setColor(11);
            printf("   >> %s%s\n", contents[4], phone);
            setColor(7);
        } else {
            printf("       %s%s\n", contents[4], phone);
        }

        //In phòng
        if (choice == 6) {
            setColor(11);
            printf("   >> %s%s\n", contents[5], roomInput);
            setColor(7);
        } else {
            printf("       %s%s\n", contents[5], roomInput);
        }

        //In xác nhận
        if (fail == 1) {
            setColor(12);
            printf("   >> [Fail]. Username không hợp lệ\n");
            setColor(7);
            fail = 0;
        }
        else if (fail == 2) {
            setColor(12);
            printf("   >> [Fail]. Username đã tồn tại\n");
            setColor(7);
            fail = 0;
        }
        else if (fail == 3) {
            setColor(12);
            printf("   >> [Fail]. Tên không hợp lệ\n");
            setColor(7);
            fail = 0;
        }
        else if (fail == 4) {
            setColor(12);
            printf("   >> [Fail]. Mật khẩu không hợp lệ\n");
            setColor(7);
            fail = 0;
        }
        else if (fail == 5) {
            setColor(12);
            printf("   >> [Fail]. CCCD không hợp lệ\n");
            setColor(7);
            fail = 0;
        }
        else if (fail == 6) {
            setColor(12);
            printf("   >> [Fail]. Số điện thoại không hợp lệ\n");
            setColor(7);
            fail = 0;
        }
        else if (fail == 7) {
            setColor(12);
            printf("   >> [Fail]. Phòng không hợp lệ (VD: 101)\n");
            setColor(7);
            fail = 0;
        } else if (choice == 7) {
            setColor(11);
            printf("   >> %s\n", contents[6]);
            setColor(7);
        } else {
            printf("       %s\n", contents[6]);
        }

        //In hướng dẫn
        printf("\nNhấn ▲ ▼ để di chuyển\n");
        printf("Nhấn Enter xác nhận\n");
        printf("Nhấn Esc để thoát\n");

        //Di chuyển con trỏ
        if (choice == 1) {
            gotoxy(28 + strlen(username),  9);
        }
        else if (choice == 2) {
            gotoxy(28 + strlen(name),      10);
        }
        else if (choice == 3) {
            gotoxy(28 + strlen(password),  11);
        }
        else if (choice == 4) {
            gotoxy(28 + strlen(CCCD),      12);
        }
        else if (choice == 5) {
            gotoxy(28 + strlen(phone),     13);
        }
        else if (choice == 6) {
            gotoxy(28 + strlen(roomInput), 14);
        }

        //Nhận phím
        key = getch();

        //Điều hướng mũi tên
        if (key == 224) {
            key = getch();

            //Lên
            if (key == KEY_UP) {
                choice--;
                if (choice < 1) {
                    choice = 7;
                }
            }
            //Xuống
            else if (key == KEY_DOWN) {
                choice++;
                if (choice > 7) {
                    choice = 1;
                }
            }
        }

        //Esc để thoát
        else if (key == ESC) {
            return;
        }

        //Backspace
        else if (key == BACKSPACE) {

            //Username
            if (choice == 1 && strlen(username) > 0) {
                username[strlen(username) - 1] = '\0';
            }

            //Tên
            else if (choice == 2 && strlen(name) > 0) {
                name[strlen(name) - 1] = '\0';
            }

            //Mật khẩu
            else if (choice == 3 && strlen(password) > 0) {
                password[strlen(password) - 1] = '\0';
            }

            //CCCD
            else if (choice == 4 && strlen(CCCD) > 0) {
                CCCD[strlen(CCCD) - 1] = '\0';
                strcpy(year, "");
                strcpy(gender, "");
                strcpy(province, "");
            }

            //Số điện thoại
            else if (choice == 5 && strlen(phone) > 0) {
                phone[strlen(phone) - 1] = '\0';
            }

            //Phòng
            else if (choice == 6 && strlen(roomInput) > 0) {
                roomInput[strlen(roomInput) - 1] = '\0';
            }
        }

        //Enter
        else if (key == ENTER) {

            //Nếu đang chọn xác nhận
            if (choice == 7) {

                //Kiểm tra username
                if(checkUsername(username) == 0 || strlen(username) < 3) {
                    fail = 1;
                    continue;
                }

                if(checkDuplicateUsernameForResident(username)) {
                    fail = 2;
                    continue;
                }

                //Kiểm tra tên
                if (strlen(name) == 0) {
                    fail = 3;
                    continue;
                }

                //Kiểm tra mật khẩu
                if (checkPassword(password) == 0) {
                    fail = 4;
                    continue;
                }

                //Kiểm tra CCCD (có thể không có)
                if(strlen(CCCD) != 0) {
                    if(checkCCCD(year, province, CCCD, gender) == 0) {
                        fail = 5;
                        continue;
                    }
                }

                //Kiểm tra số điện thoại (có thể không có)
                if(strlen(phone) != 0) {
                    if(checkPhoneNumber(phone) == 0) {
                        fail = 6;
                        continue;
                    }
                }

                //Kiểm tra phòng
                if (strlen(roomInput) != 3 || !isAllDigits(roomInput)) {
                    fail = 7;
                    continue;
                }
                int floor = roomInput[0] - '0';
                int room  = atoi(roomInput + 1);
                if (floor < 1 || floor > 5 || room < 1 || room > 5) {
                    fail = 7;
                    continue;
                }

                //Tạo path thư mục phòng
                char folderPath[256];
                sprintf(folderPath, "FloorList/Floor%d/P%d%02d", floor, floor, room);

                //Tạo thư mục nếu chưa có
                CreateDirectoryA(folderPath, NULL);

                //Kiểm tra username đã tồn tại trong phòng
                char filePath[300];
                sprintf(filePath, "%s/%s.txt", folderPath, username);
                if (checkDuplicateUsernameForResident(username) == 1) {
                    fail = 2;
                    continue;
                }

                //Tạo file
                FILE *f = fopen(filePath, "w");
                if (f != NULL) {

                    //Ghi thông tin vào file
                    fprintf(f, "%s\n", password);
                    fprintf(f, "%s\n", name);
                    fprintf(f, "%s\n", CCCD);
                    fprintf(f, "%s\n", year);
                    fprintf(f, "%s\n", gender);
                    fprintf(f, "%s\n", province);
                    fprintf(f, "%s\n", phone);
                    fclose(f);

                    //Thông báo thành công
                    gotoxy(0, 15);
                    setColor(10);
                    printf("       Tạo tài khoản cư dân thành công! (Phòng P%d%02d)\n", floor, room);
                    setColor(7);
                    printf("\nNhấn Enter hoặc Esc để thoát\n                                       \n                                   ");

                    //Lưu lịch sử
                    char history[256];
                    sprintf(history, "Quản lý '%s' đã tạo tài khoản cho cư dân với username là '%s' ở phòng P%d%02d.", manage, username, floor, room);
                    saveHistory("QUẢN LÝ", "THÀNH CÔNG", "Tạo tài khoản", history);  
                } else {

                    //Thông báo thất bại
                    gotoxy(0, 15);
                    setColor(12);
                    printf("\n       Tạo tài khoản thất bại!\n");
                    setColor(7);
                    printf("\nNhấn Enter hoặc Esc để thoát\n                                       \n                                   ");

                    //Lưu lịch sử
                    char history[256];
                    sprintf(history, "Quản lý '%s' đã cố gắn tạo tài khoản cho cư dân với username là '%s' ở phòng P%d%02d.", manage, username, floor, room);
                    saveHistory("QUẢN LÝ", "THẤT BẠI", "Tạo tài khoản", history);    
                }
                
                //Đợi người dùng thoát
                while (1) {
                    key = getch();
                    if (key == ENTER || key == ESC) {
                        return;
                    }
                }
            }
        }

        //Nhập ký tự thường
        else {

            //Username
            if (choice == 1 && strlen(username) < 49) {
                if (
                    (key >= 'a' && key <= 'z') ||
                    (key >= 'A' && key <= 'Z') ||
                    (key >= '0' && key <= '9')
                ) {
                    int len = strlen(username);
                    username[len] = key;
                    username[len + 1] = '\0';
                }
            }

            //Tên thật
            else if (choice == 2 && strlen(name) < 99) {
                int len = strlen(name);
                name[len] = (char)key;
                name[len + 1] = '\0';
            }

            //Mật khẩu
            else if (choice == 3 && strlen(password) < 49) {
                if (key >= 32 && key <= 126) {
                    int len = strlen(password);
                    password[len] = key;
                    password[len + 1] = '\0';
                }
            }

            //CCCD
            else if (choice == 4 && strlen(CCCD) < 19) {
                if (key >= '0' && key <= '9') {
                    int len = strlen(CCCD);
                    CCCD[len] = key;
                    CCCD[len + 1] = '\0';
                    if (strlen(CCCD) == 12) {
                        checkCCCD(year, province, CCCD, gender);
                    }
                }
            }

            //Số điện thoại
            else if (choice == 5 && strlen(phone) < 19) {
                if (key >= '0' && key <= '9') {
                    int len = strlen(phone);
                    phone[len] = key;
                    phone[len + 1] = '\0';
                }
            }

            //Phòng
            else if (choice == 6 && strlen(roomInput) < 9) {
                if (key >= '0' && key <= '9') {
                    int len = strlen(roomInput);
                    roomInput[len] = key;
                    roomInput[len + 1] = '\0';
                }
            }
        }
    }
}

//Tìm đường dẫn file cư dân theo username
int findResidentPath(char *targetUsername, char *outPath) {

    DIR *dir;
    struct dirent *entry;

    //Duyệt từng tầng
    for (int floor = 1; floor <= 5; floor++) {

        //Duyệt từng phòng
        for (int room = 1; room <= 5; room++) {

            //Tạo đường dẫn thư mục phòng
            char folderPath[256];
            sprintf(folderPath, "FloorList/Floor%d/P%d%02d", floor, floor, room);

            //Mở thư mục
            dir = opendir(folderPath);
            if (!dir) continue;

            //Đọc từng file
            while ((entry = readdir(dir)) != NULL) {

                //Bỏ qua file ẩn
                if (entry->d_name[0] == '.') continue;

                //Bỏ qua file không phải .txt
                if (!strstr(entry->d_name, ".txt")) continue;

                //Lấy username từ tên file
                char uname[50] = "";
                strncpy(uname, entry->d_name, strlen(entry->d_name) - 4);
                uname[strlen(entry->d_name) - 4] = '\0';

                //So sánh username
                if (strcmp(uname, targetUsername) == 0) {
                    sprintf(outPath, "%s/%s.txt", folderPath, targetUsername);
                    closedir(dir);
                    return 1;
                }
            }

            closedir(dir);
        }
    }

    //Không tìm thấy
    return 0;
}

/*
    Chỉnh sửa thông tin tài khoản cư dân
                                           */
void editResidentInfo(char manage[]) {

    //Khai báo biến cần thiết
    char searchUsername[50] = "";
    int choice = 1;
    int key;
    int fail = 0;

    //Tạo vòng lặp
    while (1) {

        //Làm sạch màn hình
        system("cls");

        //In chữ EDIT RESIDENT
        printf("\n");
        printf("███████╗██████╗ ██╗████████╗    ██████╗ ███████╗███████╗██╗██████╗ ███████╗███╗   ██╗████████╗\n");
        printf("██╔════╝██╔══██╗██║╚══██╔══╝    ██╔══██╗██╔════╝██╔════╝██║██╔══██╗██╔════╝████╗  ██║╚══██╔══╝\n");
        printf("█████╗  ██║  ██║██║   ██║       ██████╔╝█████╗  ███████╗██║██║  ██║█████╗  ██╔██╗ ██║   ██║   \n");
        printf("██╔══╝  ██║  ██║██║   ██║       ██╔══██╗██╔══╝  ╚════██║██║██║  ██║██╔══╝  ██║╚██╗██║   ██║   \n");
        printf("███████╗██████╔╝██║   ██║       ██║  ██║███████╗███████║██║██████╔╝███████╗██║ ╚████║   ██║   \n");
        printf("╚══════╝╚═════╝ ╚═╝   ╚═╝       ╚═╝  ╚═╝╚══════╝╚══════╝╚═╝╚═════╝ ╚══════╝╚═╝  ╚═══╝   ╚═╝   \n\n\n");

        //In ô nhập username
        if (choice == 1) {
            setColor(11);
            printf("   >> Nhập username cư dân: %s\n", searchUsername);
            setColor(7);
        } else {
            printf("       Nhập username cư dân: %s\n", searchUsername);
        }

        //In xác nhận
        if (fail) {
            setColor(12);
            printf("   >> [Fail]. Không tìm thấy cư dân\n");
            setColor(7);
            fail = 0;
        } else if (choice == 2) {
            setColor(11);
            printf("   >> Xác nhận\n");
            setColor(7);
        } else {
            printf("       Xác nhận\n");
        }

        //Hướng dẫn
        printf("\nNhấn ▲ ▼ để di chuyển\n");
        printf("Nhấn Enter xác nhận\n");
        printf("Nhấn Esc để thoát\n");

        //Di chuyển con trỏ
        gotoxy(28 + strlen(searchUsername), 9);

        //Nhận phím
        key = getch();

        //Điều hướng mũi tên
        if (key == 224) {
            key = getch();

            //Lên
            if (key == KEY_UP) {
                choice--;
                if (choice < 1) {
                    choice = 2;
                }
            }
            //Xuống
            else if (key == KEY_DOWN) {
                choice++;
                if (choice > 2) {
                    choice = 1;
                }
            }
        }

        //Esc để thoát
        else if (key == ESC) {
            return;
        }

        //Backspace
        else if (key == BACKSPACE) {
            if (choice == 1 && strlen(searchUsername) > 0) {
                searchUsername[strlen(searchUsername) - 1] = '\0';
            }
        }

        //Enter
        else if (key == ENTER) {

            //Nếu đang chọn xác nhận
            if (choice == 2) {

                //Tìm đường dẫn file cư dân
                char resPath[300] = "";
                if (!findResidentPath(searchUsername, resPath)) {
                    fail = 1;
                    continue;
                }

                //Đọc thông tin từ file
                char password[50]  = "";
                char name[50]      = "";
                char CCCD[20]      = "";
                char year[10]      = "";
                char gender[10]    = "";
                char province[50]  = "";
                char phone[20]     = "";

                FILE *f = fopen(resPath, "r");
                if (f != NULL) {
                    fgets(password, sizeof(password), f);  password[strcspn(password, "\n")] = '\0';
                    fgets(name,     sizeof(name),     f);  name[strcspn(name, "\n")]         = '\0';
                    fgets(CCCD,     sizeof(CCCD),     f);  CCCD[strcspn(CCCD, "\n")]         = '\0';
                    fgets(year,     sizeof(year),     f);  year[strcspn(year, "\n")]         = '\0';
                    fgets(gender,   sizeof(gender),   f);  gender[strcspn(gender, "\n")]     = '\0';
                    fgets(province, sizeof(province), f);  province[strcspn(province, "\n")] = '\0';
                    fgets(phone,    sizeof(phone),    f);  phone[strcspn(phone, "\n")]       = '\0';
                    fclose(f);
                }

                //Lưu giá trị cũ để so sánh
                char oldCCCD[20];
                strcpy(oldCCCD, CCCD);

                char editUsername[50];
                strcpy(editUsername, searchUsername);

                //Khai báo biến cần thiết cho màn hình chỉnh sửa
                int ec = 1;
                int ek;
                int ef = 0;

                //================ HIỂN THỊ THÔNG TIN ================

                while (1) {

                    //Làm sạch màn hình
                    system("cls");

                    //In chữ MANAGE INFO
                    printf("\n");
                    printf("███╗   ███╗ █████╗ ███╗   ██╗ █████╗  ██████╗ ███████╗    ██╗███╗   ██╗███████╗ ██████╗ \n");
                    printf("████╗ ████║██╔══██╗████╗  ██║██╔══██╗██╔════╝ ██╔════╝    ██║████╗  ██║██╔════╝██╔═══██╗\n");
                    printf("██╔████╔██║███████║██╔██╗ ██║███████║██║  ███╗█████╗      ██║██╔██╗ ██║█████╗  ██║   ██║\n");
                    printf("██║╚██╔╝██║██╔══██║██║╚██╗██║██╔══██║██║   ██║██╔══╝      ██║██║╚██╗██║██╔══╝  ██║   ██║\n");
                    printf("██║ ╚═╝ ██║██║  ██║██║ ╚████║██║  ██║╚██████╔╝███████╗    ██║██║ ╚████║██║     ╚██████╔╝\n");
                    printf("╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝    ╚═╝╚═╝  ╚═══╝╚═╝      ╚═════╝ \n\n\n");

                    //Username
                    if (ec == 1) {
                        setColor(11);
                        printf("   >> Username : %s\n", editUsername);
                        setColor(7);
                    } else {
                        printf("       Username : %s\n", editUsername);
                    }

                    //Password
                    if (ec == 2) {
                        setColor(11);
                        printf("   >> Password : %s\n", password);
                        setColor(7);
                    } else {
                        printf("       Password : %s\n", password);
                    }

                    //Name
                    if (ec == 3) {
                        setColor(11);
                        printf("   >> Name     : %s\n", name);
                        setColor(7);
                    } else {
                        printf("       Name     : %s\n", name);
                    }

                    //CCCD
                    if (ec == 4) {
                        setColor(11);
                        printf("   >> CCCD     : %s\n", CCCD);
                        setColor(7);
                    } else {
                        printf("       CCCD     : %s\n", CCCD);
                    }

                    //Year
                    if (ec == 5) {
                        setColor(11);
                        printf("   >> Year     : %s\n", year);
                        setColor(7);
                    } else {
                        printf("       Year     : %s\n", year);
                    }

                    //Gender
                    if (ec == 6) {
                        setColor(11);
                        printf("   >> Gender   : %s\n", gender);
                        setColor(7);
                    } else {
                        printf("       Gender   : %s\n", gender);
                    }

                    //Province
                    if (ec == 7) {
                        setColor(11);
                        printf("   >> Province : %s\n", province);
                        setColor(7);
                    } else {
                        printf("       Province : %s\n", province);
                    }

                    //Phone
                    if (ec == 8) {
                        setColor(11);
                        printf("   >> Phone    : %s\n", phone);
                        setColor(7);
                    } else {
                        printf("       Phone    : %s\n", phone);
                    }

                    //In xác nhận / thông báo lỗi
                    if (ef == 1) {
                        setColor(12);
                        printf("   >> Username không hợp lệ\n");
                        setColor(7);
                        ef = 0;
                    }
                    else if (ef == 2) {
                        setColor(12);
                        printf("   >> Password không hợp lệ\n");
                        setColor(7);
                        ef = 0;
                    }
                    else if (ef == 3) {
                        setColor(12);
                        printf("   >> Tên không hợp lệ\n");
                        setColor(7);
                        ef = 0;
                    }
                    else if (ef == 4) {
                        setColor(12);
                        printf("   >> CCCD không hợp lệ\n");
                        setColor(7);
                        ef = 0;
                    }
                    else if (ef == 5) {
                        setColor(12);
                        printf("   >> SĐT không hợp lệ\n");
                        setColor(7);
                        ef = 0;
                    }
                    else if (ec == 9) {
                        setColor(11);
                        printf("   >> Xác nhận\n");
                        setColor(7);
                    } else {
                        printf("       Xác nhận\n");
                    }

                    //Hướng dẫn
                    printf("\nNhấn ▲ ▼ để di chuyển\n");
                    printf("Nhấn Enter để chỉnh sửa\n");
                    printf("Nhấn Esc để thoát\n");

                    //Di chuyển con trỏ
                    if (ec == 1) {
                        gotoxy(17 + strlen(editUsername), 9);
                    } else if (ec == 2) {
                        gotoxy(17 + strlen(password),    10);
                    } else if (ec == 3) {
                        gotoxy(17 + strlen(name),        11);
                    } else if (ec == 4) {
                        gotoxy(17 + strlen(CCCD),        12);
                    } else if (ec == 8) {
                        gotoxy(17 + strlen(phone),       16);
                    }

                    //Nhận phím
                    ek = getch();

                    //Điều hướng mũi tên
                    if (ek == 224) {
                        ek = getch();

                        //Lên
                        if (ek == KEY_UP) {
                            ec--;
                            if (ec < 1) {
                                ec = 9;
                            }
                        }
                        //Xuống
                        else if (ek == KEY_DOWN) {
                            ec++;
                            if (ec > 9) {
                                ec = 1;
                            }
                        }
                    }

                    //Esc để thoát
                    else if (ek == ESC) {
                        return;
                    }

                    //Backspace
                    else if (ek == BACKSPACE) {

                        //Username
                        if (ec == 1 && strlen(editUsername) > 0) {
                            editUsername[strlen(editUsername) - 1] = '\0';
                        }

                        //Password
                        else if (ec == 2 && strlen(password) > 0) {
                            password[strlen(password) - 1] = '\0';
                        }

                        //Name
                        else if (ec == 3 && strlen(name) > 0) {
                            name[strlen(name) - 1] = '\0';
                        }

                        //CCCD
                        else if (ec == 4 && strlen(CCCD) > 0) {
                            CCCD[strlen(CCCD) - 1] = '\0';
                            strcpy(year, "");
                            strcpy(gender, "");
                            strcpy(province, "");
                        }

                        //Phone
                        else if (ec == 8 && strlen(phone) > 0) {
                            phone[strlen(phone) - 1] = '\0';
                        }
                    }

                    //Enter
                    else if (ek == ENTER) {

                        //Xác nhận lưu
                        if (ec == 9) {

                            //Kiểm tra username
                            if (checkUsername(editUsername) == 0 || strlen(editUsername) < 3) {
                                ef = 1;
                                continue;
                            }

                            //Kiểm tra password
                            if (checkPassword(password) == 0) {
                                ef = 2;
                                continue;
                            }

                            //Kiểm tra tên
                            if (strlen(name) == 0) {
                                ef = 3;
                                continue;
                            }

                            //Kiểm tra CCCD (có thể không có)
                            if (strlen(CCCD) > 0) {
                                if (checkDuplicateCCCD(CCCD) && strcmp(CCCD, oldCCCD) != 0) {
                                    ef = 4;
                                    continue;
                                }
                                if (checkCCCDOnly(year, province, CCCD, gender) == 0) {
                                    ef = 4;
                                    continue;
                                }
                            }

                            //Kiểm tra số điện thoại (có thể không có)
                            if(strlen(phone) != 0) {
                                if(checkPhoneNumber(phone) == 0) {
                                    fail = 5;
                                    continue;
                                }
                            }

                            //Xác định đường dẫn mới nếu username thay đổi
                            char folder[300] = "";
                            strncpy(folder, resPath, strlen(resPath));

                            //Cắt bỏ tên file
                            char *lastSlash = strrchr(folder, '/');
                            if (lastSlash) {
                                *lastSlash = '\0';
                            }

                            char newPath[350];
                            sprintf(newPath, "%s/%s.txt", folder, editUsername);

                            //Đổi tên file nếu username thay đổi
                            if (strcmp(searchUsername, editUsername) != 0) {
                                rename(resPath, newPath);
                            }

                            //Ghi thông tin vào file
                            FILE *fw = fopen(newPath, "w");
                            if (fw != NULL) {
                                fprintf(fw, "%s\n", password);
                                fprintf(fw, "%s\n", name);
                                fprintf(fw, "%s\n", CCCD);
                                fprintf(fw, "%s\n", year);
                                fprintf(fw, "%s\n", gender);
                                fprintf(fw, "%s\n", province);
                                fprintf(fw, "%s\n", phone);
                                fclose(fw);

                                //Thông báo thành công
                                gotoxy(0, 17);
                                setColor(10);
                                printf("      Lưu thông tin cư dân thành công!\n");
                                setColor(7);
                                printf("\nNhấn Enter hoặc Esc để thoát\n                                       \n                                   ");
    
                                //Lưu lịch sử
                                char history[256];
                                sprintf(history, "Quản lý '%s' đã đổi thông tin của cư dân '%s'.", manage, searchUsername);
                                saveHistory("QUẢN LÝ", "THÀNH CÔNG", "Đổi thông tin", history);
                            }

                            //Đợi người dùng thoát
                            while (1) {
                                ek = getch();
                                if (ek == ENTER || ek == ESC) {
                                    return;
                                }
                            }
                        }
                    }

                    //Chỉnh sửa trực tiếp
                    else {

                        //Username
                        if (ec == 1) {
                            if (
                                (ek >= 'a' && ek <= 'z') ||
                                (ek >= 'A' && ek <= 'Z') ||
                                (ek >= '0' && ek <= '9')
                            ) {
                                int len = strlen(editUsername);
                                editUsername[len] = ek;
                                editUsername[len + 1] = '\0';
                            }
                        }

                        //Password
                        if (ec == 2) {
                            if (ek >= 32 && ek <= 126) {
                                int len = strlen(password);
                                password[len] = ek;
                                password[len + 1] = '\0';
                            }
                        }

                        //Name
                        if (ec == 3) {
                            int len = strlen(name);
                            name[len] = (char)ek;
                            name[len + 1] = '\0';
                        }

                        //CCCD
                        if (ec == 4) {
                            if (ek >= '0' && ek <= '9') {
                                int len = strlen(CCCD);
                                CCCD[len] = ek;
                                CCCD[len + 1] = '\0';

                                //Nếu vừa đủ 12 số thì suy ra thông tin
                                if (strlen(CCCD) == 12) {
                                    checkCCCD(year, province, CCCD, gender);
                                }
                            }
                        }

                        //Phone
                        if (ec == 8) {
                            if (strlen(phone) < 19 && ek >= '0' && ek <= '9') {
                                int len = strlen(phone);
                                phone[len] = ek;
                                phone[len + 1] = '\0';
                            }
                        }
                    }
                }
            }
        }

        //Nhập username
        else {
            if (choice == 1 && strlen(searchUsername) < 49) {
                if (
                    (key >= 'a' && key <= 'z') ||
                    (key >= 'A' && key <= 'Z') ||
                    (key >= '0' && key <= '9')
                ) {
                    int len = strlen(searchUsername);
                    searchUsername[len] = key;
                    searchUsername[len + 1] = '\0';
                }
            }
        }
    }
}

/*
    Xóa tài khoản cư dân
                          */
void deleteResidentAccount(char manage[]) {

    //Khai báo biến cần thiết
    char username[50] = "";
    int choice = 1;
    int key;
    int fail = 0;

    //Tạo vòng lặp
    while (1) {

        //Làm sạch màn hình
        system("cls");

        //In chữ DELETE RESIDENT
        printf("\n");
        printf("██████╗ ███████╗██╗     ███████╗████████╗███████╗    ██████╗ ███████╗███████╗██╗██████╗ ███████╗███╗   ██╗████████╗\n");
        printf("██╔══██╗██╔════╝██║     ██╔════╝╚══██╔══╝██╔════╝    ██╔══██╗██╔════╝██╔════╝██║██╔══██╗██╔════╝████╗  ██║╚══██╔══╝\n");
        printf("██║  ██║█████╗  ██║     █████╗     ██║   █████╗      ██████╔╝█████╗  ███████╗██║██║  ██║█████╗  ██╔██╗ ██║   ██║   \n");
        printf("██║  ██║██╔══╝  ██║     ██╔══╝     ██║   ██╔══╝      ██╔══██╗██╔══╝  ╚════██║██║██║  ██║██╔══╝  ██║╚██╗██║   ██║   \n");
        printf("██████╔╝███████╗███████╗███████╗   ██║   ███████╗    ██║  ██║███████╗███████║██║██████╔╝███████╗██║ ╚████║   ██║   \n");
        printf("╚═════╝ ╚══════╝╚══════╝╚══════╝   ╚═╝   ╚══════╝    ╚═╝  ╚═╝╚══════╝╚══════╝╚═╝╚═════╝ ╚══════╝╚═╝  ╚═══╝   ╚═╝   \n\n\n");

        //In ô nhập username
        if (choice == 1) {
            setColor(11);
            printf("   >> Nhập username cư dân: %s\n", username);
            setColor(7);
        } else {
            printf("       Nhập username cư dân: %s\n", username);
        }

        //In xác nhận / thông báo lỗi
        if (fail) {
            setColor(12);
            printf("   >> [Fail] Không tìm thấy cư dân\n");
            setColor(7);
            fail = 0;
        } else if (choice == 2) {
            setColor(11);
            printf("   >> Xác nhận\n");
            setColor(7);
        } else {
            printf("       Xác nhận\n");
        }

        //Hướng dẫn
        printf("\nNhấn ▲ ▼ để di chuyển\n");
        printf("Nhấn Enter xác nhận\n");
        printf("Nhấn Esc để thoát\n");

        //Di chuyển con trỏ
        gotoxy(28 + strlen(username), 9);

        //Nhận phím
        key = getch();

        //Điều hướng mũi tên
        if (key == 224) {
            key = getch();

            //Lên
            if (key == KEY_UP) {
                choice--;
                if (choice < 1) {
                    choice = 2;
                }
            }
            //Xuống
            else if (key == KEY_DOWN) {
                choice++;
                if (choice > 2) {
                    choice = 1;
                }
            }
        }

        //Esc để thoát
        else if (key == ESC) {
            return;
        }

        //Backspace
        else if (key == BACKSPACE) {
            if (choice == 1 && strlen(username) > 0) {
                username[strlen(username) - 1] = '\0';
            }
        }

        //Enter
        else if (key == ENTER) {

            //Nếu đang chọn xác nhận
            if (choice == 2) {

                //Tìm đường dẫn file cư dân
                char resPath[300] = "";
                if (!findResidentPath(username, resPath)) {
                    fail = 1;
                    continue;
                }

                //================ XÁC NHẬN XÓA ================

                int confirmChoice = 1;
                int confirmKey;

                while (1) {

                    //Làm sạch màn hình
                    system("cls");

                    //In tiêu đề
                    printf("\n");
                    printf("██████╗ ███████╗██╗     ███████╗████████╗███████╗    ██████╗ ███████╗███████╗██╗██████╗ ███████╗███╗   ██╗████████╗\n");
                    printf("██╔══██╗██╔════╝██║     ██╔════╝╚══██╔══╝██╔════╝    ██╔══██╗██╔════╝██╔════╝██║██╔══██╗██╔════╝████╗  ██║╚══██╔══╝\n");
                    printf("██║  ██║█████╗  ██║     █████╗     ██║   █████╗      ██████╔╝█████╗  ███████╗██║██║  ██║█████╗  ██╔██╗ ██║   ██║   \n");
                    printf("██║  ██║██╔══╝  ██║     ██╔══╝     ██║   ██╔══╝      ██╔══██╗██╔══╝  ╚════██║██║██║  ██║██╔══╝  ██║╚██╗██║   ██║   \n");
                    printf("██████╔╝███████╗███████╗███████╗   ██║   ███████╗    ██║  ██║███████╗███████║██║██████╔╝███████╗██║ ╚████║   ██║   \n");
                    printf("╚═════╝ ╚══════╝╚══════╝╚══════╝   ╚═╝   ╚══════╝    ╚═╝  ╚═╝╚══════╝╚══════╝╚═╝╚═════╝ ╚══════╝╚═╝  ╚═══╝   ╚═╝   \n\n\n");

                    //Cảnh báo
                    setColor(12);
                    printf("   Bạn có chắc muốn xóa cư dân \"%s\" không?\n\n", username);
                    setColor(7);

                    //In lựa chọn
                    if (confirmChoice == 1) {
                        setColor(11);
                        printf("   >> Có\n");
                        setColor(7);
                    } else {
                        printf("       Có\n");
                    }

                    if (confirmChoice == 2) {
                        setColor(11);
                        printf("   >> Không\n");
                        setColor(7);
                    } else {
                        printf("       Không\n");
                    }

                    //Hướng dẫn
                    printf("\nNhấn ▲ ▼ để di chuyển\n");
                    printf("Nhấn Enter xác nhận\n");
                    printf("Nhấn Esc để thoát\n");

                    //Nhận phím
                    confirmKey = getch();

                    //Điều hướng mũi tên
                    if (confirmKey == 224) {
                        confirmKey = getch();

                        //Lên
                        if (confirmKey == KEY_UP) {
                            confirmChoice--;
                            if (confirmChoice < 1) {
                                confirmChoice = 2;
                            }
                        }
                        //Xuống
                        else if (confirmKey == KEY_DOWN) {
                            confirmChoice++;
                            if (confirmChoice > 2) {
                                confirmChoice = 1;
                            }
                        }
                    }

                    //Esc để thoát
                    else if (confirmKey == ESC) {
                        return;
                    }

                    //Enter
                    else if (confirmKey == ENTER) {

                        //Chọn Có → xóa file
                        if (confirmChoice == 1) {

                            gotoxy(0, 9);
                            if (remove(resPath) == 0) {
                                setColor(10);
                                printf("      Xóa cư dân \"%s\" thành công!                  \n", username);
                                setColor(7);

                                //Lưu lịch sử
                                char history[256];
                                sprintf(history, "Quản lý '%s' đã xóa thành công cư dân với username là '%s'.", manage, username);
                                saveHistory("QUẢN LÝ", "THÀNH CÔNG", "Xóa cư dân", history);
                            } else {
                                setColor(12);
                                printf("[Fail] Không thể xóa file!\n");
                                setColor(7);

                                //Lưu lịch sử
                                char history[256];
                                sprintf(history, "Quản lý '%s' đã cố gắn xóa cư dân với username là '%s'.", manage, username);
                                saveHistory("QUẢN LÝ", "THẤT BẠI", "Xóa cư dân", history);
                            }

                            //Hướng dẫn
                            printf("\nNhấn Enter hoặc Esc để thoát\n                                       \n                                   ");
                            printf("\n                                       \n                                   \n                                 ");

                            //Đợi người dùng thoát
                            while (1) {
                                confirmKey = getch();
                                if (confirmKey == ENTER || confirmKey == ESC) {
                                    return;
                                }
                            }
                        }

                        //Chọn Không → quay lại
                        else if (confirmChoice == 2) {
                            break;
                        }
                    }
                }
            }
        }

        //Nhập username
        else {
            if (choice == 1 && strlen(username) < 49) {
                if (
                    (key >= 'a' && key <= 'z') ||
                    (key >= 'A' && key <= 'Z') ||
                    (key >= '0' && key <= '9')
                ) {
                    int len = strlen(username);
                    username[len] = key;
                    username[len + 1] = '\0';
                }
            }
        }
    }
}

/*
    Quản lý tài khoản cư dân
                               */
void accountResident(char manage[]) {

    //Khai báo hàm cần thiết
    int choice = 1;
    int key;
    char *options[] = {
        "Tạo tài khoản cư dân",
        "Chỉnh sửa thông tin tài khoản cư dân",
        "Xóa tài khoản cư dân",
        "Thoát",
    };

    //Lấy số lượng phần tử trong mảng options
    int numOptions = sizeof(options) / sizeof(options[0]);

    //Tạo vòng lặp
    while (1) {

        //Làm sạch màn hình
        system("cls");

        //In chữ ACCOUNT RESIDENT
        printf("\n");
        printf(" █████╗  ██████╗ ██████╗ ██████╗ ██╗   ██╗███╗   ██╗████████╗    ██████╗ ███████╗███████╗██╗██████╗ ███████╗███╗   ██╗████████╗\n");
        printf("██╔══██╗██╔════╝██╔════╝██╔═══██╗██║   ██║████╗  ██║╚══██╔══╝    ██╔══██╗██╔════╝██╔════╝██║██╔══██╗██╔════╝████╗  ██║╚══██╔══╝\n");
        printf("███████║██║     ██║     ██║   ██║██║   ██║██╔██╗ ██║   ██║       ██████╔╝█████╗  ███████╗██║██║  ██║█████╗  ██╔██╗ ██║   ██║   \n");
        printf("██╔══██║██║     ██║     ██║   ██║██║   ██║██║╚██╗██║   ██║       ██╔══██╗██╔══╝  ╚════██║██║██║  ██║██╔══╝  ██║╚██╗██║   ██║   \n");
        printf("██║  ██║╚██████╗╚██████╗╚██████╔╝╚██████╔╝██║ ╚████║   ██║       ██║  ██║███████╗███████║██║██████╔╝███████╗██║ ╚████║   ██║   \n");
        printf("╚═╝  ╚═╝ ╚═════╝ ╚═════╝ ╚═════╝  ╚═════╝ ╚═╝  ╚═══╝   ╚═╝       ╚═╝  ╚═╝╚══════╝╚══════╝╚═╝╚═════╝ ╚══════╝╚═╝  ╚═══╝   ╚═╝   \n\n\n");

        //In nội dung lựa chọn
        for (int i = 0; i < numOptions; i++) {
            printContent(options[i], i + 1, choice);
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
                if (choice < 1) {
                    choice = numOptions;
                }
            }
            //Xuống
            else if (key == KEY_DOWN) {
                choice++;
                if (choice > numOptions) {
                    choice = 1;
                }
            }
        }

        //Enter
        else if (key == ENTER) {
            switch (choice) {
                case 1:
                    createResidentAccount(manage);
                    break;
                case 2:
                    editResidentInfo(manage);
                    break;
                case 3:
                    deleteResidentAccount(manage);
                    break;
                case 4:
                    return;
            }
        }
    }
}

/*
    Xem danh sách các phòng
                              */
void viewRoomList() {

    //Làm sạch màn hình
    system("cls");

    //In chữ ROOM LIST
    printf("\n");
    printf("██████╗  ██████╗  ██████╗ ███╗   ███╗    ██╗     ██╗███████╗████████╗\n");
    printf("██╔══██╗██╔═══██╗██╔═══██╗████╗ ████║    ██║     ██║██╔════╝╚══██╔══╝\n");
    printf("██████╔╝██║   ██║██║   ██║██╔████╔██║    ██║     ██║███████╗   ██║   \n");
    printf("██╔══██╗██║   ██║██║   ██║██║╚██╔╝██║    ██║     ██║╚════██║   ██║   \n");
    printf("██║  ██║╚██████╔╝╚██████╔╝██║ ╚═╝ ██║    ███████╗██║███████║   ██║   \n");
    printf("╚═╝  ╚═╝ ╚═════╝  ╚═════╝ ╚═╝     ╚═╝    ╚══════╝╚═╝╚══════╝   ╚═╝   \n\n\n");

    //Khai báo mảng lưu danh sách phòng trống và phòng có người cho từng tầng
    char emptyRooms[5][256];
    char occupiedRooms[5][256];

    //Khởi tạo chuỗi rỗng
    for (int i = 0; i < 5; i++) {
        strcpy(emptyRooms[i], "");
        strcpy(occupiedRooms[i], "");
    }

    //Duyệt qua từng tầng và từng phòng
    for (int floor = 1; floor <= 5; floor++) {
        for (int room = 1; room <= 5; room++) {

            //Tạo đường dẫn đến thư mục phòng
            char pathFolder[256];
            sprintf(pathFolder, "FloorList/Floor%d/P%d%02d", floor, floor, room);

            //Tạo tên phòng
            char roomName[10];
            sprintf(roomName, "P%d%02d", floor, room);

            //Kiểm tra thư mục có tồn tại không
            DIR *dir = opendir(pathFolder);
            if (dir == NULL) {

                //Thư mục không tồn tại → coi như phòng trống
                if (strlen(emptyRooms[floor - 1]) > 0) {
                    strcat(emptyRooms[floor - 1], ", ");
                }
                strcat(emptyRooms[floor - 1], roomName);
                continue;
            }

            //Kiểm tra thư mục có file nào không
            int hasFile = 0;
            struct dirent *entry;
            while ((entry = readdir(dir)) != NULL) {

                //Bỏ qua file ẩn
                if (entry->d_name[0] == '.') continue;

                //Nếu có file .txt thì phòng có người
                if (strstr(entry->d_name, ".txt") != NULL) {
                    hasFile = 1;
                    break;
                }
            }
            closedir(dir);

            //Phân loại phòng
            if (hasFile) {

                //Phòng có người
                if (strlen(occupiedRooms[floor - 1]) > 0) {
                    strcat(occupiedRooms[floor - 1], ", ");
                }
                strcat(occupiedRooms[floor - 1], roomName);

            } else {

                //Phòng trống
                if (strlen(emptyRooms[floor - 1]) > 0) {
                    strcat(emptyRooms[floor - 1], ", ");
                }
                strcat(emptyRooms[floor - 1], roomName);
            }
        }
    }

    //================ IN BẢNG PHÒNG TRỐNG ================

    setColor(10);
    printf("   Phòng trống\n");
    setColor(7);
    printf("   +-----------+--------------------------------------------------+\n");

    for (int i = 0; i < 5; i++) {

        //Đếm ký tự UTF-8 để căn chỉnh cột tầng
        char floorName[20];
        sprintf(floorName, "Tầng %d", i + 1);
        int floorSpace = 9 - utf8len(floorName);

        printf("   | %s ", floorName);
        for (int j = 0; j < floorSpace; j++) printf(" ");

        if (strlen(emptyRooms[i]) > 0) {
            printf("| %-49s|\n", emptyRooms[i]);
        } else {
            printf("| %-49s|\n", "Không có phòng trống");
        }
    }

    printf("   +-----------+--------------------------------------------------+\n\n");

    //================ IN BẢNG PHÒNG CÓ CƯ DÂN ================

    setColor(14);
    printf("   Phòng có cư dân\n");
    setColor(7);
    printf("   +-----------+--------------------------------------------------+\n");

    for (int i = 0; i < 5; i++) {

        //Đếm ký tự UTF-8 để căn chỉnh cột tầng
        char floorName[20];
        sprintf(floorName, "Tầng %d", i + 1);
        int floorSpace = 9 - utf8len(floorName);

        printf("   | %s ", floorName);
        for (int j = 0; j < floorSpace; j++) printf(" ");

        if (strlen(occupiedRooms[i]) > 0) {
            printf("| %-49s|\n", occupiedRooms[i]);
        } else {
            printf("| Không có cư dân                                  |\n");
        }
    }

    printf("   +-----------+--------------------------------------------------+\n");

    //Nhận phím từ người dùng
    printf("\nNhấn Enter hoặc Esc để quay lại\n");
    int key = getch();
    while (key != ENTER && key != ESC) {
        key = getch();
    }
}

/*
    Tìm kiếm cư dân
                     */
void searchResident() {

    //Khai báo biến cần thiết
    char keyword[100] = "";
    int choice = 1;
    int key;
    int fail = 0;

    //Tạo vòng lặp
    while (1) {

        //Làm sạch màn hình
        system("cls");

        //In chữ SEARCH
        printf("\n");
        printf("███████╗███████╗ █████╗ ██████╗  ██████╗██╗  ██╗\n");
        printf("██╔════╝██╔════╝██╔══██╗██╔══██╗██╔════╝██║  ██║\n");
        printf("███████╗█████╗  ███████║██████╔╝██║     ███████║\n");
        printf("╚════██║██╔══╝  ██╔══██║██╔══██╗██║     ██╔══██║\n");
        printf("███████║███████╗██║  ██║██║  ██║╚██████╗██║  ██║\n");
        printf("╚══════╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝\n\n\n");

        //In ô nhập từ khóa
        if (choice == 1) {
            setColor(11);
            printf("   >> Nhập tên / username / CCCD: %s\n", keyword);
            setColor(7);
        } else {
            printf("       Nhập tên / username / CCCD: %s\n", keyword);
        }

        //In xác nhận / thông báo lỗi
        if (fail) {
            setColor(12);
            printf("   >> Không tìm thấy kết quả\n");
            setColor(7);
            fail = 0;
        } else if (choice == 2) {
            setColor(11);
            printf("   >> Tìm kiếm\n");
            setColor(7);
        } else {
            printf("       Tìm kiếm\n");
        }

        //Hướng dẫn
        printf("\nNhấn ▲ ▼ để di chuyển\n");
        printf("Nhấn Enter xác nhận\n");
        printf("Nhấn Esc để thoát\n");

        //Di chuyển con trỏ
        gotoxy(35 + strlen(keyword), 9);

        //Nhận phím
        key = getch();

        //Điều hướng mũi tên
        if (key == 224) {
            key = getch();

            //Lên
            if (key == KEY_UP) {
                choice--;
                if (choice < 1) {
                    choice = 2;
                }
            }
            //Xuống
            else if (key == KEY_DOWN) {
                choice++;
                if (choice > 2) {
                    choice = 1;
                }
            }
        }

        //Esc để thoát
        else if (key == ESC) {
            return;
        }

        //Backspace
        else if (key == BACKSPACE) {
            if (choice == 1 && strlen(keyword) > 0) {
                keyword[strlen(keyword) - 1] = '\0';
            }
        }

        //Enter
        else if (key == ENTER) {

            //Nếu đang chọn tìm kiếm
            if (choice == 2) {

                if (strlen(keyword) == 0) {
                    fail = 1;
                    continue;
                }

                //================ TÌM KIẾM ================

                //Làm sạch màn hình
                system("cls");

                //In tiêu đề
                printf("\n");
                printf("████████╗██╗███╗   ███╗    ██╗  ██╗██╗███████╗███╗   ███╗\n");
                printf("╚══██╔══╝██║████╗ ████║    ██║ ██╔╝██║██╔════╝████╗ ████║\n");
                printf("   ██║   ██║██╔████╔██║    █████╔╝ ██║█████╗  ██╔████╔██║\n");
                printf("   ██║   ██║██║╚██╔╝██║    ██╔═██╗ ██║██╔══╝  ██║╚██╔╝██║\n");
                printf("   ██║   ██║██║ ╚═╝ ██║    ██║  ██╗██║███████╗██║ ╚═╝ ██║\n");
                printf("   ╚═╝   ╚═╝╚═╝     ╚═╝    ╚═╝  ╚═╝╚═╝╚══════╝╚═╝     ╚═╝\n\n\n");

                setColor(14);
                printf("   Kết quả tìm kiếm: \"%s\"\n\n", keyword);
                setColor(7);

                printf("   +----------+------------------+----------------------------------+---------------+\n");
                printf("   | Phòng    | Username         | Tên                              | CCCD          |\n");
                printf("   +----------+------------------+----------------------------------+---------------+\n");

                int found = 0;
                DIR *dir;
                struct dirent *entry;

                //Duyệt từng tầng và từng phòng
                for (int floor = 1; floor <= 5; floor++) {
                    for (int room = 1; room <= 5; room++) {

                        //Tạo đường dẫn thư mục phòng
                        char folderPath[256];
                        sprintf(folderPath, "FloorList/Floor%d/P%d%02d", floor, floor, room);

                        dir = opendir(folderPath);
                        if (!dir) continue;

                        while ((entry = readdir(dir)) != NULL) {

                            //Bỏ qua file ẩn
                            if (entry->d_name[0] == '.') continue;

                            //Bỏ qua file không phải .txt
                            if (!strstr(entry->d_name, ".txt")) continue;

                            //Lấy username từ tên file
                            char uname[50] = "";
                            strncpy(uname, entry->d_name, strlen(entry->d_name) - 4);
                            uname[strlen(entry->d_name) - 4] = '\0';

                            //Tạo đường dẫn đầy đủ đến file
                            char filePath[300];
                            sprintf(filePath, "%s/%s", folderPath, entry->d_name);

                            //Đọc thông tin từ file
                            char password[50]  = "";
                            char name[50]      = "";
                            char CCCD[20]      = "";
                            char year[10]      = "";
                            char gender[10]    = "";
                            char province[50]  = "";
                            char phone[20]     = "";

                            FILE *f = fopen(filePath, "r");
                            if (f != NULL) {
                                fgets(password, sizeof(password), f);  password[strcspn(password, "\n")] = '\0';
                                fgets(name,     sizeof(name),     f);  name[strcspn(name, "\n")]         = '\0';
                                fgets(CCCD,     sizeof(CCCD),     f);  CCCD[strcspn(CCCD, "\n")]         = '\0';
                                fgets(year,     sizeof(year),     f);
                                fgets(gender,   sizeof(gender),   f);
                                fgets(province, sizeof(province), f);
                                fgets(phone,    sizeof(phone),    f);
                                fclose(f);
                            }

                            //Chuyển keyword và field về lowercase để so sánh không phân biệt hoa thường
                            char kwLow[100];
                            char uLow[50];
                            char nLow[50];

                            strcpy(kwLow, keyword);
                            strcpy(uLow,  uname);
                            strcpy(nLow,  name);

                            for (int i = 0; kwLow[i]; i++) kwLow[i] = tolower(kwLow[i]);
                            for (int i = 0; uLow[i];  i++) uLow[i]  = tolower(uLow[i]);
                            for (int i = 0; nLow[i];  i++) nLow[i]  = tolower(nLow[i]);

                            //Kiểm tra khớp với keyword
                            int match = 0;
                            if (strstr(uLow, kwLow) || strstr(nLow, kwLow) || strstr(CCCD, keyword)) {
                                match = 1;
                            }

                            if (match) {
                                found++;
                                int ns = 32 - utf8len(name);
                                printf("   | P%d%02d     | %-16s | %s ", floor, room, uname, name);
                                for (int i = 0; i < ns; i++) printf(" ");
                                printf("| %-13s |\n", CCCD);
                            }
                        }

                        closedir(dir);
                    }
                }

                printf("   +----------+------------------+----------------------------------+---------------+\n");

                //In kết quả
                if (!found) {
                    setColor(12);
                    printf("\n   Không tìm thấy cư dân nào phù hợp.\n");
                    setColor(7);
                } else {
                    setColor(10);
                    printf("\n   Tìm thấy %d kết quả.\n", found);
                    setColor(7);
                }

                //Nhận phím
                printf("\nNhấn Enter hoặc Esc để quay lại\n");
                int k;
                while (1) {
                    k = getch();
                    if (k == ENTER || k == ESC) {
                        break;
                    }
                }
                return;
            }
        }

        //Nhập ký tự thường
        else {
            if (choice == 1 && strlen(keyword) < 99) {
                int len = strlen(keyword);
                keyword[len] = (char)key;
                keyword[len + 1] = '\0';
            }
        }
    }
}

/*
    Nhập thông tin số điện, số nước
                                      */
void inputUtilities(char manage[]) {

    //Khai báo biến cần thiết
    int choice = 1;
    int key;
    int fail = 0;

    char roomInput[10] = "";
    char month[3]      = "";
    char year[5]       = "";

    //Đơn giá mặc định
    float electricityRate = 3000.0f;
    float waterRate       = 15000.0f;
    float roomPrice       = 10000000.0f;

    //Tạo vòng lặp
    while (1) {

        //Làm sạch màn hình
        system("cls");

        //In chữ INPUT UTILITIES
        printf("\n");
        printf("██╗███╗   ██╗██████╗ ██╗   ██╗████████╗    ██╗   ██╗████████╗██╗██╗     ██╗████████╗██╗███████╗███████╗\n");
        printf("██║████╗  ██║██╔══██╗██║   ██║╚══██╔══╝    ██║   ██║╚══██╔══╝██║██║     ██║╚══██╔══╝██║██╔════╝██╔════╝\n");
        printf("██║██╔██╗ ██║██████╔╝██║   ██║   ██║       ██║   ██║   ██║   ██║██║     ██║   ██║   ██║█████╗  ███████╗\n");
        printf("██║██║╚██╗██║██╔═══╝ ██║   ██║   ██║       ██║   ██║   ██║   ██║██║     ██║   ██║   ██║██╔══╝  ╚════██║\n");
        printf("██║██║ ╚████║██║     ╚██████╔╝   ██║       ╚██████╔╝   ██║   ██║███████╗██║   ██║   ██║███████╗███████║\n");
        printf("╚═╝╚═╝  ╚═══╝╚═╝      ╚═════╝    ╚═╝        ╚═════╝    ╚═╝   ╚═╝╚══════╝╚═╝   ╚═╝   ╚═╝╚══════╝╚══════╝\n\n\n");

        //In phòng
        if (choice == 1) {
            setColor(11);
            printf("   >> Phòng (VD: 101)    : %s\n", roomInput);
            setColor(7);
        } else {
            printf("       Phòng (VD: 101)    : %s\n", roomInput);
        }

        //In tháng
        if (choice == 2) {
            setColor(11);
            printf("   >> Tháng (1-12)       : %s\n", month);
            setColor(7);
        } else {
            printf("       Tháng (1-12)       : %s\n", month);
        }

        //In năm
        if (choice == 3) {
            setColor(11);
            printf("   >> Năm  (VD: 2026)    : %s\n", year);
            setColor(7);
        } else {
            printf("       Năm  (VD: 2026)    : %s\n", year);
        }

        //In xác nhận / thông báo lỗi
        if (fail == 1) {
            setColor(12);
            printf("   >> [Fail]. Phòng không hợp lệ\n");
            setColor(7);
            fail = 0;
        }
        else if (fail == 2) {
            setColor(12);
            printf("   >> [Fail]. Tháng không hợp lệ (1-12)\n");
            setColor(7);
            fail = 0;
        }
        else if (fail == 3) {
            setColor(12);
            printf("   >> [Fail]. Năm phải đủ 4 chữ số\n");
            setColor(7);
            fail = 0;
        }
        else if (fail == 4) {
            setColor(12);
            printf("   >> [Fail]. Phòng không có cư dân\n");
            setColor(7);
            fail = 0;
        }
        else if (choice == 4) {
            setColor(11);
            printf("   >> Tiếp tục\n");
            setColor(7);
        } else {
            printf("       Tiếp tục\n");
        }

        //Hướng dẫn
        printf("\nNhấn ▲ ▼ để di chuyển\n");
        printf("Nhấn Enter xác nhận\n");
        printf("Nhấn Esc để thoát\n");

        //Di chuyển con trỏ
        if (choice == 1) {
            gotoxy(27 + strlen(roomInput), 9);
        } else if (choice == 2) {
            gotoxy(27 + strlen(month),    10);
        } else if (choice == 3) {
            gotoxy(27 + strlen(year),     11);
        }

        //Nhận phím
        key = getch();

        //Điều hướng mũi tên
        if (key == 224) {
            key = getch();

            //Lên
            if (key == KEY_UP) {
                choice--;
                if (choice < 1) {
                    choice = 4;
                }
            }
            //Xuống
            else if (key == KEY_DOWN) {
                choice++;
                if (choice > 4) {
                    choice = 1;
                }
            }
        }

        //Esc để thoát
        else if (key == ESC) {
            return;
        }

        //Backspace
        else if (key == BACKSPACE) {

            //Phòng
            if (choice == 1 && strlen(roomInput) > 0) {
                roomInput[strlen(roomInput) - 1] = '\0';
            }

            //Tháng
            else if (choice == 2 && strlen(month) > 0) {
                month[strlen(month) - 1] = '\0';
            }

            //Năm
            else if (choice == 3 && strlen(year) > 0) {
                year[strlen(year) - 1] = '\0';
            }
        }

        //Enter
        else if (key == ENTER) {

            //Nếu đang chọn tiếp tục
            if (choice == 4) {

                //Kiểm tra phòng
                if (strlen(roomInput) != 3 || !isAllDigits(roomInput)) {
                    fail = 1;
                    continue;
                }
                int floor = roomInput[0] - '0';
                int room  = atoi(roomInput + 1);
                if (floor < 1 || floor > 5 || room < 1 || room > 5) {
                    fail = 1;
                    continue;
                }

                //Kiểm tra tháng
                int monthInt = atoi(month);
                if (strlen(month) == 0 || monthInt < 1 || monthInt > 12) {
                    fail = 2;
                    continue;
                }

                //Kiểm tra năm
                if (strlen(year) != 4) {
                    fail = 3;
                    continue;
                }

                //Kiểm tra phòng có cư dân không
                char folderPath[256];
                sprintf(folderPath, "FloorList/Floor%d/P%d%02d", floor, floor, room);

                DIR *dir = opendir(folderPath);
                int hasResident = 0;

                if (dir != NULL) {
                    struct dirent *entry;
                    while ((entry = readdir(dir)) != NULL) {
                        if (entry->d_name[0] == '.') continue;
                        if (strstr(entry->d_name, ".txt")) {
                            hasResident = 1;
                            break;
                        }
                    }
                    closedir(dir);
                }

                if (!hasResident) {
                    fail = 4;
                    continue;
                }

                //================ NHẬP SỐ ĐIỆN VÀ SỐ NƯỚC ================

                char electricStr[20] = "";
                char waterStr[20]    = "";
                int ic   = 1;
                int ik;
                int ifail = 0;

                while (1) {

                    //Làm sạch màn hình
                    system("cls");

                    //In tiêu đề
                    printf("\n");
                    printf("██╗███╗   ██╗██████╗ ██╗   ██╗████████╗    ██╗   ██╗████████╗██╗██╗     ██╗████████╗██╗███████╗███████╗\n");
                    printf("██║████╗  ██║██╔══██╗██║   ██║╚══██╔══╝    ██║   ██║╚══██╔══╝██║██║     ██║╚══██╔══╝██║██╔════╝██╔════╝\n");
                    printf("██║██╔██╗ ██║██████╔╝██║   ██║   ██║       ██║   ██║   ██║   ██║██║     ██║   ██║   ██║█████╗  ███████╗\n");
                    printf("██║██║╚██╗██║██╔═══╝ ██║   ██║   ██║       ██║   ██║   ██║   ██║██║     ██║   ██║   ██║██╔══╝  ╚════██║\n");
                    printf("██║██║ ╚████║██║     ╚██████╔╝   ██║       ╚██████╔╝   ██║   ██║███████╗██║   ██║   ██║███████╗███████║\n");
                    printf("╚═╝╚═╝  ╚═══╝╚═╝      ╚═════╝    ╚═╝        ╚═════╝    ╚═╝   ╚═╝╚══════╝╚═╝   ╚═╝   ╚═╝╚══════╝╚══════╝\n\n\n");

                    setColor(14);
                    printf("   Nhập số liệu cho phòng P%d%02d - Tháng %02d/%s\n\n", floor, room, monthInt, year);
                    setColor(7);

                    //Tính tiền
                    float ep    = atof(electricStr) * electricityRate;
                    float wp    = atof(waterStr) * waterRate;
                    float total = roomPrice + ep + wp;

                    //In số điện
                    if (ic == 1) {
                        setColor(11);
                        printf("   >> Số điện (kWh) : %s", electricStr);
                        if (strlen(electricStr) > 0) printf(" → %.0f VNĐ", ep);
                        printf("\n");
                        setColor(7);
                    } else {
                        printf("       Số điện (kWh) : %s", electricStr);
                        if (strlen(electricStr) > 0) printf(" → %.0f VNĐ", ep);
                        printf("\n");
                    }

                    //In số nước
                    if (ic == 2) {
                        setColor(11);
                        printf("   >> Số nước (m³)  : %s", waterStr);
                        if (strlen(waterStr) > 0) printf(" → %.0f VNĐ", wp);
                        printf("\n");
                        setColor(7);
                    } else {
                        printf("       Số nước (m³)  : %s", waterStr);
                        if (strlen(waterStr) > 0) printf(" → %.0f VNĐ", wp);
                        printf("\n");
                    }

                    //In bảng tổng
                    printf("\n");
                    printf("       Tiền phòng     : %.0f VNĐ\n", roomPrice);
                    printf("       Tiền điện      : %.0f VNĐ  (%s kWh x %.0f)\n", ep, electricStr, electricityRate);
                    printf("       Tiền nước      : %.0f VNĐ  (%s m³ x %.0f)\n",  wp, waterStr, waterRate);
                    setColor(10);
                    printf("       Tổng cộng      : %.0f VNĐ\n", total);
                    setColor(7);

                    //In xác nhận / thông báo lỗi
                    if (ifail == 1) {
                        setColor(12);
                        printf("\n   >> [Fail]. Số điện không hợp lệ\n");
                        setColor(7);
                        ifail = 0;
                    }
                    else if (ifail == 2) {
                        setColor(12);
                        printf("\n   >> [Fail]. Số nước không hợp lệ\n");
                        setColor(7);
                        ifail = 0;
                    }
                    else if (ic == 3) {
                        printf("\n");
                        setColor(11);
                        printf("   >> Xác nhận lưu\n");
                        setColor(7);
                    } else {
                        printf("\n       Xác nhận lưu\n");
                    }

                    //Hướng dẫn
                    printf("\nNhấn ▲ ▼ để di chuyển\n");
                    printf("Nhấn Enter xác nhận\n");
                    printf("Nhấn Esc để quay lại\n");

                    //Di chuyển con trỏ
                    if (ic == 1) {
                        gotoxy(22 + strlen(electricStr), 11);
                    } else if (ic == 2) {
                        gotoxy(22 + strlen(waterStr),   12);
                    }

                    //Nhận phím
                    ik = getch();

                    //Điều hướng mũi tên
                    if (ik == 224) {
                        ik = getch();

                        //Lên
                        if (ik == KEY_UP) {
                            ic--;
                            if (ic < 1) {
                                ic = 3;
                            }
                        }
                        //Xuống
                        else if (ik == KEY_DOWN) {
                            ic++;
                            if (ic > 3) {
                                ic = 1;
                            }
                        }
                    }

                    //Esc để quay lại
                    else if (ik == ESC) {
                        return;
                    }

                    //Backspace
                    else if (ik == BACKSPACE) {

                        //Số điện
                        if (ic == 1 && strlen(electricStr) > 0) {
                            electricStr[strlen(electricStr) - 1] = '\0';
                        }

                        //Số nước
                        else if (ic == 2 && strlen(waterStr) > 0) {
                            waterStr[strlen(waterStr) - 1] = '\0';
                        }
                    }

                    //Enter
                    else if (ik == ENTER) {

                        //Nếu đang chọn xác nhận lưu
                        if (ic == 3) {

                            //Kiểm tra số điện
                            float ev = atof(electricStr);
                            if (strlen(electricStr) == 0 || ev < 0) {
                                ifail = 1;
                                continue;
                            }

                            //Kiểm tra số nước
                            float wv = atof(waterStr);
                            if (strlen(waterStr) == 0 || wv < 0) {
                                ifail = 2;
                                continue;
                            }

                            //Tạo thư mục bill nếu chưa có
                            char billFolder[256];
                            sprintf(billFolder, "Data/Bill/Floor%d", floor);
                            CreateDirectoryA(billFolder, NULL);
                            sprintf(billFolder, "Data/Bill/Floor%d/P%d%02d", floor, floor, room);
                            CreateDirectoryA(billFolder, NULL);

                            //Tạo file hóa đơn
                            char billFile[300];
                            sprintf(billFile, "%s/%02d%s.txt", billFolder, monthInt, year);

                            FILE *bf = fopen(billFile, "w");
                            if (bf != NULL) {
                                fprintf(bf, "%.0f\n", roomPrice);
                                fprintf(bf, "%.0f\n", ev);
                                fprintf(bf, "%.0f\n", ev * electricityRate);
                                fprintf(bf, "%.0f\n", wv);
                                fprintf(bf, "%.0f\n", wv * waterRate);
                                fclose(bf);
                            }

                            //Thông báo thành công
                            gotoxy(0, 19);
                            setColor(10);
                            printf("       Lưu hóa đơn phòng P%d%02d tháng %02d/%s thành công!\n", floor, room, monthInt, year);
                            setColor(7);
                            printf("\nNhấn Enter hoặc Esc để thoát\n                                       \n                                   ");
                            printf("\n                                    \n                               \n");
                            
                            //Lưu lịch sử
                            char history[256];
                            sprintf(history, "Quản lý '%s' tạo hóa đơn cho P%d%02d với tổng tiền là %.0f cho tháng %02d/%s.", manage, floor, room, total, monthInt, year);
                            saveHistory("QUẢN LÝ", "THÀNH CÔNG", "Tạo hóa đơn", history);   

                            //Đợi người dùng thoát
                            while (1) {
                                ik = getch();
                                if (ik == ENTER || ik == ESC) {
                                    return;
                                }
                            }
                        }
                    }

                    //Nhập ký tự thường
                    else {

                        //Số điện
                        if (ic == 1 && strlen(electricStr) < 19) {
                            if (
                                (ik >= '0' && ik <= '9') ||
                                (ik == '.' && !strchr(electricStr, '.'))
                            ) {
                                int len = strlen(electricStr);
                                electricStr[len] = ik;
                                electricStr[len + 1] = '\0';
                            }
                        }

                        //Số nước
                        if (ic == 2 && strlen(waterStr) < 19) {
                            if (
                                (ik >= '0' && ik <= '9') ||
                                (ik == '.' && !strchr(waterStr, '.'))
                            ) {
                                int len = strlen(waterStr);
                                waterStr[len] = ik;
                                waterStr[len + 1] = '\0';
                            }
                        }
                    }
                }
            }
        }

        //Nhập ký tự thường
        else {

            //Phòng
            if (choice == 1 && strlen(roomInput) < 9 && key >= '0' && key <= '9') {
                int len = strlen(roomInput);
                roomInput[len] = key;
                roomInput[len + 1] = '\0';
            }

            //Tháng
            else if (choice == 2 && strlen(month) < 2 && key >= '0' && key <= '9') {
                int len = strlen(month);
                month[len] = key;
                month[len + 1] = '\0';
            }

            //Năm
            else if (choice == 3 && strlen(year) < 4 && key >= '0' && key <= '9') {
                int len = strlen(year);
                year[len] = key;
                year[len + 1] = '\0';
            }
        }
    }
}

//In logo tháng/năm
void printMonthYearLogoM(int month, char year[]) {

    //Định nghĩa từng chữ số 0-9 theo 6 dòng
    char *digits[10][6] = {
        // 0
        {
            " █████╗ ",
            "██╔══██╗",
            "██║  ██║",
            "██║  ██║",
            "╚█████╔╝",
            " ╚════╝ "
        },
        // 1
        {
            " ██╗",
            "███║",
            "╚██║",
            " ██║",
            " ██║",
            " ╚═╝"
        },
        // 2
        {
            "██████╗ ",
            "╚════██╗",
            " █████╔╝",
            "██╔═══╝ ",
            "███████╗",
            "╚══════╝"
        },
        // 3
        {
            "██████╗ ",
            "╚════██╗",
            " █████╔╝",
            " ╚═══██╗",
            "██████╔╝",
            "╚═════╝ "
        },
        // 4
        {
            "██╗  ██╗",
            "██║  ██║",
            "███████║",
            "╚════██║",
            "     ██║",
            "     ╚═╝"
        },
        // 5
        {
            "███████╗",
            "██╔════╝",
            "███████╗",
            "╚════██║",
            "███████║",
            "╚══════╝"
        },
        // 6
        {
            " ██████╗",
            "██╔════╝",
            "███████╗",
            "██╔══██║",
            "███████║",
            "╚══════╝"
        },
        // 7
        {
            "███████╗",
            "╚════██║",
            "    ██╔╝",
            "   ██╔╝ ",
            "   ██║  ",
            "   ╚═╝  "
        },
        // 8
        {
            " █████╗ ",
            "██╔══██╗",
            "╚█████╔╝",
            "██╔══██╗",
            "╚█████╔╝",
            " ╚════╝ "
        },
        // 9
        {
            " █████╗ ",
            "██╔══██╗",
            "╚██████║",
            " ╚═══██║",
            " █████╔╝",
            " ╚════╝ "
        }
    };

    //Dấu gạch chéo /
    char *slash[6] = {
        "    ██╗",
        "   ██╔╝",
        "  ██╔╝ ",
        " ██╔╝  ",
        "██╔╝   ",
        "╚═╝    "
    };

    //Khoảng trắng giữa các chữ số
    char *space[6] = {
        "  ",
        "  ",
        "  ",
        "  ",
        "  ",
        "  "
    };

    //Tạo mảng chứa các ký tự cần in: MM/YYYY
    char *parts[15][6];
    int count = 0;

    //Thêm chữ số tháng (2 chữ số)
    char ms[3];
    sprintf(ms, "%02d", month);

    for (int d = 0; d < 2; d++) {
        if (d > 0) {
            for (int r = 0; r < 6; r++) parts[count][r] = space[r];
            count++;
        }
        int idx = ms[d] - '0';
        for (int r = 0; r < 6; r++) parts[count][r] = digits[idx][r];
        count++;
    }

    //Thêm dấu /
    for (int r = 0; r < 6; r++) parts[count][r] = slash[r];
    count++;

    //Thêm 4 chữ số năm
    for (int d = 0; d < 4; d++) {
        if (d > 0) {
            for (int r = 0; r < 6; r++) parts[count][r] = space[r];
            count++;
        }
        int idx = year[d] - '0';
        for (int r = 0; r < 6; r++) parts[count][r] = digits[idx][r];
        count++;
    }

    //In từng dòng
    printf("\n");
    for (int row = 0; row < 6; row++) {
        printf("   ");
        for (int col = 0; col < count; col++) {
            printf("%s", parts[col][row]);
        }
        printf("\n");
    }
    printf("\n\n");
}

/*
    Xem danh sách hóa đơn theo tháng
                                       */
void viewBillByMonthManage() {

    //Khai báo biến cần thiết
    int choice = 1;
    int key;
    int fail = 0;

    char month[3] = "";
    char year[5]  = "";

    //Tạo vòng lặp
    while (1) {

        //Làm sạch màn hình
        system("cls");

        //In chữ VIEW BILL
        printf("\n");
        printf("██╗   ██╗██╗███████╗██╗    ██╗    ██████╗ ██╗██╗     ██╗     \n");
        printf("██║   ██║██║██╔════╝██║    ██║    ██╔══██╗██║██║     ██║     \n");
        printf("██║   ██║██║█████╗  ██║ █╗ ██║    ██████╔╝██║██║     ██║     \n");
        printf("╚██╗ ██╔╝██║██╔══╝  ██║███╗██║    ██╔══██╗██║██║     ██║     \n");
        printf(" ╚████╔╝ ██║███████╗╚███╔███╔╝    ██████╔╝██║███████╗███████╗\n");
        printf("  ╚═══╝  ╚═╝╚══════╝ ╚══╝╚══╝     ╚═════╝ ╚═╝╚══════╝╚══════╝\n\n\n");

        //In ô nhập tháng
        if (choice == 1) {
            setColor(11);
            printf("   >> Nhập tháng (1-12): %s\n", month);
            setColor(7);
        } else {
            printf("       Nhập tháng (1-12): %s\n", month);
        }

        //In ô nhập năm
        if (choice == 2) {
            setColor(11);
            printf("   >> Nhập năm (VD: 2026): %s\n", year);
            setColor(7);
        } else {
            printf("       Nhập năm (VD: 2026): %s\n", year);
        }

        //In xác nhận / thông báo lỗi
        if (fail == 1) {
            setColor(12);
            printf("   >> [Fail] Tháng không hợp lệ (1-12)\n");
            setColor(7);
            fail = 0;
        }
        else if (fail == 2) {
            setColor(12);
            printf("   >> [Fail] Năm phải đủ 4 chữ số\n");
            setColor(7);
            fail = 0;
        }
        else if (choice == 3) {
            setColor(11);
            printf("   >> Xác nhận\n");
            setColor(7);
        } else {
            printf("       Xác nhận\n");
        }

        //Hướng dẫn
        printf("\nNhấn ▲ ▼ để di chuyển\n");
        printf("Nhấn Enter xác nhận\n");
        printf("Nhấn Esc để thoát\n");

        //Di chuyển con trỏ
        if (choice == 1) {
            gotoxy(25 + strlen(month),  9);
        } else if (choice == 2) {
            gotoxy(27 + strlen(year),  10);
        }

        //Nhận phím
        key = getch();

        //Điều hướng mũi tên
        if (key == 224) {
            key = getch();

            //Lên
            if (key == KEY_UP) {
                choice--;
                if (choice < 1) {
                    choice = 3;
                }
            }
            //Xuống
            else if (key == KEY_DOWN) {
                choice++;
                if (choice > 3) {
                    choice = 1;
                }
            }
        }

        //Esc để thoát
        else if (key == ESC) {
            return;
        }

        //Backspace
        else if (key == BACKSPACE) {

            //Tháng
            if (choice == 1 && strlen(month) > 0) {
                month[strlen(month) - 1] = '\0';
            }

            //Năm
            else if (choice == 2 && strlen(year) > 0) {
                year[strlen(year) - 1] = '\0';
            }
        }

        //Enter
        else if (key == ENTER) {

            //Nếu đang chọn xác nhận
            if (choice == 3) {

                //Kiểm tra tháng
                int monthInt = atoi(month);
                if (strlen(month) == 0 || monthInt < 1 || monthInt > 12) {
                    fail = 1;
                    continue;
                }

                //Kiểm tra năm
                if (strlen(year) != 4) {
                    fail = 2;
                    continue;
                }

                //================ ĐỌC VÀ IN HÓA ĐƠN ================

                //Làm sạch màn hình
                system("cls");

                //In tiêu đề
                printf("\n");
                printMonthYearLogoM(monthInt, year);

                setColor(14);
                printf("\n   Hóa đơn tháng %d/%s\n\n", monthInt, year);
                setColor(7);

                //In bảng tiêu đề
                printf("   +----------+--------------------+--------------+--------------------+------------+--------------------+--------------------+\n");
                printf("   | Phòng    | Tiền phòng(VNĐ)    | Số điện(kWh) | Tiền điện(VNĐ)     | Số nước(m³)| Tiền nước(VNĐ)     | Tổng tiền(VNĐ)     |\n");
                printf("   +----------+--------------------+--------------+--------------------+------------+--------------------+--------------------+\n");

                //Tạo tên file theo tháng/năm
                char fileName[20];
                sprintf(fileName, "%02d%s.txt", monthInt, year);

                //Biến tổng doanh thu
                float totalRevenue = 0;

                //Cờ kiểm tra có hóa đơn nào không
                int hasBill = 0;

                //Duyệt qua từng tầng và từng phòng
                for (int floor = 1; floor <= 5; floor++) {
                    for (int room = 1; room <= 5; room++) {

                        //Tạo đường dẫn đến file hóa đơn
                        char pathFile[300];
                        sprintf(pathFile, "Data/Bill/Floor%d/P%d%02d/%s", floor, floor, room, fileName);

                        //Mở file
                        FILE *f = fopen(pathFile, "r");
                        if (f == NULL) continue;

                        //Đánh dấu có hóa đơn
                        hasBill = 1;

                        //Đọc dữ liệu
                        float roomPriceVal     = 0;
                        float electricityNumber = 0;
                        float electricityPrice  = 0;
                        float waterNumber      = 0;
                        float waterPrice       = 0;

                        fscanf(f, "%f", &roomPriceVal);
                        fscanf(f, "%f", &electricityNumber);
                        fscanf(f, "%f", &electricityPrice);
                        fscanf(f, "%f", &waterNumber);
                        fscanf(f, "%f", &waterPrice);
                        fclose(f);

                        //Tính tổng tiền của phòng
                        float total = roomPriceVal + electricityPrice + waterPrice;
                        totalRevenue += total;

                        //In thông tin ra bảng
                        printf("   | P%d%02d     | %-19.0f| %-13.0f| %-19.0f| %-11.0f| %-19.0f| %-19.0f|\n",
                            floor, room,
                            roomPriceVal,
                            electricityNumber,
                            electricityPrice,
                            waterNumber,
                            waterPrice,
                            total
                        );
                    }
                }

                //In dòng cuối bảng
                printf("   +----------+--------------------+--------------+--------------------+------------+--------------------+--------------------+\n");

                //In kết quả
                if (hasBill == 0) {
                    setColor(12);
                    printf("\n   Không có hóa đơn nào trong tháng %d/%s\n", monthInt, year);
                    setColor(7);
                } else {
                    setColor(10);
                    printf("\n   Tổng doanh thu tháng %d/%s: %.0f VNĐ\n", monthInt, year, totalRevenue);
                    setColor(7);
                }

                //Nhận phím
                printf("\nNhấn Enter hoặc Esc để quay lại\n");
                int k;
                while (1) {
                    k = getch();
                    if (k == ENTER || k == ESC) {
                        break;
                    }
                }
                return;
            }
        }

        //Nhập số
        else {

            //Tháng
            if (choice == 1 && key >= '0' && key <= '9' && strlen(month) < 2) {
                int len = strlen(month);
                month[len] = key;
                month[len + 1] = '\0';
            }

            //Năm
            else if (choice == 2 && key >= '0' && key <= '9' && strlen(year) < 4) {
                int len = strlen(year);
                year[len] = key;
                year[len + 1] = '\0';
            }
        }
    }
}

/*
    Menu chính của quản lý
                            */
void ManageLogin(char username[]) {

    //Lấy thông tin manage
    Manage manage;
    strcpy(manage.username, username);
    getManageInfo(&manage);

    //Khai báo hàm cần thiết
    int choice = 1;
    int key;
    char *options[] = {
        "Hiển thị thông tin quản lý",
        "Chỉnh sửa thông tin tài khoản quản lý",
        "Quản lý tài khoản cư dân",
        "Xem danh sách các phòng",
        "Tìm kiếm cư dân",
        "Nhập thông tin số điện, số nước",
        "Xem danh sách hóa đơn theo tháng",
        "Đăng xuất",
    };

    //Lấy số lượng phần tử trong mảng options
    int numOptions = sizeof(options) / sizeof(options[0]);

    //Tạo vòng lặp
    while (1) {

        //Làm sạch màn hình
        system("cls");

        //In chữ WELCOME MANAGE
        printf("\n");
        printf("██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗    ███╗   ███╗ █████╗ ███╗   ██╗ █████╗  ██████╗ ███████╗\n");
        printf("██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝    ████╗ ████║██╔══██╗████╗  ██║██╔══██╗██╔════╝ ██╔════╝\n");
        printf("██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗      ██╔████╔██║███████║██╔██╗ ██║███████║██║  ███╗█████╗  \n");
        printf("██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝      ██║╚██╔╝██║██╔══██║██║╚██╗██║██╔══██║██║   ██║██╔══╝  \n");
        printf("╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗    ██║ ╚═╝ ██║██║  ██║██║ ╚████║██║  ██║╚██████╔╝███████╗\n");
        printf(" ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝    ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝\n\n\n");

        //In nội dung lựa chọn
        for (int i = 0; i < numOptions; i++) {
            printContent(options[i], i + 1, choice);
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
                if (choice < 1) {
                    choice = numOptions;
                }
            }
            //Xuống
            else if (key == KEY_DOWN) {
                choice++;
                if (choice > numOptions) {
                    choice = 1;
                }
            }
        }

        //Enter
        else if (key == ENTER) {
            switch (choice) {
                case 1:
                    printManageInfo(manage);
                    break;
                case 2:
                    editManageSelfInfo(&manage);
                    break;
                case 3:
                    accountResident(manage.username);
                    break;
                case 4:
                    viewRoomList();
                    break;
                case 5:
                    searchResident();
                    break;
                case 6:
                    inputUtilities(manage.username);
                    break;
                case 7:
                    viewBillByMonthManage();
                    break;
                case 8:
                    logout();
                    return;
            }
        }
    }
}