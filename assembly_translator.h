#ifndef ASSTRTOR
#define ASSTRTOR

#include "header.h"

#define AMOUNT_OF_LABLES 10


struct lbl_ptr_t {
    int adress;
    char name[MAX_LEN_OF_RECEIVED_COMMAND];
};

struct lbl_t {
    int indexes[AMOUNT_OF_LABLES];
    struct lbl_ptr_t pointer[AMOUNT_OF_LABLES];
};

#include "header.h"
int AssemblyTranslator(char *received_command[], int *next_is_command) ;
void DataClear(char **data, int size);

#endif //ASSTRTOR
