#include "interfaces.h"
#include <chrono>
#include <thread>




Simulation::Simulation(){};

Simulation::Simulation(int width, int height){
    gameFlag = true;
    window_width = width;
    window_height = height;
    FPS = 60;

    //create window
    window = new sf::RenderWindow(sf::VideoMode(window_width, window_height), "Fluid");
};

Simulation::~Simulation(){};


void Simulation::drawAll(){
    sf::RectangleShape background(sf::Vector2f(window_width, window_height));
    background.setFillColor(sf::Color::Black);

    window->clear();

    //draw background
    window->draw(background);

    //draw all planets
    int i = 0;
    Particle* curr = ge.getParticle(i);
    while(curr != NULL){
        curr->draw();
        i++;
        curr = ge.getParticle(i);
    }

    window->display();
};



void Simulation::run(){

    //create first experimental planets
    Particle p1(1500.0f, 1000.0f, 0.0f, 0.0f, 250.0f, 100000.0f, window, sf::Color::Yellow);
    Particle p2(2000.0f, 1000.0f, 0.0f, -15.0f, 100.0f, 10.0f, window, sf::Color::Green);

    ge.addParticle(&p1);
    ge.addParticle(&p2);

    //main loop
    std::chrono::high_resolution_clock::time_point frameStartTime = std::chrono::high_resolution_clock::now();
    while(gameFlag){

        //update widow size variables
        window_width = window->getSize().x;
        window_height = window->getSize().y;

        //drawing all
        drawAll();

        //moving all objects
        ge.moveAll();
        
        //handle events
        sf::Event event;
        while (window->pollEvent(event)) {
            //closing window
            if (event.type == sf::Event::Closed) {
                gameFlag = false;
                window->close();
            }
        }

        //clock and FPS control
        std::chrono::high_resolution_clock::time_point frameEndTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> frameDuration = frameEndTime - frameStartTime;
        std::chrono::duration<float> sleepDuration = std::chrono::duration<float, std::milli>(1000.0f / FPS) - frameDuration;
        std::this_thread::sleep_for(sleepDuration);
        frameStartTime = std::chrono::high_resolution_clock::now();


    }

    window->close();


};