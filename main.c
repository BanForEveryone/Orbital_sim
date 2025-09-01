#include <stdio.h>
#include "definitions.h"
#include <stdlib.h>



int main() {
    char mystr;

    struct EarthParams current_earth_params;
    current_earth_params.RADIUS = 6370e3;
    current_earth_params.GRAVITY = 9.81;
    current_earth_params.TIMESTEP = 0.01;

    struct MissileParams current_missile_params;
    current_missile_params.HEIGHT = 6900e3;
    current_missile_params.PHI = 0.5;
    current_missile_params.THETA = 0.5;

    current_missile_params.CENTRAL_SPEED = 0;
    current_missile_params.AZI_SPEED = 0;
    current_missile_params.PERP_SPEED = 220000;

    current_missile_params.MASS = 200;
    
    struct MissileParams *current_missile_params_ptr = &current_missile_params;


    float sim_time = 500;
    struct MissileParams *ptr = simulate(current_missile_params_ptr,sim_time,current_earth_params);
    
    ///attempt to open a file
    float timestep_count = sim_time/current_earth_params.TIMESTEP;
    

    FILE *clrfptr = fopen("results.txt", "w");
    fclose(clrfptr);

    FILE *fptr = fopen("results.txt", "a");
    
    fprintf(fptr, "HEIGHT;THETA;PHI;CENTRAL_SPEED;PERP_SPEED;AZI_SPEED \n");

    for(int i=1;i<timestep_count;i++) {

        
        fprintf(fptr,"%f;%f;%f;%f;%f;%f\n", ptr->HEIGHT,ptr->THETA,ptr->PHI, ptr->CENTRAL_SPEED, ptr->PERP_SPEED,ptr->AZI_SPEED);
        ptr++;
    }
    fclose(fptr);

    return 0;
}

