#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

double func(double x)
{
        return ( (2*x*x*x + x*x - 15*x -3) / (x*x*x - x + 2) ) * sin(M_PI/180);
        //return x*x*x;
}


void integral(const double a, const double b, const double h, double *res)
{
        int i, n  = (int)((b - a) * h);
        double sum = 0.0, x;
        //omp_set_nested(true);
        #pragma omp parallel for private (x) reduction(+: sum) 
        for( i = 0; i < n; i++)
        {
                x = a + i / h;
                sum += func(x) / h;
        }
        *res = sum;
}


double experiment(double *res)
{
        double stime, ftime;
        double a = 0.0 ;
        double b = 100.0;
        double h = 1000000000; //10
        stime = omp_get_wtime( );
        integral(a, b, h, res);
        ftime = omp_get_wtime( );
        return (ftime - stime);
}

int main ()
{
        double time, res;
        time = experiment(&res);
        printf("Интеграл равен: %lf \n", res);
        printf( "Время выполнения: %lf \n", time*1000000);
        return 0;
}
