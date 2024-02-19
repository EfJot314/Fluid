#include "interfaces.h"

using namespace std;

SimulationEngine::SimulationEngine(){
    nOfParticles = 0;
    this->particles = vector<Particle*>(0);

    nX = 5;
    nY = 5;
    this->sectors = vector<vector<vector<Particle*>>>(nX, vector<vector<Particle*>>(nY, vector<Particle*>(0)));
};


SimulationEngine::SimulationEngine(int nx, int ny){
    nOfParticles = 0;
    this->particles = vector<Particle*>(0);

    nX = nx;
    nY = ny;
    this->sectors = vector<vector<vector<Particle*>>>(nX, vector<vector<Particle*>>(nY, vector<Particle*>(0)));
};


SimulationEngine::~SimulationEngine(){};


void SimulationEngine::moveAll(int width, int height){
    //memory allocation
    vector<float*> accelerations(nOfParticles);
    //assign particles to sectors
    int dx = width / nX;
    int dy = height / nY;
    for(Particle* particle : particles){
        int i = particle->getPositionX() / dx;
        int j = particle->getPositionY() / dy;
        if(i < 0)
            i = 0;
        if(i >= nX)
            i = nX-1;
        if(j < 0)
            j = 0;
        if(j >= nY)
            j = nY-1;
        sectors[i][j].push_back(particle);
    }
    //get accelerations
    for(int i=0;i<nOfParticles;i++){
        accelerations.at(i) = getAcceleration(i);
    }
    //update position and velocity of each planet
    for(int i=0;i<nOfParticles;i++){
        particles[i]->updateKinematicProperties(accelerations[i], width, height);
    }   
    //clear sectors
    for(int i=0;i<nX;i++){
        for(int j=0;j<nY;j++){
            sectors[i][j].clear();
        }
    }
    //free memory
    for(int i=0;i<nOfParticles;i++)
        delete accelerations[i];
};


float* SimulationEngine::getAcceleration(int particleId){
    //accelerations
    float ax = 0;
    float ay = g;
    //particle position
    float xp = particles[particleId]->getPositionX();
    float yp = particles[particleId]->getPositionY();
    //create structure to return
    float* acceleration = new float[2];
    acceleration[0] = ax;
    acceleration[1] = ay;
    //return
    return acceleration;

}



void SimulationEngine::addParticle(Particle* particle){
    if(nOfParticles < MaxNoParticles){
        particles.push_back(particle);
        nOfParticles++;
    }
};

Particle* SimulationEngine::getParticle(int i){
    return particles[i];
};


