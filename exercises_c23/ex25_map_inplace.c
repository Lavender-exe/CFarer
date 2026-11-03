// CFarer Exercise 25: Applying a Function to an Array
// TOPIC: Function pointer parameter, transform in place
// DIFFICULTY: Advanced
//
// Functions can take other functions as arguments. This is how callbacks work:
//   void map_in_place(int *arr, int len, int (*fn)(int))
// The caller decides WHAT to do (double? square?), your function decides WHEN.
//
// Task: implement map_in_place() so every element becomes fn(element).

#include <stdio.h>
#include <assert.h>

int double_it(int x) { return x * 2; }
int square(int x)    { return x * x; }

// TODO: implement map_in_place - replace each arr[i] with fn(arr[i])
void map_in_place(int *arr, int len, int (*fn)(int)) {
}

int main(void) {
    int a[] = {1, 2, 3};
    map_in_place(a, 3, double_it);
    assert(a[0] == 2 && a[1] == 4 && a[2] == 6);

    int b[] = {1, 2, 3, 4};
    map_in_place(b, 4, square);
    assert(b[0] == 1 && b[1] == 4 && b[2] == 9 && b[3] == 16);

    printf("map_in_place() works correctly!\n");
    return 0;
}

// I AM NOT DONE
