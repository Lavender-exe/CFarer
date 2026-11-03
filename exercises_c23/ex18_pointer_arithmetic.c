// CFarer Exercise 18: Pointer Arithmetic
// TOPIC: Pointer + offset, pointer vs array
// DIFFICULTY: Intermediate
//
// A pointer can be incremented to walk through memory.
//   int arr[] = {10, 20, 30};
//   int *p = arr;    // p points at arr[0]
//   p++;             // now p points at arr[1]
//   *p               // == 20
//
// Task: Implement sum_ptr() which sums an array using ONLY pointer arithmetic
// (no [] subscript operator allowed in the function body).

#include <stdio.h>
#include <assert.h>

int sum_ptr(const int *p, int len) {
    int total = 0;
    // TODO: walk p forward 'len' times and accumulate
    // Use  *p  to read and  p++  to advance - no arr[i] allowed here
    return total;
}

int main(void) {
    int a[] = {1, 2, 3, 4, 5};
    assert(sum_ptr(a, 5) == 15);

    int b[] = {10, -3, 7};
    assert(sum_ptr(b, 3) == 14);

    printf("sum_ptr() works correctly!\n");
    return 0;
}

// I AM NOT DONE
