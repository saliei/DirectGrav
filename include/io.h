#include <stdlib.h>
#include <stdio.h>
#include <string.h>

long int NUM_PARTICLES;
double SOFTENING;
double G;
double TOTAL_MASS;
long int NUM_STEPS;
unsigned int SNAPSHOT_FREQUENCY;
char OUTPUT_FORAMT[10];

void read_params(char *filename);
