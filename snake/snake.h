#ifndef SNAKE
#define SNAKE

struct Coords
{
	int x, y;
};

struct Snake
{
	struct Coords head;
	struct Coords tail[RES_X * RES_Y];
	int tail_len;
	int direction;
	char symbol;
};

// Draw the initial grid, initialize structures, initial drawing
void setup(struct Snake *snake, struct Coords *food);
// Process the keyboard IF a button was hit
void input(struct Snake *snake);
// Core logic of the game itself
int process(struct Snake *snake, struct Coords *food);
// Gets called after the game loop is over
void end(void);

#endif