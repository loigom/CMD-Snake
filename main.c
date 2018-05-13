#include <windows.h> // Sleep()
#include "config.h"
#include "snake.h"   // setup() input() process() end() and structs

int main(void)
{
	int playing = 1;
	struct Snake snake;
	struct Coords food;
	setup(&snake, &food);

	while (playing)
	{
		input(&snake);
		playing = process(&snake, &food);
		Sleep(DELAY_MS);
	}

	end();
}