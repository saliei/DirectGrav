#ifndef IO_H
#define IO_H

#define MAX_LINE_LENGTH 256
#define MAX_PARAM_LENGTH 128
#define MAX_FILE_NAME_LENGTH 128
#define MAX_DATA_FORMAT_LENGTH 8

extern char const *PARAM_FILE_NAME;
extern char const *DATADIR;

long int NUM_PARTICLES;
double SOFTENING;
double G;
double TOTAL_MASS;
long int NUM_STEPS;
long int TEND;
unsigned int SNAPSHOT_FREQUENCY;
char OUTPUT_FORMAT[MAX_DATA_FORMAT_LENGTH];

void read_params();
void snapshot(double *pos, double *vel, double *massf, int step);

#endif
