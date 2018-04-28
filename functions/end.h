#ifndef END
#define END

// Gets called after the game loop is over
void end(void)
{
	// Print "game over" to bottom-right
	char over[] = "Game over";
	int i = strlen(over) - 1;
	int x = RES_X - 1;
	for (; i >= 0; i--)
	{
		cmd_write(x--, RES_Y, over[i]);
	}
	// Move cmd cursor to bottom
	cmd_write(0, RES_Y + 1, ' ');
}

#endif