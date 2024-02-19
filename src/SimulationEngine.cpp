#include "interfaces.h"


SimulationEngine::SimulationEngine(){
    nOfParticles = 0;
    this->particles = (Particle**)calloc(MaxNoParticles, sizeof(Particle));
};


SimulationEngine::~SimulationEngine(){};


void SimulationEngine::moveAll(int width, int height){
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
    float ay = g;
    //particle position
    float xp = particles[particleId]->getPositionX();
    float yp = particles[particleId]->getPositionY();
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


