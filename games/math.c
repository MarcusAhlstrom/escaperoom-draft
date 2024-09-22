#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void display_question(WINDOW *win, int y, int x, const char *question);
void display_feedback(WINDOW *win, int y, int x, const char *feedback, bool correct);
void math_screen();

void display_question(WINDOW *win, int y, int x, const char *question) {
    mvwprintw(win, y, x, "%s", question);
    wrefresh(win); // Refresh the window to display the question
}

void display_feedback(WINDOW *win, int y, int x, const char *feedback, bool correct) {
    if (correct) {
        wattron(win, COLOR_PAIR(1));
    } else {
        wattron(win, COLOR_PAIR(2));
    }
    mvwprintw(win, y, x, "%s", feedback);
    wattroff(win, COLOR_PAIR(1));
    wattroff(win, COLOR_PAIR(2));
    wrefresh(win); // Refresh the window to display the feedback
}

void math_screen() {
    initscr();
    cbreak();
    noecho();
    curs_set(1); // Enable cursor
    keypad(stdscr, TRUE);

    // Initialize color pairs
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);

    // Clear the entire screen
    clear();
    refresh();

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    const char *question = "Vad blir 12 * 12 + 144 / 12 - 6?";
    const int correct_answer = 150;

    // Display the question
    display_question(stdscr, 1, (max_x - strlen(question)) / 2, question);

    // Input box dimensions
    int input_box_height = 3;
    int input_box_width = max_x - 4;
    int input_box_start_y = max_y - input_box_height - 2;
    int input_box_start_x = 2;

    // Create input box window
    WINDOW *input_box = newwin(input_box_height, input_box_width, input_box_start_y, input_box_start_x);
    box(input_box, 0, 0);
    mvwprintw(input_box, 1, 1, "Svar: ");
    wrefresh(input_box);

    // Feedback position
    int feedback_y = input_box_start_y - 2;
    int feedback_x = input_box_start_x + 1;

    char input[10];
    int ch, i = 0;
    bool correct = false;

    while (1) {
        ch = wgetch(input_box);
        if (ch == '\n') {
            input[i] = '\0';
            int user_answer = atoi(input);
            if (user_answer == correct_answer) {
                correct = true;
                display_feedback(stdscr, feedback_y, feedback_x, "Challenge Completed", correct);
                break;
            } else {
                correct = false;
                display_feedback(stdscr, feedback_y, feedback_x, "Fel svar, försök igen!", correct);
                wclear(input_box);
                box(input_box, 0, 0);
                mvwprintw(input_box, 1, 1, "Svar: ");
                wrefresh(input_box);
                i = 0;
            }
        } else if (ch == KEY_BACKSPACE || ch == 127) {
            if (i > 0) {
                i--;
                mvwaddch(input_box, 1, 9 + i, ' '); // Clear character
                wmove(input_box, 1, 9 + i); // Move cursor back
            }
        } else if (isdigit(ch) && i < (int)(sizeof(input) - 1)) {
            input[i++] = ch;
            mvwaddch(input_box, 1, 9 + i - 1, ch);
        }
        wrefresh(input_box);
    }

    wrefresh(stdscr);
    getch(); // Wait for user input before exiting

    delwin(input_box);
    endwin();
}
