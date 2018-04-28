#ifndef SETUP
#define SETUP

// Draw the initial grid, initialize structures, initial drawing
void setup(struct Snake *snake, struct Coords *food)
{
	// Seed the random integer generator
	srand(time(NULL));
	// Draw the initial grid
	system("cls");
	int x, y;
	// Top horizontal border
	for (x = 0; x < RES_X; x++)
	{
		putchar('#');
	}
	putchar('\n');
	// Sides
	for (y = 1; y < RES_Y - 1; y++)
	{
		putchar('#');
		for (x = 1; x < RES_X - 1; x++)
		{
			putchar(' ');
		}
		putchar('#');
		putchar('\n');
	}
	// Bottom horizontal border
	for (x = 0; x < RES_X; x++)
	{
		putchar('#');
	}
	putchar('\n');
	puts("Score: 0");

	// Configure the snake
	snake->head.x = RES_X / 2;
	snake->head.y = RES_Y / 2;
	snake->direction = RIGHT;
	snake->symbol = '>';
	snake->tail_len = 0;
	// Configure the food
	food->x = rand() % (RES_X - 2) + 1; // Taking the borders into consideration
	food->y = rand() % (RES_Y - 2) + 1;
	// Draw initial stuff
	cmd_write(snake->head.x, snake->head.y, snake->symbol);
	cmd_write(food->x, food->y, FOOD_SYMBOL);
}

#endif