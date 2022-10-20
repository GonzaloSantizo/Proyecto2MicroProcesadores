
/*---------------------------------------------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* FACULTAD DE INGENIERÍA
* DEPARTAMENTO DE CIENCIA DE LA COMPUTACIÓN
*
* Curso:       CC3086 - Programación de microprocesadores     Ciclo II - 2022
* Descripción: Encontrar el valor de convergencia de una serie
* Creador Gonzalo Santizo - 21504, Diego Vásquez - 211628.
------------------------------------------------------------------------------*/
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include <algorithm>
#include <chrono>
#include<vector>
pthread_mutex_t lock; //Definimos el mutex
sem_t sem1; //Definimos el semáforo
using namespace std;
using namespace std::chrono;

void *SeriesValue(void *Value) //function that will find the value of a specific "n" number in a series
{
    int args = *(int *)Value;
    pthread_mutex_lock(&lock); //Hacemos el lock del mutex, antes de la sección crítica del código.
    *(double *)Value = (1.00000) / ((double)args * ((double)args + 1)); // 1 / (n(n+1))
    pthread_mutex_unlock(&lock); //Hacemos el unlock después de la sección crítica del código.
    return Value; // returns value
}

void *SeriesSum(void *Value) //function that will find the value of a specific "n" number in a series
{
    int args = *(int *)Value;
    pthread_mutex_lock(&lock); //Hacemos el lock del mutex, antes de la sección crítica del código.
    *(double *)Value = ((double)args * ((double)args + 1)) / (2.00000); // (n(n+1)/2)
    pthread_mutex_unlock(&lock); //Hacemos el unlock después de la sección crítica del código.
    return Value; // returns value
}


void *SeriesCube(void *Value) //function that will find the value of a specific "n" number in a series
{
    int args = *(int *)Value;
    pthread_mutex_lock(&lock); //Hacemos el lock del mutex, antes de la sección crítica del código.
    *(double *)Value = ((double)args * (double)args  * ((double)args + 1) * (double)args + 1) / (4.00000); // (n*n(n+1)(n+1)/4)
    pthread_mutex_unlock(&lock); //Hacemos el unlock después de la sección crítica del código.
    return Value; // returns value
}

void *SeriesInverseSquare(void *Value) //function that will find the value of a specific "n" number in a series
{
    int args = *(int *)Value;
    pthread_mutex_lock(&lock); //Hacemos el lock del mutex, antes de la sección crítica del código.
    *(double *)Value = (1.00000) / ((double)args * (double)args); // 1/n*n
    pthread_mutex_unlock(&lock); //Hacemos el unlock después de la sección crítica del código.
    return Value; // returns value
}

void *SeriesValue(void *Value);
void *SeriesSum(void *Value);
void *SeriesCube(void *Value);
void *SeriesInverseSquare(void *Value);
 
