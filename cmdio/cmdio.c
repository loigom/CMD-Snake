#include <windows.h>
#include <stdio.h>
#include "..\config.h"
#include "cmdio.h"

// Write a char to the cmd prompt using coordinates
void cmd_write(int x, int y, char c)
{
	COORD coord = { x, y };
	COORD bottom_left = { 0, RES_Y + 1 };
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, coord);
	putchar(c);
}

// Read a char from the cmd prompt using coordinates
char cmd_read(int x, int y)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	char out;
	COORD coord = { x, y };
	long unsigned int num_read;
	ReadConsoleOutputCharacter(h, &out, 1, coord, &num_read);
	return out;
}