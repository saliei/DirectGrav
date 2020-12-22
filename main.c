#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define N 1000
#define softening 0.01
#define G  1.0
#define num_steps 1000
#define tEnd 10000
#define TOTAL_MASS 20.0
#define nsnapshot 50

void snapshot(double *pos, double *vel, double *mass, double t, int step)
{
    FILE *posf, *velf, *massf;
    char posfbuf[100], velfbuf[100], massfbuf[100];
    int i;
    struct stat st = {0}; 
    
    if (stat("./data", &st) == -1){
        mkdir("./data", 0700);
    }

    snprintf(posfbuf, sizeof posfbuf, "./data/positions-%d.dat", step);
    snprintf(velfbuf, sizeof velfbuf, "./data/velocities-%d.dat", step);
    snprintf(massfbuf, sizeof massfbuf, "./data/mass-%d.dat", step);


    posf = fopen(posfbuf, "w");
    velf = fopen(velfbuf, "w");
    massf = fopen(massfbuf, "w");

    if (posf == NULL || velf == NULL || massf == NULL)
    {
        fprintf(stdout, "Error on opening one of the files.");
        exit(1);
    }

    fprintf(posf, "t = %f  X------------Y-------------Z\n", t);
    fprintf(velf, "t = %f  Vx-----------Vy-----------Vz\n", t);
    fprintf(massf, "t = %f  mass\n", t);
    for(i = 0; i < N; i++)
    {
        fprintf(posf, "%f           %f           %f\n", pos[3*i], pos[3*i+1], pos[3*i+2]);
        fprintf(velf, "%f           %f           %f\n", vel[3*i], vel[3*i+1], vel[3*i+2]);
        fprintf(massf, "%f\n", mass[i]);
    }
}

void init(double *pos, double *vel, double *mass)
{
    int i;
    float L = 1.0;

    for(i = 0; i < N; i++)
    {
        pos[3*i]     = ((float)rand() / (float)(RAND_MAX)) * L;
        pos[3*i + 1] = ((float)rand() / (float)(RAND_MAX)) * L;
        pos[3*i + 2] = ((float)rand() / (float)(RAND_MAX)) * L;

        vel[3*i]     = ((float)rand() / (float)(RAND_MAX)) * L;
        vel[3*i + 1] = ((float)rand() / (float)(RAND_MAX)) * L;
        vel[3*i + 2] = ((float)rand() / (float)(RAND_MAX)) * L;

        mass[i] = TOTAL_MASS * 1.0 / N;
    }

}

void acceleration(double *pos, double * mass, double *acc)
{
    int i, j;
    double dx, dy, dz;
    double inv_r3;
// TODO: SoA data structure.
    for(i = 0; i < N; i++)
        for(j = 0; j < N; j++)
        {
            dx = pos[3*j] - pos[3*i];
            dy = pos[3*j+1] - pos[3*i+1];
            dz = pos[3*j+2] - pos[3*i+2];

            inv_r3 = pow((dx*dx + dy*dy + dz*dz + softening*softening),-1.5);

            acc[3*i]   += G * (dx * inv_r3) * mass[j];
            acc[3*i+1] += G * (dy * inv_r3) * mass[j];
            acc[3*i+2] += G * (dz * inv_r3) * mass[j];

        }
}

int main(){
     int i;
     double t, dt = tEnd / num_steps;
     int step;
    double* pos = (double*)malloc(N*3*sizeof(double));
    double* vel = (double*)malloc(N*3*sizeof(double));
    double* acc = (double*)malloc(N*3*sizeof(double));
    double* mass = (double*)malloc(N*1*sizeof(double));

    //INITI
    srand((unsigned int)time(NULL));
    init(pos, vel, mass);
    
    acceleration(pos, mass, acc);

    for(step = 0; step < num_steps; step++)
    {
        /*fprintf(stdout, "vel[0]: %f, pos[0]: %f\n", pow(vel[0]*vel[0]+vel[1]*vel[1]+vel[2]*vel[2], 0.5), pow(pos[0]*pos[0]+pos[1]*pos[1]+pos[2]*pos[2], 0.5));*/
        for(i = 0; i < N; i++)
        {
            vel[3*i]   += acc[3*i] * dt/2.0;
            vel[3*i+1] += acc[3*i] * dt/2.0;
            vel[3*i+2] += acc[3*i] * dt/2.0;
        }

        for(i = 0; i < N; i++)
        {
            pos[3*i]   += vel[3*i]   * dt;
            pos[3*i+1] += vel[3*i+1] * dt;
            pos[3*i+2] += vel[3*i+2] * dt;
        }
       
        acceleration(pos, mass, acc); 

        for(i = 0; i < N; i++)
        {
            vel[3*i]   += acc[3*i]     * dt/2.0;
            vel[3*i+1] += acc[3*i + 1] * dt/2.0;
            vel[3*i+2] += acc[3*i + 2] * dt/2.0;
        }
        
        if( step % nsnapshot == 0 ) snapshot(pos, vel, mass, t, step);

        t += dt;


    }

    free(pos);
    free(vel);
    free(acc);
    free(mass);
    
    return 0;

}
