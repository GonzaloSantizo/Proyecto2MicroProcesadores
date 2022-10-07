/**
 * UNIVERSIDAD DEL VALLE DE GUATEMALA
 * 21504 - Gonzalo Santizo
 * Programacion de Microprocesadores
 * Seccion: 10
 * Proyecto 2
 */


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <iostream>
#include <math.h>
using namespace std;

//Primero iniciamos creando las variables 
int n;
double sumando = 0;

//Luego se define la subrutina y su funcionamiento
void *Sumatoria(void *numeros){
    int number = (int)numeros;
    double* resultado = new double;
    *resultado = 3/(pow(2,number));
    return resultado;
}
//Iniciamos con el main 
int main(){
    cout << "\n**************************************************************" <<endl;
    cout << "Bienvenidos al programa 2 calculadora de sumatorias del proyecto 2 es un gusto atenderte" <<endl;
    cout << "****************************************************************\n"<<endl;
    cout << "Por favor, Ingresa el valor de n que deceas calcular: ->";
    cin >> n;
    cout << endl;
    cout << "Este fue el valor de n que agregaste->: " << n << endl;
    
    //Aqui es para usar todo el proceso pthread y de los attr de la subrutina
    int nums;
    long i;
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    //Se empieza creando el puntero para la base del resultado ingresado de la subrutina
    void *suma;
    //Aqui se inicia la sumatoria y la ira almacenando
    for(int i = 0; i<=n ;i++){
        nums = pthread_create(&tid, &attr, Sumatoria, (void *)i);
        nums = pthread_join(tid, &suma);
        sumando += (*(double*) suma);
    }
    
    cout << "******************************************************"<<endl;
    cout << "Este es el resultado de la sumatoria->: " << sumando << endl;
    cout << "******************************************************\n"<<endl;
    cout << "Fue un gusto tenerte conmigo, Regresa pronto! <3 \n"<<endl;
    pthread_exit(NULL);
    return 0;
}

