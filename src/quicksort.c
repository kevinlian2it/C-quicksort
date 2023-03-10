#include <stdio.h>
#include <string.h>
#include "quicksort.h"

/* Static (private to this file) function prototypes. */
static void swap(void *a, void *b, size_t size);
static int lomuto(void *array, int left, int right, size_t elem_sz,
                  int (*cmp) (const void*, const void*));
static void quicksort_helper(void *array, int left, int right, size_t elem_sz,
                             int (*cmp) (const void*, const void*));

static void swap(void *a, void *b, size_t size) {
	char *p = a, *q = b, tmp;
    	for (size_t i = 0; i < size; i++) {
        	tmp = *(p + i);
        	*(p + i) = *(q + i);
        	*(q + i) = tmp;
    	}
}

static int lomuto(void *array, int left, int right, size_t elem_sz,
                  int (*cmp) (const void*, const void*)) {
	void* p = (char *)array + left * elem_sz;
	int s = left;
	for(int i = left+1;i <= right;i++) {
		if(cmp((char *)array + i * elem_sz,p) < 0 ) {
			s++;
			swap((char *)array + s,(char *)array + i,elem_sz);
		}
	}
	swap((char *)array + left, (char *)array + s,elem_sz);
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
    int int_a = *((int*) a);
    int int_b = *((int*) b);
    return (int_a > int_b) - (int_a < int_b);
}

int dbl_cmp(const void *a, const void *b) {
    double double_a = *((double*) a);
    double double_b = *((double*) b);
    return (double_a > double_b) - (double_a < double_b);
}

int str_cmp(const void *a, const void *b) {
    const char *char_a = *(const char**) a;
    const char *char_b = *(const char**) b;
    return strcmp(char_a, char_b);
}
void quicksort(void *array, size_t len, size_t elem_sz, int (*cmp) (const void*, const void*)) {
	quicksort_helper(array, 0, (int)len-1, elem_sz, cmp);
}
