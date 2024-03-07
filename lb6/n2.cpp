
#include <stdio.h>
#include <string.h>

#define MAX_TEXT_SIZE 255
#define TEXT "hello world!"

#define SEPARATORS " -,/.!?():;\'\""

void fillFile(FILE * f)
{
    fputs(TEXT, f);
}

void outputDataFile(FILE * f)
{
    char chff;
    while ( (chff = fgetc(f)) != EOF )
        putchar(chff);
}

char findWord(char words[MAX_TEXT_SIZE/2][MAX_TEXT_SIZE], int amountWords, char word [] )
{
    for (int i = 0; i < amountWords; ++i)
        if (stricmp(words[i], word) == 0) return 1;
    return 0;    
}

void freadCharsTo(char a[], FILE * f)
{
    char chff;
    int amountCh = 0;
    while ( (chff = fgetc(f)) != EOF )
        a[amountCh++] = chff;
}

void countWordsAndWrite(char words[MAX_TEXT_SIZE/2][MAX_TEXT_SIZE], 
                            int resultAmount[MAX_TEXT_SIZE/2], int amountLex)
{
    for (int i = 0; i < amountLex; ++i) 
        for (int j = 0; j < amountLex; ++j)
            if (stricmp(words[i], words[j]) == 0)
                resultAmount[i] += 1;
}

int findMax(int a[MAX_TEXT_SIZE/2], int len)
{
    int max = a[0];
    for (int i = 0; i < len; i++)
        if (a[i] > max) max = a[i];
    return max;
}

void outResult(FILE * f)
{
    char wordsf [MAX_TEXT_SIZE/2][MAX_TEXT_SIZE];
    char outputedWordsf [MAX_TEXT_SIZE/4][MAX_TEXT_SIZE];
    char strfF [MAX_TEXT_SIZE];
    int amountOfWordsInText[MAX_TEXT_SIZE/2] = {0};

    int amountLex = 0;

    // Считывание
    freadCharsTo(strfF, f);

    // Разбиение на слова
    char * word = strtok(strfF, SEPARATORS);
    while (word != NULL)
    {
        strcpy(wordsf[amountLex++], word);
        word = strtok(NULL, SEPARATORS);
    }

    // Подсчет каждого слова
    countWordsAndWrite(wordsf, amountOfWordsInText, amountLex);
    
    // Нахождение максимального
    int max = findMax(amountOfWordsInText, amountLex); 

    // Вывод слов, если они упоминаются в тексте максимальное кол-во раз раз
    int amountOutLex = 0;
    printf("\n\nMet most times:");
    for (int i = 0; i < amountLex; ++i) {
        if (amountOfWordsInText[i] == max 
                    && !findWord(outputedWordsf, amountOutLex, wordsf[i])) {
            strcpy(outputedWordsf[amountOutLex++], wordsf[i]);
            printf("\n%s, amount: %d", wordsf[i], amountOfWordsInText[i]);
        }
    }
    if (amountOutLex == 1) puts("\n--- Only one word");
}

int main()
{
    FILE * ptrFileW = fopen("out2.txt", "w");
    FILE * ptrFileR = fopen("out2.txt", "r");
    
    printf("\nOrigin file: ");
    fillFile(ptrFileW);
    fclose(ptrFileW);
    outputDataFile(ptrFileR);
    
    fseek(ptrFileR, 0, SEEK_SET); // сброс указателя

    outResult(ptrFileR);
}