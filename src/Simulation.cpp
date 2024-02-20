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

    //create simulation engine
    this->se = SimulationEngine(100, 100);
    
};

Simulation::~Simulation(){};

void Simulation::createParticles(int n){

    if(n > MaxNoParticles){
        perror("Too many particles to create!\n");
        exit(1);
    }

    float r = 5.0f;
    float mass = 1.0f;
    for(int i=0;i<n;i++){
        //random position
        int x_win = rand() % (window_width - 2*(int)r) + (int)r;
        int y_win = rand() % (window_height - 2*(int)r) + (int)r;
        Particle* p = new Particle(x_win, y_win, 0.0f, 0.0f, r, mass, window, sf::Color::Green);
        se.addParticle(p);
    }
};


void Simulation::createParticlesInCircle(int x, int y, int r, int n){
    int counter = 0;
    while(counter < n){
        //polar coordinate system
        int ri = random() % r;
        int theta = random() % 360;
        //convert to Cartesian
        int xi = x + ri * cos(theta * M_PI / 180);
        int yi = y + ri * sin(theta * M_PI / 180);
        //check position
        if(xi > 0 && xi < window_width && yi > 0 && yi < window_height){
            Particle* p = new Particle(xi, yi, 0.0f, 0.0f, 5.0f, 1.0f, window, sf::Color::Green);
            se.addParticle(p);
            counter++;
        }

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
            if(event.type == sf::Event::Closed) {
                gameFlag = false;
                window->close();
            }
            //LPM pressed - add particles
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
                createParticlesInCircle(mousePosition.x, mousePosition.y, 30, 2);
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