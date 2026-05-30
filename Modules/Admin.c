//Thư viện 
#include "Admin.h"
#include "Utils.h"
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>
#include <dirent.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define BACKSPACE 8
#define ENTER 13
#define ESC 27

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

typedef struct Admin {
    char username[50];
    char password[50];
    char name[50];
    char CCCD[20];
    char year[10];
    char gender[10];
    char province[50];
    char phone[20];
} Admin;

//Lấy thông tin admin
void getAdminInfo(Admin *admin) {

    //Tạo đường dẫn đầy đủ đến file tài khoản Admin
    char path[256];
    sprintf(path, "Data/Account/Admin/%s.txt", admin->username);

    //Mở file
    FILE *f = fopen(path, "r");

    //Nếu file không tồn tại
    if (f == NULL) {
        return;
    }

    //Đọc thông tin cá nhân từ file
    fgets(admin->password, sizeof(admin->password), f);    admin->password[strcspn(admin->password, "\n")] = '\0';  
    fgets(admin->name, sizeof(admin->name), f);            admin->name[strcspn(admin->name, "\n")] = '\0';
    fgets(admin->CCCD, sizeof(admin->CCCD), f);            admin->CCCD[strcspn(admin->CCCD, "\n")] = '\0';  
    fgets(admin->year, sizeof(admin->year), f);            admin->year[strcspn(admin->year, "\n")] = '\0';  
    fgets(admin->gender, sizeof(admin->gender), f);        admin->gender[strcspn(admin->gender, "\n")] = '\0';  
    fgets(admin->province, sizeof(admin->province), f);    admin->province[strcspn(admin->province, "\n")] = '\0';  
    fgets(admin->phone, sizeof(admin->phone), f);          admin->phone[strcspn(admin->phone, "\n")] = '\0';  

    //Đóng file
    fclose(f);
}

/*
    Hiển thị thông tin cá nhân
                                */
void printAdminInfo(Admin admin) {

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

    printf("       Userame        : %s\n", admin.username);
    printf("       Tên            : %s\n", admin.name);
    printf("       CCCD           : %s\n", admin.CCCD);
    printf("       Năm sinh       : %s\n", admin.year);
    printf("       Giới tính      : %s\n", admin.gender);
    printf("       Quê quán       : %s\n", admin.province);
    printf("       Số điện thoại  : %s\n", admin.phone);

    //Nhấn enter hoặc esc để quay lại
    printf("\nNhấn Enter hoặc Esc để quay lại\n");

    //Nhận phím từ người dùng
    int key = getch();
    while (key != ENTER && key != ESC) {
        key = getch();
    }
}

