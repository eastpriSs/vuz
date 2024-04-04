/*

    Модуль ввода inputFunc.c

*/

#include <stdio.h>
#include <ctype.h>
#include <conio.h>

#define INVALID_INPUT -1
#define MAX_SIZE_GNAME 255

typedef struct Record Record;


void waitButtom()
{
    printf("\n\nWaiting for the button...");
    _getch();
}

void clearStdin()
{
    fseek(stdin, 0, SEEK_SET);
}

void waitInt(int * ref)
{
    while (scanf("%d", ref) != 1)
        clearStdin();
    clearStdin();
}

int inputGraphic(int * g)
// Коды ошибки: -1
{
    int temp = 0;

    printf("\ngraphics > ");
    
    waitInt(&temp);
    if ( !(temp >= 0 && temp <= 2) ) return INVALID_INPUT;
    *g = temp;

    return 0;

}

int inputPlayerAm(int * pa)
// Коды ошибки: -1
{
    int temp = 0;
    printf("\nplayers > ");

    waitInt(&temp);
    if (temp != 0 && temp != 1) return INVALID_INPUT;
    *pa = temp;
    
    return 0;
}

int inputArate(int * r)
// Коды ошибки: -1
{
    int temp = 0;
    printf("\nRange of ratings [0 ; 100]\nrating of critics > ");

    waitInt(&temp);
    if (!(temp >= 0 && temp <= 100)) return INVALID_INPUT;
    *r = temp;
       
    return 0;

}

int countCharsstrstr(char * countHere, char * chFrom){
    size_t cfl = strlen(chFrom);
    size_t chl = strlen(countHere);
    size_t count = 0;
    char ischfrom = 0;
    for (int i = 0; i < chl; ++i)
    {
        ischfrom = 0;
        for (int j = 0; j < cfl; ++j)
        {
            if ( countHere[i] == chFrom[j] && chFrom[j] != '\0')
                ischfrom = 1;
        }
        if (ischfrom) count += 1;
    }
    return count; 
}

int inputNameAndCheckOrThrowEx(char n [])
{
    char sep[] = " <>-,/.!?():;\'\"\n\t";
    char str [MAX_SIZE_GNAME];
    const int MAX_SEP_AMOUNT = 7; 

    printf("\nThe name of the game > ");
    gets_s(str, MAX_SIZE_GNAME);

    // Если знаков-разделитей неестественно много
    if (countCharsstrstr(str, sep) > MAX_SEP_AMOUNT) {
        printf( "Many seporators" );
        return -1;
    }

    strcpy(n, str);

    return 0;
}


int inputMemoryD(int * m)
// Коды ошибки: -1
{
    int temp = 0;
    printf("\nmemory > ");

    waitInt(&temp);
    
    if (temp <= 0) return INVALID_INPUT;
    *m = temp;   
    return 0;
}


int checkAgeROrThrowEx(const char s[])
{
    char ds [] = "----";
    int ps = 0;
    char isCorrectInput = 1;

    // Синтакическая правильность
    if (s[ps] == '+' ) {
        printf("\nExpected digit or \"+\"\n");
        isCorrectInput = 0;
    }
    while (s[ps] != '+' && isCorrectInput)
    {
        if ( !isdigit( s[ps++] ) ){
            printf("\n:nExpected \"+\" or digit.");
            printf("\n:%.*s", ps - 1, s);
            printf("\n:%.*s^\n", ps - 1, ds);
            isCorrectInput = 0;
        }
    }

    return isCorrectInput;
}

char * numInStr(char* s)
// Находит число от начала строки до символа,
// который не является цифрой. Пример. 16+
// Вывод. 16
{
    char * num = (char*)calloc(strlen(s) + 1, sizeof(char));
    
    size_t i = 0;
    for (; isdigit(s[i]); ++i){
        num[i] = s[i];
    }
    num[i + 1] = '\0';
    return num;
}

