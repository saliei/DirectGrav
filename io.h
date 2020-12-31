#ifndef IO_H
#define IO_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define MAX_PARAM_LENGTH 128
#define MAX_FILE_NAME_LENGTH 128

char const *PARAM_FILE_NAME = "params.in";
char const *DATADIR = "data";

long int NUM_PARTICLES;
double SOFTENING;
double G;
double TOTAL_MASS;
long int NUM_STEPS;
long int TEND;
unsigned int SNAPSHOT_FREQUENCY;
char OUTPUT_FORMAT[MAX_PARAM_LENGTH];

void read_params(char const *filename);
void snapshot(double *pos, double *vel, double *massf, int step);

#endif
