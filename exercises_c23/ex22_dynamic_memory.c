// CFarer Exercise 22: Dynamic Memory
// TOPIC: malloc, free, NULL check
// DIFFICULTY: Intermediate
//
// malloc(n) allocates n bytes on the heap and returns a void*.
// Always check the return value - it is NULL if allocation fails.
// Every malloc must be matched with a free().
//
// Task: Implement int_array_new() and int_array_free().
//   int_array_new(len)  - allocate an int array of length len, return pointer
//   int_array_free(p)   - free the memory

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int *int_array_new(int len) {
    // TODO: allocate, NULL-check, return
    return NULL;
}

void int_array_free(int *p) {
    // TODO: free the memory
}

int main(void) {
    int *arr = int_array_new(5);
    assert(arr != NULL);

    for (int i = 0; i < 5; i++) arr[i] = i * 10;
    assert(arr[0] == 0);
    assert(arr[4] == 40);

    int_array_free(arr);
    arr = NULL;   // good practice after free

    printf("Dynamic memory allocation works!\n");
    return 0;
}

// I AM NOT DONE
