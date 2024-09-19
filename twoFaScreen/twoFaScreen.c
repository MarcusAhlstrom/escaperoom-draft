#include "../includeAll.h"

void twoFaScreen(){
  initscr();
  noecho(); // Disable echoing of typed characters
  cbreak(); // Disable line buffering
  keypad(stdscr, TRUE); // Enable function keys

  int term_height, term_width;
  getmaxyx(stdscr, term_height, term_width);

  // Center the initial message
  const char *initial_msg = "2 FACTOR AUTHENTICATION";
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

  char input1[30];

  while (1) {
      werase(textbox_win1);
      box(textbox_win1, 0, 0);
      mvwprintw(textbox_win1, 1, 1, "Enter Code: ");
      wrefresh(textbox_win1);

      echo();

      mvwgetnstr(textbox_win1, 1, 12, input1, 29);

      noecho();
      refresh();
      int input_msg_y = start_y + height * 2 + 4;
      int input_msg_x = (term_width - (12 + strlen(input1) + 5)) / 2;
      mvprintw(input_msg_y, input_msg_x, "You entered: %s", input1);
      refresh();


      if (strcmp(input1, "2fa") == 0) {
          mvprintw(input_msg_y + 1, input_msg_x, "Correct inputs. Don't try again");
          refresh();
          getch();
          endwin();

          stageThree();
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
