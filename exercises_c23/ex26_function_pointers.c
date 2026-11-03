// CFarer Exercise 26: Function Pointers
// TOPIC: Function pointer declaration, callbacks
// DIFFICULTY: Advanced
//
// A function pointer stores the address of a function.
// Declaration:   return_type (*name)(param_types);
//
// Task: Implement apply() - it takes an int array, its length, and a
// function pointer 'fn'. It returns a new heap-allocated array where
// result[i] = fn(arr[i]).

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int double_it(int x) { return x * 2; }
int square(int x)    { return x * x; }

// TODO: implement apply
// Signature: int *apply(const int *arr, int len, int (*fn)(int))
int *apply(const int *arr, int len, int (*fn)(int)) {
    return NULL;
}

int main(void) {
    int src[] = {1, 2, 3, 4, 5};
    int len   = 5;

    int *doubled = apply(src, len, double_it);
    assert(doubled != NULL);
    assert(doubled[0] == 2);
    assert(doubled[4] == 10);
    free(doubled);

    int *squared = apply(src, len, square);
    assert(squared != NULL);
    assert(squared[0] == 1);
    assert(squared[2] == 9);
    assert(squared[4] == 25);
    free(squared);

    printf("apply() with function pointers works!\n");
    return 0;
}

// I AM NOT DONE
