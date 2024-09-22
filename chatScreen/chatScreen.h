#ifndef CHAT_SCREEN
#define CHAT_SCREEN

#define MAX_MESSAGES 100
#define MAX_MESSAGE_LENGTH 256

void init_windows(WINDOW **chat_win, WINDOW **input_win, int term_height, int term_width);
void handle_input(WINDOW *chat_win, WINDOW *input_win, int term_width);
void draw_message_box(WINDOW *win, int y, int x, const char *message);
const char* get_random_response();
void chatScreen();


#endif
