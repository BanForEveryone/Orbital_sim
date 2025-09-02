#include <stdlib.h>
#include <math.h>
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

struct MissileParams {
    float MASS;

    float POLAR_SPEED;
    float THETA;

    float RADIAL_SPEED;
    float HEIGHT;

    float AZI_SPEED;
    float PHI;
    float FLIGHT_TIME;

};

struct EarthParams {
    float RADIUS;
    float GRAVITY;
    float TIMESTEP;
    float DRAG_COEFF;
}; 

float get_drag(float height, float speed) {
    float drag_coeff = 2;
    if (height>(6370e3 + 100000)) {
        return 0;

    }
    else {
        float density = 1.3 * exp((-height)/(7000));
        float drag_force = drag_coeff * density * pow(speed,2);
        
        if (speed>0) {
            return -drag_force;
        } 
        else {
            return drag_force;
        }
    } 
    ///RETURNS DRAG FORCE WITH RESPECT TO SIGN
}

float get_force(float height, float speed, float time) {

    return 0;
}

void sim_step_euler(struct MissileParams *params, struct EarthParams earth_params) {

    ///for central 
    params->RADIAL_SPEED = params->RADIAL_SPEED + earth_params.TIMESTEP * (-9.81);
    params->HEIGHT = params->HEIGHT + earth_params.TIMESTEP * params->RADIAL_SPEED;
    
    ///for perp 
    float theta_ang_speed = params->POLAR_SPEED / params->HEIGHT;
    params->THETA = params->THETA + theta_ang_speed * earth_params.TIMESTEP;

    ///for azi
    float phi_ang_speed = params->AZI_SPEED / params->HEIGHT;
    params->PHI = params->PHI + phi_ang_speed * earth_params.TIMESTEP;

};

