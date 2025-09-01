#include <stdlib.h>
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

struct MissileParams {
    float MASS;

    float PERP_SPEED;
    float THETA;

    float CENTRAL_SPEED;
    float HEIGHT;

    float AZI_SPEED;
    float PHI;

};

struct EarthParams {
    float RADIUS;
    float GRAVITY;
    float TIMESTEP;
}; 

void sim_step(struct MissileParams *params, struct EarthParams earth_params) {

    ///for central 
    params->CENTRAL_SPEED = params->CENTRAL_SPEED + earth_params.TIMESTEP * (-9.81);
    params->HEIGHT = params->HEIGHT + earth_params.TIMESTEP * params->CENTRAL_SPEED;
    
    ///for perp 
    float theta_ang_speed = params->PERP_SPEED / params->HEIGHT;
    params->THETA = params->THETA + theta_ang_speed * earth_params.TIMESTEP;

    ///for azi
    float phi_ang_speed = params->AZI_SPEED / params->HEIGHT;
    params->PHI = params->PHI + phi_ang_speed * earth_params.TIMESTEP;

};

struct MissileParams *simulate(struct MissileParams *missile_params, float time, struct EarthParams earth_params) {
    
    float current_time = 0;
    float timestep_count = time/earth_params.TIMESTEP;
    int current_step= 0;

    struct MissileParams *results = malloc(timestep_count*sizeof(struct MissileParams));
    struct MissileParams *current_result = results;

    while (current_step<timestep_count)
    {
        sim_step(missile_params, earth_params);
        *current_result = *missile_params;

        current_result++;
        current_step++;
        current_time = current_time + earth_params.TIMESTEP;
    }
    
    return results;
}

#endif