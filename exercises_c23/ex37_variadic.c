// CFarer Exercise 37: Variadic Functions
// TOPIC: <stdarg.h>, va_list, va_start, va_arg, va_end
// DIFFICULTY: Advanced
//
// Variadic functions accept a variable number of arguments (like printf).
// They use the <stdarg.h> macros to walk the argument list.
//
// Task: Implement sum_ints(count, ...) which sums 'count' integer arguments.
// Example: sum_ints(3, 10, 20, 30) == 60

#include <stdio.h>
#include <stdarg.h>
#include <assert.h>

int sum_ints(int count, ...) {
    int total = 0;
    // TODO:
    //   va_list ap;
    //   va_start(ap, count);
    //   loop count times, calling va_arg(ap, int)
    //   va_end(ap);
    return total;
}

int main(void) {
    assert(sum_ints(0)           == 0);
    assert(sum_ints(1, 42)       == 42);
    assert(sum_ints(3, 10, 20, 30) == 60);
    assert(sum_ints(4, 1, 2, 3, 4) == 10);

    printf("sum_ints() variadic function works!\n");
    return 0;
}

// I AM NOT DONE
