#include <stdio.h>
#include <string.h>
#include "quicksort.h"

/* Static (private to this file) function prototypes. */
static void swap(void *a, void *b, size_t size);
static int lomuto(void *array, int left, int right, size_t elem_sz,
                  int (*cmp) (const void*, const void*));
static void quicksort_helper(void *array, int left, int right, size_t elem_sz,
                             int (*cmp) (const void*, const void*));

/*void swap(void *a, void *b, size_t size) {
    char temp[size]; 
    char *p = a, *q = b;
    for (size_t i = 0; i < size; i++) {
        temp[i] = *(p + i);
        *(p + i) = *(q + i);
        *(q + i) = temp[i];
    }
}
*/
void swap(void* a, void* b, size_t size) {
    char temp[size];
    char* p = (char*)a;
    char* q = (char*)b;
    memcpy(temp, p, size);
    memcpy(p, q, size);
    memcpy(q, temp, size);
}
static int lomuto(void *array, int left, int right, size_t elem_sz,
                  int (*cmp) (const void*, const void*)) {
    char *arr = array;
    void *pivot = arr + (left * elem_sz);
    int s = left;
    for (int i = left + 1; i <= right; i++) {
        void *current = arr + (i * elem_sz);
        if (cmp(current, pivot) < 0) {
            s++;
            swap(arr + (s * elem_sz), current, elem_sz);
        }
    }
    swap(arr + (left * elem_sz), arr + (s * elem_sz), elem_sz);
    return s;
}
static void quicksort_helper(void *array, int left, int right, size_t elem_sz,
                             int (*cmp) (const void*, const void*)) {
        if (left < right) {
                int pivot = lomuto(array, left, right, elem_sz, cmp);
                quicksort_helper(array, left, pivot-1, elem_sz, cmp);
                quicksort_helper(array, pivot+1, right, elem_sz, cmp);
        }
}

int int_cmp(const void *a, const void *b) {
    const int int_a = *((int*) a);
    const int int_b = *((int*) b);
    return (int_a > int_b) - (int_a < int_b);
}

int dbl_cmp(const void *a, const void *b) {
    const double double_a = *((double*) a);
    const double double_b = *((double*) b);
    if(double_a < double_b) return -1;
    if(double_a > double_b) return 1;
    return 0;
}

int str_cmp(const void *a, const void *b) {
    const char *char_a = *(const char**) a;
    const char *char_b = *(const char**) b;
    return strcmp(char_a, char_b);
}
void quicksort(void *array, size_t len, size_t elem_sz, int (*cmp) (const void*, const void*)) {
        if (array == NULL) {
                return;
        }
	quicksort_helper(array, 0, (int)len-1, elem_sz, cmp);
}
