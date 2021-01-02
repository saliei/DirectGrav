#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "../include/io.h"

char const *PARAM_FILE_NAME = "params.in";
char const *DATADIR = "data/";

void read_params()
{
    FILE *file;
    char line[MAX_LINE_LENGTH];
    char prm[MAX_PARAM_LENGTH], prm_val[MAX_PARAM_LENGTH];
    int  count, linenum = 0;
    char *tok;

    file = fopen(PARAM_FILE_NAME, "r");
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
            else if(strcmp(prm, "OUTPUT_FORMAT") == 0) 
            {
                int len = strlen(prm_val);
                prm_val[len-1] = '\0';
                strcpy(OUTPUT_FORMAT, prm_val);
            }
            else
            {
                fprintf(stdout, "Error! Unknown parameter %s at line %d\n", prm, linenum);
                exit(EXIT_FAILURE);
            } 

            tok = strtok(NULL, " ");
            count += 1;
        }
    }

    fclose(file);
}

void snapshot(double *pos, double *vel, double *mass, int step)
{
    FILE *posf, *velf, *massf;
    char posfbuf[MAX_FILE_NAME_LENGTH], velfbuf[MAX_FILE_NAME_LENGTH], massfbuf[MAX_FILE_NAME_LENGTH];
    struct stat st;
    int i;

    if (stat(DATADIR, &st) == -1) mkdir(DATADIR, 0700);

    snprintf(posfbuf,  sizeof posfbuf,   "%s/positions-%d.%s",  DATADIR, step, OUTPUT_FORMAT);
    snprintf(velfbuf,  sizeof velfbuf,   "%s/velocities-%d.%s", DATADIR, step, OUTPUT_FORMAT);
    snprintf(massfbuf, sizeof massfbuf,  "%s/mass-%d.%s",       DATADIR, step, OUTPUT_FORMAT);

    posf  = fopen(posfbuf,  "w");
    velf  = fopen(velfbuf,  "w");
    massf = fopen(massfbuf, "w");

    if (posf == NULL || velf == NULL || massf == NULL)
    {
        fprintf(stdout, "Error! Could not open one of the files to write.\n");
        exit(EXIT_FAILURE);
    }

    if(strcmp(OUTPUT_FORMAT, "dat") == 0)
    {
        fprintf(posf, "X            Y           Z\n");
        fprintf(velf, "Vx           Vy          Vz\n");
        fprintf(massf,"Mass");

        for(i = 0; i < NUM_PARTICLES; i++)
        {
            fprintf(posf, "%10f %15f %15f\n", pos[3*i], pos[3*i+1], pos[3*i+2]);
            fprintf(velf, "%10f %15f,%15f\n", vel[3*i], vel[3*i+1], vel[3*i+2]);
            fprintf(massf,"%10f\n", mass[i]);
        }
    }
    else if(strcmp(OUTPUT_FORMAT, "csv") == 0)
    {
        fprintf(posf, "X,           Y,          Z\n");
        fprintf(velf, "Vx,          Vy,         Vz\n");
        fprintf(massf,"Mass\n");

        for(i = 0; i < NUM_PARTICLES; i++)
        {
            fprintf(posf, "%10f, %15f, %15f\n", pos[3*i], pos[3*i+1], pos[3*i+2]);
            fprintf(velf, "%10f, %15f, %15f\n", vel[3*i], vel[3*i+1], vel[3*i+2]);
            fprintf(massf,"%8f\n", mass[i]);
        }
    }
    else if(strcmp(OUTPUT_FORMAT, "vtk") == 0)
    {
        fprintf(posf, "POSITION DATA\n");
        fprintf(posf, "ASCII\n");
        fprintf(posf, "DATASET STRUCTURED_POINTS\n");
        fprintf(posf, "DIMENSIONS %ld %ld %ld\n", NUM_PARTICLES, NUM_PARTICLES, NUM_PARTICLES);
        fprintf(posf, "ORGINI 0 0 0\n");
        fprintf(posf, "SPACING 1 1 1\n");
        fprintf(posf, "POINT_DATA %ld\n", NUM_PARTICLES);
        fprintf(posf, "SCALARS POSITION double\n");
        fprintf(posf, "LOOKUP_TABLE DEFAULT\n");

        for(i = 0; i < NUM_PARTICLES; i++)
        {
            fprintf(posf, "%10f %15f %15f\n", pos[3*i], pos[3*i+1], pos[3*i+2]);
            fprintf(velf, "%10f %15f %15f\n", vel[3*i], vel[3*i+1], vel[3*i+2]);
            fprintf(massf,"%10f\n", mass[i]);
        }
    }
    else
    {
        fprintf(stderr, "Error! Data dump format, '%s' is not implemented.\n", OUTPUT_FORMAT);
        exit(EXIT_FAILURE);
    }

    fclose(posf);
    fclose(velf);
    fclose(massf);
}

