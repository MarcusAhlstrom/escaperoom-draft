#include "../includeAll.h"

#include <ncurses.h>

void audioCheckScreen(Save *save) {
    // Initialize the NCURSES library
    refresh();

    initscr();
    noecho();
    cbreak();

    clear();

    // Get the screen dimensions
    int row, col;
    getmaxyx(stdscr, row, col);

    // Calculate the position to center the message
    char message[] = "Please connect audio device!!!";
    int start_row = row / 2;
    int start_col = (col - strlen(message)) / 2;

    // Display the message
    mvprintw(start_row, start_col, "%s", message);

    // Refresh the screen to show the message
    refresh();

    // Wait for user input to exit
    REALLYensureUARTConnected();

    chatScreen(save);

    // Clean up and close the NCURSES library
    endwin();
}