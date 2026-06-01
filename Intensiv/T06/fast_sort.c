#include <stdio.h>

#define N 10

int input(int *a);
void output(int *a);
void quick_sort(int *a, int first, int last);
void heap_sort(int *a);
void heapify(int *a, int n, int i);

int main() {
    int data[N];
    if (input(data) == 1) {
        return 1;
    }
    int data_copy[N];
    for (int i = 0; i < N; i++) {
        data_copy[i] = data[i];
    }
    quick_sort(data, 0, N - 1);
    output(data);
    printf("\n");
    heap_sort(data_copy);
    output(data_copy);
    return 0;
}

int input(int *a) {
    for (int i = 0; i < N; i++) {
        if (scanf("%d", &a[i]) != 1) {
            printf("n/a");
            return 1;
        }
    }
    return 0;
}

void output(int *a) {
    for (int i = 0; i < N; i++) {
        printf("%d", a[i]);
        if (i < N - 1) {
            printf(" ");
        }
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quick_sort(int *a, int first, int last) {
    if (first < last) {
        int left = first, right = last;
        int middle = a[(left + right) / 2];
        do {
            while (a[left] < middle) left++;
            while (a[right] > middle) right--;
            if (left <= right) {
                swap(&a[left], &a[right]);
                left++;
                right--;
            }
        } while (left <= right);
        quick_sort(a, first, right);
        quick_sort(a, left, last);
    }
}

void heap_sort(int *a) {
    for (int i = N / 2 - 1; i >= 0; i--) {
        heapify(a, N, i);
    }
    for (int i = N - 1; i > 0; i--) {
        int temp = a[0];
        a[0] = a[i];
        a[i] = temp;
        heapify(a, i, 0);
    }
}

void heapify(int *a, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && a[left] > a[largest]) largest = left;
    if (right < n && a[right] > a[largest]) largest = right;

    if (largest != i) {
        int temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;
        heapify(a, n, largest);
    }
}