
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
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


void addToEventWay(fptr e) { prevent.eventWay[prevent.ptrew++] = e; }
void backEventWay() { prevent.ptrew--; }
void startcEventWay() { prevent.eventWay[prevent.ptrew - 1](); }
//

// TABLE
int amountElTable = 0;
struct Record
{
    int number;

    struct GameStat
    {
        char name[MAX_SIZE_GNAME];
        int memoryD;
        int ageR;
        int graphic;
        int plrL;
        int arate;

    } gmst;

} table[MAX_SIZE_TABLE];

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

bool isNumber(const char* str)
{
    if (*str == '+' || *str == '-')
        str++;

    while (*str != '\0')
    {
        if (*str < '0' || *str > '9')
            return 0;
        str++;
    }
    return 1;
}

int inputNumber(int* n)
{
    const int MAX_LEN_NUMBER = 100;
    char str_num[MAX_LEN_NUMBER];
    gets_s(str_num, MAX_LEN_NUMBER);
    if (strlen(str_num) == 0) return -1;
    if (!isNumber(str_num)) return -1;
    *n = atoi(str_num);
    return 0;
}

#ifdef _WIN32
void clearConsole()
{
    system("cls");
}
#endif
#ifdef linux
void clearConsole()
{
    system("clear")
}
#endif


int inputGraphic(int* g)
// Коды ошибки: -1
{
    int temp = 0;

    printf("\n(2 - хорошая, 1 - нормальная,  0 - плохая)\nГрафика>");
    if (inputNumber(&temp) != INVALID_INPUT)
    {
        if (!(temp >= 0 && temp <= 2)) return INVALID_INPUT;
        *g = temp;
    }
    else return INVALID_INPUT;
    return 0;

}

int inputPlayerAm(int* pa)
// Коды ошибки: -1
{
    int temp = 0;
    printf("\n(1 - индивидуальная,  0 - без ограничений)\nКол-во игроков>");

    if (inputNumber(&temp) != INVALID_INPUT)
    {
        if (temp != 0 && temp != 1) return INVALID_INPUT;
        *pa = temp;

    }
    else return INVALID_INPUT;
    return 0;
}

int inputArate(int* r)
// Коды ошибки: -1
{
    int temp = 0;
    printf("\n(0 - 100)\nсред. рейтинг>");

    if (inputNumber(&temp) != INVALID_INPUT)
    {
        if (!(temp >= 0 && temp <= 100)) return INVALID_INPUT;
        *r = temp;

    }
    else return INVALID_INPUT;
    return 0;

}

int countCharsstrstr(char* countHere, char* chFrom) {
    size_t cfl = strlen(chFrom);
    size_t chl = strlen(countHere);
    size_t count = 0;
    char ischfrom = 0;
    for (int i = 0; i < chl; ++i)
    {
        ischfrom = 0;
        for (int j = 0; j < cfl; ++j)
        {
            if (countHere[i] == chFrom[j] && chFrom[j] != '\0')
                ischfrom = 1;
        }
        if (ischfrom) count += 1;
    }
    return count;
}

int inputNameAndCheckOrThrowEx(char n[])
{
    char sep[] = " <>-,/.!?():;\'\"\n\t";
    char str[MAX_SIZE_GNAME];
    const int MAX_SEP_AMOUNT = 7;

    printf("\nимя>");
    gets_s(str, MAX_SIZE_GNAME);

    if (strlen(str) == 0) return INVALID_INPUT;

    // Если знаков-разделитей неестественно много
    if (countCharsstrstr(str, sep) > MAX_SEP_AMOUNT) {
        printf("Чересчур много разделителей.");
        return -1;
    }

    strcpy(n, str);

    return 0;
}


int inputMemoryD(int* m)
// Коды ошибки: -1
{
    int temp = 0;
    printf("\nместо на диске>");

    if (inputNumber(&temp) != INVALID_INPUT)
    {
        if (temp <= 0) return INVALID_INPUT;
        *m = temp;

    }
    else return INVALID_INPUT;
    return 0;
}


int checkAgeROrThrowEx(const char s[])
{
    char ds[] = "----";
    int ps = 0;
    char isCorrectInput = 1;

    // Синтакическая правильность
    if (s[ps] == '+') {
        printf("\nОжидалось число перед знаком \"+\"\n");
        isCorrectInput = 0;
    }
    while (s[ps] != '+' && isCorrectInput)
    {
        if (!isdigit(s[ps++])) {
            printf("\n:Ожидался \"+\" или число.");
            printf("\n:%.*s", ps - 1, s);
            printf("\n:%.*s^\n", ps - 1, ds);
            isCorrectInput = 0;
        }
    }

    return isCorrectInput;
}

char* numInStr(char* s)
// Находит число от начала строки до символа,
// который не является цифрой. Пример. 16+
// Вывод. 16
{
    char* num = (char*)calloc(strlen(s) + 1, sizeof(char));

    size_t i = 0;
    for (; isdigit(s[i]); ++i) {
        num[i] = s[i];
    }
    num[i + 1] = '\0';
    return num;
}

