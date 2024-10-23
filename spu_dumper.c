#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "spu_dumper.h"



void SpuDumper(struct spu_t spu) {
    printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
    printf ("intstruction pointer = %d\n", spu.instr_ptr);

    for (int i = 0; i < AMOUNT_OF_REGISTERS + 0; i++)
        printf("register %cx = %d\n", i - '0' + 'a', (spu.registers)[i]);
}

