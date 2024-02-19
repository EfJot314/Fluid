#include "interfaces.h"


SimulationEngine::SimulationEngine(){
    nOfParticles = 0;
    this->particles = (Particle**)calloc(MaxNoParticles, sizeof(Particle));
};

SimulationEngine::~SimulationEngine(){};

void SimulationEngine::moveAll(){
    //memory allocation
    float** accelerations = (float**)malloc(nOfParticles*sizeof(float*));
    //get accelerations
    for(int i=0;i<nOfParticles;i++){
        accelerations[i] = getAcceleration(i);
    }
    //update position and velocity of each planet
    for(int i=0;i<nOfParticles;i++){
        particles[i]->updateKinematicProperties(accelerations[i]);
    }   
    //free memory
    for(int i=0;i<nOfParticles;i++){
        free(accelerations[i]);
    }
    free(accelerations);
};


float* SimulationEngine::getAcceleration(int particleId){
    //accelerations
    float ax = 0;
    float ay = 0;
    //planet position
    float xp = particles[particleId]->getPositionX();
    float yp = particles[particleId]->getPositionY();
    //iterate on planets and add acceleration from each of them
    for(int i=0;i<nOfParticles;i++){
        //if it is the same then continue
        if(i == particleId)
            continue;
        //if everything is ok, then add to accelerations
        float x = particles[i]->getPositionX();
        float y = particles[i]->getPositionY();
        float mass = particles[i]->getMass();
        //R^2
        float Rsq = (xp-x)*(xp-x) + (yp-y)*(yp-y);
        //a = G*M/R^2
        float a = G * mass / Rsq;
        //apply sin() and cos() to get ax and ay
        ax += a * (x-xp)/sqrt(Rsq);
        ay += a * (y-yp)/sqrt(Rsq);
    }
    //create structure to return
    float* acceleration = (float*)malloc(2*sizeof(float));
    acceleration[0] = ax;
    acceleration[1] = ay;
    //return
    return acceleration;

}



void SimulationEngine::addParticle(Particle* particle){
    if(nOfParticles < MaxNoParticles){
        particles[nOfParticles] = particle;
        nOfParticles++;
    }
};

Particle* SimulationEngine::getParticle(int i){
    if(i < nOfParticles){
        return particles[i];
    }
    return NULL;
};


