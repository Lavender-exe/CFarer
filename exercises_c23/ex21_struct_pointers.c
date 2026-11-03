// CFarer Exercise 21: Pointers to Structs
// TOPIC: -> operator, walking arrays of structs
// DIFFICULTY: Intermediate
//
// Given a pointer to a struct, -> accesses members:
//   struct Point *pp = &p;
//   pp->x            // same as  (*pp).x
//
// Task:
//   1. Implement total_price(items, n) - sum of price * quantity for all items.
//      Use [] or pointer walking, your choice.
//   2. Implement most_expensive(items, n) - return a POINTER to the item
//      with the highest price.

#include <stdio.h>
#include <stddef.h>
#include <assert.h>

typedef struct {
    const char *name;
    double      price;
    int         quantity;
} Item;

// TODO: implement total_price
double total_price(const Item *items, int n) {
    return 0.0;
}

// TODO: implement most_expensive (return NULL if n <= 0)
const Item *most_expensive(const Item *items, int n) {
    return NULL;
}

int main(void) {
    Item cart[] = {
        {"apple",  0.50, 4},
        {"bread",  2.25, 1},
        {"cheese", 5.00, 2},
    };
    int n = 3;

    assert(total_price(cart, n) == 14.25);

    const Item *top = most_expensive(cart, n);
    assert(top != NULL);
    assert(top->price == 5.00);

    const Item *nothing = most_expensive(cart, 0);
    assert(nothing == NULL);

    printf("Most expensive: %s\n", top->name);
    return 0;
}

// I AM NOT DONE
