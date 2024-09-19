#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX_MESSAGES 100
#define MAX_MESSAGE_LENGTH 256

void init_windows(WINDOW **chat_win, WINDOW **input_win, int term_height, int term_width);
void handle_input(WINDOW *chat_win, WINDOW *input_win, int term_width);
void draw_message_box(WINDOW *win, int y, int x, const char *message);
const char* get_random_response();
void chatScreen();

void init_windows(WINDOW **chat_win, WINDOW **input_win, int term_height, int term_width) {
    int chat_height = term_height - 3;
    int input_height = 3;

    *chat_win = newwin(chat_height, term_width, 0, 0);
    *input_win = newwin(input_height, term_width, chat_height, 0);

    scrollok(*chat_win, TRUE);
    wrefresh(*chat_win);
    wrefresh(*input_win);
}

void draw_message_box(WINDOW *win, int y, int x, const char *message) {
    int length = strlen(message);
    mvwprintw(win, y, x, "+");
    mvwprintw(win, y, x + length + 1, "+");
    mvwprintw(win, y + 2, x, "+");
    mvwprintw(win, y + 2, x + length + 1, "+");

    for (int i = 1; i <= length; i++) {
        mvwprintw(win, y, x + i, "-");
        mvwprintw(win, y + 2, x + i, "-");
    }

    mvwprintw(win, y + 1, x, "|");
    mvwprintw(win, y + 1, x + length + 1, "|");

    mvwprintw(win, y + 1, x + 1, "%s", message);
}

const char* get_random_response() {
    const char* responses[] = {
        "Hello!",
        "How are you?",
        "Nice to meet you!",
        "What's up?",
        "Goodbye!"
    };
    int num_responses = sizeof(responses) / sizeof(responses[0]);
    return responses[rand() % num_responses];
}

void handle_input(WINDOW *chat_win, WINDOW *input_win, int term_width) {
    char input[MAX_MESSAGE_LENGTH];
    char messages[MAX_MESSAGES][MAX_MESSAGE_LENGTH];
    int message_count = 0;

    while (1) {
        // Clear the input window and prompt for input
        werase(input_win);
        mvwprintw(input_win, 1, 1, "Type a message: ");
        wrefresh(input_win);

        // Get the user input
        wgetnstr(input_win, input, MAX_MESSAGE_LENGTH - 1);

        // Exit the loop if the user types "exit"
        if (strcmp(input, "exit") == 0) {
            break;
        }

        // Store the user's message and display it in the chat window
        strncpy(messages[message_count % MAX_MESSAGES], input, MAX_MESSAGE_LENGTH);
        message_count++;

        werase(chat_win);
        for (int i = 0; i < message_count && i < MAX_MESSAGES; i++) {
            int y = i * 3; // Adjust y-coordinate for vertical spacing
            int x;
            if (i % 2 == 0) {
                // User's message on the right side
                x = term_width / 2 + 1;
            } else {
                // Random response on the left side
                x = 1;
            }
            draw_message_box(chat_win, y, x, messages[i]); // Draw box around message
        }
        wrefresh(chat_win);

        // Display "Computer is typing..." indicator
        mvwprintw(chat_win, message_count * 3, 1, "Generating answer...");
        wrefresh(chat_win);

        // Delay for 1-3 seconds
        int delay = (rand() % 3) + 1;
        sleep(delay);

        // Clear the "Computer is typing..." indicator
        werase(chat_win);
        for (int i = 0; i < message_count && i < MAX_MESSAGES; i++) {
            int y = i * 3; // Adjust y-coordinate for vertical spacing
            int x;
            if (i % 2 == 0) {
                // User's message on the right side
                x = term_width / 2 + 1;
            } else {
                // Random response on the left side
                x = 1;
            }
            draw_message_box(chat_win, y, x, messages[i]); // Draw box around message
        }
        wrefresh(chat_win);

        // Generate a random response and store it
        const char* response = get_random_response();
        strncpy(messages[message_count % MAX_MESSAGES], response, MAX_MESSAGE_LENGTH);
        message_count++;

        werase(chat_win);
        for (int i = 0; i < message_count && i < MAX_MESSAGES; i++) {
            int y = i * 3; // Adjust y-coordinate for vertical spacing
            int x;
            if (i % 2 == 0) {
                // User's message on the right side
                x = term_width / 2 + 1;
            } else {
                // Random response on the left side
                x = 1;
            }
            draw_message_box(chat_win, y, x, messages[i]); // Draw box around message
        }
        wrefresh(chat_win);
    }
}

void chatScreen() {
    initscr();
    cbreak();
    noecho();
    srand(time(NULL)); // Seed the random number generator

    int term_height, term_width;
    getmaxyx(stdscr, term_height, term_width);

    WINDOW *chat_win, *input_win;
    init_windows(&chat_win, &input_win, term_height, term_width);

    handle_input(chat_win, input_win, term_width);

    endwin();
}