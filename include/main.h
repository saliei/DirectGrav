#ifndef MAIN_H
#define MAIN_H

#define DirectGrav_VERSION_MAJOR @DirectGrav_VERSION_MAJOR@
#define DirectGrav_VERSION_MINOR @DirectGrav_VERSION_MINOR@

#include "io.h"

void init(double *pos, double *vel, double *mass);
void acceleration(double *pos, double * mass, double *acc);

#endif
