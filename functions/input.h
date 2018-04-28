#ifndef INPUT
#define INPUT

// Process the keyboard IF a button was hit
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

#endif