int inputAgeR(int * ag)
// Коды ошибки: -1
{
    char str[20];
    char * n;
    printf("\n(format: 6+,7+,..,18+,....)\n age rate > ");
    gets_s(str, 20);
    if (checkAgeROrThrowEx(str) == 0)
        return -1;
    n = numInStr(str);
    *ag = atoi( n );
    free(n);
    return 0;
}

enum field_codes {NAME, MEM, AGER, GRAPHIC, PLAYERS, AVERATE};
void fillField(struct Record *rec, int numberf)
{
    switch (numberf)
    {

    case NAME:
        while( inputNameAndCheckOrThrowEx(rec->gmst.name) == INVALID_INPUT);
    break;

    case MEM:
        while( inputMemoryD(&rec->gmst.memoryD) == INVALID_INPUT);    
    break;

    case AGER:
        while ( inputAgeR(&rec->gmst.ageR) == INVALID_INPUT);
    break;

    case GRAPHIC:
        while (inputGraphic(&rec->gmst.graphic) == INVALID_INPUT);
    break;

    case PLAYERS:
        while ( inputPlayerAm(&rec->gmst.plrL) == INVALID_INPUT);
    break;

    case AVERATE:
        while ( inputArate(&rec->gmst.arate) == INVALID_INPUT);
    break;

    }
}

void fillRecord(struct Record *rec)
{
    fillField(rec, NAME);
    fillField(rec, MEM);
    fillField(rec, AGER);
    fillField(rec, GRAPHIC);
    fillField(rec, PLAYERS);
    fillField(rec, AVERATE);
}

void inputNameForCall(struct Call *cl)
{
    do {
        printf("\nAbsolute coincidence = %d, Part coincidence = %d\n: ", cl->ABSOLUTE, cl->INTER);
        waitInt(&cl->nc);
    } while (cl->nc != cl->ABSOLUTE && cl->nc != cl->INTER);
    while ( inputNameAndCheckOrThrowEx(cl->name) == INVALID_INPUT );
}

void inputMemForCall(struct Call *cl)
{
    do {
        printf("\nMore = %d, less = %d\n: ", cl->MORE, cl->LESS);
        waitInt(&cl->bmem);
    } while (cl->bmem != cl->MORE && cl->bmem != cl->LESS);
    while ( inputMemoryD(&cl->mem) == INVALID_INPUT );
}

void inputAverForCall(struct Call *cl)
{
    do {
        printf("\nMore = %d, less = %d\n: ", cl->MORE, cl->LESS);
        waitInt(&cl->barate);
    } while (cl->barate != cl->MORE && cl->barate != cl->LESS);
    while ( inputArate(&cl->arate) == INVALID_INPUT );
}


void inputAgerateForCall(struct Call *cl)
{
    do {
        printf("\nEnter your age > ");
        waitInt(&cl->ageR);
    } while(cl->ageR < 0 && cl->ageR > 100);
}

void enterFileName(char * fn) // ?? inputFuncs
{
    printf("\n- * - Enter name of file with database  - * - \n");
    printf("\n - If the program finds the file, it will be able to open it. ");
    printf("\n - Else, the program can create it.\n");
    char loop;
    do {
        loop = 1;
        printf("\nEnter \"-1\" for exit OR name of file");
        printf("\n > ");
        gets_s(fn, MAX_FILENAME);
        
        if ( strpbrk(fn, "\\/:*?\"<>|") != NULL ) continue;

        if ( (strcmp(fn, "con") == 0 ) || (strcmp(fn, "prn") == 0) )
            continue;

        if (strcmp(fn, "-1") == 0) exit(EXIT_SUCCESS);

        if (!isFileExistInCDir(fn)) 
        {
            printf("\nThere is no such file.\n");
            printf("\nMaybe we'll create one?\n");
        }
        else 
            printf("\nThe file has been found. Open it?\n");
        
        printf("\nEnter \"y\" fore positive answer > ");
        if (getchar() == 'y') loop = 0;
        clearStdin();
        
    } while(loop);
}