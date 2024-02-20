#include <SFML/Graphics.hpp>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <math.h>
#include <cmath>
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
        void updateKinematicProperties(float* acceleration, int width, int height);
};



class SimulationEngine{
    private:
        int nOfParticles;
        int nX, nY;
        std::vector<Particle*> particles;
        std::vector<std::vector<std::vector<Particle*>>> sectors;
    public:
        SimulationEngine();
        SimulationEngine(int nx, int ny);
        ~SimulationEngine();
        void moveAll(int width, int height);
        float* getAcceleration(Particle* particle, std::vector<Particle*> sectorParticles);
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
        void createParticlesInCircle(int x, int y, int r, int n);
        void run();
};

