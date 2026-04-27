// CFarer Exercise 07: while Loop
// TOPIC: while, loop control
// DIFFICULTY: Beginner
//
// Task: Complete sum_to() so it returns the sum of all integers 1..n.
// Example: sum_to(5) == 1+2+3+4+5 == 15

#include <stdio.h>
#include <assert.h>

int sum_to(int n) {
    int total = 0;
    int i     = 1;

    // TODO: write a while loop that adds i to total, then increments i,
    //       stopping when i > n

    return total;
}

int main(void) {
    assert(sum_to(1)  == 1);
    assert(sum_to(5)  == 15);
    assert(sum_to(10) == 55);
    assert(sum_to(0)  == 0);

    printf("sum_to() works correctly!\n");
    return 0;
}

// I AM NOT DONE
