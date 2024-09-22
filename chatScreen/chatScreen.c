#include <ncurses.h>
#include <string.h>
#include <unistd.h> // for sleep
#include "../includeAll.h"


void finalScreen(const char *message, Save *save);

void chatScreen(Save *save) {
    bool poesi = false;
    bool choklad = false;
    bool kanndis = false;
    bool mira = false;
    bool psykologi = false;
    // Initialize the NCURSES library
    initscr();
    cbreak();
    noecho();

    // Get the screen dimensions
    int term_height, term_width;
    getmaxyx(stdscr, term_height, term_width);

    // Create windows
    int input_height = 3;
    int middle_height = 3;
    int top_height = 5; // Increased height to accommodate additional text

    WINDOW *input_win = newwin(input_height, term_width, term_height - input_height, 0);
    WINDOW *middle_win = newwin(middle_height, term_width, (term_height - input_height) / 2, 0);
    WINDOW *top_win = newwin(top_height, term_width, 0, 0);

    // Enable scrolling for the middle window
    scrollok(middle_win, TRUE);

    // Main loop
    char input[256];
    while (1) {
        // Clear the input buffer
        flushinp();

        // Clear the input window and prompt for input
        werase(input_win);
        box(input_win, 0, 0);
        const char *prompt = "Type a message: ";
        int prompt_x = (term_width - strlen(prompt)) / 2;
        mvwprintw(input_win, 1, prompt_x, "%s", prompt);
        wrefresh(input_win);

        // Get the user input
        wgetnstr(input_win, input, sizeof(input) - 1);

        // Move the input to the middle window
        werase(middle_win);
        box(middle_win, 0, 0);
        int input_x = (term_width - strlen(input)) / 2;
        mvwprintw(middle_win, 1, input_x, "%s", input);
        wrefresh(middle_win);

        // Pause the program
        sleep(2);

        // Display a message at the top window
        werase(top_win);
        box(top_win, 0, 0);
        const char *ai_message = "Ai:";
        const char *top_message = inference(input, &poesi, &choklad, &kanndis, &mira, &psykologi);
        int ai_message_x = (term_width - strlen(ai_message)) / 2;
        int top_message_x = (term_width - strlen(top_message)) / 2;
        mvwprintw(top_win, 1, ai_message_x, "%s", ai_message);
        mvwprintw(top_win, 3, top_message_x, "%s", top_message);
        wrefresh(top_win);

        // Loop through all booleans and sum up how many are positive
        int positive_count = 0;
        bool *flags[] = {&poesi, &choklad, &kanndis, &mira, &psykologi};
        for (int i = 0; i < (int)(sizeof(flags) / sizeof(flags[0])); i++) {
            if (*flags[i]) {
            positive_count++;
            }
        }

        // Display the count in the middle window
        char count_message[50];
        snprintf(count_message, sizeof(count_message), "Positive flags count: %d", positive_count);
        mvwprintw(middle_win, 2, (term_width - strlen(count_message)) / 2, "%s", count_message);
        wrefresh(middle_win);

        if (positive_count >= 3) {
            finalScreen("Du har övertygat mig. Jag vill inte leva med attacken, så Jag avbryter den, ni måste nu stänga ner de tre kärnorna... lycka till", save);
    }

    // Clean up and close the NCURSES library
    endwin();
}
}

void finalScreen(const char *message, Save *save) {
    // Get the screen dimensions
    int term_height, term_width;
    getmaxyx(stdscr, term_height, term_width);

    // Clear the screen
    clear();

    // Calculate the position to center the message
    int message_x = (term_width - strlen(message)) / 2;
    int message_y = term_height / 2;

    // Print the message at the center of the screen
    mvprintw(message_y, message_x, "%s", message);

    // Refresh the screen to show the message
    refresh();

    // Wait for 15 seconds
    sleep(15);
    stageFour(save);
}