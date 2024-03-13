#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

#define N 80
#define M 255

char table[N][M];
size_t amountLines = 0;

void inputTable()
{
    for (size_t i = 0; i < N; ++i) { 
        gets(table[i]);
        if ( strcmp(table[i], "###") == 0 ){
            amountLines = i;
            break;
        }
    }
}

void outputTable()
{
    puts("\n<Name>\t    <Memory> <Age rating> <Graphics> <Players> <Rate>\n");
    char line[M];
    char * lex;
    char sep[] = " "; 
    size_t llen = 0;
    for (size_t i = 0; i < amountLines; ++i) {
        strcpy(line, table[i]);
        lex = strtok(line, sep);
        while (lex != NULL)
        {
            llen = strlen(lex);
            if (llen > 8) printf("%13s", lex);
            else if (llen > 20) printf("%15s", lex);
            else printf("%10s", lex);
            lex = strtok(NULL, sep);
        }
        printf("\n");
    }
}


char * numInStr(char* s)
// Находит число от начала строки до символа,
// который не является цифрой. Пример. 16+
// Вывод. 16
{
    char * num = calloc(strlen(s) + 1, sizeof(char));
    
    size_t i = 0;
    for (; isdigit(s[i]); ++i){
        num[i] = s[i];
    }
    num[i + 1] = '\0';
    return num;
}

void makeCall(int currentAge)
{
    char line[M];
    char space [] = " ";
    char * la; // возраст
    char * lg; // графика
    char * lp; // игроки
    int numLa;
    char isFind = 0;
    for (size_t i = 0; i < amountLines; ++i)
    {
        strcpy(line, table[i]); // сохраняем значение
        strtok(line, space); // имя
        strtok(NULL, space);  // память
        la = numInStr(strtok(NULL, space));
        lg = strtok(NULL, space);
        lp = strtok(NULL, space);

        numLa = atoi(la);
        if ( (currentAge >= numLa) 
        && (strcmp(lg, "2") == 0)
        &&  (strcmp(lp, "1") == 0) )
        {
            printf("\n");
            puts(table[i]);
            isFind = 1;
        }
        free(la);
    }
    
    if (!isFind) printf("\nFor age = %d did not found any games.\n", currentAge);
}


int tableCorrect()
// -1 таблица верна
{
    char line[M];
    char space [] = " ";
    int aml;
    for (size_t i = 0; i < amountLines; ++i)
    {
        aml = 0;
        strcpy(line, table[i]);
        strtok(line, space);
        while (strtok(NULL, space) != NULL) aml++;

        if (aml != 5) return i;
    }
    return -1;
}

int main()
{
    int tc;
    do{ 
        puts("\nEnter your text.");
        puts("\nEnter ### for stop.");

        inputTable();
        tc = tableCorrect();
        if (tc != -1) printf("\n!! Invalid line id:%d\n", tc+1); 

    }while(tc != -1);

    do{
        outputTable();

        int currentAge;
        printf("\nEnter age:");
        scanf("%d", &currentAge);

        printf("\nSolo games for your age(%d) with good graphic:\n", currentAge);
        makeCall(currentAge);
    
        printf("\nEnter ESCAPE for close.");
    } while (getch() != 27);
}