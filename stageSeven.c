#include "includeAll.h"
#include <ncurses.h>
#include <string.h>

void stageSeven(Save *save) {

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

    // Get screen dimensions
    int height, width;
    getmaxyx(stdscr, height, width);

    // Define the options
    const char *options[] = {
        "1. Nyckel 1: Ej ikopplad",
        "2. Nyckel 2: Ej ikopplad",
        "3. Nyckel 3: Ej ikopplad"
    };
    int num_options = sizeof(options) / sizeof(options[0]);

    // Define the message
    const char *message = "Säkerhetskärnan: Koppla i alla nycklar för att stänga ned kärnan!";

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

          //char *check1USB = "stat /dev/disk/by-uuid/9C05-81B5 > /tmp/hello.txt 2>&1";
        char *check1USB = "/dev/disk/by-uuid/9C05-81B5";
        char *check2USB = "/dev/disk/by-uuid/1CA3-1328";
        char *check3USB = "/dev/disk/by-uuid/EE43-5823";

        int hello[] = {1, 1, 1};
        
        struct stat statedStruct;

        hello[0] = lstat(check1USB, &statedStruct);
        if(hello[0] == 0) {
            save->usb1 = true;
            options[0] = "1. Nyckel 1: Inkopplad";
        }

        hello[1] = lstat(check2USB, &statedStruct);
        if(hello[1] == 0){
            save->usb2 = true;
            options[1] = "2. Nyckel 2: Inkopplad";
        }

        hello[2] = lstat(check3USB, &statedStruct);
        if(hello[2] == 0) {
            save->usb3 = true;
            options[2] = "3. Nyckel 3: Inkopplad";
        }

        if (hello[0] == 0 && hello[1] == 0 && hello[2] == 0) {
            stageSix(save);
        }
        
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
                        break;
                    case 1:
                        break;
                    case 2:
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
    }

    // End ncurses mode
    endwin();
}