//Sửa tên tài khoản
void editUsernameAdmin(char username[]) {

    //Khai báo hàm cần thiết
    char newUsername[50] = "";
    int choice = 1;
    int key;
    int fail = 0;
    char *contents[] = {
        "Nhập Username mới: ",
        "Xác nhận",
    };

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
        if(choice == 1) {
            setColor(11);
            printf("   >> %s%s\n", contents[0], newUsername);
            setColor(7);
        } else {
            printf("       %s%s\n", contents[0], newUsername);
        }

        //In chỗ xác nhận
        if(fail == 1) {
            setColor(12);
            printf("   >> [Fail]. Username không hợp lệ\n");
            setColor(7);
            fail = 0;
        } else if (fail == 2) {
            setColor(12);
            printf("   >> [Fail]. Username đã tồn tại\n");
            setColor(7);
            fail = 0;
        } else if(choice == 2) {
            setColor(11);
            printf("   >> %s\n", contents[1]);
            setColor(7);
        } else {
            printf("       %s\n", contents[1]);
        }

        //In hướng dẫn
        printf("\nNhấn ▲ ▼ để di chuyển\n");
        printf("Nhấn Enter xác nhận\n");
        printf("Nhấn Esc để thoát\n");
        
        //Di chuyển con trỏ đến vị trí nhập username
        gotoxy(24 + strlen(newUsername) + 1, 9);

        //Điều hướng mũi tên
        key = getch();
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

        //Backspace để xóa từ ký tự
        else if(key == BACKSPACE) {
            if(choice == 1 && strlen(newUsername) > 0) {
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

                //Tạo Path đầy đủ
                char oldPath[100];
                char newPath[100];

                sprintf(oldPath, "Data/Account/Admin/%s.txt", username);
                sprintf(newPath, "Data/Account/Admin/%s.txt", newUsername);

                if (checkDuplicateUsername(newUsername, newPath) == 1){
                    //In thông báo username đã tồn tại
                    fail = 2;
                    continue;
                }

                //Rename username
                if (rename(oldPath, newPath) == 0) {
                    strcpy(username, newUsername);
                }

                //In thông báo đổi username thành công
                setColor(10);
                printf("\n       Đổi Username thành công!\n");
                setColor(7);
                printf("\nNhấn Enter hoặc Esc để thoát\n                                       \n                                   ");

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
            if(choice == 1 && strlen(newUsername) < 49) {

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

//Sửa tên thật
void editNameAdmin(Admin *admin) {

    //Khai báo hàm cần thiết
    int choice = 1;
    int key;
    int fail = 0;
    char newName[50] = "";
    char *contents[] = {
        "Nhập tên mới: ",
        "Xác nhận",
    };

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
        if(choice == 1) {
            setColor(11);
            printf("   >> %s%s\n", contents[0], newName);
            setColor(7);
        } else {
            printf("       %s%s\n", contents[0], newName);
        }

        //In chỗ xác nhận
        if (fail) {
            setColor(12);
            printf("   >> Tên không hợp lệ");
            setColor(7);
            fail = 0;
        } else if(choice == 2) {
            setColor(11);
            printf("   >> %s\n", contents[1]);
            setColor(7);
        } else {
            printf("       %s\n", contents[1]);
        }

        //In hướng dẫn
        printf("\nNhấn ▲ ▼ để di chuyển\n");
        printf("Nhấn Enter xác nhận\n");
        printf("Nhấn Esc để thoát\n");

        //Di chuyển con trỏ đến vị trí mới
        gotoxy(20 + strlen(newName), 9);

        //Điều hướng mũi tên
        key = getch();
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

        //Backspace để xóa từ ký tự
        else if(key == BACKSPACE) {
            if(choice == 1 && strlen(newName) > 0) {
                newName[strlen(newName) - 1] = '\0';
            }
        } 

        //Enter để xác nhận
        else if (key == ENTER) {

            //Nếu đang chọn xác nhận
            if (choice == 2) {

                //Kiểm tra có phải toàn chữ hay không
                if(isOnlyLetter(newName) == 0) {
                    fail = 1;
                    continue;
                }

                //Kiểm tra có rỗng không
                if(strlen(newName) == 0) {
                    fail = 1;
                    continue;
                }

                //Chuẩn hóa tên

                //Cập nhật mật khẩu mới vào struct admin
                strncpy(admin->name, newName, sizeof(admin->name) - 1);		admin->name[sizeof(admin->name) - 1] = '\0';

                //Cập nhật mật khẩu mới vào file
                char path[256];
                sprintf(path, "Data/Account/Admin/%s.txt", admin->username);
                FILE *f = fopen(path, "w");
                if (f != NULL) {
                    
                    //Ghi lại toàn bộ thông tin cá nhân vào file với mật khẩu mới
                    fprintf(f, "%s\n", admin->password);
                    fprintf(f, "%s\n", admin->name);
                    fprintf(f, "%s\n", admin->CCCD);
                    fprintf(f, "%s\n", admin->year);
                    fprintf(f, "%s\n", admin->gender);
                    fprintf(f, "%s\n", admin->province);
                    fprintf(f, "%s\n", admin->phone);
                    fclose(f);
                }

                //In thông báo đổi username thành công
                setColor(10);
                printf("\n       Đổi tên thành công!\n");
                setColor(7);
                printf("\nNhấn Enter hoặc Esc để thoát\n                                       \n                                   ");

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
void editPassword(Admin *admin) {

    //Khai báo hàm cần thiết
    int choice = 1;
    int key;
    int fail = 0;
    char newPassword[50] = "";
    char oldPassword[50] = "";
    char *contents[] = {
        "Nhập mật khẩu cũ: ",
        "Nhập mật khẩu mới: ",
        "Xác nhận",
    };

    //Tạo vòng lặp để tạo bảng và lựa chọn
    while (1) {

        //Làm sạch màng hình
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
        if(choice == 1) {
            setColor(11);
            printf("   >> %s", contents[0]);
            for(int i = 0; i < strlen(oldPassword); i++) {
                printf("*");
            }
            printf("\n");
            setColor(7);
        } else {
            printf("       %s", contents[0]);
            for(int i = 0; i < strlen(oldPassword); i++) {
                printf("*");
            }
            printf("\n");
        }

        //In chỗ nhập mật khẩu mới
        if(choice == 2) {
            setColor(11);
            printf("   >> %s", contents[1]);
            for(int i = 0; i < strlen(newPassword); i++) {
                printf("*");
            }
            printf("\n");
            setColor(7);
        } else {
            printf("       %s", contents[1]);
            for(int i = 0; i < strlen(newPassword); i++) {
                printf("*");
            }
            printf("\n");
        }

        //In chỗ xác nhận
        if(fail == 1) {
            setColor(12);
            printf("   >> [Fail]. Mật khẩu không hợp lệ\n");
            setColor(7);
            fail = 0;
        } else if(fail == 2) {
            setColor(12);
            printf("   >> [Fail]. Mật khẩu cũ không đúng\n");
            setColor(7);
            fail = 0;
        } else if(choice == 3) {
            setColor(11);
            printf("   >> %s\n", contents[2]);
            setColor(7);
        } else {
            printf("       %s\n", contents[2]);
        }

        //In hướng dẫn
        printf("\nNhấn ▲ ▼ để di chuyển\n");
        printf("Nhấn Enter xác nhận\n");
        printf("Nhấn Esc để thoát\n");

        //Di chuyển con trỏ đến vị trí nhập mật khẩu mới
        if(choice == 1) {
            gotoxy(23 + strlen(oldPassword) + 1, 9);
        } else if(choice == 2) {
            gotoxy(24 + strlen(newPassword) + 1, 10);
        }

        //Điều hướng mũi tên
        key = getch();
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

        //Backspace để xóa từ ký tự
        else if(key == BACKSPACE) {
            if(choice == 1 && strlen(oldPassword) > 0) {
                oldPassword[strlen(oldPassword) - 1] = '\0';
            }
        else if(choice == 2 && strlen(newPassword) > 0) {
                newPassword[strlen(newPassword) - 1] = '\0';
            }
        }

        //Enter
        else if (key == ENTER) {

            //Nếu đang chọn xác nhận
            if (choice == 3) {

                //Kiểm tra mật khẩu mới có hợp lệ hay không
                if (checkPassword(newPassword) == 0) {
                    //In thông báo số điện thoại không hợp lệ
                    fail = 1;
                    continue;
                }

                //Kiểm tra mật khẩu cũ có đúng hay không
                if (strcmp(oldPassword, admin->password) != 0) {
                    //In thông báo mật khẩu cũ không đúng
                    fail = 2;
                    continue;
                }

                //Cập nhật mật khẩu mới vào struct admin
                strncpy(admin->password, newPassword, sizeof(admin->password) - 1);		admin->password[sizeof(admin->password) - 1] = '\0';

                //Cập nhật mật khẩu mới vào file
                char path[256];
                sprintf(path, "Data/Account/Admin/%s.txt", admin->username);
                FILE *f = fopen(path, "w");
                if (f != NULL) {
                    
                    //Ghi lại toàn bộ thông tin cá nhân vào file với mật khẩu mới
                    fprintf(f, "%s\n", admin->password);
                    fprintf(f, "%s\n", admin->name);
                    fprintf(f, "%s\n", admin->CCCD);
                    fprintf(f, "%s\n", admin->year);
                    fprintf(f, "%s\n", admin->gender);
                    fprintf(f, "%s\n", admin->province);
                    fprintf(f, "%s\n", admin->phone);
                    fclose(f);
                }

                //In thông báo đổi mật khẩu thành công
                gotoxy(7, 10);
                setColor(10);
                printf("\n       Đổi mật khẩu thành công!\n");
                setColor(7);
                printf("\nNhấn Enter hoặc Esc để thoát\n                                       \n                                   ");

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
            if(choice == 1 && strlen(oldPassword) < 49) {
                int len = strlen(oldPassword);
                oldPassword[len] = key;
                oldPassword[len + 1] = '\0';
            }
            else if(choice == 2 && strlen(newPassword) < 49) {
                int len = strlen(newPassword);
                newPassword[len] = key;
                newPassword[len + 1] = '\0';
            }
        }
    }
}

//Đổi số điện thoại
void editPhoneNumber(Admin *admin) {

    //Khai báo hàm cần thiết
    int choice = 1;
    int key;
    int fail = 0;
    char newPhone[20] = "";
    char *contents[] = {
        "Nhập số điện thoại mới: ",
        "Xác nhận",
    };

    //Tạo vòng lặp để tạo bảng và lựa chọn
    while (1) {
    	
    	//Làm sạch màng hình
    	system("cls");
    	
        //In chữ CHANGE NUMBER
        printf("\n");
        printf(" ██████╗██╗  ██╗ █████╗ ███╗   ██╗ ██████╗ ███████╗    ██████╗ ██╗  ██╗ ██████╗ ███╗   ██╗███████╗    ███╗   ██╗██╗   ██╗███╗   ███╗██████╗ ███████╗██████╗ \n");
        printf("██╔════╝██║  ██║██╔══██╗████╗  ██║██╔════╝ ██╔════╝    ██╔══██╗██║  ██║██╔═══██╗████╗  ██║██╔════╝    ████╗  ██║██║   ██║████╗ ████║██╔══██╗██╔════╝██╔══██╗\n");
        printf("██║     ███████║███████║██╔██╗ ██║██║  ███╗█████╗      ██████╔╝███████║██║   ██║██╔██╗ ██║█████╗      ██╔██╗ ██║██║   ██║██╔████╔██║██████╔╝█████╗  ██████╔╝\n");
        printf("██║     ██╔══██║██╔══██║██║╚██╗██║██║   ██║██╔══╝      ██╔═══╝ ██╔══██║██║   ██║██║╚██╗██║██╔══╝      ██║╚██╗██║██║   ██║██║╚██╔╝██║██╔══██╗██╔══╝  ██╔══██╗\n");
        printf("╚██████╗██║  ██║██║  ██║██║ ╚████║╚██████╔╝███████╗    ██║     ██║  ██║╚██████╔╝██║ ╚████║███████╗    ██║ ╚████║╚██████╔╝██║ ╚═╝ ██║██████╔╝███████╗██║  ██║\n");
        printf(" ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝ ╚═════╝ ╚══════╝    ╚═╝     ╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝    ╚═╝  ╚═══╝ ╚═════╝ ╚═╝     ╚═╝╚═════╝ ╚══════╝╚═╝  ╚═╝\n\n\n");

        //In chỗ nhập số điện thoại mới
        if(choice == 1) {
            setColor(11);
            printf("   >> %s%s\n", contents[0], newPhone);
            setColor(7);
        } else {
            printf("       %s%s\n", contents[0], newPhone);
        }

        //In chỗ xác nhận
        if(fail) {
            setColor(12);
            printf("   >> [Fail]. Số điện thoại không hợp lệ\n");
            setColor(7);
            fail = 0;
        } else if(choice == 2) {
            setColor(11);
            printf("   >> %s\n", contents[1]);
            setColor(7);
        } else {
            printf("       %s\n", contents[1]);
        }

        //In hướng dẫn
        printf("\nNhấn ▲ ▼ để di chuyển\n");
        printf("Nhấn Enter xác nhận\n");
        printf("Nhấn Esc để thoát\n");
        
        //Di chuyển con trỏ đến vị trí nhập số điện thoại
        gotoxy(30 + strlen(newPhone) + 1, 9);
        
        //Điều hướng mũi tên
        key = getch();
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

        //Enter để xác nhận
        else if (key == ENTER) {

            //Nếu đang chọn xác nhận
            if (choice == 2) {

                if (checkPhoneNumber(newPhone) == 0) {
                    //In thông báo số điện thoại không hợp lệ
                    fail = 1;
                    continue;
                }

                //Cập nhật số điện thoại mới vào struct admin
                strncpy(admin->phone, newPhone, sizeof(admin->phone) - 1);		admin->phone[sizeof(admin->phone) - 1] = '\0';

                //Cập nhật số điện thoại mới vào file
                char path[256];
                sprintf(path, "Data/Account/Admin/%s.txt", admin->username);
                FILE *f = fopen(path, "w");
                if (f != NULL) {
                    
                    //Ghi lại toàn bộ thông tin cá nhân vào file với số điện thoại mới
                    fprintf(f, "%s\n", admin->password);
                    fprintf(f, "%s\n", admin->name);
                    fprintf(f, "%s\n", admin->CCCD);
                    fprintf(f, "%s\n", admin->year);
                    fprintf(f, "%s\n", admin->gender);
                    fprintf(f, "%s\n", admin->province);
                    fprintf(f, "%s\n", admin->phone);
                    fclose(f);
                }

                //In thông báo đổi số điện thoại thành công
                setColor(10);
                printf("\n       Đổi số điện thoại thành công!\n");
                setColor(7);
                printf("\nNhấn Enter hoặc Esc để thoát\n                                       \n                                   ");

                //Đợi người dùng nhấn Enter hoặc Esc
                while (1) {
                    key = getch();
                    if (key == ENTER || key == ESC) {
                        return;
                    }
                }
            }
        } 

        //Esc để thoát
        else if (key == ESC) {
            return;
        }

        //Backspace để xóa từ ký tự
        else if(key == BACKSPACE) {
            if(choice == 1 && strlen(newPhone) > 0) {
                newPhone[strlen(newPhone) - 1] = '\0';
            }
        } 

        //Nhập ký tự thường
        else {
            if(choice == 1 && strlen(newPhone) < 19 && key >= '0' && key <= '9') {
                int len = strlen(newPhone);
                newPhone[len] = key;
                newPhone[len + 1] = '\0';
            }
        }
    }
}

/*
    Chỉnh sửa thông tin cá nhân
                                */
void editOtherInfoAdmin (Admin *admin) {

    //Khai báo hàm cần thiết
    int choice = 1;
    int key;
    char *options[] = {
        "Sửa tên tài khoản",
        "Sửa tên",
        "Đổi mật khẩu",
        "Đổi số điện thoại",
        "thoát",
    };

    //Lấy số lượng phần tử trong mảng options
    int numOptions = sizeof(options) / sizeof(options[0]);

    //Tạo vòng lặp để tạo bảng và lựa chọn
    while (1) {

        //làm sạch màn hình
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
                    editUsernameAdmin(admin->username);
                    break;
                case 2:
                    editNameAdmin(admin);
                    break;
                case 3:
                    editPassword(admin);
                    break;
                case 4:
                    editPhoneNumber(admin);
                    break;
                case 5:
                    return;
            }
        }
    }
}

//Tạo tài khoản quản lý
void createManageAccount() {

    //Khai báo biến cần thiết
    int choice = 1;
    int key;
    int fail = 0;

    char username[50] = "";
    char name[100] = "";
    char password[50] = "";
    char CCCD[20] = "";
    char year[10] = "";
    char gender[10] = "";
    char province[50] = "";
    char phone[20] = "";

    char *contents[] = {
        "Nhập username: ",
        "Nhập tên thật: ",
        "Nhập mật khẩu: ",
        "Nhập CCCD: ",
        "Nhập số điện thoại: ",
        "Xác nhận",
    };

    //Tạo vòng lặp
    while (1) {

        //Làm sạch màn hình
        system("cls");

        //In chữ CREATE ADMIN ACCOUNT
        printf("\n");
        printf(" ██████╗██████╗ ███████╗ █████╗ ████████╗███████╗     █████╗  ██████╗ ██████╗ ██████╗ ██╗   ██╗███╗   ██╗████████╗\n");
        printf("██╔════╝██╔══██╗██╔════╝██╔══██╗╚══██╔══╝██╔════╝    ██╔══██╗██╔════╝██╔════╝██╔═══██╗██║   ██║████╗  ██║╚══██╔══╝\n");
        printf("██║     ██████╔╝█████╗  ███████║   ██║   █████╗      ███████║██║     ██║     ██║   ██║██║   ██║██╔██╗ ██║   ██║   \n");
        printf("██║     ██╔══██╗██╔══╝  ██╔══██║   ██║   ██╔══╝      ██╔══██║██║     ██║     ██║   ██║██║   ██║██║╚██╗██║   ██║   \n");
        printf("╚██████╗██║  ██║███████╗██║  ██║   ██║   ███████╗    ██║  ██║╚██████╗╚██████╗╚██████╔╝╚██████╔╝██║ ╚████║   ██║   \n");
        printf(" ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝    ╚═╝  ╚═╝ ╚═════╝ ╚═════╝ ╚═════╝  ╚═════╝ ╚═╝  ╚═══╝   ╚═╝   \n\n\n");

        //In username
        if(choice == 1) {
            setColor(11);
            printf("   >> %s%s\n", contents[0], username);
            setColor(7);
        } else {
            printf("       %s%s\n", contents[0], username);
        }

        //In tên thật
        if(choice == 2) {
            setColor(11);
            printf("   >> %s%s\n", contents[1], name);
            setColor(7);
        } else {
            printf("       %s%s\n", contents[1], name);
        }

        //In mật khẩu
        if(choice == 3) {
            setColor(11);
            printf("   >> %s", contents[2]);

            for(int i = 0; i < strlen(password); i++) {
                printf("*");
            }

            printf("\n");
            setColor(7);
        } else {

            printf("       %s", contents[2]);

            for(int i = 0; i < strlen(password); i++) {
                printf("*");
            }

            printf("\n");
        }

        //In CCCD
        if(choice == 4) {
            setColor(11);
            printf("   >> %s%s\n", contents[3], CCCD);
            setColor(7);
        } else {
            printf("       %s%s\n", contents[3], CCCD);
        }

        //In số điện thoại
        if(choice == 5) {
            setColor(11);
            printf("   >> %s%s\n", contents[4], phone);
            setColor(7);
        } else {
            printf("       %s%s\n", contents[4], phone);
        }

        //In xác nhận
        if(fail == 1) {
            setColor(12);
            printf("   >> [Fail]. Username không hợp lệ\n");
            setColor(7);
            fail = 0;
        }
        else if(fail == 2) {
            setColor(12);
            printf("   >> [Fail]. Username đã tồn tại\n");
            setColor(7);
            fail = 0;
        }
        else if(fail == 3) {
            setColor(12);
            printf("   >> [Fail]. Tên không hợp lệ\n");
            setColor(7);
            fail = 0;
        }
        else if(fail == 4) {
            setColor(12);
            printf("   >> [Fail]. Mật khẩu không hợp lệ\n");
            setColor(7);
            fail = 0;
        }
        else if(fail == 5) {
            setColor(12);
            printf("   >> [Fail]. CCCD không hợp lệ\n");
            setColor(7);
            fail = 0;
        }
        else if(fail == 6) {
            setColor(12);
            printf("   >> [Fail]. Số điện thoại không hợp lệ\n");
            setColor(7);
            fail = 0;
        }
        else if(choice == 6) {
            setColor(11);
            printf("   >> %s\n", contents[5]);
            setColor(7);
        } else {
            printf("       %s\n", contents[5]);
        }

        //In hướng dẫn
        printf("\nNhấn ▲ ▼ để di chuyển\n");
        printf("Nhấn Enter xác nhận\n");
        printf("Nhấn Esc để thoát\n");

        //Di chuyển con trỏ
        if(choice == 1) {
            gotoxy(21 + strlen(username), 9);
        }
        else if(choice == 2) {
            gotoxy(21 + strlen(name), 10);
        }
        else if(choice == 3) {
            gotoxy(21 + strlen(password), 11);
        }
        else if(choice == 4) {
            gotoxy(17 + strlen(CCCD), 12);
        }
        else if(choice == 5) {
            gotoxy(26 + strlen(phone), 13);
        }

        //Nhận phím
        key = getch();

        //Điều hướng mũi tên
        if(key == 224) {

            key = getch();

            //Lên
            if(key == KEY_UP) {

                choice--;

                if(choice < 1) {
                    choice = 6;
                }
            }

            //Xuống
            else if(key == KEY_DOWN) {

                choice++;

                if(choice > 6) {
                    choice = 1;
                }
            }
        }

        //Esc để thoát
        else if(key == ESC) {
            return;
        }

        //Backspace
        else if(key == BACKSPACE) {

            //Username
            if(choice == 1 && strlen(username) > 0) {
                username[strlen(username) - 1] = '\0';
            }

            //Tên
            else if(choice == 2 && strlen(name) > 0) {
                name[strlen(name) - 1] = '\0';
            }

            //Mật khẩu
            else if(choice == 3 && strlen(password) > 0) {
                password[strlen(password) - 1] = '\0';
            }

            //CCCD
            else if(choice == 4 && strlen(CCCD) > 0) {
                CCCD[strlen(CCCD) - 1] = '\0';
            }

            //Số điện thoại
            else if(choice == 5 && strlen(phone) > 0) {
                phone[strlen(phone) - 1] = '\0';
            }
        }

        //Enter
        else if(key == ENTER) {

            //Nếu đang chọn xác nhận
            if(choice == 6) {

                //Kiểm tra username
                if(checkUsername(username) == 0 || strlen(username) < 3) {
                    fail = 1;
                    continue;
                }

                //Kiểm tra username trùng
                char path[256];
                sprintf(path, "Data/Account/Manage/%s.txt", username);
                if(checkDuplicateUsername(username, path) == 1) {
                    fail = 2;
                    continue;
                }

                //Kiểm tra tên
                if(strlen(name) == 0) {
                    fail = 3;
                    continue;
                }

                //Kiểm tra mật khẩu
                if(checkPassword(password) == 0) {
                    fail = 4;
                    continue;
                }

                //Kiểm tra CCCD
                if(checkCCCD(year, province, CCCD, gender) == 0) {
                    fail = 5;
                    continue;
                }

                //Kiểm tra số điện thoại
                if(checkPhoneNumber(phone) == 0) {
                    fail = 6;
                    continue;
                }

                //Tạo đường dẫn file
                sprintf(path, "Data/Account/Manage/%s.txt", username);

                //Tạo file
                FILE *f = fopen(path, "w");

                //Kiểm tra file
                if(f != NULL) {

                    //Ghi thông tin vào file
                    fprintf(f, "%s\n", password);
                    fprintf(f, "%s\n", name);
                    fprintf(f, "%s\n", CCCD);
                    fprintf(f, "%s\n", year);
                    fprintf(f, "%s\n", gender);
                    fprintf(f, "%s\n", province);
                    fprintf(f, "%s\n", phone);

                    fclose(f);
                }

                //Thông báo thành công
                gotoxy(6, 13);
                setColor(10);
                printf("\n       Tạo tài khoản thành công!\n");
                setColor(7);

                printf("\nNhấn Enter hoặc Esc để thoát\n                                       \n                                   ");

                //Đợi người dùng thoát
                while (1) {

                    key = getch();

                    if(key == ENTER || key == ESC) {
                        return;
                    }
                }
            }
        }

        //Nhập ký tự thường
        else {

            //Username
            if(choice == 1 && strlen(username) < 49) {

                if(
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
            else if(choice == 2 && strlen(name) < 99) {

                int len = strlen(name);

                name[len] = (char)key;
                name[len + 1] = '\0';
            }

            //Mật khẩu
            else if(choice == 3 && strlen(password) < 49) {

                if(key >= 32 && key <= 126) {

                    int len = strlen(password);

                    password[len] = key;
                    password[len + 1] = '\0';
                }
            }

            //CCCD
            else if(choice == 4 && strlen(CCCD) < 19) {

                if(key >= '0' && key <= '9') {

                    int len = strlen(CCCD);

                    CCCD[len] = key;
                    CCCD[len + 1] = '\0';
                }
            }

            //Số điện thoại
            else if(choice == 5 && strlen(phone) < 19) {

                if(key >= '0' && key <= '9') {

                    int len = strlen(phone);

                    phone[len] = key;
                    phone[len + 1] = '\0';
                }
            }
        }
    }
}

//Đọc thông tin manage từ file
int loadManageInfo(char *username, Manage *manage) {
    char path[256];
    sprintf(path, "Data/Account/Manage/%s.txt", username);

    FILE *f = fopen(path, "r");
    if(f == NULL) return 0; // Không tìm thấy

    fgets(manage->password, sizeof(manage->password), f); manage->password[strcspn(manage->password, "\n")] = '\0';
    fgets(manage->name,     sizeof(manage->name),     f); manage->name[strcspn(manage->name, "\n")] = '\0';
    fgets(manage->CCCD,     sizeof(manage->CCCD),     f); manage->CCCD[strcspn(manage->CCCD, "\n")] = '\0';
    fgets(manage->year,     sizeof(manage->year),     f); manage->year[strcspn(manage->year, "\n")] = '\0';
    fgets(manage->gender,   sizeof(manage->gender),   f); manage->gender[strcspn(manage->gender, "\n")] = '\0';
    fgets(manage->province, sizeof(manage->province), f); manage->province[strcspn(manage->province, "\n")] = '\0';
    fgets(manage->phone,    sizeof(manage->phone),    f); manage->phone[strcspn(manage->phone, "\n")] = '\0';

    fclose(f);
    return 1; // Thành công
}

//Lưu thông tin
int saveManageInfo(Manage *manage, char *oldUsername, char *oldCCCD) {

    if(checkUsername(manage->username) == 0 || strlen(manage->username) < 3) return 1;

    if(checkDuplicateUsername(manage->username, oldUsername) == 1)
        if(strcmp(manage->username, oldUsername) != 0) return 1;

    if(checkPassword(manage->password) == 0) return 2;

    if(strlen(manage->name) == 0) return 3;

    // Chỉ kiểm tra CCCD nếu có nhập
    if(strlen(manage->CCCD) > 0) {

        // Chỉ báo lỗi nếu trùng với người KHÁC
        if(checkDuplicateCCCD(manage->CCCD) == 1)
            if(strcmp(manage->CCCD, oldCCCD) != 0) return 4;

        // Dùng hàm validate thuần — không check duplicate
        if(checkCCCDOnly(manage->year, manage->province, manage->CCCD, manage->gender) == 0) return 4;
    }

    if(checkPhoneNumber(manage->phone) == 0) return 5;

    // Lưu file
    char savePath[256], oldPath[256];
    sprintf(savePath, "Data/Account/Manage/%s.txt", manage->username);
    sprintf(oldPath,  "Data/Account/Manage/%s.txt", oldUsername);

    if(strcmp(oldUsername, manage->username) != 0)
        rename(oldPath, savePath);

    FILE *save = fopen(savePath, "w");
    if(save != NULL) {
        fprintf(save, "%s\n", manage->password);
        fprintf(save, "%s\n", manage->name);
        fprintf(save, "%s\n", manage->CCCD);
        fprintf(save, "%s\n", manage->year);
        fprintf(save, "%s\n", manage->gender);
        fprintf(save, "%s\n", manage->province);
        fprintf(save, "%s\n", manage->phone);
        fclose(save);
    }

    return 0; // Thành công
}

//Chỉnh sửa thông tin quản lý
void editManageInfo() {

    //Khai báo biến cần thiết
    int choice = 1;
    int key;
    int fail = 0;

    char username[50] = "";

    Manage manage;

    char *contents[] = {
        "Nhập username quản lý: ",
        "Xác nhận",
    };

    //Tạo vòng lặp
    while (1) {

        //Làm sạch màn hình
        system("cls");

        //In chữ EDIT MANAGE INFO
        printf("\n");
        printf("███████╗██████╗ ██╗████████╗    ███╗   ███╗ █████╗ ███╗   ██╗ █████╗  ██████╗ ███████╗\n");
        printf("██╔════╝██╔══██╗██║╚══██╔══╝    ████╗ ████║██╔══██╗████╗  ██║██╔══██╗██╔════╝ ██╔════╝\n");
        printf("█████╗  ██║  ██║██║   ██║       ██╔████╔██║███████║██╔██╗ ██║███████║██║  ███╗█████╗  \n");
        printf("██╔══╝  ██║  ██║██║   ██║       ██║╚██╔╝██║██╔══██║██║╚██╗██║██╔══██║██║   ██║██╔══╝  \n");
        printf("███████╗██████╔╝██║   ██║       ██║ ╚═╝ ██║██║  ██║██║ ╚████║██║  ██║╚██████╔╝███████╗\n");
        printf("╚══════╝╚═════╝ ╚═╝   ╚═╝       ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝\n\n\n");

        //In ô nhập username
        if(choice == 1) {
            setColor(11);
            printf("   >> %s%s\n", contents[0], username);
            setColor(7);
        } else {
            printf("       %s%s\n", contents[0], username);
        }

        //In xác nhận
        if(fail) {
            setColor(12);
            printf("   >> [Fail]. Username không tồn tại\n");
            setColor(7);
            fail = 0;
        } else if(choice == 2) {
            setColor(11);
            printf("   >> %s\n", contents[1]);
            setColor(7);
        } else {
            printf("       %s\n", contents[1]);
        }

        //Hướng dẫn
        printf("\nNhấn ▲ ▼ để di chuyển\n");
        printf("Nhấn Enter xác nhận\n");
        printf("Nhấn Esc để thoát\n");

        //Di chuyển con trỏ
        gotoxy(29 + strlen(username), 9);

        //Nhận phím
        key = getch();

        //Điều hướng
        if(key == 224) {

            key = getch();

            //Lên
            if(key == KEY_UP) {

                choice--;

                if(choice < 1) {
                    choice = 2;
                }
            }

            //Xuống
            else if(key == KEY_DOWN) {

                choice++;

                if(choice > 2) {
                    choice = 1;
                }
            }
        }

        //Esc để thoát
        else if(key == ESC) {
            return;
        }

        //Backspace
        else if(key == BACKSPACE) {

            if(choice == 1 && strlen(username) > 0) {
                username[strlen(username) - 1] = '\0';
            }
        }

        //Enter
        else if(key == ENTER) {

            //Nếu chọn xác nhận
            if(choice == 2) {

                //Lấy thông tin
                Manage manage;
                if(loadManageInfo(username, &manage) == 0) {
                    fail = 1;
                    continue;
                }

                //Lưu username
                char oldUsername[50];
                strcpy(manage.username, username);
                strcpy(oldUsername, manage.username);

                //Lưu CCCD
                char oldCCCD[20];
                strcpy(oldCCCD, manage.CCCD);
                
                //Khai hàm cần thiết
                int choice = 1;
                int fail = 0;
                int key;

                //================ HIỂN THỊ THÔNG TIN ================

                while(1) {

                    //Làm sạch màn hình
                    system("cls");

                    //In tiêu đề
                    printf("\n");
                    printf("███╗   ███╗ █████╗ ███╗   ██╗ █████╗  ██████╗ ███████╗    ██╗███╗   ██╗███████╗ ██████╗ \n");
                    printf("████╗ ████║██╔══██╗████╗  ██║██╔══██╗██╔════╝ ██╔════╝    ██║████╗  ██║██╔════╝██╔═══██╗\n");
                    printf("██╔████╔██║███████║██╔██╗ ██║███████║██║  ███╗█████╗      ██║██╔██╗ ██║█████╗  ██║   ██║\n");
                    printf("██║╚██╔╝██║██╔══██║██║╚██╗██║██╔══██║██║   ██║██╔══╝      ██║██║╚██╗██║██╔══╝  ██║   ██║\n");
                    printf("██║ ╚═╝ ██║██║  ██║██║ ╚████║██║  ██║╚██████╔╝███████╗    ██║██║ ╚████║██║     ╚██████╔╝\n");
                    printf("╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝    ╚═╝╚═╝  ╚═══╝╚═╝      ╚═════╝ \n\n\n");

                    //Username
                    if(choice == 1) {
                        setColor(11);
                        printf("   >> Username : %s\n", manage.username);
                        setColor(7);
                    } else {
                        printf("       Username : %s\n", manage.username);
                    }

                    //Password
                    if(choice == 2) {
                        setColor(11);
                        printf("   >> Password : %s\n", manage.password);
                        setColor(7);
                    } else {
                        printf("       Password : %s\n", manage.password);
                    }

                    //Name
                    if(choice == 3) {
                        setColor(11);
                        printf("   >> Name     : %s\n", manage.name);
                        setColor(7);
                    } else {
                        printf("       Name     : %s\n", manage.name);
                    }

                    //CCCD
                    if(choice == 4) {
                        setColor(11);
                        printf("   >> CCCD     : %s\n", manage.CCCD);
                        setColor(7);
                    } else {
                        printf("       CCCD     : %s\n", manage.CCCD);
                    }

                    //Year
                    if(choice == 5) {
                        setColor(11);
                        printf("   >> Year     : %s\n", manage.year);
                        setColor(7);
                    } else {
                        printf("       Year     : %s\n", manage.year);
                    }

                    //Gender
                    if(choice == 6) {
                        setColor(11);
                        printf("   >> Gender   : %s\n", manage.gender);
                        setColor(7);
                    } else {
                        printf("       Gender   : %s\n", manage.gender);
                    }

                    //Province
                    if(choice == 7) {
                        setColor(11);
                        printf("   >> Province : %s\n", manage.province);
                        setColor(7);
                    } else {
                        printf("       Province : %s\n", manage.province);
                    }

                    //Phone
                    if(choice == 8) {
                        setColor(11);
                        printf("   >> Phone    : %s\n", manage.phone);
                        setColor(7);
                    } else {
                        printf("       Phone    : %s\n", manage.phone);
                    }

                    //Xác nhận
                    if(fail == 1) {
                        setColor(12);
                        printf("   >> Username không không hợp lệ\n");
                        setColor(7);
                        fail = 0;
                    } else if(fail == 2) {
                        setColor(12);
                        printf("   >> Password không hợp lệ\n");
                        setColor(7);
                        fail = 0;
                    } else if(fail == 3) {
                        setColor(12);
                        printf("   >> Tên không không hợp lệ\n");
                        setColor(7);
                        fail = 0;
                    } else if(fail == 4) {
                        setColor(12);
                        printf("   >> CCCD không không hợp lệ\n");
                        setColor(7);
                        fail = 0;
                    } else if(fail == 5) {
                        setColor(12);
                        printf("   >> SĐT không không hợp lệ\n");
                        setColor(7);
                        fail = 0;
                    } else if(choice == 9) {
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
                    if(choice == 1) {
                        gotoxy(17 + strlen(manage.username), 9);
                    } else if(choice == 2) {
                    	gotoxy(17 + strlen(manage.password), 10);
					} else if(choice == 3) {
						gotoxy(17 + strlen(manage.name), 11);
					} else if(choice == 4) {
						gotoxy(17 + strlen(manage.CCCD), 12);
					} else if(choice == 8) {
						gotoxy(17 + strlen(manage.phone), 16);
					}

                    //Nhận phím
                    key = getch();

                    //Mũi tên
                    if(key == 224) {

                        key = getch();

                        //Lên
                        if(key == KEY_UP) {

                            choice--;

                            if(choice < 1) {
                                choice = 9;
                            }
                        }

                        //Xuống
                        else if(key == KEY_DOWN) {

                            choice++;

                            if(choice > 9) {
                                choice = 1;
                            }
                        }
                    }

                    //Esc
                    else if(key == ESC) {
                        return;
                    }

                    //Enter
                    else if(key == ENTER) {

                        //Xác nhận lưu
                        if(choice == 9) {

                            //Kiểm tra
                            int result = saveManageInfo(&manage, oldUsername, oldCCCD);
                            if(result != 0) {
                                fail = result;
                                continue;
                            }

                            //Thông báo
                            gotoxy(0, 17);
                            setColor(10);
                            printf("      Lưu thông tin thành công!\n");
                            setColor(7);

                            //In hưỡng dẫn
                            printf("\nNhấn Enter hoặc Esc để thoát\n                                       \n                                   ");

                            //Đợi người dùng thoát
                            while (1) {
                                key = getch();
                                if(key == ENTER || key == ESC) {
                                    return;
                                }
                            }
                        }
                    }

                    //Backspace
                    else if(key == BACKSPACE) {

                        //Username
                        if(choice == 1 && strlen(manage.username) > 0) {

                            manage.username[strlen(manage.username) - 1] = '\0';
                        }

                        //Password
                        else if(choice == 2 && strlen(manage.password) > 0) {

                            manage.password[strlen(manage.password) - 1] = '\0';
                        }

                        //Name
                        else if(choice == 3 && strlen(manage.name) > 0) {

                            manage.name[strlen(manage.name) - 1] = '\0';
                        }

                        //CCCD
                        else if(choice == 4 && strlen(manage.CCCD) > 0) {

                            manage.CCCD[strlen(manage.CCCD) - 1] = '\0';

                            // Reset vì CCCD không còn hợp lệ nữa
                            strcpy(manage.year, "");
                            strcpy(manage.gender, "");
                            strcpy(manage.province, "");
                        }

                        //Phone
                        else if(choice == 8 && strlen(manage.phone) > 0) {

                            manage.phone[strlen(manage.phone) - 1] = '\0';
                        }
                    }

                    //Chỉnh sửa trực tiếp
                    else {

                        //username
                        if(choice == 1) {
                            if(strlen(manage.username) < 49) {
                                if(
                                    (key >= 'a' && key <= 'z') ||
                                    (key >= 'A' && key <= 'Z') ||
                                    (key >= '0' && key <= '9')
                                ) {
                                    int len = strlen(manage.username);
                                    manage.username[len] = key;
                                    manage.username[len + 1] = '\0';
                                }
                            }
                        }

                        //Password
                        if(choice == 2) {
                            if(key >= 32 && key <= 126) {
                                int len = strlen(manage.password);
                                manage.password[len] = key;
                                manage.password[len + 1] = '\0';
                            }
                        }

                        //Name
                        if(choice == 3) {
                            int len = strlen(manage.name);
                            manage.name[len] = (char)key;
                            manage.name[len + 1] = '\0';
                        }

                        //CCCD
                        if(choice == 4) {
                            if(key >= '0' && key <= '9') {
                                int len = strlen(manage.CCCD);
                                manage.CCCD[len] = key;
                                manage.CCCD[len + 1] = '\0';

                                //Nếu vừa đủ 12 số suy ra thông tin
                                if(strlen(manage.CCCD) == 12) {
                                    checkCCCD(manage.year, manage.province, manage.CCCD, manage.gender);
                                }
                            }
                        }

                        //Số điện thoại
                        if(choice == 8) {
                            if(strlen(manage.phone) < 19 && key >= '0' && key <= '9') {
                                int len = strlen(manage.phone);
                                manage.phone[len] = key;
                                manage.phone[len + 1] = '\0';
                            }
                        }
                    }
                }
            }
        }

        //Nhập username
        else {

            if(choice == 1 && strlen(username) < 49) {

                //Chỉ nhận chữ và số
                if(
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

//In danh sách quản lý
void viewManageList() {

    //Làm sạch màn hình
    system("cls");

    //In chữ MANAGE LIST
    printf("\n");
    printf("███╗   ███╗ █████╗ ███╗   ██╗ █████╗  ██████╗ ███████╗    ██╗     ██╗███████╗████████╗\n");
    printf("████╗ ████║██╔══██╗████╗  ██║██╔══██╗██╔════╝ ██╔════╝    ██║     ██║██╔════╝╚══██╔══╝\n");
    printf("██╔████╔██║███████║██╔██╗ ██║███████║██║  ███╗█████╗      ██║     ██║███████╗   ██║   \n");
    printf("██║╚██╔╝██║██╔══██║██║╚██╗██║██╔══██║██║   ██║██╔══╝      ██║     ██║╚════██║   ██║   \n");
    printf("██║ ╚═╝ ██║██║  ██║██║ ╚████║██║  ██║╚██████╔╝███████╗    ███████╗██║███████║   ██║   \n");
    printf("╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝    ╚══════╝╚═╝╚══════╝   ╚═╝   \n\n\n");

    //Tạo path đến thư mục chứa danh sách quản lý
    char pathFolder[256];
    sprintf(pathFolder, "Data/Account/Manage");

    //Mở thư mục
    DIR *dir = opendir(pathFolder);
    if (dir == NULL) {

        //In thông báo
        printf("       Không có quản lý nào\n");

        //Nhận phím từ người dùng
        printf("\nNhấn Enter hoặc Esc để quay lại\n");
        int key = getch();
        while (key != ENTER && key != ESC) {
            key = getch();
        }
        return;
    }

    //In bảng tiêu đề
    printf("       +------------------+----------------------------------+---------------+-------------+-----------------+\n");
    printf("       |  Username        |  Tên                             |  CCCD         |  Năm sinh   |  Số điện thoại  |\n");
    printf("       +------------------+----------------------------------+---------------+-------------+-----------------+\n");

    //Đọc từng file trong thư mục
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {

        //Bỏ qua các file ẩn và thư mục . và ..
        if (entry->d_name[0] == '.') {
            continue;
        }

        //Bỏ qua các file không phải là file .txt
        if (strstr(entry->d_name, ".txt") == NULL) {
            continue;
        }

        //Lấy username từ tên file (bỏ phần .txt)
        char username[50] = "";
        strncpy(username, entry->d_name, strlen(entry->d_name) - 4);
        username[strlen(entry->d_name) - 4] = '\0';

        //Tạo đường dẫn đầy đủ đến file
        char pathFile[256];
        sprintf(pathFile, "%s/%s", pathFolder, entry->d_name);

        //Khai báo biến lưu thông tin
        char password[50]  = "";
        char name[50]      = "";
        char CCCD[20]      = "";
        char year[10]      = "";
        char gender[10]    = "";
        char province[50]  = "";
        char phone[20]     = "";

        //Đọc thông tin từ file
        FILE *f = fopen(pathFile, "r");
        if (f != NULL) {
            fgets(password, sizeof(password), f);   password[strcspn(password, "\n")] = '\0';
            fgets(name,     sizeof(name),     f);   name[strcspn(name, "\n")]         = '\0';
            fgets(CCCD,     sizeof(CCCD),     f);   CCCD[strcspn(CCCD, "\n")]         = '\0';
            fgets(year,     sizeof(year),     f);   year[strcspn(year, "\n")]         = '\0';
            fgets(gender,   sizeof(gender),   f);   gender[strcspn(gender, "\n")]     = '\0';
            fgets(province, sizeof(province), f);   province[strcspn(province, "\n")] = '\0';
            fgets(phone,    sizeof(phone),    f);   phone[strcspn(phone, "\n")]       = '\0';
            fclose(f);
        }

        //Đếm ký tự UTF-8 để căn chỉnh cột tên
        int nameSpace = 32 - utf8len(name);

        //In thông tin ra bảng
        printf("       |  %-16s", username);
        printf("|  %s", name);
        for (int i = 0; i < nameSpace; i++) printf(" ");
        printf("|  %-13s", CCCD);
        printf("|  %-11s", year);
        printf("|  %-15s|\n", phone);

        //Reset sau khi in xong 1 dòng
        memset(username, 0, sizeof(username));
        memset(password, 0, sizeof(password));
        memset(name,     0, sizeof(name));
        memset(CCCD,     0, sizeof(CCCD));
        memset(year,     0, sizeof(year));
        memset(gender,   0, sizeof(gender));
        memset(province, 0, sizeof(province));
        memset(phone,    0, sizeof(phone));
    }

    //In dòng cuối bảng
    printf("       +------------------+----------------------------------+---------------+-------------+-----------------+\n");

    //Đóng thư mục
    closedir(dir);

    //Nhận phím từ người dùng
    printf("\nNhấn Enter hoặc Esc để quay lại\n");
    int key = getch();
    while (key != ENTER && key != ESC) {
        key = getch();
    }
}

//Xóa tài khoản quản lý
void deleteManageInfo() {

    //Khai báo biến cần thiết
    int choice = 1;
    int key;
    int fail = 0;

    char username[50] = "";

    char *contents[] = {
        "Nhập username quản lý: ",
        "Xác nhận",
    };

    //Tạo vòng lặp
    while (1) {

        //Làm sạch màn hình
        system("cls");

        //In chữ DELETE MANAGE
        printf("\n");
        printf("██████╗ ███████╗██╗     ███████╗████████╗███████╗    ███╗   ███╗ █████╗ ███╗   ██╗ █████╗  ██████╗ ███████╗\n");
        printf("██╔══██╗██╔════╝██║     ██╔════╝╚══██╔══╝██╔════╝    ████╗ ████║██╔══██╗████╗  ██║██╔══██╗██╔════╝ ██╔════╝\n");
        printf("██║  ██║█████╗  ██║     █████╗     ██║   █████╗      ██╔████╔██║███████║██╔██╗ ██║███████║██║  ███╗█████╗  \n");
        printf("██║  ██║██╔══╝  ██║     ██╔══╝     ██║   ██╔══╝      ██║╚██╔╝██║██╔══██║██║╚██╗██║██╔══██║██║   ██║██╔══╝  \n");
        printf("██████╔╝███████╗███████╗███████╗   ██║   ███████╗    ██║ ╚═╝ ██║██║  ██║██║ ╚████║██║  ██║╚██████╔╝███████╗\n");
        printf("╚═════╝ ╚══════╝╚══════╝╚══════╝   ╚═╝   ╚══════╝    ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝\n\n\n");

        //In ô nhập username
        if (choice == 1) {
            setColor(11);
            printf("   >> %s%s\n", contents[0], username);
            setColor(7);
        } else {
            printf("       %s%s\n", contents[0], username);
        }

        //In xác nhận / thông báo lỗi
        if (fail == 1) {
            setColor(12);
            printf("   >> [Fail] Username không tồn tại\n");
            setColor(7);
            fail = 0;
        } else if (choice == 2) {
            setColor(11);
            printf("   >> %s\n", contents[1]);
            setColor(7);
        } else {
            printf("       %s\n", contents[1]);
        }

        //Hướng dẫn
        printf("\nNhấn ▲ ▼ để di chuyển\n");
        printf("Nhấn Enter xác nhận\n");
        printf("Nhấn Esc để thoát\n");

        //Di chuyển con trỏ
        gotoxy(29 + strlen(username), 9);

        //Nhận phím
        key = getch();

        //Mũi tên
        if (key == 224) {

            key = getch();

            //Lên
            if (key == KEY_UP) {
                choice--;
                if (choice < 1) choice = 2;
            }

            //Xuống
            else if (key == KEY_DOWN) {
                choice++;
                if (choice > 2) choice = 1;
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

            if (choice == 2) {

                //Kiểm tra file có tồn tại không
                char path[256];
                sprintf(path, "Data/Account/Manage/%s.txt", username);

                FILE *f = fopen(path, "r");
                if (f == NULL) {
                    fail = 1;
                    continue;
                }
                fclose(f);

                //================ XÁC NHẬN XÓA ================

                int confirmChoice = 1;
                int confirmKey;

                while (1) {

                    //Làm sạch màn hình
                    system("cls");

                    //In tiêu đề
                    printf("\n");
                    printf("██████╗ ███████╗██╗     ███████╗████████╗███████╗    ███╗   ███╗ █████╗ ███╗   ██╗ █████╗  ██████╗ ███████╗\n");
                    printf("██╔══██╗██╔════╝██║     ██╔════╝╚══██╔══╝██╔════╝    ████╗ ████║██╔══██╗████╗  ██║██╔══██╗██╔════╝ ██╔════╝\n");
                    printf("██║  ██║█████╗  ██║     █████╗     ██║   █████╗      ██╔████╔██║███████║██╔██╗ ██║███████║██║  ███╗█████╗  \n");
                    printf("██║  ██║██╔══╝  ██║     ██╔══╝     ██║   ██╔══╝      ██║╚██╔╝██║██╔══██║██║╚██╗██║██╔══██║██║   ██║██╔══╝  \n");
                    printf("██████╔╝███████╗███████╗███████╗   ██║   ███████╗    ██║ ╚═╝ ██║██║  ██║██║ ╚████║██║  ██║╚██████╔╝███████╗\n");
                    printf("╚═════╝ ╚══════╝╚══════╝╚══════╝   ╚═╝   ╚══════╝    ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝\n\n\n");

                    //Cảnh báo
                    setColor(12);
                    printf("   Bạn có chắc muốn xóa quản lý \"%s\" không?\n\n", username);
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

                    //Mũi tên
                    if (confirmKey == 224) {

                        confirmKey = getch();

                        if (confirmKey == KEY_UP) {
                            confirmChoice--;
                            if (confirmChoice < 1) confirmChoice = 2;
                        } else if (confirmKey == KEY_DOWN) {
                            confirmChoice++;
                            if (confirmChoice > 2) confirmChoice = 1;
                        }
                    }

                    //Esc
                    else if (confirmKey == ESC) {
                        return;
                    }

                    //Enter
                    else if (confirmKey == ENTER) {

                        //Chọn Có → xóa file
                        if (confirmChoice == 1) {

                            //Di chuyển con trỏ
                            gotoxy(0, 9);
                            if (remove(path) == 0) {
                                setColor(10);
                                printf("      Xóa quản lý \"%s\" thành công!                 \n", username);
                                setColor(7);
                            } else {
                                setColor(12);
                                printf("[Fail] Không thể xóa file!\n");
                                setColor(7);
                            }

                            //In hưỡng dẫn
                            printf("\nNhấn Enter hoặc Esc để thoát\n                                       \n                                   \n                                         ");
                            printf("\n                                       \n                                   \n                                         ");
                            
                            //Đợi người dùng thoát
                            while (1) {
                                key = getch();
                                if(key == ENTER || key == ESC) {
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
    Quản lý
              */
void accountManage() {

    //Khai báo hàm cần thiết
    int choice = 1;
    int key;
    char *options[] = {
        "Tạo tài khoản quản lý",
        "Chỉnh sửa tài khoản quản lý",
        "Xem danh sách quản lý",
        "Xóa tài khoản quản lý",
        "thoát",
    };

    //Lấy số lượng phần tử trong mảng options
    int numOptions = sizeof(options) / sizeof(options[0]);

    //Tạo vòng lặp
    while (1) {
        
        //Làm sạch màn hình 
        system("cls");

        //In chữ ACCOUNT MANAGE
        printf("\n");
        printf(" █████╗  ██████╗ ██████╗ ██████╗ ██╗   ██╗███╗   ██╗████████╗    ███╗   ███╗ █████╗ ███╗   ██╗ █████╗  ██████╗ ███████╗\n");
        printf("██╔══██╗██╔════╝██╔════╝██╔═══██╗██║   ██║████╗  ██║╚══██╔══╝    ████╗ ████║██╔══██╗████╗  ██║██╔══██╗██╔════╝ ██╔════╝\n");
        printf("███████║██║     ██║     ██║   ██║██║   ██║██╔██╗ ██║   ██║       ██╔████╔██║███████║██╔██╗ ██║███████║██║  ███╗█████╗  \n");
        printf("██╔══██║██║     ██║     ██║   ██║██║   ██║██║╚██╗██║   ██║       ██║╚██╔╝██║██╔══██║██║╚██╗██║██╔══██║██║   ██║██╔══╝  \n");
        printf("██║  ██║╚██████╗╚██████╗╚██████╔╝╚██████╔╝██║ ╚████║   ██║       ██║ ╚═╝ ██║██║  ██║██║ ╚████║██║  ██║╚██████╔╝███████╗\n");
        printf("╚═╝  ╚═╝ ╚═════╝ ╚═════╝ ╚═════╝  ╚═════╝ ╚═╝  ╚═══╝   ╚═╝       ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝\n\n\n");
    
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
                    createManageAccount();
                    break;
                case 2:
                    editManageInfo();
                    break;
                case 3:
                    viewManageList();
                    break;
                case 4:
                    deleteManageInfo();
                    break;
                case 5:
                    return;
            }
        }
    }
}

/*
    Xem danh sách phòng trống
                                 */
void viewRoomStatus() {

    //Làm sạch màn hình
    system("cls");

    //In chữ ROOM STATUS
    printf("\n");
    printf("██████╗  ██████╗  ██████╗ ███╗   ███╗    ███████╗████████╗ █████╗ ████████╗██╗   ██╗███████╗\n");
    printf("██╔══██╗██╔═══██╗██╔═══██╗████╗ ████║    ██╔════╝╚══██╔══╝██╔══██╗╚══██╔══╝██║   ██║██╔════╝\n");
    printf("██████╔╝██║   ██║██║   ██║██╔████╔██║    ███████╗   ██║   ███████║   ██║   ██║   ██║███████╗\n");
    printf("██╔══██╗██║   ██║██║   ██║██║╚██╔╝██║    ╚════██║   ██║   ██╔══██║   ██║   ██║   ██║╚════██║\n");
    printf("██║  ██║╚██████╔╝╚██████╔╝██║ ╚═╝ ██║    ███████║   ██║   ██║  ██║   ██║   ╚██████╔╝███████║\n");
    printf("╚═╝  ╚═╝ ╚═════╝  ╚═════╝ ╚═╝     ╚═╝    ╚══════╝   ╚═╝   ╚═╝  ╚═╝   ╚═╝    ╚═════╝ ╚══════╝\n\n\n");

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

                //Bỏ qua file ẩn và thư mục . và ..
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

    //Đợi người dùng thoát
    while (1) {
        key = getch();
        if(key == ENTER || key == ESC) {
            return;
        }
    }
}

/*
    Xem danh sách cư dân
                            */
void viewAllResidents() {

    //Làm sạch màn hình
    system("cls");

    //In chữ ALL RESIDENTS
    printf("\n");
    printf(" █████╗ ██╗     ██╗         ██████╗ ███████╗███████╗██╗██████╗ ███████╗███╗   ██╗████████╗███████╗\n");
    printf("██╔══██╗██║     ██║         ██╔══██╗██╔════╝██╔════╝██║██╔══██╗██╔════╝████╗  ██║╚══██╔══╝██╔════╝\n");
    printf("███████║██║     ██║         ██████╔╝█████╗  ███████╗██║██║  ██║█████╗  ██╔██╗ ██║   ██║   ███████╗\n");
    printf("██╔══██║██║     ██║         ██╔══██╗██╔══╝  ╚════██║██║██║  ██║██╔══╝  ██║╚██╗██║   ██║   ╚════██║\n");
    printf("██║  ██║███████╗███████╗    ██║  ██║███████╗███████║██║██████╔╝███████╗██║ ╚████║   ██║   ███████║\n");
    printf("╚═╝  ╚═╝╚══════╝╚══════╝    ╚═╝  ╚═╝╚══════╝╚══════╝╚═╝╚═════╝ ╚══════╝╚═╝  ╚═══╝   ╚═╝   ╚══════╝\n\n\n");

    //Cờ kiểm tra có cư dân nào không
    int totalResidents = 0;

    //Duyệt qua từng tầng và từng phòng
    for (int floor = 1; floor <= 5; floor++) {
        for (int room = 1; room <= 5; room++) {

            //Tạo đường dẫn đến thư mục phòng
            char pathFolder[256];
            sprintf(pathFolder, "FloorList/Floor%d/P%d%02d", floor, floor, room);

            //Mở thư mục
            DIR *dir = opendir(pathFolder);
            if (dir == NULL) continue;

            //Kiểm tra thư mục có file .txt không
            int hasFile = 0;
            struct dirent *entry;
            while ((entry = readdir(dir)) != NULL) {
                if (entry->d_name[0] == '.') continue;
                if (strstr(entry->d_name, ".txt") != NULL) {
                    hasFile = 1;
                    break;
                }
            }
            closedir(dir);

            //Nếu không có file thì bỏ qua
            if (hasFile == 0) continue;

            //Đánh dấu có ít nhất 1 cư dân
            totalResidents = 1;

            //In tên phòng
            setColor(14);
            printf("       P%d%02d\n", floor, room);
            setColor(7);

            //In bảng tiêu đề
            printf("       +------------------+----------------------------------+---------------+-------------+--------------+-----------------+\n");
            printf("       |  Username        |  Tên                             |  CCCD         |  Năm sinh   |  Giới tính   |  Số điện thoại  |\n");
            printf("       +------------------+----------------------------------+---------------+-------------+--------------+-----------------+\n");

            //Mở lại thư mục để đọc từng file
            dir = opendir(pathFolder);
            if (dir == NULL) continue;

            while ((entry = readdir(dir)) != NULL) {

                //Bỏ qua file ẩn
                if (entry->d_name[0] == '.') continue;

                //Bỏ qua file không phải .txt
                if (strstr(entry->d_name, ".txt") == NULL) continue;

                //Lấy username từ tên file
                char username[50] = "";
                strncpy(username, entry->d_name, strlen(entry->d_name) - 4);
                username[strlen(entry->d_name) - 4] = '\0';

                //Tạo đường dẫn đầy đủ đến file
                char pathFile[256];
                sprintf(pathFile, "%s/%s", pathFolder, entry->d_name);

                //Khai báo biến lưu thông tin
                char password[50]  = "";
                char name[50]      = "";
                char CCCD[20]      = "";
                char year[10]      = "";
                char gender[10]    = "";
                char province[50]  = "";
                char phone[20]     = "";

                //Đọc thông tin từ file
                FILE *f = fopen(pathFile, "r");
                if (f != NULL) {
                    fgets(password, sizeof(password), f);   password[strcspn(password, "\n")] = '\0';
                    fgets(name,     sizeof(name),     f);   name[strcspn(name, "\n")]         = '\0';
                    fgets(CCCD,     sizeof(CCCD),     f);   CCCD[strcspn(CCCD, "\n")]         = '\0';
                    fgets(year,     sizeof(year),     f);   year[strcspn(year, "\n")]         = '\0';
                    fgets(gender,   sizeof(gender),   f);   gender[strcspn(gender, "\n")]     = '\0';
                    fgets(province, sizeof(province), f);   province[strcspn(province, "\n")] = '\0';
                    fgets(phone,    sizeof(phone),    f);   phone[strcspn(phone, "\n")]       = '\0';
                    fclose(f);
                }

                //Đếm ký tự UTF-8 để căn chỉnh
                int nameSpace   = 32 - utf8len(name);
                int genderSpace = 12 - utf8len(gender);

                //In thông tin ra bảng
                printf("       |  %-16s", username);
                printf("|  %s", name);
                for (int i = 0; i < nameSpace; i++) printf(" ");
                printf("|  %-13s", CCCD);
                printf("|  %-11s", year);
                printf("|  %s", gender);
                for (int i = 0; i < genderSpace; i++) printf(" ");
                printf("|  %-15s|\n", phone);

                //Reset sau khi in xong 1 dòng
                memset(username, 0, sizeof(username));
                memset(password, 0, sizeof(password));
                memset(name,     0, sizeof(name));
                memset(CCCD,     0, sizeof(CCCD));
                memset(year,     0, sizeof(year));
                memset(gender,   0, sizeof(gender));
                memset(province, 0, sizeof(province));
                memset(phone,    0, sizeof(phone));
            }

            //In dòng cuối bảng
            printf("       +------------------+----------------------------------+---------------+-------------+--------------+-----------------+\n\n");

            //Đóng thư mục
            closedir(dir);
        }
    }

    //Nếu không có cư dân nào
    if (totalResidents == 0) {
        printf("       Không có cư dân nào trong tòa nhà\n");
    }

    //Nhận phím từ người dùng
    printf("\nNhấn Enter hoặc Esc để quay lại\n");
    int key = getch();
    while (key != ENTER && key != ESC) {
        key = getch();
    }
}

//In Logo tháng năm
void printMonthYearLogo(int month, char year[]) {

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
    //Tối đa: 2 số tháng + dấu / + 4 số năm = 7 phần tử
    char *parts[7][6];
    int count = 0;

    //Thêm chữ số tháng (2 chữ số, có thể có số 0 ở đầu)
    char monthStr[3];
    sprintf(monthStr, "%02d", month);

    parts[count][0] = digits[monthStr[0] - '0'][0];
    parts[count][1] = digits[monthStr[0] - '0'][1];
    parts[count][2] = digits[monthStr[0] - '0'][2];
    parts[count][3] = digits[monthStr[0] - '0'][3];
    parts[count][4] = digits[monthStr[0] - '0'][4];
    parts[count][5] = digits[monthStr[0] - '0'][5];
    count++;

    parts[count][0] = space[0];
    parts[count][1] = space[1];
    parts[count][2] = space[2];
    parts[count][3] = space[3];
    parts[count][4] = space[4];
    parts[count][5] = space[5];
    count++;

    parts[count][0] = digits[monthStr[1] - '0'][0];
    parts[count][1] = digits[monthStr[1] - '0'][1];
    parts[count][2] = digits[monthStr[1] - '0'][2];
    parts[count][3] = digits[monthStr[1] - '0'][3];
    parts[count][4] = digits[monthStr[1] - '0'][4];
    parts[count][5] = digits[monthStr[1] - '0'][5];
    count++;

    //Thêm dấu /
    parts[count][0] = slash[0];
    parts[count][1] = slash[1];
    parts[count][2] = slash[2];
    parts[count][3] = slash[3];
    parts[count][4] = slash[4];
    parts[count][5] = slash[5];
    count++;

    //Thêm 4 chữ số năm
    for (int i = 0; i < 4; i++) {

        if (i > 0) {
            parts[count][0] = space[0];
            parts[count][1] = space[1];
            parts[count][2] = space[2];
            parts[count][3] = space[3];
            parts[count][4] = space[4];
            parts[count][5] = space[5];
            count++;
        }

        int d = year[i] - '0';
        parts[count][0] = digits[d][0];
        parts[count][1] = digits[d][1];
        parts[count][2] = digits[d][2];
        parts[count][3] = digits[d][3];
        parts[count][4] = digits[d][4];
        parts[count][5] = digits[d][5];
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
    Xem danh sách hóa đơn
                            */
void viewBillByMonth() {

    //Khai báo biến cần thiết
    int choice = 1;
    int key;
    int fail = 0;

    char month[3] = "";
    char year[5]  = "";

    //Tạo vòng lặp nhập tháng/năm
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
        } else if (fail == 2) {
            setColor(12);
            printf("   >> [Fail] Năm phải đủ 4 chữ số\n");
            setColor(7);
            fail = 0;
        } else if (choice == 3) {
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
            gotoxy(25 + strlen(month), 9);
        } else if (choice == 2) {
            gotoxy(27 + strlen(year), 10);
        }

        //Nhận phím
        key = getch();

        //Mũi tên
        if (key == 224) {

            key = getch();

            if (key == KEY_UP) {
                choice--;
                if (choice < 1) choice = 3;
            } else if (key == KEY_DOWN) {
                choice++;
                if (choice > 3) choice = 1;
            }
        }

        //Esc
        else if (key == ESC) {
            return;
        }

        //Backspace
        else if (key == BACKSPACE) {
            if (choice == 1 && strlen(month) > 0) {
                month[strlen(month) - 1] = '\0';
            } else if (choice == 2 && strlen(year) > 0) {
                year[strlen(year) - 1] = '\0';
            }
        }

        //Enter
        else if (key == ENTER) {

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

                //In tiêu đề hóa đơn
                printf("\n");
                printMonthYearLogo(monthInt, year);

                //In tiêu đề hóa đơn
                setColor(14);
                printf("\n   Hóa đơn tháng %d/%s\n\n", monthInt, year);
                setColor(7);

                //In bảng tiêu đề
                printf("   +----------+--------------------+--------------+--------------------+------------+--------------------+--------------------+\n");
                printf("   | Phòng    | Tiền phòng(VNĐ)    | Số điện(kWh) | Tiền điện(VNĐ)     | Số nước(m³)| Tiền nước(VNĐ)     | Tổng tiền(VNĐ)     |\n");
                printf("   +----------+--------------------+--------------+--------------------+------------+--------------------+--------------------+\n");

                //Tạo tên file theo tháng/năm (VD: 052026.txt)
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
                        char pathFile[256];
                        sprintf(pathFile, "Data/Bill/Floor%d/P%d%02d/%s", floor, floor, room, fileName);

                        //Mở file
                        FILE *f = fopen(pathFile, "r");
                        if (f == NULL) continue;

                        //Đánh dấu có hóa đơn
                        hasBill = 1;

                        //Đọc dữ liệu
                        float roomPrice        = 0;
                        float electricityNumber = 0;
                        float electricityPrice  = 0;
                        float waterNumber      = 0;
                        float waterPrice       = 0;

                        fscanf(f, "%f", &roomPrice);
                        fscanf(f, "%f", &electricityNumber);
                        fscanf(f, "%f", &electricityPrice);
                        fscanf(f, "%f", &waterNumber);
                        fscanf(f, "%f", &waterPrice);
                        fclose(f);

                        //Tính tổng tiền của phòng
                        float total = roomPrice + electricityPrice + waterPrice;
                        totalRevenue += total;

                        //In thông tin ra bảng
                        printf("   | P%d%02d     | %-19.0f| %-13.0f| %-19.0f| %-11.0f| %-19.0f| %-19.0f|\n",
                            floor, room,
                            roomPrice,
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

                //Nếu không có hóa đơn nào
                if (hasBill == 0) {
                    setColor(12);
                    printf("\n   Không có hóa đơn nào trong tháng %d/%s\n", monthInt, year);
                    setColor(7);
                } else {
                    //In tổng doanh thu
                    setColor(10);
                    printf("\n   Tổng doanh thu tháng %d/%s: %.0f VNĐ\n", monthInt, year, totalRevenue);
                    setColor(7);
                }

                //Nhận phím
                printf("\nNhấn Enter hoặc Esc để quay lại\n");
                int k = getch();
                while (k != ENTER && k != ESC) {
                    k = getch();
                }
                return;
            }
        }

        //Nhập số
        else {
            if (choice == 1 && key >= '0' && key <= '9' && strlen(month) < 2) {
                int len = strlen(month);
                month[len] = key;
                month[len + 1] = '\0';
            } else if (choice == 2 && key >= '0' && key <= '9' && strlen(year) < 4) {
                int len = strlen(year);
                year[len] = key;
                year[len + 1] = '\0';
            }
        }
    }
}

//Hàm main
void AdminLogin(char username[]) {

    //Lấy thông tin admin
    Admin admin;
    strcpy(admin.username, username);
    getAdminInfo(&admin);

    //Khai báo hàm cần thiết
    int choice = 1;
    int key;

    //Nội dung lựa chọn
    char *options[] = {
        "Hiển thị thông tin cá nhân",
        "Chỉnh sửa thông tin cá nhân",
        "Quản lý tài khoản của quản lý",
        "Xem danh sách phòng trống và không trống",
        "Xem danh sách cư dân",
        "Xem hóa đơn theo tháng",
        "Đăng xuất",
    };

    //Lấy số lượng phần tử trong mảng options
    int numOptions = sizeof(options) / sizeof(options[0]);

    //Tạo vòng lặp để tạo bảng và lựa chọn
    while (1) {

        //Làm sạch màn hình
        system("cls");

        //In chữ WELCOME ADMIN
        printf("\n");
        printf("██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗     █████╗ ██████╗ ███╗   ███╗██╗███╗   ██╗\n");
        printf("██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝    ██╔══██╗██╔══██╗████╗ ████║██║████╗  ██║\n");
        printf("██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗      ███████║██║  ██║██╔████╔██║██║██╔██╗ ██║\n");
        printf("██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝      ██╔══██║██║  ██║██║╚██╔╝██║██║██║╚██╗██║\n");
        printf("╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗    ██║  ██║██████╔╝██║ ╚═╝ ██║██║██║ ╚████║\n");
        printf(" ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝    ╚═╝  ╚═╝╚═════╝ ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝\n\n\n");
        
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
                    printAdminInfo(admin);
                    break;
                case 2:
                    editOtherInfoAdmin(&admin);
                    break;
                case 3:
                    accountManage();
                    break;
                case 4:
                    viewRoomStatus();
                    break;
                case 5:
                    viewAllResidents();
                    break;
                case 6:
                    viewBillByMonth();
                    break;
                case 7:
                    logout();
                    return;
            }
        }
    }
}