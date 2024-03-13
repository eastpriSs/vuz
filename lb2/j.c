#define _CRT_SECURE_NO_WARNINGS
#define MAX_STR 15
#define MAX_LEN 100
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <conio.h>

int main()
{
    char str[MAX_STR][MAX_LEN] = { 0 }; // Строки
    char groups[MAX_STR][3][MAX_LEN] = { 0 }; // Массив групп для запроса
    char line[MAX_LEN], destination[MAX_LEN], date[MAX_LEN], time[MAX_LEN];
    int i, a, b, c = 0;
    // Ввод строк
    puts("To finish typing strings do '!' like a string");
    for (i = 0; i < MAX_STR; i++) {

        do {
            int count = 0;
            gets_s(str[i]);
            strcpy(line, str[i]);
            char* words = strtok(line, " ");
            while (words != NULL) {
                words = strtok(NULL, " ");
                count++;
            }
        } while(count != 6);

            if (strcmp(str[i], "!") == 0) {
                break;
                str[i][MAX_LEN] = NULL;
            }
    }
    // Понижение регистра и вывод строк
    for (a = 0; a < i; a++) {
         _strlwr(str[a]);
         printf("%s\n", str[a]);
    }
    // Разделение строк на слова
    for (a = 0; a < i; a++) { 
        strcpy(line, str[a]); // Cохраняем значение
        char* buffer = strtok(line, ", ?!-;");
        for (b = 0; b < 4; b++) {
             if (buffer != NULL) {
                 if (b >= 1) strcpy(groups[a][c++], buffer);
                 buffer = strtok(NULL, ", ?!-;");
             }
        }
        c = 0;
    }
    // Вывод ГРУПП
    for (a = 0; a < i; a++) {
        for (b = 0; b < 3; b++) {
            if (groups[a][b][0] != '\0') {
                printf("%s ", groups[a][b]);
            }
        }
        printf("\n");
    }
    // Запросы
    do {
        puts("Enter DESTINATION, DATE AND TIME separated by a space");
        scanf("%s%s%s", &destination, &date, &time);
        puts("<Number> <Destination> <Date> <time> <Places> <Cost>");
        for (a = 0; a < i; a++) printf("%s\n", str[a]);
        puts("<Number> <Destination> <Date> <time> <Places> <Cost>\n");
        for (a = 0; a < i; a++) {
            int flag = 1;
            if (_stricmp(groups[a][0], destination) != 0) flag = 0;
            if (strcmp(groups[a][1], date) != 0) flag = 0;
            if (strcmp(groups[a][2], time) >= 0) flag = 0;
            if (flag) {
                printf("\n");
                puts(str[a]);
            }
        }
        printf("\nEnter ESCAPE for close.");
    } while (_getch() != 27);
}