#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include <math.h>

using namespace std;

int main(int argc, char *argv[])
{   
    float exponencial=0;
    int i=0, x, n, j;
    double factorial=1;

    cout<<"Introduzca el valor de x: ";
    cin>>x;
    cout<<"Introduzca el numero de terminos de la serie: ";
    cin>>n;

    while (i<=n)
    {
        j=1;
        factorial=1;
        while (j<=i)
        {
            factorial=factorial*j;
            j=j+1;
        }
        exponencial = exponencial+pow(x,i)/factorial;
        i=i+1;
    }
    cout<<"El valor exponencial de x es: "<<exponencial<<endl;
    return 0;
}