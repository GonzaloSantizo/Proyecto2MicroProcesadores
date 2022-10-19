
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
#include <algorithm>
#include <chrono>
#include<vector>
using namespace std;
using namespace std::chrono;

void *SeriesValue(void *Value) //function that will fiund the value of a specific "n" number in a series
{
    int args = *(int *)Value;
    *(double *)Value = (1.00000) / ((double)args * ((double)args + 1)); // 1 / (n(n+1))
    return Value; // returns value
}


void *SeriesValue(void *Value);
 
int main()
{
 
    vector<int> values(10000); //creates vector to measure

    // Generate Random values
    auto f = []() -> int { return rand() % 10000; };
 
    // Fill up the vector
    generate(values.begin(), values.end(), f);

 
    // Get starting timepoint
    auto start = high_resolution_clock::now();

    

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
    double sum = 0; // variable to save value of series

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

    // Call the function, here sort()
    sort(values.begin(), values.end());
 
    // Get ending timepoint
    auto stop = high_resolution_clock::now();
 
    // Get duration. Substart timepoints to
    // get duration. To cast it to proper unit
    // use duration cast method
    auto duration = duration_cast<microseconds>(stop - start);
 
    cout << "Time taken by function: " //print total time since the begginning of the function
         << duration.count() << " microseconds" << endl;
 
    return 0;
}