int inputAgeR(int* ag)
// Коды ошибки: -1
{
    char str[100];
    char* n;
    printf("\n(формат:6+,7+,..,18+,....)\nвозрастной рейтинг>");
    gets_s(str, 100);
    if (checkAgeROrThrowEx(str) == 0)
        return -1;
    n = numInStr(str);
    *ag = atoi(n);
    free(n);
    return 0;
}

enum field_codes { NAME, MEM, AGER, GRAPHIC, PLAYERS, AVERATE };
void fillField(struct Record* rec, int numberf)
{
    switch (numberf)
    {

    case NAME:
        while (inputNameAndCheckOrThrowEx(rec->gmst.name) == INVALID_INPUT);
        break;

    case MEM:
        while (inputMemoryD(&rec->gmst.memoryD) == INVALID_INPUT);
        break;

    case AGER:
        while (inputAgeR(&rec->gmst.ageR) == INVALID_INPUT);
        break;

    case GRAPHIC:
        while (inputGraphic(&rec->gmst.graphic) == INVALID_INPUT);
        break;

    case PLAYERS:
        while (inputPlayerAm(&rec->gmst.plrL) == INVALID_INPUT);
        break;

    case AVERATE:
        while (inputArate(&rec->gmst.arate) == INVALID_INPUT);
        break;

    }
}

void fillRecord(struct Record* rec)
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
    char isExist = 0;
    int numberLine = 0;
    char acceptCh = 0;

    do {
        printf("\nВведите -2 для выхода.");
        do {
            do printf("\nномер строки для удаления>");
            while (inputNumber(&numberLine) == INVALID_INPUT);
            if (numberLine == -2) return;
        } while (numberLine < 0);

        do {
            printf("\nВы уверены в выборе? Y(es), N(o):");
            acceptCh = getchar();
            while (getchar() != '\n');
            if (tolower(acceptCh) == 'n') return;
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
            printf("\nСтрока с заданным номером не была найдена.");
        }

        printf("\nНажмите ESCAPE для выхода в добавление/удаление...");
    } while (_getch() != 27);
}

void event_addRemove()
{
    char inputCommand[10];

    do {
        clearConsole();
        outputTable();

        printf("\n-- Добавление/Удаление");
        printf("\nкоманды:");
        printf("\n- 1) ADD");
        printf("\n- 2) REMOVE");
        printf("\n- 3) EXIT\n");
        printf("\nВведите команду или номер команды:");
        scanf("%s", inputCommand);

        while (getchar() != '\n');

        if (_stricmp(inputCommand, ADD_COMMAND) == 0
            || _stricmp(inputCommand, ADD_COMMAND_CODE) == 0)
        {
            event_add();
        }
        else if (_stricmp(inputCommand, REMOVE_COMMAND) == 0
            || _stricmp(inputCommand, REMOVE_COMMAND_CODE) == 0)
        {
            event_rem();
        }
        else if (_stricmp(inputCommand, EXIT_COMMAND) == 0
            || _stricmp(inputCommand, EXIT_COMMAND_CODE) == 0)
        {
            break;
        }
        else {
            printf("\nКоманда не была найдена.");
        }

        printf("\nНажмите ESCAPE для выхода в меню...");
    } while (_getch() != 27);
}
//

void event_edit()
{
    enum field_codes { NAME, MEM, AGER, GRAPHIC, PLAYERS, AVERATE };
    int numberl = 0;
    int numberf = 0;

    if (amountElTable == 0) {
        printf("\nНету записей в таблице.");
        return;
    }

    printf("\nВведите -2 для выхода.");

    do {
        do printf("\nНомер запии>");
        while (inputNumber(&numberl) == INVALID_INPUT);
        if (numberl == -2) return;
    } while (!isLineExist(numberl));

    do {
        do printf("\nНомер поля>");
        while (inputNumber(&numberf) == INVALID_INPUT);
        if (numberf == -2) return;
    } while (!isFieldExist(numberf));

    fillField(&table[numberl - 1], numberf);
}


struct Call
{
    enum nameCoincedence { ABSOLUTE, INTER };
    int nc;
    char name[MAX_SIZE_GNAME];

    enum borders { MORE, LESS };
    int bmem;
    int mem;

    int ageR;
    int graphic;
    int plrL;

    int barate;
    int arate;
};

void inputNameForCall(struct Call* cl)
{
    do
        do printf("\nАбсолютное совпадение = %d, Имеется вхождение = %d\n:", cl->ABSOLUTE, cl->INTER);
    while (inputNumber(&cl->nc) == INVALID_INPUT);
    while (cl->nc != cl->ABSOLUTE && cl->nc != cl->INTER);
    printf("\nимя>");
    while (inputNameAndCheckOrThrowEx(cl->name) == INVALID_INPUT);
}

