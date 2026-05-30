#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

// ================= CONSOLE =================
void gotoxy(int x, int y);
void setColor(int color);
void hideCursor(void);
void showCursor(void);

// ================= FOLDER =================
void createDataFolder(void);
void createProvinceFolder(void);
void createAccountFolder(void);
void createFloorList(void);
void createBill(void);

// ================= HISTORY =================
void saveHistory(char role[], char status[],
                 char action[], char target[]);

// ================= STRING =================
int utf8len(const char *s);
void printContent(char content[], int num, int choice);

int checkUsername(char username[]);
int checkDuplicateUsername(char newUsername[], char path[]);
int checkDuplicateUsernameForResident(char username[]);

int isOnlyLetter(char str[]);
int checkPassword(char password[]);
int checkPhoneNumber(char phone[]);

int isAllDigits(char *s);

// ================= CCCD =================
int validProvince(int CCCD);

int checkDuplicateCCCD(char CCCD[]);

int checkCCCD(char year[],
              char province[],
              char CCCD[],
              char gender[]);

int checkCCCDOnly(char year[],
                  char province[],
                  char CCCD[],
                  char gender[]);

// ================= UI =================
void logout();

#endif