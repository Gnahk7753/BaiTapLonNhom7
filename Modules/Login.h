#ifndef LOGIN_H
#define LOGIN_H

//In chữ LOGIN ADMIN
void printAdminBanner();

//Hàm vẽ giao diện login
void printLoginForm(char username[], char password[], int currentField);

//Đăng nhập với tư cách Admin
void loginAdmin();

//Hàm hiển thị menu và điều hướng mũi tên để chọn
int menuLogin(char *items[], int size);

#endif