void inputMemForCall(struct Call* cl)
{
    do
        do printf("\nБОЛЬШЕ = %d, меньше = %d\n:", cl->MORE, cl->LESS);
    while (inputNumber(&cl->bmem) == INVALID_INPUT);
    while (cl->bmem != cl->MORE && cl->bmem != cl->LESS);
    while (inputMemoryD(&cl->mem) == INVALID_INPUT);
}

void inputAverForCall(struct Call* cl)
{
    do
        do printf("\nБОЛЬШЕ = %d, меньше = %d\n:", cl->MORE, cl->LESS);
    while (inputNumber(&cl->barate) == INVALID_INPUT);
    while (cl->barate != cl->MORE && cl->barate != cl->LESS);
    while (inputArate(&cl->arate) == INVALID_INPUT);
}


void inputAgerateForCall(struct Call* cl)
{
    do
        do printf("\nвозрастной рейтинг>");
    while (inputNumber(&cl->ageR) == INVALID_INPUT);
    while (cl->ageR < 0 && cl->ageR > 100);
}

void call_init_default(struct Call* cl)
{
    strcpy(cl->name, DEFAULT_INIT_STRING);
    cl->mem = DEFAULT_INIT_INT;
    cl->ageR = DEFAULT_INIT_INT;
    cl->graphic = DEFAULT_INIT_INT;
    cl->plrL = DEFAULT_INIT_INT;
    cl->arate = DEFAULT_INIT_INT;
}

void outRecord(const struct Record* rec)
{
    printf(" %10d ", rec->number);
    printf(" \t%10s ", rec->gmst.name);
    printf(" %10d ", rec->gmst.memoryD);
    printf(" %10d+ ", rec->gmst.ageR);
    printf(" \t%10d ", rec->gmst.graphic);
    printf(" \t%10d ", rec->gmst.plrL);
    printf(" \t%10d ", rec->gmst.arate);

}

void inputFieldsForCall(struct Call* cl)
{
    char fields[50];

    printf("\nВведите exit для выхода");
    printf("\nинтересующие поля>");
    gets_s(fields, 50);

    if (_stricmp(EXIT_COMMAND, fields) == 0) return;

    size_t flen = strlen(fields);
    for (int i = 0; i < flen; ++i)
    {
        printf("\nПоле номер %d\n", fields[i] - '0');
        switch (fields[i] - '0')
        {
        case NAME: inputNameForCall(cl);
            break;
        case MEM: inputMemForCall(cl);
            break;
        case AGER: inputAgerateForCall(cl);
            break;
        case GRAPHIC: while (inputGraphic(&cl->graphic) == INVALID_INPUT);
            break;
        case PLAYERS: while (inputPlayerAm(&cl->plrL) == INVALID_INPUT);
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

    printf("\nЗаписи, удовлетворяющие запросу:\n");
    const struct Record* rec;
    char isNeedRec;
    for (int i = 0; i < amountElTable; ++i)
    {
        isNeedRec = 1;
        rec = &table[i];
        if (strcmp(cl.name, DEFAULT_INIT_STRING) != 0)
            if (cl.nc == cl.ABSOLUTE)
                isNeedRec = (_stricmp(cl.name, rec->gmst.name) == 0);
            else
                isNeedRec = (strstr(rec->gmst.name, cl.name) != NULL);

        if (cl.mem != DEFAULT_INIT_INT && isNeedRec)
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

        if (isNeedRec) {
            outRecord(rec);
            printf("\n");
        }
    }
}

void outputTable()
{
    printf("\n  Номер\t\t Имя(%d) \t Память(%d) \t Возраст(%d) \t Графика(%d) \t Игроки(%d) \t Оценка(%d)\n",
        NAME, MEM, AGER, GRAPHIC, PLAYERS, AVERATE);

    for (int i = 0; i < amountElTable; i++)
    {
        outRecord(&table[i]);
        printf("\n");
    }

}

void event_exit_program()
{
    printf("Спасибо, что использовали наше ПО. \nДо новых встреч!");
    exit(0);
}

void intro()
{
    printf("\n\n\t\t\tДобро пожаловать!");
    printf("\n\t\t\tразработано им -> https://github.com/eastpriSs");
    _getch();
}

void event_ivalid_command()
{
    printf("\nНеверная команда\n");
}

// START EVENT
void start()
{
    int input = 0;

    printf("\nВведите номер блока:");
    printf("\n1) Добавление/Удаление");
    printf("\n2) Редактирование");
    printf("\n3) Уникальный запрос");
    printf("\n4) Выход");
    printf("\nномер блока>");

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


int main()
{
    setlocale(LC_ALL, "Russian");
    intro();
    clearConsole();
    addToEventWay(start);
    while (1) {
        outputTable();
        startcEventWay(); // запускаем старт
        startcEventWay(); // ивент, добавленный со старта
        printf("\nждёт любую кнопку...\n");
        _getch();
        backEventWay();
        clearConsole();
    }
}
