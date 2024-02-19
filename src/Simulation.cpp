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

void Simulation::createParticles(int n){

    if(n > MaxNoParticles){
        perror("Too big requested number of particles to create!\n");
        exit(1);
    }

    float r = 5.0f;
    float mass = 1.0f;
    for(int i=0;i<n;i++){
        //random position
        int x_win = rand() % window_width;
        int y_win = rand() % window_height;
        Particle* p = new Particle(x_win, y_win, 0.0f, 0.0f, r, mass, window, sf::Color::Green);
        se.addParticle(p);
    }

};


void Simulation::drawAll(){
    sf::RectangleShape background(sf::Vector2f(window_width, window_height));
    background.setFillColor(sf::Color::Black);

    window->clear();

    //draw background
    window->draw(background);

    //draw all particles
    int i = 0;
    Particle* curr = se.getParticle(i);
    while(curr != NULL){
        curr->draw();
        i++;
        curr = se.getParticle(i);
    }

    window->display();
};



void Simulation::run(){

    

    //main loop
    std::chrono::high_resolution_clock::time_point frameStartTime = std::chrono::high_resolution_clock::now();
    while(gameFlag){

        //update widow size variables
        window_width = window->getSize().x;
        window_height = window->getSize().y;

        //drawing all
        drawAll();

        //moving all objects
        se.moveAll(window_width, window_height);
        
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