/*---------------------------------------------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* FACULTAD DE INGENIERÍA
* DEPARTAMENTO DE CIENCIA DE LA COMPUTACIÓN
*
* Curso:       CC3086 - Programación de microprocesadores     Ciclo II - 2022
* Descripción: Encontrar el valor de convergencia de una serie
* Creador Gonzalo Santizo - 21504
------------------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <pthread.h>


void *SeriesValue(void *Value) //function that will fiund the value of a specific "n" number in a series
{
    int args = *(int *)Value;
    *(double *)Value = (1.00000) / ((double)args * ((double)args + 1)); // 1 / (n(n+1))
    return Value; // returns value
}


void *SeriesValue(void *Value);


// driver code
int main(int argc, char *argv[])
{
    int maxValue; //variable for user input
    printf("enter max value of the series: ");
    scanf("%d", &maxValue); // this records user input

    pthread_t threads[maxValue]; // creates n amount of threads
    int i;
    for (i = 0; i < maxValue; i++)
    {
        int *parameter = (int *)malloc(sizeof(int)); //using malloc to ensure proper function
        *parameter = i + 1;
        if (pthread_create(&threads[i], NULL, &SeriesValue, parameter) != 0)
        {
            perror("Failed creating the threads");
        }
    }

    double *ConvValue;
    double sum = 0;
    for (i = 0; i < maxValue; i++) // adds all threads together
    {
        if (pthread_join(threads[i], (void **)&ConvValue))
        {
            perror("Failing to join the threads to the main thread");
        }
        printf("\nEl Thread result %d, es %lf:", i + 1, *ConvValue);
        sum += *ConvValue;
        }
    free(ConvValue);
    printf("The final value of the series is: %lf\n", sum); //prints final result
    return 0;
}

