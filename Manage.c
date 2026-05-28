#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define MAX 100

typedef struct {
    char fullName[MAX];
    char cccd[MAX];
    char birthYear[MAX];
    char province[MAX];
    char phoneNumber[MAX];
} Manager;

Manager manager;
char currentPassword[MAX], currentAccountPath[200];

//	Hàm hiển thị thông tin
void showManagerInfo() {

    printf("\n========== THÔNG TIN QUẢN LÝ ==========\n");

    printf("Họ tên       : %s\n", manager.fullName);
    printf("CCCD         : %s\n", manager.cccd);
    printf("Năm sinh     : %s\n", manager.birthYear);
    printf("Quê quán     : %s\n", manager.province);
    printf("Số điện thoại: %s\n", manager.phoneNumber);
}

//	Hàm chỉnh sửa thông tin
void editManagerAccount() {

    int choice;

    char oldPassword[MAX];
    char newPassword[MAX];
    char newPhoneNumber[MAX];

    char filePassword[MAX];

    FILE *file;

    printf("\n========== CHỈNH SỬA TÀI KHOẢN ==========\n");

    printf("1. Thay đổi số điện thoại\n");
    printf("2. Thay đổi mật khẩu\n");
    printf("3. Thay đổi thông tin khác\n");

    printf("\nNhập lựa chọn: ");
    scanf("%d", &choice);

    switch(choice) {

        // ====================================
        // THAY ĐỔI SỐ ĐIỆN THOẠI
        // ====================================

        case 1:

            printf("\nNhập số điện thoại mới: ");
            scanf("%s", newPhoneNumber);

            // Cập nhật struct
            strcpy(manager.phoneNumber, newPhoneNumber);

            /*
                ======================================
                GHI ĐÈ FILE
                ======================================
            */

            file = fopen(currentAccountPath, "w");

            if(file == NULL) {

                printf("\nKhông thể mở file!\n");

                return;
            }

            // Ghi lại toàn bộ dữ liệu
            fprintf(file, "%s\n", currentPassword);
            fprintf(file, "%s\n", manager.fullName);
            fprintf(file, "%s\n", manager.cccd);
            fprintf(file, "%s\n", manager.birthYear);
            fprintf(file, "%s\n", manager.province);
            fprintf(file, "%s\n", manager.phoneNumber);

            fclose(file);

            printf("\nĐã cập nhật số điện thoại thành công!\n");

            break;

        // ====================================
        // THAY ĐỔI MẬT KHẨU
        // ====================================

        case 2:

            printf("\nNhập mật khẩu cũ: ");
            scanf("%s", oldPassword);

            // Kiểm tra mật khẩu cũ
            if(strcmp(oldPassword, currentPassword) != 0) {

                printf("\nMật khẩu cũ không đúng!\n");

                return;
            }

            printf("Nhập mật khẩu mới: ");
            scanf("%s", newPassword);

            // Cập nhật mật khẩu hiện tại
            strcpy(currentPassword, newPassword);

            /*
                ======================================
                GHI ĐÈ FILE
                ======================================
            */

            file = fopen(currentAccountPath, "w");

            if(file == NULL) {

                printf("\nKhông thể mở file!\n");

                return;
            }

            // Ghi mật khẩu mới
            fprintf(file, "%s\n", currentPassword);

            // Ghi lại thông tin
            fprintf(file, "%s\n", manager.fullName);
            fprintf(file, "%s\n", manager.cccd);
            fprintf(file, "%s\n", manager.birthYear);
            fprintf(file, "%s\n", manager.province);
            fprintf(file, "%s\n", manager.phoneNumber);

            fclose(file);

            printf("\nĐổi mật khẩu thành công!\n");

            break;

        // ====================================
        // THÔNG TIN KHÁC
        // ====================================

        case 3:

            printf("\nVui lòng báo với admin để được hỗ trợ.\n");

            break;

        default:

            printf("\nLựa chọn không hợp lệ!\n");
    }
}

//	Hàm tạo tài khoản cho cư dân
void createResidentAccount() {
    printf("\n[Tạo tài khoản cho cư dân]\n");
}

//	Hàm chỉnh sửa thông tin tài khoản cư dân
void editResidentAccount() {
    printf("\n[Chỉnh sửa thông tin tài khoản cư dân]\n");
}

//	Hàm xóa tài khoản cư dân
void deleteResidentAccount() {
    printf("\n[Xóa tài khoản cư dân]\n");
}

