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

/*
void LablesDumper() {
    for (int add_of_lable = 0; add_of_lable < AMOUNT_OF_LABLES; add_of_lable++) {
        printf("\nLable :");

        for (int j = 0; j < MAX_LEN_OF_RECEIVED_COMMAND; j++)
            printf("%d ", (lables.name)[add_of_lable][j]);
        printf("addr %d", lables.address_to_move[add_of_lable]);
        }
    printf("end of lables\n");
}
*/
