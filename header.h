#ifndef HEADER
#define HEADER

typedef int stk_elem_t;        //Size of elements of stack
typedef stk_elem_t poison_elem_t; //first is size not bigger than  stk_elem_t
typedef stk_elem_t canary_t;      //first is size

/*
#define DEBUG_MODE 1
*/
#define MAX_LEN_OF_RECEIVED_COMMAND 15
#define AMOUNT_OF_REGISTERS 8
#define MAX_AMOUNT_OF_RECEIVED_CYMBOLS 1000
#define DEBUG_MODE 1

#if DEBUG_MODE == 1
    #define DEBUG(...) __VA_ARGS__
#else
    #define DEBUG(...)
#endif

struct spu_t {
    char all_instructions[MAX_AMOUNT_OF_RECEIVED_CYMBOLS / 2][2];
    int instr_ptr;
    int amount_of_cymbols_readed;
    stk_elem_t registers[AMOUNT_OF_REGISTERS];
};



struct stk_t {
    DEBUG(canary_t stk_r_canary;)

    stk_elem_t *data;
    unsigned int size;
    unsigned int capacity;
    poison_elem_t poison_elem;

    DEBUG(stk_elem_t hash;)
    DEBUG(stk_elem_t hash_after;)
    DEBUG(stk_elem_t stk_hash;)

    DEBUG(canary_t canary;)
    DEBUG(canary_t stk_l_canary;)
};

enum exit_codes {
    ALL_GOOD = 1,
    ERROR = 0,
};

enum all_numbers_commands {
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
};

#endif // HEAder
