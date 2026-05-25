#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <direct.h>

// kiểm tra folder/file tồn tại
int exists(const char *path) {
    struct stat st;
    return (stat(path, &st) == 0);
}

// tạo folder nếu chưa có
void createDir(const char *path) {
    if (!exists(path)) {
        _mkdir(path);
    }
}

// tạo cấu trúc Data/Bill/TangX/PXY
void createStructure() {
    char path[200];

    createDir("Data");
    createDir("Data/Bill");

    for (int tang = 1; tang <= 5; tang++) {
        sprintf(path, "Data/Bill/Tang%d", tang);
        createDir(path);

        for (int i = 1; i <= 5; i++) {
            sprintf(path, "Data/Bill/Tang%d/P%d%d", tang, tang, i);
            createDir(path);
        }
    }
}

// tạo file theo tháng-năm dạng 052026.txt
void createMonthlyFile() {
    char filename[50];

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // MMYYYY
    sprintf(filename, "Data/Bill/%02d%04d.txt",
            tm.tm_mon + 1,
            tm.tm_year + 1900);

    if (!exists(filename)) {
        FILE *f = fopen(filename, "w");
        if (f) {
            fprintf(f, "Bill file created for %02d/%04d\n",
                    tm.tm_mon + 1,
                    tm.tm_year + 1900);
            fclose(f);
        }
    }
}

int main() {
    createStructure();
    createMonthlyFile();

    printf("He thong thu muc + file da duoc tao xong.\n");
    return 0;
}