void sim_step_rk4(struct MissileParams *params, struct EarthParams earth_params) {

    ///radial direction, let k be related to h, and l be related to v
    float k0 = params->RADIAL_SPEED * earth_params.TIMESTEP;
    float l0 =  earth_params.TIMESTEP *(-earth_params.GRAVITY +  ((get_drag(params->HEIGHT,params->RADIAL_SPEED))/(params->MASS))
    + get_force(params->HEIGHT,params->RADIAL_SPEED, params->FLIGHT_TIME) );

    float k1 = earth_params.TIMESTEP * (params->RADIAL_SPEED + (0.5*l0));
    float l1 = earth_params.TIMESTEP *(-earth_params.GRAVITY +  ((get_drag(params->HEIGHT+0.5*k0 ,params->RADIAL_SPEED+0.5*l0))/(params->MASS))
    + get_force(params->HEIGHT + 0.5*k0,params->RADIAL_SPEED+0.5*l0, params->FLIGHT_TIME + 0.5* earth_params.TIMESTEP )/(params->MASS) );

    float k2 = earth_params.TIMESTEP * (params->RADIAL_SPEED + (0.5*l1));
    float l2 = earth_params.TIMESTEP *(-earth_params.GRAVITY +  ((get_drag(params->HEIGHT+0.5*k1 ,params->RADIAL_SPEED+0.5*l1))/(params->MASS))
    + get_force(params->HEIGHT + 0.5*k1,params->RADIAL_SPEED+0.5*l1, params->FLIGHT_TIME + 0.5* earth_params.TIMESTEP )/(params->MASS) );
    
    float k3 = earth_params.TIMESTEP * (params->RADIAL_SPEED + (1.0*l2));
    float l3 = earth_params.TIMESTEP *(-earth_params.GRAVITY +  ((get_drag(params->HEIGHT+1.0*k2 ,params->RADIAL_SPEED+1.0*l2))/(params->MASS))
    + get_force(params->HEIGHT + 1.0*k2,params->RADIAL_SPEED+1.0*l2, params->FLIGHT_TIME + 1.0* earth_params.TIMESTEP )/(params->MASS) );

    


    ///radial direction, let p be related to theta, and n be related to v
    float p0 = (params->POLAR_SPEED) * earth_params.TIMESTEP;
    float n0 =  earth_params.TIMESTEP *((get_drag(params->HEIGHT,params->POLAR_SPEED)
    + get_force(params->HEIGHT,params->POLAR_SPEED, params->FLIGHT_TIME))/ (params->MASS));

    float p1 = earth_params.TIMESTEP * (params->POLAR_SPEED+ 0.5*n0);
    float n1 =  earth_params.TIMESTEP *((get_drag(params->HEIGHT,params->POLAR_SPEED+ 0.5*n0)
    + get_force(params->HEIGHT,params->POLAR_SPEED+ 0.5*n0, params->FLIGHT_TIME+0.5*earth_params.TIMESTEP))/(params->MASS));

    float p2 = earth_params.TIMESTEP * (params->POLAR_SPEED+ 0.5*n1);
    float n2 =  earth_params.TIMESTEP *((get_drag(params->HEIGHT,params->POLAR_SPEED+ 0.5*n1)
    + get_force(params->HEIGHT,params->POLAR_SPEED+ 0.5*n1, params->FLIGHT_TIME+0.5*earth_params.TIMESTEP))/(params->MASS));

    float p3 = earth_params.TIMESTEP * (params->POLAR_SPEED+ 1.0*n2);
    float n3 =  earth_params.TIMESTEP *((get_drag(params->HEIGHT,params->POLAR_SPEED+ 1.0*n2)
    + get_force(params->HEIGHT,params->POLAR_SPEED+ 1.0*n2, params->FLIGHT_TIME+1.0*earth_params.TIMESTEP))/(params->MASS));

    


    /// azimuthal direction, let a be related to theta, and s be related to v
    float a0 = (params->AZI_SPEED) * earth_params.TIMESTEP;
    float s0 =  earth_params.TIMESTEP *((get_drag(params->HEIGHT,params->AZI_SPEED)
    + get_force(params->HEIGHT,params->AZI_SPEED, params->FLIGHT_TIME))/ (params->MASS));

    float a1 = earth_params.TIMESTEP * (params->AZI_SPEED+ 0.5*s0);
    float s1 =  earth_params.TIMESTEP *((get_drag(params->HEIGHT,params->AZI_SPEED+ 0.5*s0)
    + get_force(params->HEIGHT,params->AZI_SPEED+ 0.5*s0, params->FLIGHT_TIME+0.5*earth_params.TIMESTEP))/(params->MASS));

    float a2 = earth_params.TIMESTEP * (params->AZI_SPEED+ 0.5*s1);
    float s2 =  earth_params.TIMESTEP *((get_drag(params->HEIGHT,params->AZI_SPEED+ 0.5*s1)
    + get_force(params->HEIGHT,params->AZI_SPEED+ 0.5*s1, params->FLIGHT_TIME+0.5*earth_params.TIMESTEP))/(params->MASS));

    float a3 = earth_params.TIMESTEP * (params->AZI_SPEED+ 1.0*s2);
    float s3 =  earth_params.TIMESTEP *((get_drag(params->HEIGHT,params->AZI_SPEED+ 1.0*s2)
    + get_force(params->HEIGHT,params->AZI_SPEED+ 1.0*s2, params->FLIGHT_TIME+1.0*earth_params.TIMESTEP))/(params->MASS));


    params->HEIGHT = params->HEIGHT + (k0 + 2*k1 +2*k2 + 2*k3)/6;
    params->RADIAL_SPEED = params->RADIAL_SPEED + (l0 + 2*l1 +2*l2 + 2*l3)/6;

    params->THETA = params->THETA + (p0 + 2*p1 + 2*p2 + p3)/(6*params->HEIGHT);
    params->POLAR_SPEED = params->POLAR_SPEED + (n0 + 2*n1 + 2*n2 + n3)/(6);

    params->PHI = params->PHI + (a0 + 2*a1 + 2*a2 + a3)/(6*params->HEIGHT);
    params->AZI_SPEED = params->AZI_SPEED + (s0 + 2*s1 + 2*s2 + s3)/(6);


}

struct MissileParams *simulate(struct MissileParams *missile_params, float time, struct EarthParams earth_params) {
    
    float current_time = 0;
    float timestep_count = time/earth_params.TIMESTEP;
    int current_step= 0;

    struct MissileParams *results = malloc(timestep_count*sizeof(struct MissileParams));
    struct MissileParams *current_result = results;

    while (current_step<timestep_count)
    {
        sim_step_rk4(missile_params, earth_params);
        *current_result = *missile_params;

        current_result++;
        current_step++;
        current_time = current_time + earth_params.TIMESTEP;

        if (missile_params->HEIGHT < earth_params.RADIUS) {
            break;
        }

    }
    
    return results;
}

#endif
