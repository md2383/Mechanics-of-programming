// File: $Id: quick_sort.c,v 1.0 2023/07/30 23:27:00 csci243 Exp $
//
// Description:  Quick Sort Comparison -> Threaded vs Non-Threaded
//
// Author:  Miguel Dias Pinto (md2383)
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/// Creates array of random integers between 0 and 10.
///
/// @param size, the size of the array
/// @return array with random nums
int *create_random_nums(int size) {
    int *arr = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % (size * 10);
    }
    return arr;
}

/// Swaps the values of integers
///
/// @param a,b integers to be swapped
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/// Function that performs the Partition step in Quick Sort.
///
/// @param arr, Array with the values
/// @param low,high indexes to partition the array
/// @return index of pivot after partition
int partition(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

/// Recursive Helper Function for Non-Threaded Quicksort
///
/// @param arr, Array with the values
/// @param low,high indexes to be sorted
void quick_sort_helper(int *arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort_helper(arr, low, pi - 1);
        quick_sort_helper(arr, pi + 1, high);
    }
}

/// Creates a Copy of the array, and loops it through recursive Quick_Sort_Helper
///
/// @param arr, Array with the values
/// @param low,high indexes to be sorted
/// @return Sorted Array
int *quick_sort(int *arr, int size) {
    int *sorted_arr = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        sorted_arr[i] = arr[i];
    }
    quick_sort_helper(sorted_arr, 0, size - 1);
    return sorted_arr;
}

/// Struct to hold arguments for Threaded Quicksort
struct QuickSortArgs {
    int *arr;      //Array to be sorted
    int low;       //Low index to sort
    int high;      //High index to sort
};

// Add a condition variable and mutex for synchronization
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int sorting_completed = 0;

/// Threaded Quicksort function
void *quick_sort_threads(void *arg) {
    struct QuickSortArgs *qs_args = (struct QuickSortArgs *)arg;
    int *arr = qs_args->arr;
    int low = qs_args->low;
    int high = qs_args->high;

    if (low < high) {
        // Use sequential quick sort for small sub-arrays
        if (high - low < 1000) {
            quick_sort_helper(arr, low, high);
        } else {
            int pi = partition(arr, low, high);

            // Create arguments for the left and right sub-arrays
            struct QuickSortArgs args1 = { arr, low, pi - 1 };
            struct QuickSortArgs args2 = { arr, pi + 1, high };

            // Create two threads, each handling one sub-array
            pthread_t thread1, thread2;
            pthread_create(&thread1, NULL, quick_sort_threads, &args1);
            pthread_create(&thread2, NULL, quick_sort_threads, &args2);

            // Wait for both threads to complete
            pthread_join(thread1, NULL);
            pthread_join(thread2, NULL);
        }
    }

    // This thread's work is done, return NULL
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <size>\n", argv[0]);
        return 1;
    }

    int size = atoi(argv[1]);
    int *arr = create_random_nums(size);

    // Create a copy of the original array for non-threaded quick sort
    int *arr_non_threaded = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        arr_non_threaded[i] = arr[i];
    }

    // Non-threaded quick sort
    clock_t start = clock();
    int *sorted_arr_non_threaded = quick_sort(arr_non_threaded, size);
    clock_t end = clock();
    double non_threaded_time = (double)(end - start) / CLOCKS_PER_SEC;

    // Threaded quick sort
    start = clock();
    struct QuickSortArgs args = { arr, 0, size - 1 };
    quick_sort_threads(&args);
    clock_t end_threaded = clock();
    double threaded_time = (double)(end_threaded - start) / CLOCKS_PER_SEC;

    // Display results
    printf("Non-Threaded Quick Sort Time: %f seconds\n", non_threaded_time);
    printf("Threaded Quick Sort Time: %f seconds\n", threaded_time);
    printf("Time Difference: %f seconds\n", non_threaded_time - threaded_time);

    free(arr);
    free(arr_non_threaded);
    free(sorted_arr_non_threaded);

    return 0;
}
