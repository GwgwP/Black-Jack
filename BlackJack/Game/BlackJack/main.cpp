#include "sgg/graphics.h"
#include "defines.h"
#include "Game.h"
#include <string>
#include <chrono> 


void draw() 
{
	Game* game = Game::getInstance();
	game->draw();
};

void update(float ms) 
{
	Game* game = Game::getInstance();
	game->update();
};

int main(int argc, char ** argv)
{
	graphics::createWindow(700, 600, "BlackJack");

	srand(time(0));  //randomize deck of cards

	Game* game = Game::getInstance();
	
	graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
	
	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);
	
	graphics::startMessageLoop();

	
	Game::releaseInstance();

	return 0;
}