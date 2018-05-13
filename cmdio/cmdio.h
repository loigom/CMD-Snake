#ifndef CMDIO
#define CMDIO

// Write a char to the cmd prompt using coordinates
void cmd_write(int x, int y, char c);
// Read a char from the cmd prompt using coordinates
char cmd_read(int x, int y);

#endif