//	Hàm hiển thị danh sách các phòng
void showRoomList() {
    printf("\n[Xem danh sách các phòng]\n");
}

//	Hàm tìm kiếm cư dân
void searchResident() {
    printf("\n[Tìm kiếm cư dân]\n");
}

//	Hàm nhập số điện, số nước
void inputElectricWater() {
    printf("\n[Nhập thông tin số điện, số nước]\n");
}

//	Hàm hiển thị danh sách hóa đơn
void showMonthlyBills() {
    printf("\n[Xem danh sách hóa đơn theo tháng]\n");
}

//	Hàm đăng nhập
int login() {

    char username[MAX], password[MAX], path[200], filePassword[MAX];

    FILE *file;

    printf("=============== ĐĂNG NHẬP ===============\n");

    printf("Nhập tên tài khoản: ");
    scanf("%s", username);

    printf("Nhập mật khẩu: ");
    scanf("%s", password);

    // Tạo đường dẫn file
    sprintf(path, "Data/Account/Manage/%s.txt", username);

    // Mở file
    file = fopen(path, "r");

    if(file == NULL) {
        printf("\nKhông tìm thấy tài khoản!\n");
        return 0;
    }

    // Đọc mật khẩu dòng đầu tiên
    fgets(filePassword, MAX, file);

    // Xóa '\n'
    filePassword[strcspn(filePassword, "\n")] = 0;

    // Kiểm tra mật khẩu
    if(strcmp(password, filePassword) != 0) {

        printf("\nSai mật khẩu!\n");

        fclose(file);

        return 0;
    }

    // Đọc thông tin dòng 2 -> 6
    fgets(manager.fullName, MAX, file);
    fgets(manager.cccd, MAX, file);
    fgets(manager.birthYear, MAX, file);
    fgets(manager.province, MAX, file);
    fgets(manager.phoneNumber, MAX, file);

    // Xóa '\n'
    manager.fullName[strcspn(manager.fullName, "\n")] = 0;
    manager.cccd[strcspn(manager.cccd, "\n")] = 0;
    manager.birthYear[strcspn(manager.birthYear, "\n")] = 0;
    manager.province[strcspn(manager.province, "\n")] = 0;
    manager.phoneNumber[strcspn(manager.phoneNumber, "\n")] = 0;
    
    //	Lưu mật khẩu hiện tại
    strcpy(currentPassword, password);

	//	Lưu đường dẫn file hiện tại
	strcpy(currentAccountPath, path);
	
    fclose(file);

    printf("\nĐăng nhập thành công!\n");

    return 1;
}

void manageMenu()
{
	int choice;

    do {

        system("cls"); 

        printf("====================================================\n");
        printf("                    QUẢN LÝ                        \n");
        printf("====================================================\n");

        printf("1. Hiển thị thông tin quản lý\n");
        printf("2. Chỉnh sửa thông tin tài khoản quản lý\n");
        printf("3. Tạo tài khoản cho cư dân\n");
        printf("4. Chỉnh sửa thông tin tài khoản cư dân\n");
        printf("5. Xóa tài khoản cư dân\n");
        printf("6. Xem danh sách các phòng\n");
        printf("7. Tìm kiếm cư dân\n");
        printf("8. Nhập thông tin số điện, số nước\n");
        printf("9. Xem danh sách hóa đơn theo tháng\n");
        printf("0. Thoát\n");

        printf("====================================================\n");
        printf("Nhập lựa chọn của bạn: ");
        scanf("%d", &choice);

        switch(choice) {

            case 1:
                showManagerInfo();
                break;

            case 2:
                editManagerAccount();
                break;

            case 3:
                createResidentAccount();
                break;

            case 4:
                editResidentAccount();
                break;

            case 5:
                deleteResidentAccount();
                break;

            case 6:
                showRoomList();
                break;

            case 7:
                searchResident();
                break;

            case 8:
                inputElectricWater();
                break;

            case 9:
                showMonthlyBills();
                break;

            case 0:
                printf("Đang thoát chương trình...\n");
                break;

            default:
                printf("Lựa chọn không hợp lệ!\n");
        }

        if(choice != 0) {
            printf("\nNhấn Enter để tiếp tục...");
            getchar();
            getchar();
        }

    } while(choice != 0);
}
int main() {

    SetConsoleOutputCP(65001);
	SetConsoleCP(65001);

	// Đăng nhập
	if(login() == 0) {
   		printf("\nĐăng nhập thất bại!\n");
    	return 0;
	}

	//	Menu
	manageMenu();
}