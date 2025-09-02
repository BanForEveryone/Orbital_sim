#include <stdio.h>
#include "definitions.h"
#include <stdlib.h>
#include <time.h>



int main() {
    char mystr;

    struct EarthParams current_earth_params;
    current_earth_params.RADIUS = 6370e3;
    current_earth_params.GRAVITY = 9.8;
    current_earth_params.TIMESTEP = 0.01;

    struct MissileParams current_missile_params;
    current_missile_params.HEIGHT = 6400e3;
    current_missile_params.PHI = 0.5;
    current_missile_params.THETA = 0.5;

    current_missile_params.RADIAL_SPEED = 7000;
    current_missile_params.AZI_SPEED = 2100;
    current_missile_params.POLAR_SPEED = 9000;

    current_missile_params.MASS = 200;
    
    struct MissileParams *current_missile_params_ptr = &current_missile_params;


    float sim_time = 50000;

    ///
    clock_t begin = clock();
    struct MissileParams *ptr = simulate(current_missile_params_ptr,sim_time,current_earth_params);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%f",time_spent);
    ///

    ///attempt to open a file
    float timestep_count = sim_time/current_earth_params.TIMESTEP;
    

    FILE *clrfptr = fopen("results.txt", "w");
    fclose(clrfptr);

    FILE *fptr = fopen("results.txt", "a");
    
    fprintf(fptr, "HEIGHT;THETA;PHI;RADIAL_SPEED;POLAR_SPEED;AZI_SPEED \n");


    for(int i=1;i<timestep_count;i++) {

        
        fprintf(fptr,"%f;%f;%f;%f;%f;%f\n", ptr->HEIGHT,ptr->THETA,ptr->PHI, ptr->RADIAL_SPEED, ptr->POLAR_SPEED,ptr->AZI_SPEED);
        ptr++;
    }
    fclose(fptr);

    return 0;
}

