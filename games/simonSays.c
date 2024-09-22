#include "../includeAll.h"
#include <ncurses.h>
#include <string.h>

void simon1(Save *save);

void simon2(Save *save);

void simon3(Save *save);

void simonSays(Save *save) {

    if (save == NULL) {
        printf("Error: Save is NULL\n");
        exit(1);
    }

    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE); // Enable special keys

    // Get screen dimensions
    int height, width;
    getmaxyx(stdscr, height, width);

    // Define the options
    const char *options[] = {
        "1. Nivå 1",
        "2. Nivå 2",
        "3. Nivå 3"
    };

    if (save->completedSimonSays1) {
        options[0] = "1. Nivå 1 (Klar)";
    }
    if (save->completedSimonSays2) {
        options[1] = "2. Nivå 2 (Klar)";
    }
    if (save->completedSimonSays3) {
        options[2] = "3. Nivå 3 (Klar)";
    }
    int num_options = sizeof(options) / sizeof(options[0]);

    // Define the message
    const char *message = "Prestandakärnan: Klara alla utmaningar för att stänga ned kärnan!";

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
                switch (current_selection) {
                    case 0:
                        simon1(save);
                        break;
                    case 1:
                        simon2(save);
                        break;
                    case 2:
                        simon3(save);
                        break;
                }
                refresh();
                getch();
                endwin();
                return;
            case KEY_BACKSPACE: 
                endwin();
                stageFour(save);
                return;
        }
        // End ncurses mode
        endwin();
    }
}



void simon1(Save *save) {
    // Clear the screen
    clear();
    // Refresh the screen to show changes
    refresh();
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    curs_set(0);

    // Get screen dimensions
    int height, width;
    getmaxyx(stdscr, height, width);

    // Define the message
    const char *message = "Klara av simon nivå 1!";

    // Calculate center position for the message
    int message_y = height / 2;
    int message_x = (width - strlen(message)) / 2;

    // Display the message in the center
    mvprintw(message_y, message_x, "%s", message);

    // Refresh the screen to show changes
    refresh();

    // Wait for user input to continue
    simonStage1();
    save->completedSimonSays1 = (bool)true;
    simonSays(save);


    // End ncurses mode
    endwin();
}

void simon2(Save *save) {

    // Clear the screen
    clear();
    // Refresh the screen to show changes
    refresh();
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    curs_set(0);

    // Get screen dimensions
    int height, width;
    getmaxyx(stdscr, height, width);

    // Define the message
    const char *message = "Klara av simon nivå 2!";

    // Calculate center position for the message
    int message_y = height / 2;
    int message_x = (width - strlen(message)) / 2;

    // Display the message in the center
    mvprintw(message_y, message_x, "%s", message);

    // Refresh the screen to show changes
    refresh();

    // Wait for user input to continue
    simonStage1();
    save->completedSimonSays2 = (bool)true;
    simonSays(save);


    // End ncurses mode
    endwin();
}

void simon3(Save *save) {

    // Clear the screen
    clear();
    // Refresh the screen to show changes
    refresh();
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    curs_set(0);

    // Get screen dimensions
    int height, width;
    getmaxyx(stdscr, height, width);

    // Define the message
    const char *message = "Klara av simon nivå 3!";

    // Calculate center position for the message
    int message_y = height / 2;
    int message_x = (width - strlen(message)) / 2;

    // Display the message in the center
    mvprintw(message_y, message_x, "%s", message);

    // Refresh the screen to show changes
    refresh();

    // Wait for user input to continue
    simonStage3();
    save->completedSimonSays3 = (bool)true;
    simonSays(save);

    // End ncurses mode
    endwin();
}
