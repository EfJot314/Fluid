main:
	g++ -c main.cpp Simulation.cpp Particle.cpp SimulationEngine.cpp -I$(CURDIR)/SFML/sfml/include
	g++ Particle.o -o Particle SimulationEngine.o -o SimulationEngine Simulation.o -o Simulation main.o -o main -L$(CURDIR)/SFML/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system


clean:
	rm -f main main.o Vector2d Vector2d.o Particle Particle.o Simulation Simulation.o SimulationEngine SimulationEngine.o

all:
	make clean
	make main



