#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "mystring.h"

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

        _prints("\n\nEnter text: ");
        _gets(text);

        // Добавление слов в массив
        char * word = _strtok(text, SEPARATORS);
        size_t amountLex = 0;

        while (word != NULL)
        {
            _strcpy(wordsOfText[amountLex++], word);
            word = _strtok(NULL, SEPARATORS);
        }
        // Подсчет упоминаний каждого слова в тексте 
        for (size_t i = 0; i < amountLex; ++i) 
        {
            for (size_t j = 0; j < amountLex; ++j)
            {
                if (_stricmp(wordsOfText[i], wordsOfText[j]) == 0)
                    amountOfWordsInText[i] += 1;
            }
        }
        // Вывод слов и количество упоминаний, соответсвенно
        for (size_t i = 0; i < amountLex; ++i){
            _prints("\nWord: ");
            _prints(wordsOfText[i]);
            _prints(" amount:");
            printf("%d\n", amountOfWordsInText[i]);
        }

        // Вывод слов, если они упоминаются в тексте один раз, т.е. уникальные
        _prints("\nUnique words:\n");
        for (size_t i = 0; i < amountLex; ++i)
            if (amountOfWordsInText[i] == 1) {
                _prints(wordsOfText[i]);
                _prints("\n");
            }
        _prints("\nEnter ESCAPE for exit.");
    } while(_getch() != 27);
}