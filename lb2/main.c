
#include <stdio.h>
#include <string.h>

#define N 80
#define M 255

char table[N][M];
char unager [N][4]; // Все возрастные рейтинги, без повторений 
size_t amountLines = 0;
size_t amountuAger = 0;

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

char* getAgeFromLine(char * line)
{
    char space [] = " ";
    char _line[M];
    strcpy(_line, line); 
    strtok(_line, space); // имя
    strtok(NULL, space); // память
    return strtok(NULL, space); // возраст
}

void findUnAgerFillTable()
{
    char * la;
    char isFind = 0;
    for (size_t i = 0; i < amountLines; ++i)
    {
        la = getAgeFromLine(table[i]);
        isFind = 0;
        for (size_t j = 0; j < amountLines; ++j)
        {
            if ( strcmp(la, unager[j]) == 0 ) isFind = 1;
        }
        if (!isFind) strcpy(unager[amountuAger++], la);
    }
    
} 

/*

Valorant 1000 6+ 2 1 89
###

*/

void makeCall()
{
    char line[M];
    char space [] = " ";
    char * graphic;
    char * plrs;
    for (size_t i = 0; i < amountuAger; ++i)
    {
        printf("\n* Games for %s\n\n", unager[i]);
        for (size_t j = 0; j < amountLines; ++j)
        {
            if ( strcmp( unager[i], getAgeFromLine(table[j]) ) == 0 ) {
                strcpy(line, table[j]);
                strtok(line, space);
                strtok(NULL, space);
                strtok(NULL, space);
                graphic = strtok(NULL, space);
                plrs = strtok(NULL, space);
                if (strcmp(graphic, "2") == 0 && strcmp(plrs, "1") == 0)
                    puts(table[j]);
            }
        }
    }
    
}

int main()
{

    puts("\nEnter your text.");
    puts("\nEnter ### for stop.");
    inputTable();

    puts("\n<Name>\t    <Memory> <Age rating> <Graphics> <Players> <Rate>\n");
    outputTable();

    findUnAgerFillTable();

    makeCall();
       
}