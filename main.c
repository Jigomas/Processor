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
#include "spu_dumper.h"
void EndingFunctionOfProgram(struct stk_t *stk, int exit_code);

int RunOfProcessor(struct stk_t *stk, int exit_code);

int CheckIfRegister(struct spu_t spu);
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

    struct spu_t spu = {};
    spu.instr_ptr = 0;
    exit_code *= TextReader();

    FILE *file_to_read   = fopen("assembly_text.txt","r");
    char temp_instructions[MAX_AMOUNT_OF_RECEIVED_CYMBOLS] = {};
    int is_sth_readed    = 0;
    int i = 0;
    spu.amount_of_cymbols_readed = -1; //kostyl



    while (is_sth_readed != EOF) { //todo not -1 but HALT
        is_sth_readed = fscanf(file_to_read, " %c", &(temp_instructions[i]));
        i++;
        spu.amount_of_cymbols_readed ++;
    }

    printf("amount of cymbols was read %d\n", spu.amount_of_cymbols_readed);

    for (int i = 0; i < spu.amount_of_cymbols_readed; i++) {
        spu.all_instructions[i][0] = temp_instructions[i];
        spu.all_instructions[i][1] = temp_instructions[i + 1];
        printf("command %c%c \n", spu.all_instructions[i][0], spu.all_instructions[i][1]);
        i++;
    }

    spu.amount_of_cymbols_readed = spu.amount_of_cymbols_readed / 2;

    while (1) {
        // 4 is kostyl bc its int allignmented
        int command = ((stk_elem_t)*(char*)((char*)spu.all_instructions + (4 * spu.instr_ptr)     * sizeof(char)) - '0') * 10
                     + (stk_elem_t)*(char*)((char*)spu.all_instructions + (4 * spu.instr_ptr + 1) * sizeof(char)) - '0';

        switch ( command )  {
            case PUSH: {
                spu.instr_ptr += 1;
                int adress_of_register = CheckIfRegister(spu);

                if (adress_of_register == -1) { //kostyl
                    StkPush(stk, ((stk_elem_t)*(char*)((char*)spu.all_instructions + (4 * spu.instr_ptr)     * sizeof(char)) - '0') * 10
                                + (stk_elem_t)*(char*)((char*)spu.all_instructions + (4 * spu.instr_ptr + 1) * sizeof(char)) - '0');
                }

                else {
                    StkPush(stk, (spu.registers)[adress_of_register]);
                }
                spu.instr_ptr += 1;
                DEBUG(StkDumper(stk, __FILE__, __LINE__);)
                SpuDumper(spu);
                continue;
            }

            case POP: {
                spu.instr_ptr += 1;
                int adress_of_register = CheckIfRegister(spu);
                printf("%d\n", adress_of_register);
                if (adress_of_register == -1) { //kostyl
                    spu.instr_ptr -= 1;
                    StkPop(stk, 0); //kostyl
                }

                else {
                    (spu.registers)[adress_of_register] = *(stk_elem_t *)((char *)stk->data +
                                (stk->size - 1) * sizeof(stk_elem_t) DEBUG(+ sizeof(canary_t)));
                }
                spu.instr_ptr += 1;
                DEBUG(StkDumper(stk, __FILE__, __LINE__);)
                SpuDumper(spu);
                continue;
            }

            case ADD: {
                stk_elem_t first_number  = 0;
                stk_elem_t second_number = 0;

                StkPop(stk, &second_number);
                StkPop(stk, &first_number);

                StkPush(stk, first_number + second_number);

                spu.instr_ptr += 1;
                DEBUG(StkDumper(stk, __FILE__, __LINE__);)
                SpuDumper(spu);
                continue;
            }

            case SUB: {
                stk_elem_t first_number  = 0;
                stk_elem_t second_number = 0;

                StkPop(stk, &second_number);
                StkPop(stk, &first_number);

                StkPush(stk, first_number - second_number);

                spu.instr_ptr += 1;
                DEBUG(StkDumper(stk, __FILE__, __LINE__);)
                SpuDumper(spu);
                continue;
            }

            case MULT: {
                stk_elem_t first_number  = 0;
                stk_elem_t second_number = 0;

                StkPop(stk, &second_number);
                StkPop(stk, &first_number);

                StkPush(stk, first_number * second_number);

                spu.instr_ptr += 1;
                DEBUG(StkDumper(stk, __FILE__, __LINE__);)
                SpuDumper(spu);
                continue;
            }

            case DIV: {
                stk_elem_t first_number  = 0;
                stk_elem_t second_number = 0;

                StkPop(stk, &second_number);
                StkPop(stk, &first_number);

                StkPush(stk, first_number / second_number);

                spu.instr_ptr += 1;
                DEBUG(StkDumper(stk, __FILE__, __LINE__);)
                SpuDumper(spu);
                continue;
            }

            case OUT: {
                printf(">>OUTNUM: %lf", *(stk_elem_t *)((char *)stk->data +
                                (stk->size - 1) * sizeof(stk_elem_t) DEBUG(+ sizeof(canary_t))));

                spu.instr_ptr += 1;
                DEBUG(StkDumper(stk, __FILE__, __LINE__);)
                SpuDumper(spu);
                continue;
            }

            case IN: {

            }

            case SQRT: {
                stk_elem_t first_number = 0;

                StkPop(stk, &first_number);

                StkPush(stk, sqrt(first_number));

                spu.instr_ptr += 1;
                DEBUG(StkDumper(stk, __FILE__, __LINE__);)
                SpuDumper(spu);
                continue;
            }

            case SIN: {

            }

            case COS: {

            }

            case DUMP: {
                StkDumper(stk, __FILE__, __LINE__);

                spu.instr_ptr += 1;
                DEBUG(StkDumper(stk, __FILE__, __LINE__);)
                SpuDumper(spu);
                continue;
            }

            case HALT: {
                return 1;
            }

            default: {
                printf(">>SNTXERR: WRONG COMMAND %lf", *(stk_elem_t*)((char*)spu.all_instructions[0] + spu.instr_ptr * sizeof(stk_elem_t)) * 10
                                                     + *(stk_elem_t*)((char*)spu.all_instructions[1] + spu.instr_ptr * sizeof(stk_elem_t)));
                return 0;
            }
        }
    }

}





int CheckIfRegister(struct spu_t spu) {
    printf("symbol is %d", toupper(*(char*)((char*)spu.all_instructions + (4 * spu.instr_ptr + 1) * sizeof(char))) );
    if (toupper(*(char*)((char*)spu.all_instructions + (4 * spu.instr_ptr + 1) * sizeof(char))) == 'X') {
        int adress_of_register = (toupper(*(char*)((char*)spu.all_instructions + (4 * spu.instr_ptr) * sizeof(char))) - 'A');

        return adress_of_register;
    }
    return -1; //KOSTYL
}