int main()
{
    pthread_mutex_init(&lock, NULL); //Inicializamos el mutex
    vector<int> values(10000); //creates vector to measure

    // Generate Random values
    auto f = []() -> int { return rand() % 10000; };
 
    // Fill up the vector
    generate(values.begin(), values.end(), f);

    int maxValue; //variable for user input
    printf("enter max value of the series: ");
    scanf("%d", &maxValue); // this records user input
    pthread_t threads[maxValue]; // creates n amount of threads
    if (pthread_mutex_init(&lock, NULL) != 0) { perror("Error en el mutex"); } //Verificamos si esta desbloqueado el mutex.

//=============================================================================================
//                                     Primera Serie
//=============================================================================================
    sem_init(&sem1, 0,1);

    // Get starting timepoint
    auto start = high_resolution_clock::now();

    int i;

    sem_wait(&sem1);
    for (i = 0; i < maxValue; i++)
    {
        int *parameter = (int *)malloc(sizeof(int)); //using malloc to ensure proper function
        *parameter = i + 1;
        if (pthread_create(&threads[i], NULL, &SeriesValue, parameter) != 0)
        {
            perror("Failed creating the threads");
        }
    }
    sem_post(&sem1);

    double *ConvValue;
    double sum = 0; // variable to save value of series

    sem_wait(&sem1);
    for (i = 0; i < maxValue; i++) // adds all threads together
    {
        if (pthread_join(threads[i], (void **)&ConvValue))
        {
            perror("Failing to join the threads to the main thread");
        }
        printf("\nEl Thread result %d, es %lf:", i + 1, *ConvValue);
        sum += *ConvValue;
        }
    sem_post(&sem1);
    free(ConvValue);
    printf("\nThe final value of the series is: %lf\n", sum); //prints final result

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

//=============================================================================================
//                                    Segunda Serie
//=============================================================================================
    
    // Get starting timepoint
    start = high_resolution_clock::now();

    sem_wait(&sem1);
    for (i = 0; i < maxValue; i++)
    {
        int *parameter = (int *)malloc(sizeof(int)); //using malloc to ensure proper function
        *parameter = i + 1;
        if (pthread_create(&threads[i], NULL, &SeriesSum, parameter) != 0)
        {
            perror("Failed creating the threads");
        }
    }
    sem_post(&sem1);

    sem_wait(&sem1);
    for (i = 0; i < maxValue; i++) // adds all threads together
    {
        if (pthread_join(threads[i], (void **)&ConvValue))
        {
            perror("Failing to join the threads to the main thread");
        }
        printf("\nEl Thread result %d, es %lf:", i + 1, *ConvValue);
        sum += *ConvValue;
        }
    sem_post(&sem1);
    free(ConvValue);
    printf("\nThe final value of the series is: %lf\n", sum); //prints final result

    // Call the function, here sort()
    sort(values.begin(), values.end());
 
    // Get ending timepoint
    stop = high_resolution_clock::now();
    // Get duration. Substart timepoints to
    // get duration. To cast it to proper unit
    // use duration cast method
    duration = duration_cast<microseconds>(stop - start);

    cout << "Time taken by function: " //print total time since the begginning of the function
         << duration.count() << " microseconds" << endl;


//=============================================================================================
//                                      Tercera Serie
//=============================================================================================

    // Get starting timepoint
    start = high_resolution_clock::now();

    sem_wait(&sem1);
    for (i = 0; i < maxValue; i++)
    {
        int *parameter = (int *)malloc(sizeof(int)); //using malloc to ensure proper function
        *parameter = i + 1;
        if (pthread_create(&threads[i], NULL, &SeriesCube, parameter) != 0)
        {
            perror("Failed creating the threads");
        }
    }
    sem_post(&sem1);

    sem_wait(&sem1);
    for (i = 0; i < maxValue; i++) // adds all threads together
    {
        if (pthread_join(threads[i], (void **)&ConvValue))
        {
            perror("Failing to join the threads to the main thread");
        }
        printf("\nEl Thread result %d, es %lf:", i + 1, *ConvValue);
        sum += *ConvValue;
        }
    sem_post(&sem1);
    free(ConvValue);
    printf("\nThe final value of the series is: %lf\n", sum); //prints final result

    // Call the function, here sort()
    sort(values.begin(), values.end());
 
    // Get ending timepoint
    stop = high_resolution_clock::now();
    // Get duration. Substart timepoints to
    // get duration. To cast it to proper unit
    // use duration cast method
    duration = duration_cast<microseconds>(stop - start);

    cout << "Time taken by function: " //print total time since the begginning of the function
         << duration.count() << " microseconds" << endl;

//=============================================================================================
//                                      Cuarta Serie
//=============================================================================================

    // Get starting timepoint
    start = high_resolution_clock::now();

    sem_wait(&sem1);
    for (i = 0; i < maxValue; i++)
    {
        int *parameter = (int *)malloc(sizeof(int)); //using malloc to ensure proper function
        *parameter = i + 1;
        if (pthread_create(&threads[i], NULL, &SeriesInverseSquare, parameter) != 0)
        {
            perror("Failed creating the threads");
        }
    }
    sem_post(&sem1);

    sem_wait(&sem1);
    for (i = 0; i < maxValue; i++) // adds all threads together
    {
        if (pthread_join(threads[i], (void **)&ConvValue))
        {
            perror("Failing to join the threads to the main thread");
        }
        printf("\nEl Thread result %d, es %lf:", i + 1, *ConvValue);
        sum += *ConvValue;
        }
    sem_post(&sem1);
    free(ConvValue);
    printf("\nThe final value of the series is: %lf\n", sum); //prints final result

    // Call the function, here sort()
    sort(values.begin(), values.end());
 
    // Get ending timepoint
    stop = high_resolution_clock::now();
    // Get duration. Substart timepoints to
    // get duration. To cast it to proper unit
    // use duration cast method
    duration = duration_cast<microseconds>(stop - start);

    cout << "Time taken by function: " //print total time since the begginning of the function
         << duration.count() << " microseconds" << endl;

    pthread_mutex_destroy(&lock); //Destruimos el mutex.
    return 0;
}