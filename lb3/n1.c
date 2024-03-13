#include <stdio.h>
#include <string.h>

#define MAX_INPUT_BUFFER 1024
#define MAX_FIO_BUFFER 255
#define MAX_CHILD_COUNT 15
#define MAX_EMPL_AMOUNT 100


int countEmpl = 0;

struct employee
// Предоставляет информацию о семье
// сотрудника
{
    char fio[MAX_FIO_BUFFER];
    unsigned ageChild[MAX_CHILD_COUNT];
    unsigned amountChild;

} table[MAX_EMPL_AMOUNT];


void printEmpl(struct employee e)
// выводит информацию о конкретном сотруднике
{
    printf(" %20s ", e.fio);
    printf(" %12d ", e.amountChild);
    printf(" \t{ ");
    for (size_t i = 0; i < e.amountChild; ++i)
        printf(" %2d ", e.ageChild[i]);
    printf(" } ");
}

void inputTable()
// Ввод данных
{
    do{
        printf("\nEnter amount of employees( < %d): ", MAX_EMPL_AMOUNT);
        scanf("%d", &countEmpl); 
    } while(countEmpl > MAX_EMPL_AMOUNT || countEmpl < 0);

    for (size_t i = 0; i < countEmpl; ++i)
    {
        printf("\n - Employee #%d\n", i+1);
        
        while(getchar() != '\n');
        printf("fio:"); 
        gets(table[i].fio);

        printf("amount childs:");
        int am = 0;
        do{
            scanf("%d", &am);
        }while(am < 0 || am > MAX_CHILD_COUNT);
        table[i].amountChild = am;

        printf("Enter age of childs with spaces:");
        for (size_t j = 0; j < table[i].amountChild; ++j)
        {
            scanf("%d", &table[i].ageChild[j]);
        }
    }
       
}

void printTable()
// Вывод полной таблицы
{
    printf("\n<Name>\t\t\t<Am.childs> \t <Ages of childs>\n");
    for (size_t i = 0; i < countEmpl; ++i)
    {
        printEmpl(table[i]);
        printf("\n");
    }
    
}

void sortTable()
// Сортирует таблицу по именам в алфавитном порядке
{
    for (int i = 0; i < countEmpl - 1; ++i)
    {
        for (int j = i + 1; j < countEmpl; ++j)
        {
            if (strcmp(table[i].fio, table[j].fio) > 0 )
            {
                struct employee temp = table[i];
                table[i] = table[j];
                table[j] = temp; 
            }
        }
    }
    
}

int isEmpHaveThreeAdultChild( struct employee e )
// Проверяет есть ли у сотрудника 3 или более несовершеннолетних детей
{
    int amount = 0;
    for (size_t i = 0; i < e.amountChild; ++i)
        if ( e.ageChild[i] < 18 ) amount += 1;

    return amount >= 3;
}

void printNeededEmpl()
// Выводит нужных сотрудников,
// у которых 3 или более несовершеннолетних детей
{
    for (size_t i = 0; i < countEmpl; i++)
    {
        if (isEmpHaveThreeAdultChild(table[i]))
            printEmpl(table[i]);
        printf("\n");
    }
    
}

int main(){
    inputTable();
    sortTable();
    printTable();
    printf("\n * Needed employees:\n");
    printNeededEmpl();
    printf("\n");
}