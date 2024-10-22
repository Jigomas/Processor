#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include "verificator.h"
#include "push-pop.h"
#include "constructor-destructor.h"
#include "reader_from_keyboard.h"
#include "text_reader.h"
#include "assembly_translator.h"

void EndingFunctionOfProgram(struct stk_t *stk, int exit_code);

int RunOfProcessor(struct stk_t *stk, int exit_code);
/*
all_numbers_commands

    PUSH = 1 ,
    ADD  = 2 ,
    SUB  = 3 ,
    MULT = 4 ,
    DIV  = 5 ,
    OUT  = 6 ,
    IN   = 7 ,
    SQRT = 8 ,
    SIN  = 9 ,
    COS  = 10,
    DUMP = 11,
    HALT = 0 ;

*/

int main() {

    /**********************************************************************************************/
    //Starting
    int exit_code = ALL_GOOD;
    int amount_to_push = 5;
    int amount_to_pop =  3;
    unsigned int capacity = 5;    // this is gonna be starting capacity


    poison_elem_t poison_elem = 0; // not bigger than  stk_elem_t
    canary_t canary = 0;

    switch (sizeof(poison_elem) ) {
        case sizeof(double): {
            poison_elem = -6666;
            canary = 123456789;
            break;
        }

        case sizeof(int): {
            poison_elem = -666;
            canary = 12345678;

            break;
        }

        case sizeof(short): {
            poison_elem = -66;
            canary = 1234567;

            break;
        }

        case sizeof(char): {
            poison_elem = -6;
            canary = 1;

            break;
        }

        default: {
            poison_elem = 0;
            canary = 1;

            break;
        }
    }


    DEBUG(printf ("Poison Element = %lf\n", poison_elem);)
    struct stk_t stk = {};

    exit_code *= StkCtor(&stk, capacity, poison_elem DEBUG(, canary));
    StkDumper(&stk, __FILE__, __LINE__);
    //EndOfStarting part
    /**********************************************************************************************/
    RunOfProcessor(&stk, exit_code);





    //EndingFunctionOfProgram(&stk, exit_code);
}



void EndingFunctionOfProgram(struct stk_t *stk, int exit_code) {
    StkVerifier(stk);
    printf("****************************************\n");
    printf("Programm ended with stack of %lf elements\n", stk->size);

    DEBUG(StkDumper(stk, __FILE__, __LINE__);)

    exit_code = StkDtor(stk);
    DEBUG(printf("Programm ended with Exit Code %lf", exit_code);)
}



int RunOfProcessor(struct stk_t *stk, int exit_code) {
    /*
    all_numbers_commands
    PUSH = 1 ,
    ADD  = 2 ,
    SUB  = 3 ,
    MULT = 4 ,
    DIV  = 5 ,
    OUT  = 6 ,
    IN   = 7 ,
    SQRT = 8 ,
    SIN  = 9 ,
    COS  = 10,
    DUMP = 11,
    HALT = 0 ;
    */

    //todo: put registers and command line and instr_ptr inside another struct
    /*

    struct spu {
        stk_elem_t instructions;
        int instr_ptr;
        stk_elem_t registers[AMOUNT_OF_REGISTERS];
    };

    */
    int instr_pnt = 0;
    exit_code *= TextReader();
    FILE *file_to_read  = fopen("assembly_text.txt","r");
    stk_elem_t all_instructions[1000] = {};

    int is_sth_readed    = 0;
    int i = 0;
    stk_elem_t registers[AMOUNT_OF_REGISTERS] = {};
    while (is_sth_readed != EOF) { //todo not -1 but HALT
        is_sth_readed = fscanf(file_to_read, " %d", &(all_instructions[i]));
        i++;
    }

    while (1) {
        int command = *(stk_elem_t*)((char*)all_instructions + instr_pnt * sizeof(stk_elem_t));
        switch ( command )  {
            case PUSH: {
                instr_pnt += 1;

                StkPush(stk, *(stk_elem_t*)((char*)all_instructions + instr_pnt * sizeof(stk_elem_t)) );

                instr_pnt += 1;
                DEBUG(StkDumper(stk, __FILE__, __LINE__);)
                continue;
            }

            case ADD: {
                stk_elem_t first_number = 0;
                stk_elem_t second_number = 0;

                StkPop(stk, &second_number);
                StkPop(stk, &first_number);

                StkPush(stk, first_number + second_number);

                instr_pnt += 1;
                DEBUG(StkDumper(stk, __FILE__, __LINE__);)
                continue;
            }

            case SUB: {
                stk_elem_t first_number = 0;
                stk_elem_t second_number = 0;

                StkPop(stk, &second_number);
                StkPop(stk, &first_number);

                StkPush(stk, first_number - second_number);

                instr_pnt += 1;
                DEBUG(StkDumper(stk, __FILE__, __LINE__);)
                continue;
            }

            case MULT: {
                stk_elem_t first_number = 0;
                stk_elem_t second_number = 0;

                StkPop(stk, &second_number);
                StkPop(stk, &first_number);

                StkPush(stk, first_number * second_number);

                instr_pnt += 1;
                DEBUG(StkDumper(stk, __FILE__, __LINE__);)
                continue;
            }

            case DIV: {
                stk_elem_t first_number = 0;
                stk_elem_t second_number = 0;

                StkPop(stk, &second_number);
                StkPop(stk, &first_number);

                StkPush(stk, first_number / second_number);

                instr_pnt += 1;
                DEBUG(StkDumper(stk, __FILE__, __LINE__);)
                continue;
            }

            case OUT: {
                printf(">>OUTNUM: %lf", *(stk_elem_t *)((char *)stk->data +
                                (stk->size - 1) * sizeof(stk_elem_t) DEBUG(+ sizeof(canary_t)) ));

                instr_pnt += 1;
                DEBUG(StkDumper(stk, __FILE__, __LINE__);)
                continue;
            }

            case IN: {

            }

            case SQRT: {
                stk_elem_t first_number = 0;

                StkPop(stk, &first_number);

                StkPush(stk, sqrt(first_number) );

                instr_pnt += 1;
                DEBUG(StkDumper(stk, __FILE__, __LINE__);)
                continue;
            }

            case SIN: {

            }

            case COS: {

            }

            case DUMP: {
                StkDumper(stk, __FILE__, __LINE__);

                instr_pnt += 1;
                DEBUG(StkDumper(stk, __FILE__, __LINE__);)
                continue;
            }

            case HALT: {
                return 1;
            }

            default: {
                printf(">>SNTXERR: WRONG COMMAND %lf", *(stk_elem_t*)((char*)all_instructions +
                                                            instr_pnt * sizeof(stk_elem_t)) );
                return 0;
            }
        }
    }
}
