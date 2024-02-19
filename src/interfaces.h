#include <SFML/Graphics.hpp>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <math.h>
#include "constants.h"


class Particle{
    private:
        int x;
        int y;
        float* position;
        float* velocity;
        float r;
        float m;
        sf::Color color;
        sf::RenderWindow* window;
        void updatePositionOnWindow();
    public:
        Particle();
        Particle(float realX, float realY, float vx, float vy, float radius, float mass, sf::RenderWindow* window, sf::Color color);
        ~Particle();
        void draw();
        float getMass();
        float getPositionX();
        float getPositionY();
        void updateKinematicProperties(float* acceleration);
};



class SimulationEngine{
    private:
        int nOfParticles;
        Particle** particles;
    public:
        SimulationEngine();
        ~SimulationEngine();
        void moveAll(int width, int height);
        float* getAcceleration(int particleId);
        void addParticle(Particle* particle);
        Particle* getParticle(int i);
};



class Simulation{
    private:
        SimulationEngine se;
        int FPS;
        int window_width;
        int window_height;
        bool gameFlag;
        sf::RenderWindow* window;
        void drawAll();
    public:
        Simulation();
        Simulation(int width, int height);
        ~Simulation();
        void createParticles(int n);
        void run();
};

