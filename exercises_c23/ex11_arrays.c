// CFarer Exercise 11: Arrays
// TOPIC: Arrays, sizeof, iteration
// DIFFICULTY: Intermediate
//
// NOTE: 'int *arr' is a pointer - arrays are passed to functions as
// a pointer to their first element. You can still use arr[i] here.
// Pointers get their own exercises starting at exercise 14.
//
// Task: Implement array_sum() - return the sum of all elements.
// Then implement array_max() - return the largest element.

#include <stdio.h>
#include <assert.h>

int array_sum(int *arr, int len) {
    // TODO: iterate and accumulate
    return 0;
}

int array_max(int *arr, int len) {
    // TODO: iterate and track the maximum
    return arr[0];
}

int main(void) {
    int nums[] = {3, 1, 4, 1, 5, 9, 2, 6};
    int len    = (int)(sizeof(nums) / sizeof(nums[0]));

    assert(array_sum(nums, len) == 31);
    assert(array_max(nums, len) == 9);

    int single[] = {42};
    assert(array_sum(single, 1) == 42);
    assert(array_max(single, 1) == 42);

    printf("Array functions work correctly!\n");
    return 0;
}

// I AM NOT DONE
