#include "interfaces.h"


Particle::Particle(){};

Particle::~Particle(){};

Particle::Particle(float realX, float realY, float vx, float vy, float radius, float mass, sf::RenderWindow* window, sf::Color color){
    this->window = window;
    this->color = color;
    position = (float*)malloc(2*sizeof(float));
    position[0] = realX;
    position[1] = realY;
    velocity = (float*)malloc(2*sizeof(float));
    velocity[0] = vx;
    velocity[1] = vy;
    r = radius;
    m = mass;
};

void Particle::updatePositionOnWindow(){
    //in the future here will be setting x,y connected with actual width, height and zoom of the window
    int width = window->getSize().x;
    int height = window->getSize().y;
    x = (int)position[0]/scaler;
    y = (int)position[1]/scaler;
};

float Particle::getMass(){
    return m;
};

float Particle::getPositionX(){
    return position[0];
}

float Particle::getPositionY(){
    return position[1];
}

void Particle::updateKinematicProperties(float* acceleration){
    //update velocity
    velocity[0] += acceleration[0] * deltaTime;
    velocity[1] += acceleration[1] * deltaTime;
    //update position
    position[0] += velocity[0] * deltaTime;
    position[1] += velocity[1] * deltaTime;
}


void Particle::draw(){
    //update positions of planet
    updatePositionOnWindow();

    //creating circle shape, setting radius and position
    sf::CircleShape circle(r/scaler, 100);
    circle.setPosition((int)(x-r/scaler), (int)(y-r/scaler));   

    //planet color
    circle.setFillColor(color);

    //drawing on the window
    window->draw(circle);

}







