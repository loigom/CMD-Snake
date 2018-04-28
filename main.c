#include <stdio.h>
#include <time.h>
#include <conio.h>

#include "constants.h"
#include "structs.h"
#include "functions/cmdio.h"
#include "functions/setup.h"
#include "functions/input.h"
#include "functions/process.h"
#include "functions/end.h"

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