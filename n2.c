#include <stdio.h>
#include <math.h>
#include <conio.h>

// Объявления, прототипы
double arccosec(double x, double e);
double fy(double x, double e);
void outxye(double x, double y, double e);
//

double callFunc(double x, double e, double (*f)(double, double)){
    return f(x, e);
}

int main()
{
    double (*parccosec) (double, double);
    double (*pfy) (double, double);

    double x, y, e;
    int n;
    do{
        // Ввод данных
        printf("\nEnter x=");
        scanf("%lf", &x);
        printf("\nEnter e=");
        scanf("%lf", &e);
        do{
            printf("\n1) arccosec(x)");
            printf("\n2) y(x)");
            printf("\nEnter n, n = (1 or 2) =");
            scanf("%d", &n);
        }while(n < 1 || n > 2);
        
        // Вызов функции
        switch (n)
        {
        case 1: y = callFunc(x,e,arccosec);
            break;
        case 2: y = callFunc(x,e,fy);
            break;

        default:
            break;
        }

        // Вывод
        printf("\nResults:");
        outxye(x,y,e);

        printf("\nFor exit press ESC..\n");
    }while(getch() != 27);
}


void outxye(double x, double y, double e)
{
    printf("\nx = %2.10lf, y = %2.10lf, e = %2.10lf", x,y,e);
}

double arccosec(double x, double e)
{
    double sum = 0;
    double x_pow = x; // степень х
    double sqr_x = x*x;
    double zn_f = 1; // множетель знаменателя 2 * 4 * 6..
    double zn = x, chis = 1.0;
    double sl = chis/zn; // очередное слагаемое
    for (int n = 1; fabs(sl) > e; ++n)
    {
        sum += sl;
        zn_f *= 2*n;
        chis *= 2*n - 1;
        x_pow *= sqr_x;
        zn = zn_f * (2*n + 1) * x_pow;
        sl = chis/zn;
    }
    return sum;
    
}

double fy(double x, double e)
{
    double sum = 0;
    double x_pow = x;
    double sqr_x = x*x;
    int sign = 1;
    int n = 1;
    double sl;
    double chis, zn;
    do
    {
        x_pow *= sqr_x;
        chis = x_pow;
        zn = 4*n*n - 1;
        sl = sign*chis/zn;
        sign *= -1;
        n += 1;
    } while(fabs(sl) > e);
    return sum;
}