#ifndef RESIDENT_H
#define RESIDENT_H

#include <stdio.h>
#include <string.h>
#include <time.h>



// ====================== UTILS.H ======================

// Hàm lưu lịch sử thay đổi
void saveHistory(const char action[]) {

    FILE *file = fopen("./data/history.txt", "a");

    if (file == NULL) {

        printf("Không thể mở file lịch sử!\n");
        return;
    }

    time_t currentTime;

    time(&currentTime);

    // Ghi lịch sử thay đổi vào file
    fprintf(file, "[%s] %s\n", ctime(&currentTime), action);

    fclose(file);
}



// ====================== RESIDENT ======================

// Struct lưu thông tin cư dân
typedef struct {

    char fullName[100];
    char citizenId[20];
    int birthYear;
    char gender[10];
    char hometown[100];
    char phone[15];
    char room[20];
    char password[50];

} Resident;


// ====================== CHECK ACCOUNT ======================

//Kiểm tra tài khoản
int checkAccount(char filePath[], char username[], char password[]) {

    FILE *file = fopen(filePath, "r");

    if (file == NULL) {

        printf("Không mở được file!\n");
        return 0;
    }

    char fileUser[50];
    char filePass[50];

    // Đọc từng tài khoản trong file
    while (fscanf(file, "%s %s", fileUser, filePass) != EOF) {

        // So sánh username + password
        if (strcmp(username, fileUser) == 0 &&
            strcmp(password, filePass) == 0) {

            fclose(file);

            return 1;
        }
    }

    fclose(file);

    return 0;
}

/*
    Hàm hiển thị thông tin cư dân
*/
void displayResidentInfo(Resident resident) {

    printf("\n========== THONG TIN CU DAN ==========\n");

    printf("Tên           : %s\n", resident.fullName);
    printf("CCCD          : %s\n", resident.citizenId);
    printf("Năm sinh      : %d\n", resident.birthYear);
    printf("Giới tính     : %s\n", resident.gender);
    printf("Quê quán      : %s\n", resident.hometown);
    printf("Số điện thoại : %s\n", resident.phone);
    printf("Phòng đang ở  : %s\n", resident.room);

    printf("======================================\n");
}



/*
    Hàm chỉnh sửa số điện thoại
*/
void editPhoneNumber(Resident *resident) {

    char newPhone[15];
    int confirm;

    printf("\nNhập số điện thoại mới: ");
    scanf("%s", newPhone);

    // Xác nhận thay đổi
    printf("Xác nhận thay đổi? (1.Có / 0.Không): ");
    scanf("%d", &confirm);

    if (confirm == 1) {

        strcpy(resident->phone, newPhone);

        printf("Cập nhật số điện thoại thành công!\n");

        // Lưu lịch sử thay đổi
        saveHistory("Cư dân thay đổi số điện thoại");
    }
    else {

        printf("Đã huỷ thay đổi!\n");
    }
}



/*
    Hàm thông báo không được sửa thông tin
*/
void showRestrictedMessage() {

    printf("\nChỉ quản lý mới được thay đổi thông tin này.\n");
    printf("Vui lòng liên hệ quản lý để được hỗ trợ.\n");
}



/*
    Hàm đổi mật khẩu
*/
void changePassword(Resident *resident) {

    char oldPassword[50];
    char newPassword[50];
    int confirm;

    printf("\nNhập mật khẩu hiện tại: ");
    scanf("%s", oldPassword);

    // Kiểm tra mật khẩu cũ
    if (strcmp(oldPassword, resident->password) != 0) {

        printf("Mật khẩu không đúng!\n");
        return;
    }

    printf("Nhập mật khẩu mới: ");
    scanf("%s", newPassword);

    // Xác nhận đổi mật khẩu
    printf("Xác nhận đổi mật khẩu? (1.Có / 0.Không): ");
    scanf("%d", &confirm);

    if (confirm == 1) {

        strcpy(resident->password, newPassword);

        printf("Đổi mật khẩu thành công!\n");

        // Lưu lịch sử thay đổi
        saveHistory("Cư dân thay đổi mật khẩu");
    }
    else {

        printf("Đã huỷ đổi mật khẩu!\n");
    }
}



/*
    Hàm xem danh sách cư dân cùng phòng
*/
void viewResidentsInRoom(Resident residents[], int size, char room[]) {

    printf("\n===== DANH SÁCH CƯ DÂN PHÒNG %s =====\n", room);

    for (int i = 0; i < size; i++) {

        if (strcmp(residents[i].room, room) == 0) {

            printf("- %s\n", residents[i].fullName);
        }
    }
}



/*
    Hàm xem hóa đơn phòng
*/
void viewRoomBill(char room[]) {

    // Dữ liệu mẫu
    int roomFee = 1500000;
    int electricNumber = 120;
    int electricMoney = 420000;
    int waterNumber = 15;
    int waterMoney = 180000;

    printf("\n========== HÓA DƠN PHÒNG ==========\n");

    printf("Phòng           : %s\n", room);

    // 1. Tiền phòng
    printf("1. Tiền phòng   : %d VND\n", roomFee);

    // 2. Số điện
    printf("2. Số điện      : %d kWh\n", electricNumber);

    // 3. Tiền điện
    printf("3. Tiền điện    : %d VND\n", electricMoney);

    // 4. Số nước
    printf("4. Số nước      : %d m3\n", waterNumber);

    // 5. Tiền nước
    printf("5. Tiền nước    : %d VND\n", waterMoney);

    printf("===================================\n");
}



/*
    Hàm menu chức năng cư dân
*/
void residentMenu(Resident *resident, Resident residents[], int size) {

    int choice;

    do {

        printf("\n========== MENU CƯ DÂN ==========\n");

        printf("1. Hiển thị thông tin cư dân\n");
        printf("2. Chỉnh sửa số điện thoại\n");
        printf("3. Đổi mật khẩu\n");
        printf("4. Chỉnh sửa thông tin khác\n");
        printf("5. Xem danh sách cư dân cùng phòng\n");
        printf("6. Xem hoá đơn phòng\n");
        printf("0. Thoát\n");

        printf("Nhập lựa chọn: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                displayResidentInfo(*resident);
                break;

            case 2:
                editPhoneNumber(resident);
                break;

            case 3:
                changePassword(resident);
                break;

            case 4:
                showRestrictedMessage();
                break;

            case 5:
                viewResidentsInRoom(residents, size, resident->room);
                break;

            case 6:
                viewRoomBill(resident->room);
                break;

            case 0:
                printf("Đã thoát menu!\n");
                break;

            default:
                printf("Lựa chọn không hợp lệ!\n");
        }

    } while (choice != 0);
}

#endif
