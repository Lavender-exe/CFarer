// CFarer Exercise 08: for Loop
// TOPIC: for loop, arrays
// DIFFICULTY: Beginner
//
// Task: Use a for loop to fill the array with the squares of 0..4,
// i.e. squares[i] = i * i.
// Expected: 0 1 4 9 16

#include <stdio.h>
#include <assert.h>

int main(void) {
    int squares[5];

    // TODO: write a for loop that sets squares[i] = i * i for i in 0..4

    assert(squares[0] == 0);
    assert(squares[1] == 1);
    assert(squares[2] == 4);
    assert(squares[3] == 9);
    assert(squares[4] == 16);

    for (int i = 0; i < 5; i++) {
        printf("%d ", squares[i]);
    }
    printf("\n");

    return 0;
}

// I AM NOT DONE
