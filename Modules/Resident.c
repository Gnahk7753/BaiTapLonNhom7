#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <time.h>

// Hàm lưu lịch sử thay đổi
void saveHistory(char action[]) {

    FILE *file = fopen("./data/history.txt", "a");

    if (file == NULL) {

        printf("Cannot open history file!\n");
        return;
    }

    time_t currentTime;

    time(&currentTime);

    fprintf(file, "[%s] %s\n", ctime(&currentTime), action);

    fclose(file);
}
