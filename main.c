#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "io.h"

void init(double *pos, double *vel, double *mass)
{
    int i;
    float LIMIT = 1.0;

    /*TODO: set up a box limit*/
    for(i = 0; i < NUM_PARTICLES; i++)
    {
        pos[3 * i]   = ((float)rand() / (float)(RAND_MAX)) * LIMIT;
        pos[3 * i+1] = ((float)rand() / (float)(RAND_MAX)) * LIMIT;
        pos[3 * i+2] = ((float)rand() / (float)(RAND_MAX)) * LIMIT;

        vel[3 * i]   = ((float)rand() / (float)(RAND_MAX)) * LIMIT;
        vel[3 * i+1] = ((float)rand() / (float)(RAND_MAX)) * LIMIT;
        vel[3 * i+2] = ((float)rand() / (float)(RAND_MAX)) * LIMIT;

        mass[i] = TOTAL_MASS * 1.0 / NUM_PARTICLES;
    }
}

void acceleration(double *pos, double * mass, double *acc)
{
    int i, j;
    double dx, dy, dz;
    double inv_r3;

    /*TODO: SoA data structure.*/
    for(i = 0; i < NUM_PARTICLES; i++)
        for(j = 0; j < NUM_PARTICLES; j++)
        {
            dx = pos[3 * j]   - pos[3 * i];
            dy = pos[3 * j+1] - pos[3 * i+1];
            dz = pos[3 * j+2] - pos[3 * i+2];

            inv_r3 = pow((dx*dx + dy*dy + dz*dz + SOFTENING*SOFTENING),-1.5);

            acc[3 * i]   += G * (dx * inv_r3) * mass[j];
            acc[3 * i+1] += G * (dy * inv_r3) * mass[j];
            acc[3 * i+2] += G * (dz * inv_r3) * mass[j];

        }
}

int main(){

    int step, i;
    double t = 0.0;

    /*read in global parameters*/
    read_params();
          
    double dt = TEND / NUM_STEPS;

    double *pos  = (double*)malloc(NUM_PARTICLES * 3 * sizeof(double));
    double *vel  = (double*)malloc(NUM_PARTICLES * 3 * sizeof(double));
    double *acc  = (double*)malloc(NUM_PARTICLES * 3 * sizeof(double));
    double *mass = (double*)malloc(NUM_PARTICLES * 1 * sizeof(double));

    srand((unsigned int)time(NULL));
    init(pos, vel, mass);
    
    double mvx = 0.0, mvy = 0.0, mvz = 0.0;
    double tm = 0.0;
    for(i = 0; i < NUM_PARTICLES; i++)
    {
       mvx += mass[i] * vel[3 * i];
       mvy += mass[i] * vel[3 * i+1];
       mvz += mass[i] * vel[3 * i+2];
       tm += mass[i];
    }

    /*change to center of mass frame*/
    double vcomx = 0.0, vcomy = 0.0, vcomz = 0.0;
    vcomx = mvx / tm;
    vcomy = mvy / tm;
    vcomz = mvz / tm;

    for( i = 0; i < NUM_PARTICLES; i++ )
    {
        vel[3 * i]   -= vcomx;
        vel[3 * i+1] -= vcomy;
        vel[3 * i+2] -= vcomz;
    }

    
    acceleration(pos, mass, acc);

    for(step = 0; step < NUM_STEPS; step++)
    {
        for(i = 0; i < NUM_PARTICLES; i++)
        {
            vel[3 * i]   += acc[3 * i] * dt / 2.0;
            vel[3 * i+1] += acc[3 * i] * dt / 2.0;
            vel[3 * i+2] += acc[3 * i] * dt / 2.0;
        }

        for(i = 0; i < NUM_PARTICLES; i++)
        {
            pos[3 * i]   += vel[3 * i]   * dt;
            pos[3 * i+1] += vel[3 * i+1] * dt;
            pos[3 * i+2] += vel[3 * i+2] * dt;
        }
       
        acceleration(pos, mass, acc); 

        for(i = 0; i < NUM_PARTICLES; i++)
        {
            vel[3 * i]   += acc[3 * i]   * dt / 2.0;
            vel[3 * i+1] += acc[3 * i+1] * dt / 2.0;
            vel[3 * i+2] += acc[3 * i+2] * dt / 2.0;
        }
        
        if( step % SNAPSHOT_FREQUENCY == 0 ) snapshot(pos, vel, mass, step);

        t += dt;
    }

    free(pos);
    free(vel);
    free(acc);
    free(mass);
    
    return 0;
}
