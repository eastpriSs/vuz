#include <stdio.h>
#include <conio.h>

#define MAX_M 20
#define MAX_N 20

void smMtrx(int a[MAX_N][MAX_M], 
            int n,  int m, int * sm)
{
    int el;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            el = a[i][j]; 
            if (el >= -5 && el <= 5)
                *sm += el;
        }
    }
}

void mltMtrx(int a[MAX_N][MAX_M], 
            int n,  int m, int * mlt)
{
    int el;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            el = a[i][j]; 
            if (el >= -5 && el <= 5)
                *mlt *= el;
        }
    }
}

void procMtrx(int a[MAX_N][MAX_M], int n,  
                int m, int *sm, int *mlt)
{
    smMtrx(a, n, m, sm); // сумма 
    mltMtrx(a, n, m, mlt); // произведение
    int el;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            el = a[i][j]; 
            if (el >= -5 && el <= 5)
                a[i][j] = 0;
        }
    }
}

void inputMtrx(int a[MAX_N][MAX_M], int n,  int m)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            scanf("%d", &a[i][j]);
        }
    }
    
}

void outMtrx(int a[MAX_N][MAX_M], int n,  int m)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            printf(" %3d", a[i][j]);
        }
        printf("\n");
    }
    
}

int main()
{
    int n,m;
    int a[MAX_M][MAX_N];
    int sm, mult;

    do
    {
        sm = 0;
        mult = 1;
        do{
            printf("Enter n, n>0 and n<%d:", MAX_N);
            scanf("%d", &n);
        }while(n > MAX_N || n < 0);

        do{
            printf("Enter m, m>0 and m<%d:", MAX_M);
            scanf("%d", &m);
        }while(m > MAX_M || m < 0);

        // Ввод, вывод
        printf("\nEnter matrix:\n");
        inputMtrx(a, n, m);
        printf("\nInput:\n");
        outMtrx(a, n, m);
        // Обработка
        procMtrx(a, n, m, &sm, &mult);
        // Результаты
        printf("\nResults:\n");
        outMtrx(a, n, m);
        printf("\nsum = %d, mult = %d", sm, mult);
    
        printf("\nFor exit press ESC..\n");
    } while(_getch() != 27);
}