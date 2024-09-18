#include "includeAll.h"

void stageOne() {
    initscr();
    noecho(); // Disable echoing of typed characters
    cbreak(); // Disable line buffering
    keypad(stdscr, TRUE); // Enable function keys

    int term_height, term_width;
    getmaxyx(stdscr, term_height, term_width);

    // Center the initial message
    const char *initial_msg = "FIRST LEVEL WHHOOOOAOAAA";
    int initial_msg_x = (term_width - strlen(initial_msg)) / 2;
    mvprintw(0, initial_msg_x, "%s", initial_msg);
    refresh();

    // Create a new window for the first textbox
    int height = 3;
    int width = 40;
    int start_y = (term_height - height) / 2; // Center vertically
    int start_x = (term_width - width) / 2; // Center horizontally
    WINDOW *textbox_win1 = newwin(height, width, start_y, start_x);
    box(textbox_win1, 0, 0); // Draw a box around the window
    wrefresh(textbox_win1); // Refresh the first textbox window

    // Create a new window for the second textbox
    WINDOW *textbox_win2 = newwin(height, width, start_y + height + 2, start_x); // Position below the first textbox
    box(textbox_win2, 0, 0); // Draw a box around the window
    wrefresh(textbox_win2); // Refresh the second textbox window

    char input1[30];
    char input2[30];
    while (1) {
        werase(textbox_win1);
        box(textbox_win1, 0, 0);
        mvwprintw(textbox_win1, 1, 1, "Enter text 1: ");
        wrefresh(textbox_win1);

        echo();

        mvwgetnstr(textbox_win1, 1, 12, input1, 29);

        werase(textbox_win2);
        box(textbox_win2, 0, 0); 
        mvwprintw(textbox_win2, 1, 1, "Enter text 2: ");
        wrefresh(textbox_win2);

        mvwgetnstr(textbox_win2, 1, 12, input2, 29);

        noecho();

        int input_msg_y = start_y + height * 2 + 4;
        int input_msg_x = (term_width - (12 + strlen(input1) + strlen(input2) + 5)) / 2;
        mvprintw(input_msg_y, input_msg_x, "You entered: %s and %s", input1, input2);
        refresh();

        char *error_message = "";

        if (strcmp(input1, "correct_username") != 0) {
            strcat(error_message, "Incorrect username. ");
        }
        if (strcmp(input2, "correct_password") != 0) {
            strcat(error_message, "Incorrect password. ");
        }

        if (strcmp(input1, "correct_username") == 0 && strcmp(input2, "correct_password") == 0) {
            mvprintw(input_msg_y + 1, input_msg_x, error_message);
            refresh();
            getch();
            endwin();
            stageTwo();
            break; 
        } else {
            mvprintw(input_msg_y + 1, input_msg_x, "Incorrect inputs. Try again.");
            refresh();
            getch();
            move(input_msg_y + 1, input_msg_x);
            clrtoeol();
        }
    }

    endwin();
}