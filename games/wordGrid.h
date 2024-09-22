#ifndef WORD_GRID
#define WORD_GRID

#define GRID_SIZE 10

void generate_random_grid(char grid[GRID_SIZE][GRID_SIZE]);
void display_grid(WINDOW *win, char grid[GRID_SIZE][GRID_SIZE], int start_y, int start_x);
int wordGrid(Save *save);

#endif
