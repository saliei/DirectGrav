#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"

void read_params(char const *filename)
{
    FILE *file;
    char line[MAX_LINE_LENGTH];
    int linenum = 0;
    char prm[MAX_PARAM_LENGTH], prm_val[MAX_PARAM_LENGTH];
    int count;
    char *tok;

    file = fopen(filename, "r");
    if(file == NULL)
    {
        fprintf(stdout, "Error! Could not open the parameter file.\n");
        exit(EXIT_FAILURE);
    }
    
    while( fgets(line, MAX_LINE_LENGTH, file) != NULL )
    {
        linenum += 1;
        if(strstr(line, "#")) continue;

        count = 0;
        tok = strtok(line, " ");

        while(tok != NULL)
        {
            if(count == 0) strncpy(prm, tok, MAX_PARAM_LENGTH);
            else if(count == 1) strncpy(prm_val, tok, MAX_PARAM_LENGTH);
            else
            {
                fprintf(stdout ,"Error! Potentially erroneous parameter at line %d.\n", linenum);
                exit(EXIT_FAILURE);
            }

            if(strcmp(prm, "NUM_PARTICLES") == 0) NUM_PARTICLES = atol(prm_val);
            else if(strcmp(prm, "SOFTENING") == 0) SOFTENING = atof(prm_val);
            else if(strcmp(prm, "G") == 0) G = atof(prm_val);
            else if(strcmp(prm, "NUM_STEPS") == 0) NUM_STEPS = atol(prm_val);
            else if(strcmp(prm, "TEND") == 0) TEND = atol(prm_val);
            else if(strcmp(prm, "TOTAL_MASS") == 0) TOTAL_MASS = atof(prm_val);
            else if(strcmp(prm, "SNAPSHOT_FREQUENCY") == 0) SNAPSHOT_FREQUENCY = atol(prm_val);
            else if(strcmp(prm, "OUTPUT_FORMAT") == 0) strcpy(OUTPUT_FORMAT, prm_val);
            else
            {
                fprintf(stdout, "Error! Unknown parameter %s at line %d\n", prm, linenum);
                exit(EXIT_FAILURE);
            } 

            tok = strtok(NULL, " ");
            count += 1;
        }
    }

    printf("G: %f\n", G);
    printf("SOF: %f\n", SOFTENING);
    printf("NUM_PAR: %ld\n", NUM_PARTICLES);
    printf("OUT_FOR: %s\n", OUTPUT_FORMAT);
    printf("NUM_STP: %ld\n", NUM_STEPS);

    fclose(file);
}


int main()
{

    read_params(filename);

    return 0;
}
