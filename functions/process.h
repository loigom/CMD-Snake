#ifndef PROCESS
#define PROCESS

// Core logic of the game itself
int process(struct Snake *snake, struct Coords *food)
{
	int playing = 1;
	int i;
	char c;
	// Append current coordinates to timeout queue
	snake->tail[snake->tail_len].x = snake->head.x;
	snake->tail[snake->tail_len].y = snake->head.y;
	// Timeout oldest tail part
	cmd_write(snake->tail[0].x, snake->tail[0].y, ' ');
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
	c = cmd_read(snake->head.x, snake->head.y);
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
			cmd_write(6 + i, RES_Y, converted[i++]);
		}
	}
	cmd_write(snake->head.x, snake->head.y, snake->symbol);
	cmd_write(food->x, food->y, FOOD_SYMBOL);
	return playing;
}

#endif