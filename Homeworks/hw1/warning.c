/// file: warning.c
/// description: faulty code example that needs fixing.
/// @author RIT CS Dept.

#include <stdio.h>

/// compute a value.
int compute(int a) {
    int b = a * 5;
    return b;           //    <<Added return value for the computed value
}

/// main function should print 2017
int main(void) {        //    <<Changed input to void as there is no input needed
    int x = 1917;       //    <<Assigned Value to x
    int y = compute(20);

    printf("%d\n", y+x);

    return 0;
}

