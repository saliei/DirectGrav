#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define MAX_PARAM_LENGTH 128

char const *filename = "params.in";

long int NUM_PARTICLES;
double SOFTENING;
double G;
double TOTAL_MASS;
long int NUM_STEPS;
long int TEND;
unsigned int SNAPSHOT_FREQUENCY;
char OUTPUT_FORMAT[MAX_PARAM_LENGTH];

void read_params(char const *filename);
