#include "../includeAll.h"

void loginScreen(Save *save) {
    if (save == NULL) {
        printf("Error: Save is NULL\n");
        exit(1);
    }
    initscr();
    noecho(); // Disable echoing of typed characters
    cbreak(); // Disable line buffering
    keypad(stdscr, TRUE); // Enable function keys

    int term_height, term_width;
    getmaxyx(stdscr, term_height, term_width);

    // Center the initial message
    const char *initial_msg = "Login Screen";
    int initial_msg_x = (term_width - strlen(initial_msg)) / 2;
    mvprintw(0, initial_msg_x, "%s", initial_msg);
    refresh();

    // Create a new window for the first textbox
    int height = 3;
    int width = 40;
    int start_y = ((term_height - height) - 7) / 2; // Center vertically
    int start_x = (term_width - width) / 2; // Center horizontally
    WINDOW *textbox_win1 = newwin(height, width, start_y, start_x);
    box(textbox_win1, 0, 0); // Draw a box around the window
    wrefresh(textbox_win1); // Refresh the first textbox window

    // Create a new window for the second textbox
    WINDOW *textbox_win2 = newwin(height, width, start_y + height + 2, start_x); // Position below the first textbox
    box(textbox_win2, 0, 0); // Draw a box around the window
    wrefresh(textbox_win2); // Refresh the second textbox window

    char *correct_username = safeCalloc(6, sizeof(char));
    char *correct_password = safeCalloc(6, sizeof(char));
    strcpy(correct_username, "admin");
    strcpy(correct_password, "admin");

    while (1) {

        char *input1 = safeCalloc(22, sizeof(char));
        char *input2 = safeCalloc(22, sizeof(char));

        werase(textbox_win1);
        box(textbox_win1, 0, 0);
        mvwprintw(textbox_win1, 1, 1, "Enter Username: ");
        wrefresh(textbox_win1);

        echo();

        werase(textbox_win2);
        box(textbox_win2, 0, 0);
        mvwprintw(textbox_win2, 1, 1, "Enter Password: ");
        wrefresh(textbox_win2);

        mvwgetnstr(textbox_win1, 1, 17, input1, 21);

        mvwgetnstr(textbox_win2, 1, 17, input2, 21);

        echo();

        int input_msg_y = start_y + height * 2 + 4;
        int input_msg_x = (term_width - (12 + strlen(input1) + strlen(input2) + 5)) / 2;
        if (strcmp(input1, correct_username) == 0 && strcmp(input2, correct_password) == 0) {
            mvprintw(input_msg_y + 1, input_msg_x, "Welcome %s, Press any key to continue", correct_username);
            refresh();
            getch();
            clear(); // Clear the screen
            refresh(); // Refresh to apply the clear
            endwin();
            free(input1);
            free(input2);
            twoFaScreen(save);
            break;
        } else {
            clrtoeol();
            mvprintw(input_msg_y, input_msg_x, "You entered: %s and %s", input1, input2);
            refresh();
            mvprintw(input_msg_y + 1, input_msg_x, "Invalid username or password. Try again.");
            refresh();
            getch();
            move(input_msg_y + 1, input_msg_x);
            clrtoeol();
        }
        free(input1);
        free(input2);
    }
    free(correct_username);
    free(correct_password);
    endwin();
}
