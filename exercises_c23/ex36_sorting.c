// CFarer Exercise 36: Sorting - qsort and comparators
// TOPIC: qsort, function pointers, comparators
// DIFFICULTY: Advanced
//
// The standard library qsort() sorts any array using a comparator function.
// Comparator signature:  int cmp(const void *a, const void *b)
//   returns < 0 if a < b, 0 if equal, > 0 if a > b
//
// Task:
//   1. Implement cmp_int_asc  - ascending integer comparator
//   2. Implement cmp_int_desc - descending integer comparator

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// TODO: implement ascending comparator
int cmp_int_asc(const void *a, const void *b) {
    return 0;
}

// TODO: implement descending comparator
int cmp_int_desc(const void *a, const void *b) {
    return 0;
}

int main(void) {
    int nums[] = {5, 2, 8, 1, 9, 3};
    int len    = (int)(sizeof(nums) / sizeof(nums[0]));

    qsort(nums, (size_t)len, sizeof(int), cmp_int_asc);
    assert(nums[0] == 1 && nums[5] == 9);

    qsort(nums, (size_t)len, sizeof(int), cmp_int_desc);
    assert(nums[0] == 9 && nums[5] == 1);

    printf("Sorted (desc): ");
    for (int i = 0; i < len; i++) printf("%d ", nums[i]);
    printf("\n");

    return 0;
}

// I AM NOT DONE
