#include <stdio.h>
#include "bit_ops.h"

// Return the nth bit of x.
// Assume 0 <= n <= 31
unsigned get_bit(unsigned x,
                 unsigned n) {
    // YOUR CODE HERE
    u_int32_t one = 1;

    return (x >> n) & one;
}
// Set the nth bit of the value of x to v.
// Assume 0 <= n <= 31, and v is 0 or 1
void set_bit(unsigned * x,
             unsigned n,
             unsigned v) {
    // YOUR CODE HERE
    // Set nth bit to 0 and then OR with v
    u_int32_t one = 1 << n;
    u_int32_t bit = (v << n);
    (*x) = ((*x) & ~one) | (bit);

    return;
}
// Flip the nth bit of the value of x.
// Assume 0 <= n <= 31
void flip_bit(unsigned * x,
              unsigned n) {
    // YOUR CODE HERE
    u_int32_t bit = get_bit(*x, n);
    set_bit(x, n, !bit);
    return;
}

