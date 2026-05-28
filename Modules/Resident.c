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

        printf("Khong the mo file lich su!\n");
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
//Kiểm tra tài khoản
int checkAccount(char filePath[], char username[], char password[]) {

    FILE *file = fopen(filePath, "r");

    if (file == NULL) {

        printf("Khong mo duoc file!\n");
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

    printf("Ten           : %s\n", resident.fullName);
    printf("CCCD          : %s\n", resident.citizenId);
    printf("Nam sinh      : %d\n", resident.birthYear);
    printf("Gioi tinh     : %s\n", resident.gender);
    printf("Que quan      : %s\n", resident.hometown);
    printf("So dien thoai : %s\n", resident.phone);
    printf("Phong dang o  : %s\n", resident.room);

    printf("======================================\n");
}



/*
    Hàm chỉnh sửa số điện thoại
*/
void editPhoneNumber(Resident *resident) {

    char newPhone[15];
    int confirm;

    printf("\nNhap so dien thoai moi: ");
    scanf("%s", newPhone);

    // Xác nhận thay đổi
    printf("Xac nhan thay doi? (1.Co / 0.Khong): ");
    scanf("%d", &confirm);

    if (confirm == 1) {

        strcpy(resident->phone, newPhone);

        printf("Cap nhat so dien thoai thanh cong!\n");

        // Lưu lịch sử thay đổi
        saveHistory("Cu dan thay doi so dien thoai");
    }
    else {

        printf("Da huy thay doi!\n");
    }
}



/*
    Hàm thông báo không được sửa thông tin
*/
void showRestrictedMessage() {

    printf("\nChi quan ly moi duoc thay doi thong tin nay.\n");
    printf("Vui long lien he quan ly de duoc ho tro.\n");
}



/*
    Hàm đổi mật khẩu
*/
void changePassword(Resident *resident) {

    char oldPassword[50];
    char newPassword[50];
    int confirm;

    printf("\nNhap mat khau hien tai: ");
    scanf("%s", oldPassword);

    // Kiểm tra mật khẩu cũ
    if (strcmp(oldPassword, resident->password) != 0) {

        printf("Mat khau khong dung!\n");
        return;
    }

    printf("Nhap mat khau moi: ");
    scanf("%s", newPassword);

    // Xác nhận đổi mật khẩu
    printf("Xac nhan doi mat khau? (1.Co / 0.Khong): ");
    scanf("%d", &confirm);

    if (confirm == 1) {

        strcpy(resident->password, newPassword);

        printf("Doi mat khau thanh cong!\n");

        // Lưu lịch sử thay đổi
        saveHistory("Cu dan thay doi mat khau");
    }
    else {

        printf("Da huy doi mat khau!\n");
    }
}



/*
    Hàm xem danh sách cư dân cùng phòng
*/
void viewResidentsInRoom(Resident residents[], int size, char room[]) {

    printf("\n===== DANH SACH CU DAN PHONG %s =====\n", room);

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

    printf("\n========== HOA DON PHONG ==========\n");

    printf("Phong           : %s\n", room);

    // 1. Tiền phòng
    printf("1. Tien phong   : %d VND\n", roomFee);

    // 2. Số điện
    printf("2. So dien      : %d kWh\n", electricNumber);

    // 3. Tiền điện
    printf("3. Tien dien    : %d VND\n", electricMoney);

    // 4. Số nước
    printf("4. So nuoc      : %d m3\n", waterNumber);

    // 5. Tiền nước
    printf("5. Tien nuoc    : %d VND\n", waterMoney);

    printf("===================================\n");
}



/*
    Hàm menu chức năng cư dân
*/
void residentMenu(Resident *resident, Resident residents[], int size) {

    int choice;

    do {

        printf("\n========== MENU CU DAN ==========\n");

        printf("1. Hien thi thong tin cu dan\n");
        printf("2. Chinh sua so dien thoai\n");
        printf("3. Doi mat khau\n");
        printf("4. Chinh sua thong tin khac\n");
        printf("5. Xem danh sach cu dan cung phong\n");
        printf("6. Xem hoa don phong\n");
        printf("0. Thoat\n");

        printf("Nhap lua chon: ");
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
                printf("Da thoat menu!\n");
                break;

            default:
                printf("Lua chon khong hop le!\n");
        }

    } while (choice != 0);
}

#endif
