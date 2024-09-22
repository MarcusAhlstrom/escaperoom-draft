#include "includeAll.h"
#include <ncurses.h>
#include <string.h>

void stageFour(Save *save) {

    if (save == NULL) {
        printf("Error: Save is NULL\n");
        exit(1);
    }

    if (allCompleted(save)) {
        stageTen(save);
    }
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE); // Enable special keys

    // Clear and refresh the screen at the beginning
    clear();
    refresh();

    // Get screen dimensions
    int height, width;
    getmaxyx(stdscr, height, width);

    // Define the options
    const char *options[] = {
        "1. Prestandakärnan",
        "2. Logikkärnan",
        "3. Säkerhetskärnan"
    };

    if (save->completedPong && save->completedLabyrinth && save->completedSimonSays3) {
        options[0] = "1. Prestandakärnan (Klar)";
    }
    if (save->completedMath && save->completedKod && save->completedWordsearch) {
        options[1] = "2. Logikkärnan (Klar)";
    }
    if (save->usb1 && save->usb2 && save->usb3) {
        options[2] = "3. Säkerhetskärnan (Klar)";
    }
    int num_options = sizeof(options) / sizeof(options[0]);

    // Define the message
    const char *message = "Stäng ned alla systemkärnor för att avvärja attacken!";

    // Calculate center position for the message and options
    int message_y = (height - num_options) / 2 - 2; // Position the message above the options
    int message_x = (width - strlen(message)) / 2;
    int start_y = (height - num_options) / 2;
    int start_x = (width - strlen(options[0])) / 2;

    // Initialize the current selection
    int current_selection = 0;

    while (1) {
        // Clear the screen
        clear();

        // Display the message in the center above the options
        mvprintw(message_y, message_x, "%s", message);

        // Display the options in the center
        for (int i = 0; i < num_options; i++) {
            if (i == current_selection) {
                attron(A_REVERSE); // Highlight the selected option
            }
            mvprintw(start_y + i, start_x, "%s", options[i]);
            if (i == current_selection) {
                attroff(A_REVERSE);
            }
        }

        // Refresh the screen to show changes
        refresh();

        // Get user input
        int ch = getch();

        // Handle user input
        switch (ch) {
            case KEY_UP:
                current_selection = (current_selection - 1 + num_options) % num_options;
                break;
            case KEY_DOWN:
                current_selection = (current_selection + 1) % num_options;
                break;
            case '\n': // Enter key
                // Handle the selection (e.g., print the selected option)
                mvprintw(height - 1, 0, "You selected: %s", options[current_selection]);
                switch (current_selection) {
                    case 0:
                        stageFive(save);
                        break;
                    case 1:
                        stageSix(save);
                        break;
                    case 2:
                        stageSeven(save);
                        break;
                }
                refresh();
                getch();
                endwin();
                return;
        }
    }

    // End ncurses mode
    endwin();
}