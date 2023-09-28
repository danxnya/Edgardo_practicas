#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>

#define ARR 500000

void pArray(int arr[], int n);
void heapSort(int arr[], int n);
void heapify(int arr[], int n, int i);
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
    heapSort(arr, n);
    uswtime(&utime1, &stime1, &wtime1);

    printf("Array ordenado: ");
    pArray(arr, n);

    FILE *times = fopen("htimes.txt", "w");
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

void heapSort(int arr[], int n) {
    int i, temp;

    for (i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (i = n - 1; i >= 0; i--) {
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int temp;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}

void uswtime(double *usertime, double *systime, double *walltime) {
    double mega = 1.0e-6;
    struct rusage buffer;
    struct timeval tp;
    struct timezone tzp;

    gettimeofday(&tp, &tzp);
    *walltime = (double) (tp.tv_sec + tp.tv_usec * mega);

    getrusage(RUSAGE_SELF, &buffer);
    *usertime = (double) (buffer.ru_utime.tv_sec + buffer.ru_utime.tv_usec * mega);
    *systime = (double) (buffer.ru_stime.tv_sec + buffer.ru_stime.tv_usec * mega);
}

