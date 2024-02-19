#include "interfaces.h"


int main()
{
    //for random numbers
    srand((unsigned) time(NULL));

    //start simulation
    Simulation sim(800, 600);
    sim.createParticles(100);
    sim.run();
  
    return 0;
}
