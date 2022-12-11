#include <iostream>
#include "KUDA/window.h"
#include "game.h"

//walls 32x32 -> 64x32 | enemy 48x32 | stuff 32x32
//delete cmake builds before presentation

int main() {
	Game game;
	game.Start();
	return 0;
	/*
    std::cout<<"Working!"<<std::endl;
    return EXIT_SUCCESS;
    */
}