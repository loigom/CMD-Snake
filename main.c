/*

TODO

1. Improve documentation and consistency.
2. Console window size needs checking.
3. Always show score while playing.
4. Make the game go faster as the score gets higher.

*/


// Dependencies and global constants
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define RES_X 40
#define RES_Y 20
#define DELAY_MS 100

#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4

#define FOOD_SYMBOL 'O'

// Structures
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

// Functions and the rest

// Write to target console buffer using coordinates
void c_write(int x, int y, char c)
{
	COORD coord = { x, y };
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, coord);
	putchar(c);
}
// Read from target console buffer using coordinates
char c_read(int x, int y)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	char out;
	DWORD len = sizeof(TCHAR);
	COORD coord = { x, y };
	long unsigned int num_read;

	ReadConsoleOutputCharacter(h, &out, len, coord, &num_read);
	return out;
}

void setup(struct Snake *snake, struct Coords *food)
{
	// Draw the initial grid
	system("cls");
	int x, y;
	for (x = 0; x < RES_X; x++)
	{
		putchar('#');
	}
	putchar('\n');
	for (y = 1; y < RES_Y-1; y++)
	{
		putchar('#');
		for (x = 1; x < RES_X-1; x++)
		{
			putchar(' ');
		}
		putchar('#');
		putchar('\n');
	}
	for (x = 0; x < RES_X; x++)
	{
		putchar('#');
	}

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
	// Did the snek drive into itself or a wall?
	c = c_read(snake->head.x, snake->head.y);
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
		c_write(food->x, food->y, FOOD_SYMBOL);
	}
	c_write(snake->head.x, snake->head.y, snake->symbol);
	return playing;
}

int main(void)
{
	srand(time(NULL));
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

	system("cls");
	puts("Game over\n");
	printf("Score: %d\n", snake.tail_len);
	printf("Exiting in 5s\n");
	Sleep(5000);
}