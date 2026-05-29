//Thư viện
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <conio.h>
#include <windows.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define BACKSPACE 8
#define ENTER 13
#define ESC 27

typedef struct Resident {
    char username[50];
    char password[50];
    char name[50];
    char CCCD[20];
    char year[10];
    char gender[10];
    char province[50];
    char phone[20];
} Resident;

//Xóa
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
 
/*======================== XÓA==============================*/
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

//Hàm đổi màu chữ
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
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

//Hàm ẩn con trỏ
void hideCursor() {

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = 0; // Ẩn con trỏ
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

/*=========================== XÓA =============================*/

//Hàm lấy thông tin cá nhân
void getPersonalInfo(Resident *resident, int *residentFloor, int *residentRoom) {

    int found = 0;
    for (int floor = 1; floor <= 5; floor++) {
        for (int room = 1; room <= 5; room++) {
            char path[256];
            sprintf(path, "FloorList/Floor%d/P%d%02d/%s.txt", floor, floor, room, "gnahk");
            FILE *file = fopen(path, "r");
            if (file != NULL) {
                //Đọc thông tin cá nhân từ file
                fclose(file);
                *residentFloor = floor;
                *residentRoom = room;
                found = 1;
                break;
            }
        }
        if (found) {
            break;
        }
    }

    //Tạo path đầy đủ đến đường dẫn
    char path[256];
    sprintf(path, "FloorList/Floor%d/P%d%02d/%s.txt", *residentFloor, *residentFloor, *residentRoom, resident[0].username);

    //Mở file để đọc thông tin cá nhân
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        return;
    }
    
    //Đọc thông tin cá nhân từ file
    fgets(resident->password, sizeof(resident->password), f);    resident->password[strcspn(resident->password, "\n")] = '\0';  
    fgets(resident->name, sizeof(resident->name), f);            resident->name[strcspn(resident->name, "\n")] = '\0';
    fgets(resident->CCCD, sizeof(resident->CCCD), f);            resident->CCCD[strcspn(resident->CCCD, "\n")] = '\0';  
    fgets(resident->year, sizeof(resident->year), f);            resident->year[strcspn(resident->year, "\n")] = '\0';  
    fgets(resident->gender, sizeof(resident->gender), f);        resident->gender[strcspn(resident->gender, "\n")] = '\0';  
    fgets(resident->province, sizeof(resident->province), f);    resident->province[strcspn(resident->province, "\n")] = '\0';  
    fgets(resident->phone, sizeof(resident->phone), f);          resident->phone[strcspn(resident->phone, "\n")] = '\0';  

    //Đóng file
    fclose(f);
}

/* 
    Hàm in thông tin cá nhân
                                */
void printPersonalInfo(Resident resident, int residentFloor, int residentRoom) {

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

    printf("       Tên: %s\n", resident.name);
    printf("       CCCD: %s\n", resident.CCCD);
    printf("       Năm sinh: %s\n", resident.year);
    printf("       Giới tính: %s\n", resident.gender);
    printf("       Quê quán: %s\n", resident.province);
    printf("       Số điện thoại: %s\n", resident.phone);
    printf("       Đang ở: P%d%02d\n", residentFloor, residentRoom);

    //Nhấn enter hoặc esc để quay lại
    printf("\nNhấn Enter hoặc Esc để quay lại\n");

    //Nhận phím từ người dùng
    int key = getch();
    while (key != ENTER && key != ESC) {
        key = getch();
    }
}

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

/*
    Hàm đổi số điện thoại
                            */
