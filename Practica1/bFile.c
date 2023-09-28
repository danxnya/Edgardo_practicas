#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>

#define ARR 500000

void pArray(int arr[], int n);
void bubbleSort(int arr[], int n);
void uswtime(double *usertime, double *systime, double *walltime);

int main() {
    double utime0, stime0, wtime0, utime1, stime1, wtime1;
    int n = 0;
    int arr[ARR];

    FILE *file = fopen("/home/danna/Downloads/numeros10millones.txt", "r");
    if (file == NULL) {
        printf("Error al abrir el archivo\n");
        exit(1);
    }

    while (fscanf(file, "%d", &arr[n]) == 1) {
        n++;
        if (n == ARR) {
            break;
        }
    }

    fclose(file);

    printf("Array original: ");
    pArray(arr, n);

    uswtime(&utime0, &stime0, &wtime0);
    bubbleSort(arr, n);
    uswtime(&utime1, &stime1, &wtime1);

    printf("Array ordenado: ");
    pArray(arr, n);

    FILE *times = fopen("btimes.txt", "w");
    if (times == NULL) {
        printf("Error al abrir el archivo\n");
        exit(1);
    }
    fprintf(times, "real (Tiempo total)  %.10f s\n", wtime1 - wtime0);
    fprintf(times, "user (Tiempo de procesamiento en CPU) %.10f s\n", utime1 - utime0);
    fprintf(times, "sys (Tiempo en acciones de E/S)  %.10f s\n", stime1 - stime0);
    fprintf(times, "CPU/Wall   %.10f %% \n", 100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
    fclose(times);

    return 0;
}

void pArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void bubbleSort(int arr[], int n) {
    int temp;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void uswtime(double *usertime, double *systime, double *walltime) {
    struct rusage buffer;
    struct timeval tp;
    struct timezone tzp;
    getrusage(RUSAGE_SELF, &buffer);
    gettimeofday(&tp, &tzp);
    *usertime = (double) buffer.ru_utime.tv_sec + 1.0e-6 * buffer.ru_utime.tv_usec;
    *systime = (double) buffer.ru_stime.tv_sec + 1.0e-6 * buffer.ru_stime.tv_usec;
    *walltime = (double) tp.tv_sec + 1.0e-6 * tp.tv_usec;
}
