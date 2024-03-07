#include <stdio.h>
#include <stdlib.h>
#include <ctime>

#define AMOUNT_NUMBERS 20 // кратно 20

void fillOriginFile(FILE * pf)
{
    srand(time(NULL));
    int posNumber = rand() % 100 + 1;
    int negNumber = -1 * (rand() % 100 + 1);
    for (int i = 0; i <= (int)(AMOUNT_NUMBERS / 20) ; ++i)
    {   
        for (int i_p = 0; i_p < 5; ++i_p, 
            posNumber = rand() % 100 + 1)
            fprintf(pf, "%d ", posNumber);
        
        for (int i_n = 0; i_n < 5; ++i_n, 
            negNumber = -1 * (rand() % 100 + 1) )
            fprintf(pf, "%d ", negNumber);
    }
}

void outputDataFile(FILE * pf)
{
    int numberfFile;
    for (int i = 0; i < AMOUNT_NUMBERS; ++i)
    {
        fscanf(pf, "%d", &numberfFile);
        printf("%d ", numberfFile);
    }
    
}

void sortAndWriteNumberfFile(int in [AMOUNT_NUMBERS], FILE * from)
{
    int fromfNumber;
    int id_pos = 0, id_neg = AMOUNT_NUMBERS / 2;
    
    for (int i = 0; i < AMOUNT_NUMBERS; ++i) {
        fscanf(from, "%d", &fromfNumber);
        if (fromfNumber > 0)
            in[id_pos++] = fromfNumber;
        else
            in[id_neg++] = fromfNumber; 
    }
}

void fillResultFile(FILE * in, FILE * from)
{
    int fromfData [AMOUNT_NUMBERS] = {0};
    sortAndWriteNumberfFile(fromfData, from);

    int i_p = 0, i_n = AMOUNT_NUMBERS/2;
    for (int i = 2; i <= (int)(AMOUNT_NUMBERS / 2); i += 2)
    {
        for (; i_p < i; ++i_p)
            fprintf(in, "%d ", fromfData[i_p]); 

        for (; i_n < AMOUNT_NUMBERS/2 + i; ++i_n)
            fprintf(in, "%d ", fromfData[i_n]); 

    }
    
}

int main()
{
    FILE * ptrFile     = fopen("origin.txt", "w");
    FILE * ptrOutFile  = fopen("result.txt", "w");
    
    printf("\nOrigin file:");
    fillOriginFile(ptrFile);
    fclose(ptrFile); // Записывем в файл
    ptrFile = fopen("origin.txt", "r");
    outputDataFile(ptrFile);
    
    printf("\n");
    fseek(ptrFile, 0, SEEK_SET); // сброс указателя

    printf("\nResult file:");    
    fillResultFile(ptrOutFile, ptrFile);
    fclose(ptrOutFile); // Записывем в файл
    ptrOutFile = fopen("result.txt", "r");
    outputDataFile(ptrOutFile);
    
    printf("\n");
}