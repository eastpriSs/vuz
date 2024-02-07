#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX_TEXT_SIZE 255
#define SEPARATORS " -,/.!?():;\'\""

int main()
{
    char text[MAX_TEXT_SIZE];
    char wordsOfText[MAX_TEXT_SIZE/2][MAX_TEXT_SIZE];
    size_t amountOfWordsInText[MAX_TEXT_SIZE/2];

    do{
        // Изначально уоличество упоминаний каждого слова равно нулю
        for (size_t i = 0; i < MAX_TEXT_SIZE/2; ++i) 
            amountOfWordsInText[i] = 0;

        printf("\n\nEnter text: ");
        gets(text);

        // Добавление слов в массив
        char * word = strtok(text, SEPARATORS);
        size_t amountLex = 0;

        while (word != NULL)
        {
            strcpy(wordsOfText[amountLex++], word);
            word = strtok(NULL, SEPARATORS);
        }
        // Подсчет упоминаний каждого слова в тексте 
        for (size_t i = 0; i < amountLex; ++i) 
        {
            for (size_t j = 0; j < amountLex; ++j)
            {
                if (stricmp(wordsOfText[i], wordsOfText[j]) == 0)
                    amountOfWordsInText[i] += 1;
            }
        }
        // Вывод слов и количество упоминаний, соответсвенно
        for (size_t i = 0; i < amountLex; ++i) 
            printf("\nword: %s, amount: %d", wordsOfText[i], amountOfWordsInText[i]);

        // Вывод слов, если они упоминаются в тексте один раз, т.е. уникальные
        puts("\nUnique words:");
        for (size_t i = 0; i < amountLex; ++i)
            if (amountOfWordsInText[i] == 1) printf("\n%s", wordsOfText[i]);

        printf("\nEnter ESCAPE for exit.");
    } while(_getch() != 27);
}