void changePhone(Resident *resident, int residentFloor, int residentRoom) {

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

                //Cập nhật số điện thoại mới vào struct Resident
                strncpy(resident->phone, newPhone, sizeof(resident->phone) - 1);		resident->phone[sizeof(resident->phone) - 1] = '\0';

                //Cập nhật số điện thoại mới vào file
                char path[256];
                sprintf(path, "FloorList/Floor%d/P%d%02d/%s.txt", residentFloor, residentFloor, residentRoom, resident->username);
                FILE *f = fopen(path, "w");
                if (f != NULL) {
                    
                    //Ghi lại toàn bộ thông tin cá nhân vào file với số điện thoại mới
                    fprintf(f, "%s\n", resident->password);
                    fprintf(f, "%s\n", resident->name);
                    fprintf(f, "%s\n", resident->CCCD);
                    fprintf(f, "%s\n", resident->year);
                    fprintf(f, "%s\n", resident->gender);
                    fprintf(f, "%s\n", resident->province);
                    fprintf(f, "%s\n", resident->phone);
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

/*
    Đổi mật khẩu
                    */
void changePassword(Resident *resident, int residentFloor, int residentRoom, char oldPasswordCorrect[]) {

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

        //Enter để xác nhận
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
                if (strcmp(oldPassword, oldPasswordCorrect) != 0) {
                    //In thông báo mật khẩu cũ không đúng
                    fail = 2;
                    continue;
                }

                //Cập nhật mật khẩu mới vào struct Resident
                strncpy(resident->password, newPassword, sizeof(resident->password) - 1);		resident->password[sizeof(resident->password) - 1] = '\0';

                //Cập nhật mật khẩu mới vào file
                char path[256];
                sprintf(path, "FloorList/Floor%d/P%d%02d/%s.txt", residentFloor, residentFloor, residentRoom, resident->username);
                FILE *f = fopen(path, "w");
                if (f != NULL) {
                    
                    //Ghi lại toàn bộ thông tin cá nhân vào file với mật khẩu mới
                    fprintf(f, "%s\n", resident->password);
                    fprintf(f, "%s\n", resident->name);
                    fprintf(f, "%s\n", resident->CCCD);
                    fprintf(f, "%s\n", resident->year);
                    fprintf(f, "%s\n", resident->gender);
                    fprintf(f, "%s\n", resident->province);
                    fprintf(f, "%s\n", resident->phone);
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

/*
    Chỉnh sửa thông tin khác
*/
void editOtherInfo() {
    
    //Làm sạch màng hình
    system("cls");

    //In chữ EDIT OTHER INFO
    printf("\n");
    printf("███████╗██████╗ ██╗████████╗    ██████╗ ████████╗██╗  ██╗███████╗██████╗     ██╗███╗   ██╗███████╗ ██████╗ \n");
    printf("██╔════╝██╔══██╗██║╚══██╔══╝   ██╔═══██╗╚══██╔══╝██║  ██║██╔════╝██╔══██╗    ██║████╗  ██║██╔════╝██╔═══██╗\n");
    printf("█████╗  ██║  ██║██║   ██║      ██║   ██║   ██║   ███████║█████╗  ██████╔╝    ██║██╔██╗ ██║█████╗  ██║   ██║\n");
    printf("██╔══╝  ██║  ██║██║   ██║      ██║   ██║   ██║   ██╔══██║██╔══╝  ██╔══██╗    ██║██║╚██╗██║██╔══╝  ██║   ██║\n");
    printf("███████╗██████╔╝██║   ██║      ╚██████╔╝   ██║   ██║  ██║███████╗██║  ██║    ██║██║ ╚████║██║     ╚██████╔╝\n");
    printf("╚══════╝╚═════╝ ╚═╝   ╚═╝       ╚═════╝    ╚═╝   ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝    ╚═╝╚═╝  ╚═══╝╚═╝      ╚═════╝ \n\n\n");

    //In thông báo
    setColor(12);
    printf("       Bạn không có quyền chỉnh sửa thông tin khác ngoài số điện thoại và mật khẩu\n");
    printf("       Vui lòng liên hệ ban quản lý để được hỗ trợ\n");
    setColor(7);
    printf("\nNhấn Enter hoặc Esc để quay lại\n");

    //Nhận phím từ người dùng
    int key = getch();
    while (key != ENTER && key != ESC) {
        key = getch();
    }
}

/*
    Xem danh sách cùng phòng
                                */
void viewRoommateList(int residentFloor, int residentRoom) {

    //Làm sạch màn hình
    system("cls");

    //In chữ ROOMMATE LIST
    printf("\n");
    printf("██████╗  ██████╗  ██████╗ ███╗   ███╗███╗   ███╗ █████╗ ████████╗███████╗    ██╗     ██╗███████╗████████╗\n");
    printf("██╔══██╗██╔═══██╗██╔═══██╗████╗ ████║████╗ ████║██╔══██╗╚══██╔══╝██╔════╝    ██║     ██║██╔════╝╚══██╔══╝\n");
    printf("██████╔╝██║   ██║██║   ██║██╔████╔██║██╔████╔██║███████║   ██║   █████╗      ██║     ██║███████╗   ██║   \n");
    printf("██╔══██╗██║   ██║██║   ██║██║╚██╔╝██║██║╚██╔╝██║██╔══██║   ██║   ██╔══╝      ██║     ██║╚════██║   ██║   \n");
    printf("██║  ██║╚██████╔╝╚██████╔╝██║ ╚═╝ ██║██║ ╚═╝ ██║██║  ██║   ██║   ███████╗    ███████╗██║███████║   ██║   \n");
    printf("╚═╝  ╚═╝ ╚═════╝  ╚═════╝ ╚═╝     ╚═╝╚═╝     ╚═╝╚═╝  ╚═╝   ╚═╝   ╚══════╝    ╚══════╝╚═╝╚══════╝   ╚═╝   \n\n\n");

    //Tạo path đầy đủ đến đường dẫn
    char pathFolder[256];
    sprintf(pathFolder, "FloorList/Floor%d/P%d%02d", residentFloor, residentFloor, residentRoom);

    //Đọc thư mục có file nào không nếu không có thì in ra không có ai trong phòng và nhận Enter hoặc Esc để quay lại
    DIR *dir = opendir(pathFolder);
    if (dir == NULL) {

        //In thông báo
        printf("       Không có ai trong phòng\n");
        
        //Nhận phím từ người dùng
        printf("\nNhấn Enter hoặc Esc để quay lại\n");
        int key = getch();
        while (key != ENTER && key != ESC) {
            key = getch();
        }
        return;
    }

    //In bảng thông tin của những người cùng phòng
    printf("       +------------------+----------------------------------+---------------+-------------+--------------+-----------------+\n");
    printf("       |  Username        |  Tên                             |  CCCD         |  Năm sinh   |  Giới tính   |  Số điện thoại  |\n");
    printf("       +------------------+----------------------------------+---------------+-------------+--------------+-----------------+\n");

    //Đọc từng file trong thư mục
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {

        //Khai báo hàm cần thiết
        char username[50];

        //Bỏ qua các file ẩn và thư mục . và ..
        if (entry->d_name[0] == '.') {
            continue;
        }

        //Bỏ qua các file không phải là file .txt
        if (strstr(entry->d_name, ".txt") == NULL) {
            continue;
        }

        //Tạo đường dẫn đầy đủ đến file
        char pathFile[256];
        sprintf(pathFile, "%s/%s", pathFolder, entry->d_name);

        //Lấy tên người dùng từ tên file (bỏ phần .txt)
        strncpy(username, entry->d_name, strlen(entry->d_name) - 4);
        username[strlen(entry->d_name) - 4] = '\0';

        //Mở file và đọc toàn bộ thông tin
        FILE *f = fopen(pathFile, "r");

        //Tạo char để lưu thông tin của từng người trong phòng
        char password[50] = "";
        char name[50] = "";
        char CCCD[20] = "";
        char year[10] = "";
        char gender[10] = "";
        char province[50] = "";
        char phone[20] = "";

        if (f != NULL) {
            fgets(password, sizeof(password), f);     password[strcspn(password, "\n")] = '\0';  
            fgets(name, sizeof(name), f);             name[strcspn(name, "\n")] = '\0';
            fgets(CCCD, sizeof(CCCD), f);             CCCD[strcspn(CCCD, "\n")] = '\0';
            fgets(year, sizeof(year), f);             year[strcspn(year, "\n")] = '\0';
            fgets(gender, sizeof(gender), f);         gender[strcspn(gender, "\n")] = '\0';
            fgets(province, sizeof(province), f);     province[strcspn(province, "\n")] = '\0';
            fgets(phone, sizeof(phone), f);           phone[strcspn(phone, "\n")] = '\0';
            fclose(f);
        }

        //Đếm số lượng ký tự của tên để căn chỉnh
        int nameLength = utf8len( name);
        int nameSpace = 32 - nameLength;

        //Đếm số lượng ký tự của giới tính để căn chỉnh
        int genderLength = utf8len( gender);
        int genderSpace = 12 - genderLength;

        //In thông tin của từng người trong phòng ra bảng
        printf("       |  %-16s", username);
        printf("|  %s",  name);
        for (int i = 0; i < nameSpace; i++) {
            printf(" ");
        }
        printf("|  %-13s", CCCD);
        printf("|  %-11s", year);
        printf("|  %s",  gender);
        for (int i = 0; i < genderSpace; i++) {
            printf(" ");
        }
        printf("|  %-15s|\n", phone);

        //Reset sau khi in thông tin của một người
        memset(username, 0, sizeof(username));
        memset(password, 0, sizeof(password));
        memset(name, 0, sizeof(name));
        memset(CCCD, 0, sizeof(CCCD));
        memset(year, 0, sizeof(year));
        memset(gender, 0, sizeof(gender));
        memset(province, 0, sizeof(province));
        memset(phone, 0, sizeof(phone));
    }

    //In dòng cuối cùng của bảng
    printf("       +------------------+----------------------------------+---------------+-------------+--------------+-----------------+\n");

    //Đóng thư mục
    closedir(dir);

    //Nhận phím từ người dùng
    printf("\nNhấn Enter hoặc Esc để quay lại\n");
    int key = getch();
    while (key != ENTER && key != ESC) {
        key = getch();
    }
}

/*
    Xem hóa đơn
                    */
void viewBill(int residentFloor, int residentRoom) {
    
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

    //Tạo path đầy đủ đến đường dẫn
    char pathFolder[256];
    sprintf(pathFolder, "Data/Bill/Floor%d/P%d%02d", residentFloor, residentFloor, residentRoom);

    //Đọc thư mục có file nào không nếu không có thì in ra không có ai trong phòng và nhận Enter hoặc Esc để quay lại
    DIR *dir = opendir(pathFolder);
    if (dir == NULL) {

        //In thông báo
        printf("       Không có hóa đơn nào\n");
        
        //Nhận phím từ người dùng
        printf("\nNhấn Enter hoặc Esc để quay lại\n");
        int key = getch();
        while (key != ENTER && key != ESC) {
            key = getch();
        }
        return;
    }

    //In bảng thông tin của những hóa đơn theo tháng
    printf("       +---------------+-------------------+--------------+--------------------+--------------+--------------------+--------------------+\n");
    printf("       | Tháng/Năm     | Tiền phòng(VNĐ)   | Số điện(kWh) | Tiền điện(VNĐ)     | Số nước(m³)  | Tiền nước(VNĐ)     | Tổng tiền(VNĐ)     |\n");
    printf("       +---------------+-------------------+--------------+--------------------+--------------+--------------------+--------------------+\n");

    //Đọc từng file trong thư mục
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)  {

        //Khai báo hàm cần thiết 
        char month[10];
        char year[10];
        float roomPrice = 0;
        float electricityNumber = 0;
        float electricityPrice = 0;
        float waterNumber = 0;
        float waterPrice = 0;

        //Bỏ qua các file ẩn
        if (entry->d_name[0] == '.') {
            continue;
        }

        //Bỏ qua các file không phải file hóa đơn (file không có đuôi .txt)
        if (strstr(entry->d_name, ".txt") == NULL) {
            continue;
        }

        //Tạo đường dẫn đầy đủ đến file 
        char pathFile[256];
        sprintf(pathFile, "%s/%s", pathFolder, entry->d_name);

        //Lấy tháng và năm từ tên file
        strncpy(month, entry->d_name, 2);
        month[2] = '\0';

        strncpy(year, entry->d_name + 2, 4);
        year[4] = '\0';

        //Lấy thông tin hóa đơn từ file
        FILE *f = fopen(pathFile, "r");
        if (f != NULL) {
            fscanf(f, "%f", &roomPrice);
            fscanf(f, "%f", &electricityNumber);
            fscanf(f, "%f", &electricityPrice);
            fscanf(f, "%f", &waterNumber);
            fscanf(f, "%f", &waterPrice);
            fclose(f);
        }

        //In thông tin của từng hóa đơn ra bảng
        printf("       | %s/%s       | %-18.0f| %-13.0f| %-19.0f| %-13.0f| %-19.0f| %-19.0f|\n", month, year, roomPrice, electricityNumber, electricityPrice, waterNumber, waterPrice, roomPrice + electricityPrice + waterPrice);

        //Reset sau khi in thông tin của một hóa đơn
        memset(month, 0, sizeof(month));
        memset(year, 0, sizeof(year));
        roomPrice = 0;
        electricityNumber = 0;
        electricityPrice = 0;
        waterNumber = 0;
        waterPrice = 0;
    }

    //In dòng cuối cùng của bảng
    printf("       +---------------+-------------------+--------------+--------------------+--------------+--------------------+--------------------+\n");

    //Đóng thư mục
    closedir(dir);

    //Nhận phím từ người dùng
    printf("\nNhấn Enter hoặc Esc để quay lại\n");
    int key = getch();
    while (key != ENTER && key != ESC) {
        key = getch();
    }
}

/*
    Đăng xuất
                */
void logout() {

    //Làm sạch màn hình
    system("cls");

    //In chữ LOGOUT
    printf("\n");
    printf("██╗      ██████╗  ██████╗  ██████╗  ██████╗ ██╗   ██╗████████╗\n");
    printf("██║     ██╔═══██╗██╔════╝ ██╔═══██╗██╔═══██╗██║   ██║╚══██╔══╝\n");
    printf("██║     ██║   ██║██║  ███╗██║   ██║██║   ██║██║   ██║   ██║   \n");
    printf("██║     ██║   ██║██║   ██║██║   ██║██║   ██║██║   ██║   ██║   \n");
    printf("███████╗╚██████╔╝╚██████╔╝╚██████╔╝╚██████╔╝╚██████╔╝   ██║   \n");
    printf("╚══════╝ ╚═════╝  ╚═════╝  ╚═════╝  ╚═════╝  ╚═════╝    ╚═╝   \n\n\n");

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

//Hàm main
int main() {

    //Chỉnh sửa lỗi front chữ Tiếng Việt xóa
	SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    hideCursor();

    //Thông số tài khoản tạm thời
    int residentFloor = 1;
    int residentRoom = 1;
    Resident resident;
    strcpy(resident.username, "gnahk");
    getPersonalInfo(&resident, &residentFloor, &residentRoom);
    
    int choice = 1;
    int key;

    //Nội dung lựa chọn
    char *options[] = {
        "Hiển thị thông tin cá nhân",
        "Đổi số điện thoại",
        "Đổi mật khẩu",
        "Chỉnh sửa thông tin khác",
        "Xem danh sách cùng phòng",
        "Xem hóa đơn",
        "Đăng xuất",
    };

    //Lấy số lượng phần tử trong mảng options
    int numOptions = sizeof(options) / sizeof(options[0]);

    //Tạo vòng lặp để tạo bảng và lựa chọn
    while (1) {

        //Làm sạch màn hình
        system("cls");

        //In chữ HELLO RESIDENT
        printf("\n");
        printf("██╗  ██╗███████╗██╗     ██╗      ██████╗     ██████╗ ███████╗███████╗██╗██████╗ ███████╗███╗   ██╗████████╗\n");
        printf("██║  ██║██╔════╝██║     ██║     ██╔═══██╗    ██╔══██╗██╔════╝██╔════╝██║██╔══██╗██╔════╝████╗  ██║╚══██╔══╝\n");
        printf("███████║█████╗  ██║     ██║     ██║   ██║    ██████╔╝█████╗  ███████╗██║██║  ██║█████╗  ██╔██╗ ██║   ██║   \n");
        printf("██╔══██║██╔══╝  ██║     ██║     ██║   ██║    ██╔══██╗██╔══╝  ╚════██║██║██║  ██║██╔══╝  ██║╚██╗██║   ██║   \n");
        printf("██║  ██║███████╗███████╗███████╗╚██████╔╝    ██║  ██║███████╗███████║██║██████╔╝███████╗██║ ╚████║   ██║   \n");
        printf("╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝ ╚═════╝     ╚═╝  ╚═╝╚══════╝╚══════╝╚═╝╚═════╝ ╚══════╝╚═╝  ╚═══╝   ╚═╝   \n\n\n");

        //In các lựa chọn có thể chọn
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
                    printPersonalInfo(resident, residentFloor, residentRoom);
                    break;
                case 2:
                    changePhone(&resident, residentFloor, residentRoom);
                    break;
                case 3:
                    changePassword(&resident, residentFloor, residentRoom, resident.password);
                    break;
                case 4:
                    editOtherInfo();
                    break;
                case 5:
                    viewRoommateList(residentFloor, residentRoom);
                    break;
                case 6:
                    viewBill(residentFloor, residentRoom);
                    break;
                case 7:
                    logout();
                    return 0;
            }
        }
    }
}