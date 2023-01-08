#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lfsr.h"

void lfsr_calculate(uint16_t *reg) {
    u_int16_t num_old = *reg;
    u_int16_t one = 1;
    u_int16_t next_bit = (num_old >> 0 & one) ^ (num_old >> 2 & one) ^
                            (num_old >> 3 & one) ^ (num_old >> 5 & one);
    num_old = num_old >> 1;
    one = 1 << 15;
    (*reg) = (num_old & ~one) | (!!next_bit << 15);

    return;
}

