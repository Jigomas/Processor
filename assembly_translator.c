#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "assembly_translator.h"
#include "header.h"



int AssemblyTranslator(char *received_command[], int *next_is_command) {
    /*
    all_numbers_commands
    PUSH =  1,
    POP  =  2,
    ADD  =  3,
    SUB  =  4,
    MULT =  5,
    DIV  =  6,
    OUT  =  7,
    IN   =  8,
    SQRT =  9,
    SIN  = 10,
    COS  = 11,
    DUMP = 12,
    JUMP = 13,
    HALT =  0,
    */

    while(1) {
        if ( toupper((*received_command)[0]) == 'P' && toupper((*received_command)[1]) == 'U'
          && toupper((*received_command)[2]) == 'S' && toupper((*received_command)[3]) == 'H') {
            *next_is_command = 0;
            DataClear(received_command, MAX_LEN_OF_RECEIVED_COMMAND);

            (*received_command)[0] = 0;
            (*received_command)[1] = PUSH;
            break;
        }

        if ( toupper((*received_command)[0]) == 'P' && toupper((*received_command)[1]) == 'O'
          && toupper((*received_command)[2]) == 'P') {
            *next_is_command = 0;
            DataClear(received_command, MAX_LEN_OF_RECEIVED_COMMAND);

            (*received_command)[0] = 0;
            (*received_command)[1] = POP;
            break;
        }

        if ( toupper((*received_command)[0]) == 'A' && toupper((*received_command)[1]) == 'D'
          && toupper((*received_command)[2]) == 'D'){
            *next_is_command = 1;
            DataClear(received_command, MAX_LEN_OF_RECEIVED_COMMAND);

            (*received_command)[0] = 0;
            (*received_command)[1] = ADD;
            break;
        }

        if ( toupper((*received_command)[0]) == 'S' && toupper((*received_command)[1]) == 'U'
          && toupper((*received_command)[2]) == 'B') {
            *next_is_command = 1;
            DataClear(received_command, MAX_LEN_OF_RECEIVED_COMMAND);

            (*received_command)[0] = 0;
            (*received_command)[1] = SUB;
            break;
        }

        if ( toupper((*received_command)[0]) == 'M' && toupper((*received_command)[1]) == 'U'
          && toupper((*received_command)[2]) == 'L' && toupper((*received_command)[3]) == 'T') {
            *next_is_command = 1;
            DataClear(received_command, MAX_LEN_OF_RECEIVED_COMMAND);

            (*received_command)[0] = 0;
            (*received_command)[1] = MULT;
            break;
        }

        if ( toupper((*received_command)[0]) == 'D' && toupper((*received_command)[1]) == 'I'
          && toupper((*received_command)[2]) == 'V') {
            *next_is_command = 1;
            DataClear(received_command, MAX_LEN_OF_RECEIVED_COMMAND);

            (*received_command)[0] = 0;
            (*received_command)[1] = DIV;
            break;
        }

        if ( toupper((*received_command)[0]) == 'O' && toupper((*received_command)[1]) == 'U'
          && toupper((*received_command)[2]) == 'T') {
            *next_is_command = 1;
            DataClear(received_command, MAX_LEN_OF_RECEIVED_COMMAND);

            (*received_command)[0] = 0;
            (*received_command)[1] = OUT;
            break;
        }

        if ( toupper((*received_command)[0]) == 'I' && toupper((*received_command)[1]) == 'N') {
            *next_is_command = 1; // todo, dont know
            DataClear(received_command, MAX_LEN_OF_RECEIVED_COMMAND);

            (*received_command)[0] = 0;
            (*received_command)[1] = IN;
            break;
        }

        if ( toupper((*received_command)[0]) == 'S' && toupper((*received_command)[1]) == 'Q'
          && toupper((*received_command)[2]) == 'R' && toupper((*received_command)[3]) == 'T') {
            *next_is_command = 1;
            DataClear(received_command, MAX_LEN_OF_RECEIVED_COMMAND);

            (*received_command)[0] = 0;
            (*received_command)[1] = SQRT;
            break;
        }

        if ( toupper((*received_command)[0]) == 'S' && toupper((*received_command)[1]) == 'I'
          && toupper((*received_command)[2]) == 'N') {
            *next_is_command = 1;
            DataClear(received_command, MAX_LEN_OF_RECEIVED_COMMAND);

            (*received_command)[0] = 1;
            (*received_command)[1] = 0;
            break;
        }

        if ( toupper((*received_command)[0]) == 'C' && toupper((*received_command)[1]) == 'O'
          && toupper((*received_command)[2]) == 'S') {
            *next_is_command = 1;
            DataClear(received_command, MAX_LEN_OF_RECEIVED_COMMAND);

            (*received_command)[0] = 1;
            (*received_command)[1] = 1;
            break;
        }

        if ( toupper((*received_command)[0]) == 'D' && toupper((*received_command)[1]) == 'U'
          && toupper((*received_command)[2]) == 'M' && toupper((*received_command)[3]) == 'P') {
            *next_is_command = 1;
            DataClear(received_command, MAX_LEN_OF_RECEIVED_COMMAND);

            (*received_command)[0] = 1;
            (*received_command)[1] = 2;
            break;
        }

        if ( toupper((*received_command)[0]) == 'J' && toupper((*received_command)[1]) == 'U'
          && toupper((*received_command)[2]) == 'M' && toupper((*received_command)[3]) == 'P') {
            *next_is_command = 0;
            DataClear(received_command, MAX_LEN_OF_RECEIVED_COMMAND);

            (*received_command)[0] = 1;
            (*received_command)[1] = 3;
            break;
        }

        if ( toupper((*received_command)[0]) == 'H' && toupper((*received_command)[1]) == 'A'
          && toupper((*received_command)[2]) == 'L' && toupper((*received_command)[3]) == 'T') {
            *next_is_command = -1;
            DataClear(received_command, MAX_LEN_OF_RECEIVED_COMMAND);

            (*received_command)[0] = 0;
            (*received_command)[1] = 0;
            break;
        }

        printf("Unknown command\n");
        return ERROR;
        break;
    }
    return ALL_GOOD;
}


void DataClear(char **data, int size) {
    for (int i = 0; i < size; i++)
        (*data)[i] = ' ';
}
