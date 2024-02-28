
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cstdlib>
#include <conio.h>

// Блок добавления/удаления
#define ADD_COMMAND "add"
#define ADD_COMMAND_CODE "1"
#define REMOVE_COMMAND "remove"
#define REMOVE_COMMAND_CODE "2"
#define EXIT_COMMAND_CODE "3"
#define EXIT_COMMAND "exit"
//

#define MAX_SIZE_TABLE 100 
#define MAX_SIZE_GNAME 150 
#define MAX_SIZE_AGER 5 
#define INVALID_INPUT -1
#define DEFAULT_INIT_STRING "__DFINIT\0"
#define DEFAULT_INIT_INT -1

void outputTable();

// Program Event
typedef void (*fptr)();
struct PrgrEvent {
    int ptrew;
    fptr eventWay[20];
} prevent;


void addToEventWay(fptr e){ prevent.eventWay[prevent.ptrew++] = e; }
void backEventWay(){ prevent.ptrew--; }
void startcEventWay(){ prevent.eventWay[prevent.ptrew - 1](); }
//

// TABLE
int amountElTable = 0;
struct Record 
{
    int number;

    struct GameStat
    {
        char name [MAX_SIZE_GNAME];
        int memoryD;
        int ageR;
        int graphic;
        int plrL;
        int arate;

    } gmst;

} table [MAX_SIZE_TABLE];

char isLineExist(int number)
{
    for (int i = 0; i < amountElTable; ++i)
        if (table[i].number == number) 
            return 1;
    return 0;
}

char isFieldExist(int number)
{
    return (number >= 0 && number <= 6);
}
//

bool isNumber(const char *str) 
{
    while(*str != '\0')
    {
        if(*str < '0' || *str > '9')
            return 0;
        str++;
    }
    return 1;
}

int inputNumber(int *n)
{
    int MAX_LEN_NUMBER = 20;
    char str_num [MAX_LEN_NUMBER];
    gets_s(str_num, MAX_LEN_NUMBER);
    if (strlen(str_num) == 0) return -1;
    if (!isNumber(str_num)) return -1;
    *n = atoi(str_num);
    return 0;
}

#ifdef _WIN32
void clearConsole()
{ system("cls"); }
#endif
#ifdef linux
void clearConsole()
{ system("clear") }
#endif


int inputGraphic(int * g)
// Коды ошибки: -1
{
    int temp = 0;

    printf("\ngraphic>");
    if ( inputNumber(&temp) != INVALID_INPUT) 
    {
        if ( !(temp >= 0 && temp <= 2) ) return INVALID_INPUT;
        *g = temp;
    }
    else return INVALID_INPUT;
    return 0;

}

int inputPlayerAm(int * pa)
// Коды ошибки: -1
{
    int temp = 0;
    printf("\nplayers>");

    if ( inputNumber(&temp) != INVALID_INPUT) 
    {
        if (temp != 0 && temp != 1) return INVALID_INPUT;
        *pa = temp;
       
    }
    else return INVALID_INPUT;
    return 0;
}

int inputArate(int * r)
// Коды ошибки: -1
{
    int temp = 0;
    printf("\nave rate>");

    if ( inputNumber(&temp) != INVALID_INPUT) 
    {
        if (!(temp >= 0 && temp <= 100)) return INVALID_INPUT;
        *r = temp;
       
    }
    else return INVALID_INPUT;
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
    char sep[] = " -,/.!?():;\'\"\n\t";
    char str [MAX_SIZE_GNAME];
    const int MAX_SEP_AMOUNT = 7; 

    printf("\nname>");
    gets_s(str, MAX_SIZE_GNAME);

    // Если знаков-разделитей неестественно много
    if (countCharsstrstr(str, sep) > MAX_SEP_AMOUNT) {
        printf( "many seps!" );
        return -1;
    }

    strcpy(n, str);

    return 0;
}


int inputMemoryD(int * m)
// Коды ошибки: -1
{
    int temp = 0;
    printf("\nmemory>");

    if ( inputNumber(&temp) != INVALID_INPUT) 
    {
        if (temp <= 0) return INVALID_INPUT;
        *m = temp;
       
    }
    else return INVALID_INPUT;
    return 0;
}


