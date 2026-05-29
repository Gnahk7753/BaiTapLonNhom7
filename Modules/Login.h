#ifndef LOGIN_H
#define LOGIN_H

//In chữ LOGIN ADMIN
void printAdminBanner();

//In chữ LOGIN MANAGE
void printManageBanner();

//In chữ LOGIN RESIDENT
void printResidentBanner();

//In chữ HELLO ADMIN
void helloAdmin();

//In chữ HELLO MANAGE
void printHelloManage();

//In chữ HELLO RESIDENT
void printHelloResident();

//Hàm vẽ giao diện login
void printLoginForm(char username[], char password[], int currentField, int *fail);

//Hàm kiểm tra tài khoản và mật khẩu Admin trả về 1 nếu đúng và 0 nếu sai
int checkLoginAdmin(char username[], char password[]);

//Hàm kiểm tra tài khoản và mật khẩu Manage trả về 1 nếu đúng và 0 nếu sai
int checkLoginManage(char username[], char password[]);

//Hàm kiểm tra tài khoản và mật khẩu Resident trả về 1 nếu đúng và 0 nếu sai
int checkLoginResident(char username[], char password[]);

//Đăng nhập với tư cách Admin
void login(int select);

//Hàm hiển thị menu và điều hướng mũi tên để chọn
int menuLogin(char *items[], int size);

#endif