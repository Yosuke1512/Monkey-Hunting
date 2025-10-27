#include <SDL3/SDL.h>
#include "simulator.hpp"

int main(int argc, char *argv[]) {
    Simulator sim;
    bool success = sim.Init();
    if(success) {
        sim.RunLoop();
    }
    sim.Shutdown();

    return 0;
}