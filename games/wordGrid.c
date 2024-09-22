#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../includeAll.h"

#define GRID_SIZE 10

void generate_random_grid(char grid[GRID_SIZE][GRID_SIZE]);
void display_grid(WINDOW *win, char grid[GRID_SIZE][GRID_SIZE], int start_y, int start_x);
void extract_correct_code(char grid[GRID_SIZE][GRID_SIZE], char *code);
int wordGrid();

void generate_random_grid(char grid[GRID_SIZE][GRID_SIZE]) {
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = charset[rand() % (sizeof(charset) - 1)];
        }
    }
}

void display_grid(WINDOW *win, char grid[GRID_SIZE][GRID_SIZE], int start_y, int start_x) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            mvwaddch(win, start_y + i, start_x + j, grid[i][j]);
        }
    }
    wrefresh(win);
}

void extract_correct_code(char grid[GRID_SIZE][GRID_SIZE], char *code) {
    code[0] = grid[0][0];
    code[1] = grid[1][4];
    code[2] = grid[1][9];
    code[3] = grid[2][1];
    code[4] = grid[3][7];
    code[5] = grid[4][2];
    code[6] = grid[6][2];
    code[7] = grid[6][7];
    code[8] = grid[6][8];
    code[9] = grid[8][8];
    code[10] = grid[9][5];
    code[11] = '\0'; // Null-terminate the string

}

int wordGrid(Save *save){ 
    if (save == NULL) {
        printf("Error: Save is NULL\n");
        exit(1);
    }

    if (allCompleted(save) == true){
        return 0;
    }
    initscr();
    noecho();
    curs_set(TRUE);
    keypad(stdscr, TRUE);
    srand(time(NULL));

    // Clear the screen
    clear();
    refresh();

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    char grid[GRID_SIZE][GRID_SIZE];
    generate_random_grid(grid);

    char correct_code[12];
    extract_correct_code(grid, correct_code);

    int start_y = (max_y - GRID_SIZE) / 2;
    int start_x = (max_x - GRID_SIZE) / 2;

    display_grid(stdscr, grid, start_y, start_x);

    // Create input box at the bottom of the screen
    int input_box_height = 3;
    int input_box_width = max_x - 4;
    int input_box_start_y = max_y - input_box_height - 2;
    int input_box_start_x = 2;

    WINDOW *input_box = newwin(input_box_height, input_box_width, input_box_start_y, input_box_start_x);
    box(input_box, 0, 0);
    mvwprintw(input_box, 1, 1, "Enter code: ");
    wrefresh(input_box);

    char input[100];
    int ch, i = 0;

    while (1) {
        ch = wgetch(input_box);
        if (ch == '\n') {
            input[i] = '\0';
            if (strcmp(input, correct_code) == 0) {
                mvprintw(max_y / 2 + GRID_SIZE / 2 + 2, (max_x - strlen("Correct code!")) / 2, "Correct code!");
                refresh();
                getch(); // Wait for user input before exiting
                if (save == NULL) {
                    printf("Error creating save\n");
                }
                save->completedWordsearch = (bool)true;
                stageSix(save);
                break;
            } else {
                mvprintw(max_y / 2 + GRID_SIZE / 2 + 2, (max_x - strlen("Incorrect code, try again.")) / 2, "Incorrect code, try again.");
                refresh();
                getch(); // Wait for user input before clearing the message
                wclear(input_box);
                box(input_box, 0, 0);
                mvwprintw(input_box, 1, 1, "Enter code: ");
                wrefresh(input_box);
                stageSix(save);
                i = 0;
            }
        } else if (ch == KEY_BACKSPACE || ch == 127) {
            if (i > 0) {
                i--;
                mvwaddch(input_box, 1, 12 + i, ' '); // Clear character
                wmove(input_box, 1, 12 + i); // Move cursor back
            }
        } else if (isprint(ch) && i < (int)(sizeof(input) - 1)) {
            input[i++] = ch;
            mvwaddch(input_box, 1, 12 + i - 1, ch);
        }
        wrefresh(input_box);
    }

    delwin(input_box);
    endwin();
    return 0;
}