#ifndef UTILS_H
#define UTILS_H

//Hàm đổi màu chữ
void setColor(int color);

//Hàm di chuyển con trỏ
void gotoxy(int x, int y);

//Tạo nơi chứa dữ liệu Tỉnh Thành
void createProvinceFolder();

//Kiểm tra folder Data có tồn tại không, nếu không thì tạo
void createDataFolder();

//Đếm ký tự UTF-8 gần đúng
int utf8len(const char *s);

//Hàm hiển thị menu và điều hướng mũi tên để chọn
int menuLogin(char *items[], int size);

//Lưu lịch sử thay đổi
void saveHistory(char role[], char status[], char action[], char target[]);

//In chữ LOGIN ADMIN
void printAdminBanner();

#endif