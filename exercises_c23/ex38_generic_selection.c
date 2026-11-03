// CFarer Exercise 38: _Generic Selection (C11+)
// TOPIC: Type-generic programming, _Generic
// DIFFICULTY: Advanced
//
// C doesn't have templates, but _Generic lets a macro dispatch on type
// at compile time - zero runtime cost.
//
// Syntax:
//   _Generic(expr,
//       type1: value1,
//       type2: value2,
//       default: fallback)
//
// The compiler picks the branch whose type matches expr, discards the rest.
//
// Task: Implement a TYPE_NAME(x) macro that returns a string literal
// naming the type of x.
// Handle: int, long, float, double, char*, void* (default: "unknown")

#include <stdio.h>
#include <string.h>
#include <assert.h>

// TODO: define TYPE_NAME(x) using _Generic
#define TYPE_NAME(x) "unknown"   // replace this

int main(void) {
    int    i = 0;
    long   l = 0L;
    float  f = 0.0f;
    double d = 0.0;
    char  *s = "hi";
    void  *v = nullptr;

    assert(strcmp(TYPE_NAME(i), "int")    == 0);
    assert(strcmp(TYPE_NAME(l), "long")   == 0);
    assert(strcmp(TYPE_NAME(f), "float")  == 0);
    assert(strcmp(TYPE_NAME(d), "double") == 0);
    assert(strcmp(TYPE_NAME(s), "char*")  == 0);
    assert(strcmp(TYPE_NAME(v), "void*")  == 0);
    assert(strcmp(TYPE_NAME(3.14), "double") == 0);  // literal is double
    assert(strcmp(TYPE_NAME(3.14f), "float") == 0);  // f suffix = float

    printf("TYPE_NAME macro works: int=%s  double=%s  char*=%s\n",
           TYPE_NAME(i), TYPE_NAME(d), TYPE_NAME(s));
    return 0;
}

// I AM NOT DONE
