/*---------------------------------------------------------------------------
* Guatemala, agosto 26 de 2022
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* CC3086 - Programación de microprocesadores, seccion 10
* Walter Cruz
*20673
------------------------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include <math.h>
using namespace std;

int x;




int main()
{
    
    int N;
    double suma=0;
    
    cout<<"Introduzca el valor de x: ";
    cin>>x;
    cout<<"Introduzca el numero de terminos de la serie: ";
    cin>>N;
    
    int menos1=-1;
    
    for (int n=0;n <= N;n++){
        
        menos1=menos1*(-1);
        
        int expon=2*n+1;
        
        int mult=x;
        
        for(int i=1; i < expon;i++){
            mult=mult*x;
        }
        
        printf("\n mult es igual a : %X \n",mult);
        
        double result= menos1*(mult/expon);
        
        printf("\n Para el término: %X se realiza la operación %X * (%X ^ %X)/%X = %lf",n,menos1,x,expon,expon,result);
        
        suma=suma+result;
        
    }
    
    printf("\n \nLa sumatoria es igual a = %lf",suma);

    return 0;
}