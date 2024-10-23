#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "text_reader.h"
#include "header.h"
#include "assembly_translator.h"

int TextReader() {
    FILE *file_to_read  = fopen("text_of_program.txt", "r");
    FILE *file_to_write = fopen("assembly_text.txt",   "w");

    char *received_command = {0};
    int  is_sth_readed     = 0;
    int  code_of_program   = 1;
    int  next_is_command   = 1;
    struct labels_t lables = {};

    received_command = (char *) calloc(sizeof(char), MAX_LEN_OF_RECEIVED_COMMAND);


    while (received_command[0] != EOF && code_of_program && next_is_command != -1) { //todo not -1 but HALT
        int index = 0;
        char flag = '1';

        for (int i = 0; i < MAX_LEN_OF_RECEIVED_COMMAND; i ++)
            received_command[i] = 0;

        while ( (flag != ' ') && flag != ';'  && flag != ':' && flag != EOF && index < MAX_LEN_OF_RECEIVED_COMMAND) {
            is_sth_readed = fscanf(file_to_read, "%c", &received_command[index]);
            flag = received_command[index];
            index ++;
        }
         if (flag == ';' || flag == EOF)
            is_sth_readed = fscanf(file_to_read, "%c", &flag);



        if (!is_sth_readed) {
            printf("READING ERR: CANNOT READ FROM FILE\n");
            break;
        }


/*
        if (flag == ':') {
            CheckLable(received_command);
        }

*/


        if (next_is_command == 1 && received_command[0] != EOF) {
            code_of_program *= AssemblyTranslator(&received_command, &next_is_command);

            for (int i = 0; i < 2; i++)
                fprintf(file_to_write, "%d", received_command[i]);
            fprintf(file_to_write, " ");
        }



        else if (index > 3) {
            printf("Please write 2-digit numbers in commands\n");
            return ERROR;
        }



        else if (next_is_command == 0 && received_command[0] != EOF ) {
            for (int j = index; j < 3; j++)
                fprintf(file_to_write, "%c", '0');
            for (int i = 0; i < index - 1; i++)
                fprintf(file_to_write, "%c", received_command[i]);
            fprintf(file_to_write, " ");
            next_is_command = 1;
        }



        else {
            printf("Something went wrong inside text_reader\n");
            return ERROR;

        }
    }


    fclose(file_to_read );
    fclose(file_to_write);
    return ALL_GOOD;
}

//int CheckLable()
