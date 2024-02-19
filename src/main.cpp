#include "interfaces.h"


int main()
{
    //for random numbers
    srand((unsigned) time(NULL));

    //start game
    Simulation sim(800, 600);
    sim.run();
  
    return 0;
}
