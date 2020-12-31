#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

void read_params(char *filename)
{
    FILE *file;
    char line[MAX_LINE_LENGTH];
    char prm[MAX_LINE_LENGTH], prm_val[MAX_LINE_LENGTH];
    char *tok;
    int count;

    file = fopen(filename, "r");
    if(file == NULL)
    {
        fprintf(stdout, "Error on reading parameter file!\n");
        exit(EXIT_FAILURE);
    }
    
    while( fgets(line, MAX_LINE_LENGTH, file) != NULL )
    {
        count = 0;
        tok = strtok(line, " ");

        while(tok != NULL)
        {
            if(count == 0) strncpy(prm, tok, MAX_LINE_LENGTH);
            else if(count == 1) strncpy(prm_val, tok, MAX_LINE_LENGTH);
            else fprintf(stdout ,"WARNING! Potentially erroneous parameter file!\n");
            tok = strtok(NULL, " ");
            count += 1;
            
        }

        printf("prm: %s\n", prm);
        printf("prm_val: %s\n", prm_val);

        
    }
    
}


/*int main()*/
/*{*/
    /*read_params("param.in");*/

    /*return 0;*/
/*}*/
