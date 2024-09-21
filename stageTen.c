#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

char *text[] = {
"       _ _____ _____ _   ___ _  __      ",
"      /_\\_   _|_   _/_\\ / __| |/ /      ",
"     / _ \\| |   | |/ _ \\ (__| ' <       ",
"  __/_/_\\_\\_|   |_/_/_\\_\\___|_|\\_\\ ___  ",
" |   \\_ _/ __| /_\\ | _ \\  \\/  | __|   \\ ",
" | |) | |\\__ \\/ _ \\|   / |\\/| | _|| |) |",
" |___/___|___/_/ \\_\\_|_\\_|  |_|___|___/ "      
};   

void stageTen();
void handle_sigint();

// Custom signal handler for SIGINT
void handle_sigint(int sig) {
    fprintf(stderr, "%d", sig);
    // Do nothing, effectively ignoring the signal
}

void stageTen() {

    // Set custom signal handler for SIGINT
    signal(SIGINT, handle_sigint);
    signal(SIGTERM, handle_sigint);
    // Initialize ncurses
    initscr();
    start_color();
    cbreak();
    noecho();
    curs_set(0);

    // Initialize color pairs
    init_pair(1, COLOR_BLACK, COLOR_GREEN);

    // Get screen dimensions
    int height, width;
    getmaxyx(stdscr, height, width);

    // Calculate center position
    int start_y = height / 2;

    // Set background color
    bkgd(COLOR_PAIR(1));

    // Display the text in the center
    attron(COLOR_PAIR(1));

    for (int i = 0; i < 7; i++) {
        mvprintw(start_y - 3 + i, (width - strlen(text[i])) / 2, "%s", text[i]);
    }
    //mvprintw(start_y, start_x, "Attack avvärjd!");
    attroff(COLOR_PAIR(1));

    // Refresh the screen to show changes
    refresh();

    // Wait for user input before exiting
    getch();

    // End ncurses mode
    endwin();

    exit(0);
}