int checkAgeROrThrowEx(const char s[])
{
    char ds [] = "----";
    int ps = 0;
    char isCorrectInput = 1;

    // Синтакическая правильность
    if (s[ps] == '+' ) {
        printf("\nExpect digit before \"+\"\n");
        isCorrectInput = 0;
    }
    while (s[ps] != '+' && isCorrectInput)
    {
        if ( !isdigit( s[ps++] ) ){
            printf("\n:EXPECT \"+\" OR DIGIT!!");
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
    printf("\nage rate>");
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

// ADD/REMOVE EVENT
void event_add()
{
    fillRecord(&table[amountElTable]);
    table[amountElTable].number = amountElTable + 1;
    ++amountElTable;
}

void event_rem()
{
    char isExist   = 0;
    int numberLine = 0;
    char acceptCh  = 0;

    do {
        do 
            do printf("\nrem:");
            while (inputNumber( &numberLine ) == INVALID_INPUT);
        while ( numberLine < 0);

        do {
            printf("\nAre u sure? Y(es), N(o):");
            acceptCh = getchar();
            if ( tolower(acceptCh) == 'n' ) return;
        } while (tolower(acceptCh) != 'y');
        
        isExist = isLineExist(numberLine);
        if (isExist)
        {
            for (int i = numberLine - 1; i < amountElTable - 1; ++i)
                table[i] = table[i + 1];
            amountElTable -= 1;
        }
        else 
        {
            printf("\nLine did not find.");
        }

        printf("\nESC for back");
    } while ( _getch() != 27 );
}

void event_addRemove()
{
    char inputCommand[10];

    do {
        clearConsole();
        outputTable();
        
        printf("\n-- event_addRemove");
        printf("\ncommands:");
        printf("\n- 1) ADD");
        printf("\n- 2) REMOVE");
        printf("\n- 3) EXIT\n");
        printf("\nEnter cmd:");
        scanf("%s", inputCommand);
        
        while (getchar() != '\n');
        
        if (stricmp(inputCommand, ADD_COMMAND) == 0 
            || stricmp(inputCommand, ADD_COMMAND_CODE) == 0)
        {
            event_add();
        } 
        else if (stricmp(inputCommand, REMOVE_COMMAND) == 0
            || stricmp(inputCommand, REMOVE_COMMAND_CODE) == 0)
        {
            event_rem();
        }
        else if (stricmp(inputCommand, EXIT_COMMAND) == 0
            || stricmp(inputCommand, EXIT_COMMAND_CODE) == 0)
        {
            break;
        }
        else {
            printf("\nCommand did not find.");
        }

        printf("\nESC for back");
    } while(_getch() != 27);
}
//

void event_edit()
{
    enum field_codes {NAME, MEM, AGER, GRAPHIC, PLAYERS, AVERATE};
    int numberl = 0;
    int numberf = 0;

    if (amountElTable == 0) {
        printf("\nLines not!");
        return;
    }

    do {
        do printf("\nEnter record:");
        while (inputNumber( &numberl ) == INVALID_INPUT);
    } while ( !isLineExist(numberl) );

    do {
        do printf("\nEnter field:");
        while (inputNumber( &numberf ) == INVALID_INPUT);
    } while ( !isFieldExist(numberf) );

    fillField(&table[numberl - 1], numberf);
}


struct Call 
{
    enum nameCoincedence {ABSOLUTE, INTER};
    int nc;
    char name[MAX_SIZE_GNAME];
    
    enum borders {MORE, LESS};
    int bmem;
    int mem;

    int ageR;
    int graphic;
    int plrL;

    int barate;
    int arate;
};

void inputNameForCall(struct Call *cl)
{
    do
        do printf("\nAbslt = %d, inter = %d\n:", cl->ABSOLUTE, cl->INTER);
        while (inputNumber(&cl->nc) == INVALID_INPUT);
    while (cl->nc != cl->ABSOLUTE && cl->nc != cl->INTER);
    printf("\nname:");
    while ( inputNameAndCheckOrThrowEx(cl->name) == INVALID_INPUT );
}

void inputMemForCall(struct Call *cl)
{
    do
        do printf("\nMORE = %d, LESS = %d\n:", cl->MORE, cl->LESS);
        while (inputNumber(&cl->bmem) == INVALID_INPUT);
    while (cl->bmem != cl->MORE && cl->bmem != cl->LESS);
    while ( inputMemoryD(&cl->mem) == INVALID_INPUT );
}

void inputAverForCall(struct Call *cl)
{
    do 
        do printf("\nMORE = %d, LESS = %d\n:", cl->MORE, cl->LESS);
        while (inputNumber(&cl->barate) == INVALID_INPUT);
    while (cl->barate != cl->MORE && cl->barate != cl->LESS);
    while ( inputArate(&cl->arate) == INVALID_INPUT );
}


void inputAgerateForCall(struct Call *cl)
{
    do
        do printf("\nage rate:");
        while (inputNumber(&cl->ageR) == INVALID_INPUT);
    while(cl->ageR < 0 && cl->ageR > 100);
}

void call_init_default(struct Call *cl)
{
    strcpy(cl->name, DEFAULT_INIT_STRING);
    cl->mem     = DEFAULT_INIT_INT;
    cl->ageR    = DEFAULT_INIT_INT;
    cl->graphic = DEFAULT_INIT_INT;
    cl->plrL    = DEFAULT_INIT_INT;
    cl->arate   = DEFAULT_INIT_INT;
}

void outRecord(const struct Record *rec)
{
    printf(" %10d ", rec->number);
    printf(" \t%10s ", rec->gmst.name);
    printf(" %10d ", rec->gmst.memoryD);
    printf(" %10d+ ", rec->gmst.ageR);
    printf(" \t%10d ", rec->gmst.graphic);
    printf(" \t%10d ", rec->gmst.plrL);
    printf(" \t%10d ", rec->gmst.arate);

}

void inputFieldsForCall(struct Call *cl)
{
    char fields[8];

    printf("\nfileds:");
    gets_s(fields, 7);
    
    for (int i = 0; i < 6; ++i)
    {
        switch (fields[i] - '0')
        {
        case NAME: inputNameForCall(cl);
            break;
        case MEM: inputMemForCall(cl);
            break;
        case AGER: inputAgerateForCall(cl);
            break;
        case GRAPHIC: inputGraphic(&cl->graphic);
            break;
        case PLAYERS: inputPlayerAm(&cl->plrL);
            break;
        case AVERATE: inputAverForCall(cl);
            break;
        }
    }
}

void event_call()
{
    struct Call cl; 
    call_init_default(&cl);
    inputFieldsForCall(&cl);

    printf("\nNeed:\n");
    const struct Record *rec;
    char isNeedRec;
    for (int i = 0; i < amountElTable; ++i)
    {
        isNeedRec = 1;
        rec = &table[i];
        if (strcmp(cl.name, DEFAULT_INIT_STRING) != 0)
            if (cl.nc == cl.ABSOLUTE)
                isNeedRec = (stricmp(cl.name, rec->gmst.name) == 0);
            else 
                isNeedRec = (strstr(rec->gmst.name, cl.name) != NULL);

        if (cl.mem != DEFAULT_INIT_INT && isNeedRec) //REFACTORING !! cl.mem != DEFAULT_INIT_INT
            if (cl.bmem == cl.LESS) isNeedRec = (rec->gmst.memoryD < cl.mem);
            else isNeedRec = (rec->gmst.memoryD > cl.mem);

        if (cl.ageR != DEFAULT_INIT_INT && isNeedRec)
            isNeedRec = (cl.ageR > rec->gmst.ageR);
        
        if (cl.graphic != DEFAULT_INIT_INT && isNeedRec)
            isNeedRec = (cl.graphic == rec->gmst.graphic);

        if (cl.plrL != DEFAULT_INIT_INT && isNeedRec)
            isNeedRec = (cl.plrL == rec->gmst.plrL);

        if (cl.arate != DEFAULT_INIT_INT && isNeedRec)
            if (cl.barate == cl.MORE) isNeedRec = (cl.arate < rec->gmst.arate);
            else isNeedRec = (cl.arate > rec->gmst.arate);
    
        if (isNeedRec){
            outRecord(rec);
            printf("\n");
        }
    }
}

void outputTable()
{
    printf("\n  Line\t\t Name(%d) \t Mem(%d) \t Age(%d) \t Graph(%d) \t Player(%d) \t aver(%d)\n", 
            NAME, MEM, AGER, GRAPHIC, PLAYERS, AVERATE);

    for (int i = 0; i < amountElTable; i++)
    {
        outRecord(&table[i]);
        printf("\n");
    }
    
}

void event_exit_program()
{
    printf("Bye");
    exit(0);
}

void intro()
{
    printf("\n\n\t\t\tWELCOME!");
    printf("\n\t\t\tdevelop by https://github.com/eastpriSs");
    _getch();
}

void event_ivalid_command()
{
    printf("\nInvalid command\n");
}

// START EVENT
void start()
{
    int input = 0;
    
    printf("\nEnter number:");
    printf("\n1) ADD/REMOVE");
    printf("\n2) EDIT");
    printf("\n3) UN CALL");
    printf("\n4) EXIT");
    printf("\ncommand>");
    
    inputNumber(&input);

    switch (input)
    {
    case 1: addToEventWay(event_addRemove);
        break;
    case 2: addToEventWay(event_edit);
        break;
    case 3: addToEventWay(event_call);
        break;
    case 4: addToEventWay(event_exit_program);
        break;
    default:
        addToEventWay(event_ivalid_command);
        break;
    }
}
//


int main ()
{
    intro();
    clearConsole();
    addToEventWay(start);
    while(1) {
        outputTable();
        startcEventWay(); // запускаем старт
        startcEventWay(); // ивент, добавленный со старта
        printf("\n...\n");
        _getch();
        backEventWay();
        clearConsole();
    }
}