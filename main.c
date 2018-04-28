/* Dependencies and global constants */
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define RES_X 40
#define RES_Y 20
#define DELAY_MS 90

#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4

#define FOOD_SYMBOL 'O'

/* Structures */
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

/* Function headers */
// Write to target console buffer using coordinates
void c_write(int x, int y, char c);
// Read from target console buffer using coordinates
char c_read(int x, int y);
// Draw the initial grid, initialize structures, initial drawing
void setup(struct Snake *snake, struct Coords *food);
// Process input, if keyboard was hit
void input(struct Snake *snake);
// Logic
int process(struct Snake *snake, struct Coords *food);
// Program end
void end(void);

/* */
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

void c_write(int x, int y, char c)
{
	COORD coord = { x, y };
	COORD bottom_left = { 0, RES_Y + 1 };
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, coord);
	putchar(c);
}

char c_read(int x, int y)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	char out;
	COORD coord = { x, y };
	long unsigned int num_read;
	ReadConsoleOutputCharacter(h, &out, 1, coord, &num_read);
	return out;
}

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
	c_write(snake->head.x, snake->head.y, snake->symbol);
	c_write(food->x, food->y, FOOD_SYMBOL);
}

void input(struct Snake *snake)
{
	if (kbhit())
	{
		switch (getch())
		{
			case 'a':
				if (snake->direction != RIGHT)
				{
					snake->direction = LEFT;
					snake->symbol = '<';
				}
				break;
			case 'd':
				if (snake->direction != LEFT)
				{
					snake->direction = RIGHT;
					snake->symbol = '>';
				}
				break;
			case 'w':
				if (snake->direction != DOWN)
				{
					snake->direction = UP;
					snake->symbol = '^';
				}
				break;
			case 's':
				if (snake->direction != UP)
				{
					snake->direction = DOWN;
					snake->symbol = 'v';
				}
				break;
		}
	}
}

int process(struct Snake *snake, struct Coords *food)
{
	int playing = 1;
	int i;
	char c;
	// Append current coordinates to timeout queue
	snake->tail[snake->tail_len].x = snake->head.x;
	snake->tail[snake->tail_len].y = snake->head.y;
	// Timeout oldest tail part
	c_write(snake->tail[0].x, snake->tail[0].y, ' ');
	// Shift array to the left
	for (i = 1; i <= snake->tail_len; i++)
	{
		snake->tail[i-1].x = snake->tail[i].x;
		snake->tail[i-1].y = snake->tail[i].y;
	}
	// Move snake's coordinates, but don't draw it to console just yet
	switch(snake->direction)
	{
		case LEFT:
			snake->head.x--;
			break;
		case RIGHT:
			snake->head.x++;
			break;
		case UP:
			snake->head.y--;
			break;
		case DOWN:
			snake->head.y++;
			break;
	}
	// Now read the console at these new coordinates
	c = c_read(snake->head.x, snake->head.y);
	// Did the snek drive into itself or a wall?
	if (c != ' ' && c != FOOD_SYMBOL)
	{
		playing = 0;
	}
	// Did snek eat food?
	else if (c == FOOD_SYMBOL)
	{
		snake->tail_len++;
		food->x = rand() % (RES_X - 2) + 1; // Taking the borders into consideration
		food->y = rand() % (RES_Y - 2) + 1;
		// Update score
		char converted[5] = { 0 };
		itoa(snake->tail_len, converted, 10);
		i = 0;
		while (converted[i])
		{
			c_write(6 + i, RES_Y, converted[i++]);
		}
	}
	c_write(snake->head.x, snake->head.y, snake->symbol);
	c_write(food->x, food->y, FOOD_SYMBOL);
	return playing;
}

void end(void)
{
	// Print "game over" to bottom-right
	char over[] = "Game over";
	int i = strlen(over) - 1;
	int x = RES_X - 1;
	for (; i >= 0; i--)
	{
		c_write(x--, RES_Y, over[i]);
	}
	// Move cmd cursor to bottom
	c_write(0, RES_Y + 1, ' ');
}