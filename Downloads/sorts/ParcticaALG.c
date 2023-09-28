#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RAND 1000

void pArray(int arr[], int n);
void shellSort(int arr[], int n, double *num_operations);
void bubbleSort(int arr[], int n, double *num_operations);
void selectionSort(int arr[], int n, double *num_operations);
void insertionSort(int arr[], int n, double *num_operations);

int main(){
int n, metodo, caso;
clock_t begin, end;
double time_spent;

printf("tamaño del array: ");
scanf("%d", &n);
int arr[n];

printf("Caso:\n [1] Peor caso\n [2] Caso medio\n [3] Mejor caso\n");
scanf("%d", &caso);
switch (caso){
case 1:
    printf("Peor caso\n");
        for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
    break;
case 2:
    printf("Caso medio\n");
        srand(time(NULL));
    for(int i = 0; i < n; i++){
        arr[i] = rand() % RAND;
    }
    break;
case 3:
    printf("Mejor caso\n");
        for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
    break;
default:
    printf("Error\n");
    break;
}




printf("Array original: ");
    pArray(arr, n);
do {
//menu para seleccionar el metodo de ordenamiento
printf("Metodo de ordenamiento:\n [1] Salir\n [2] Bubble Sort\n [3] Shell Sort\n [4] Selection Sort\n [5] Insertion Sort\n]");
scanf("%d", &metodo);
switch (metodo){
    case 1:
    printf("Saliendo...\n");
    break;

case 2:
    printf("Bubble Sort\n");
    double bubble_num_operations = 0;
    begin = clock();
    bubbleSort(arr, n, &bubble_num_operations);
    end = clock();
    printf("Array ordenado: ");
    pArray(arr, n);
    printf("Numero de operaciones: %f\n", bubble_num_operations);
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecucion: %f\n", time_spent);
    break;

case 3:
    printf("Shell Sort\n");
    double shell_num_operations = 0;
    begin = clock();
    shellSort(arr, n, &shell_num_operations);
    end = clock();
    printf("Array ordenado: ");
    pArray(arr, n);
    printf("Numero de operaciones: %f\n", shell_num_operations);
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecucion: %f\n", time_spent);
    break;

case 4:
    printf("Selection Sort\n");
    double selection_num_operations = 0;
    begin = clock();
    selectionSort(arr, n, &selection_num_operations);
    end = clock();
    printf("Array ordenado: ");
    pArray(arr, n);
    printf("Numero de operaciones: %f\n", selection_num_operations);
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecucion: %f\n", time_spent);
    break;

case 5:
    printf("Insertion Sort\n");
    double insertion_num_operations = 0;
    begin = clock();
    insertionSort(arr, n, &insertion_num_operations);
    end = clock();
    printf("Array ordenado: ");
    pArray(arr, n);
    printf("Numero de operaciones: %f\n", insertion_num_operations);
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecucion: %f\n", time_spent);
    break;

    default:
    printf("Opcion no valida\n");
    break;
}
} while (metodo != 1);


return 0;
}

//funcion para imprimir el array
void pArray(int arr[], int n){
    for(int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void shellSort(int arr[], int n, double *num_operations) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                (*num_operations)++;  // Incrementar el contador en cada comparación
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}


void bubbleSort(int arr[], int n, double *num_operations) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            (*num_operations)++;  // Incrementar el contador en cada comparación
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void selectionSort(int arr[], int n, double *num_operations) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            (*num_operations)++;  // Incrementar el contador en cada comparación
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        int temp = arr[min];
        arr[min] = arr[i];
        arr[i] = temp;
    }
}

void insertionSort(int arr[], int n, double *num_operations) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;        															
        (*num_operations)++;

        																// Mover los elementos del arreglo que son mayores que key
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;

            (*num_operations)++;
        }
        arr[j + 1] = key;
        (*num_operations)++;
    }
}