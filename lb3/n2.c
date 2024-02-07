#include <stdio.h>
#include <string.h>

#define MAX_FIO_CHARS 255
#define MAX_EMPL_AMOUNT 20

int countEmpl = 0; // Количестов сотрудников
int countFEmpl = 0; // Количестов семейных сотрудников

enum famStatus {INREL = 0, BRKREL = 1, NVEREL = 2};
struct employee
{
    char fio[MAX_FIO_CHARS];
    enum famStatus fs;

    union famStat
    {
        char fioPar[MAX_FIO_CHARS];
        int yearb; 
    } famst;

// Основная таблица и отдельная таблица для семьянинов
} table[MAX_EMPL_AMOUNT], fmlmansTable[MAX_EMPL_AMOUNT];


void printEmpl(struct employee e)
{
    printf("%15s \t%d\t", e.fio, e.fs);
    switch (e.fs)
    {

    case INREL:
        printf(" %15s", e.famst.fioPar);
        break;

    case BRKREL:
        printf(" %10d", e.famst.yearb);
        break;
    
    case NVEREL:
        printf(" - ");
        break;  
    
    default:
        break;
    }
}

void outTable(struct employee * t, int am)
{
    printf("\n -*- Code 0 - in a relationship. \nCode 1 - in divorce. \nCode 0 - never be in a relationship. -*- \n");
    printf("\n<Name>\t\t\t<FSTATUS>\t<FINFO>\n");
    for (size_t i = 0; i < am; ++i)
    {
        printEmpl(t[i]);
        printf("\n");
    }
        
}


void inputTable()
// Ввод данных
{
    do
    {
        printf("\nEnter amount of employees( < %d): ", MAX_EMPL_AMOUNT);
        scanf("%d", &countEmpl); 
    } while (countEmpl > MAX_EMPL_AMOUNT);
    
    while(getchar() != '\n');

    for (size_t i = 0; i < countEmpl; ++i)
    {
        printf("\n - Employee #%d\n", i+1);
        
        printf("fio:"); 
        gets(table[i].fio);

        do
        {
            printf("Family status (0 - in rel, 1 - break, 2 - never):");
            scanf("%d", &table[i].fs);
        } while (table[i].fs > 2 || table[i].fs < 0);
        

        while(getchar() != '\n');
        switch (table[i].fs)
        {

        case INREL:
            printf("Enter fio partner:");
            gets(table[i].famst.fioPar);
            break;
        
        case BRKREL:
            printf("Enter date partner:");
            scanf("%d", &table[i].famst.yearb);
            while(getchar() != '\n');
            break;

        case NVEREL: break;
        default:
            break;
        
        }
    }
       
}

void fillFmlmansTable()
// Заполняет таблицу фамилий семьянинов
{
    size_t i = 0, k = 0;
    for (; i < countEmpl; ++i)
    {
        if (table[i].fs == INREL) 
            fmlmansTable[k++] = table[i];
    }
    countFEmpl = k;
}

void sortTableByFio(struct employee * t, int am)
// Сортирует таблицу по имененам
{
    for (int i = 0; i < am - 1; ++i)
    {
        for (int j = i + 1; j < am; ++j)
        {
            if (strcmp(t[i].fio, t[j].fio) > 0 )
            {
                struct employee temp = t[i];
                t[i] = t[j];
                t[j] = temp; 
            }
        }
    }
}

int main()
{
    inputTable();
    printf("\nTable with all employees.\n");
    outTable(table, countEmpl);
    
    fillFmlmansTable();
    sortTableByFio(fmlmansTable, countFEmpl);
    printf("\nTable with family mans.\n");
    outTable(fmlmansTable, countFEmpl);    
}