// Estudiante: Cifuentes González Elian
// Fecha de entrega: 28/07/2024
// Curso: 1ro de TI

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>

using namespace std;

//Función que imprime un vector
void ImprimeVector(int x[], int total) {
    for(int k = 0; k < total; k++) {
        cout << endl << (k + 1) << ": " << x[k];
    }
}

//Función que llena un vector con números aleatorios
void VectorNumAleatorio(int vector1[], int vector2[], int vector3[], int vector4[], int vector5[], int total) {
    int lim_inf = 1;
    int lim_sup = 10000;
    for(int k = 0; k < total; k++) {
        int numero = lim_inf + rand() % ((lim_sup + 1) - lim_inf);
        vector1[k] = numero;
        vector2[k] = numero;
        vector3[k] = numero;
        vector4[k] = numero;
        vector5[k] = numero;
    }
}

//Función que intercambia dos números
void intercambiar(int& num1, int& num2) {
    int aux = num1;
    num1 = num2;
    num2 = aux;
}

//Ordenamiento Secuencial
void ordenSecuencial(int vector[], int total)
{
    for (int i = 0; i < total; i++)
    {
        for (int j = i + 1; j < total; j++)
    {
        if (vector [i]>vector [j])
        intercambiar (vector [i], vector [j]);
    }
    }
}

//Ordenamiento Burbuja Mejorado
void burbujaMejorado(int arreglo[], int tamano) {
    int comparaciones = tamano;
    bool termino = false;
    for (int i = 0; i < (tamano - 1); i++) {
        if (termino)
            break;
        termino = true;
        for (int j = 0; j < comparaciones - 1; j++)
            if (arreglo[j] > arreglo[j + 1]) {
                intercambiar(arreglo[j], arreglo[j + 1]);
                termino = false;
            }
        comparaciones--;
    }
}

//Ordenamiento Shell
void ordenShell(int a[], int n) {
    int ints, i, aux;
    bool band;
    ints = n;
    while (ints > 1) {
        ints = ints / 2;
        band = true;
        while (band == true) {
            band = false;
            i = 0;
            while ((i + ints) < n) {
                if (a[i] > a[i + ints]) {
                    aux = a[i];
                    a[i] = a[i + ints];
                    a[i + ints] = aux;
                    band = true;
                }
                i++;
            }
        }
    }
}
//Ordenamiento Shell Optimizado
void ordenShellOptimizado(int a[], int n) {
    int i, j, inc;
    int temp;
    for (inc = 1; inc < n; inc = inc * 3 + 1);
    while (inc > 0) {
        for (i = inc; i < n; i++) {
            j = i;
            temp = a[i];
            while ((j >= inc) && (a[j - inc] > temp)) {
                a[j] = a[j - inc];
                j = j - inc;
            }
            a[j] = temp;
        }
        inc = inc / 2;
    }
}

//Ordenamiento Quick Sort
void OrdenamientoQuicksort(int a[], int primerValor, int ultimoValor) {
    int central, i, j, pivote;
    central = (primerValor + ultimoValor) / 2;
    pivote = a[central];
    i = primerValor;
    j = ultimoValor;
    do {
        while (a[i] < pivote) i++;
        while (a[j] > pivote) j--;
        if (i <= j) {
            int temporal;
            temporal = a[i];
            a[i] = a[j];
            a[j] = temporal;
            i++;
            j--;
        }
    } while (i <= j);
    if (primerValor < j)
        OrdenamientoQuicksort(a, primerValor, j);
    if (i < ultimoValor)
        OrdenamientoQuicksort(a, i, ultimoValor);
}

//Función que calcula el tiempo de ejecución
double performancecounter_diff(LARGE_INTEGER a, LARGE_INTEGER b) {
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    return (double)(a.QuadPart - b.QuadPart) / (double)freq.QuadPart;
}

int main() {
    srand(time(NULL));
    const int MAX = 60000;
    int vectorsecuencial[MAX];
    int vectorburbuja[MAX];
    int vectorshell[MAX];
    int vectorshelloptimizado[MAX];
    int vectorquick[MAX];

    LARGE_INTEGER t_ini, t_fin;
    double secs, secsburbuja, secsshell, secsshelloptimizado, secsquick;

    VectorNumAleatorio(vectorsecuencial, vectorburbuja, vectorshell, vectorshelloptimizado, vectorquick, MAX);

    //Orden Secuencial
    QueryPerformanceCounter(&t_ini);
    ordenSecuencial(vectorsecuencial, MAX);
    QueryPerformanceCounter(&t_fin);
    secs = performancecounter_diff(t_fin, t_ini);
    
    //Burbuja Mejorado
    QueryPerformanceCounter(&t_ini);
    burbujaMejorado(vectorburbuja, MAX);
    QueryPerformanceCounter(&t_fin);
    secsburbuja = performancecounter_diff(t_fin, t_ini);

    //Orden Shell
    QueryPerformanceCounter(&t_ini);
    ordenShell(vectorshell, MAX);
    QueryPerformanceCounter(&t_fin);
    secsshell = performancecounter_diff(t_fin, t_ini);

    //Orden Shell Optimizado
    QueryPerformanceCounter(&t_ini);
    ordenShellOptimizado(vectorshelloptimizado, MAX);
    QueryPerformanceCounter(&t_fin);
    secsshelloptimizado = performancecounter_diff(t_fin, t_ini);

    //Orden Quick Sort
    QueryPerformanceCounter(&t_ini);
    OrdenamientoQuicksort(vectorquick, 0, MAX - 1);
    QueryPerformanceCounter(&t_fin);
    secsquick = performancecounter_diff(t_fin, t_ini);

    cout << endl << "Prueba con " << MAX << " elementos";
    cout << endl << "Tiempo de ejecución orden secuencial: " << secs * 1000.0;
    cout << endl << "Tiempo de ejecución burbuja mejorado: " << secsburbuja * 1000.0;
    cout << endl << "Tiempo de ejecución orden shell: " << secsshell * 1000.0;
    cout << endl << "Tiempo de ejecución orden shell optimizado: " << secsshelloptimizado * 1000.0;
    cout << endl << "Tiempo de ejecución quick sort: " << secsquick * 1000.0 ;

    return 0;
}
