#ifndef STRUCTS
#define STRUCTS

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

#endif