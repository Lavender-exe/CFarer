// CFarer Exercise 17: Arrays and Pointers
// TOPIC: Array decay, arr[i] == *(arr + i)
// DIFFICULTY: Intermediate
//
// When an array is passed to a function, it "decays" to a pointer to its
// first element. That is why earlier exercises could take 'int *arr'.
//
//   int a[] = {10, 20, 30};
//   int *p = a;          // same as &a[0]
//   a[1]                 // is exactly  *(a + 1)
//
// Task:
//   1. Implement get_at(arr, i) using ONLY pointer dereference (no []).
//   2. Implement count_to_first_negative(arr, len) - return the index of the
//      first negative element, or -1 if none. [] is allowed here.

#include <stdio.h>
#include <assert.h>

int get_at(const int *arr, int i) {
    // TODO: return the i-th element without using []
    return 0;
}

int first_negative(const int *arr, int len) {
    // TODO: return the index of the first negative value, or -1
    return -1;
}

int main(void) {
    int a[] = {10, 20, 30, 40};

    assert(get_at(a, 0) == 10);
    assert(get_at(a, 2) == 30);

    int b[] = {3, 7, -1, 5};
    assert(first_negative(b, 4) == 2);
    assert(first_negative(a, 4) == -1);

    printf("Arrays and pointers are the same thing (almost)!\n");
    return 0;
}

// I AM NOT DONE
