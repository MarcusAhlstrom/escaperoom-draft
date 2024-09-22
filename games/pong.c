#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include "../includeAll.h"

#define DELAY 40000 // Delay in microseconds

typedef struct {
    int x, y;
} Position;

typedef struct {
    Position pos;
    int width, height;
} Paddle;

typedef struct {
    Position pos;
    int dx, dy;
} Ball;

void init_paddle(Paddle *paddle, int x, int y, int width, int height);
void init_ball(Ball *ball, int x, int y, int dx, int dy);
void draw_paddle(Paddle *paddle);
void draw_ball(Ball *ball);
void move_paddle(Paddle *paddle, int direction, int max_y);
int move_ball(Ball *ball, Paddle *paddle, int max_x, int max_y, int *score);

void init_paddle(Paddle *paddle, int x, int y, int width, int height) {
    paddle->pos.x = x;
    paddle->pos.y = y;
    paddle->width = width;
    paddle->height = height;
}

void init_ball(Ball *ball, int x, int y, int dx, int dy) {
    ball->pos.x = x;
    ball->pos.y = y;
    ball->dx = dx;
    ball->dy = dy;
}

void draw_paddle(Paddle *paddle) {
    for (int i = 0; i < paddle->height; i++) {
        mvprintw(paddle->pos.y + i, paddle->pos.x, "|");
    }
}

void draw_ball(Ball *ball) {
    mvprintw(ball->pos.y, ball->pos.x, "O");
}

void move_paddle(Paddle *paddle, int direction, int max_y) {
    if (direction == KEY_UP && paddle->pos.y > 0) {
        paddle->pos.y--;
    } else if (direction == KEY_DOWN && paddle->pos.y + paddle->height < max_y) {
        paddle->pos.y++;
    }
}

int move_ball(Ball *ball, Paddle *paddle, int max_x, int max_y, int *score) {
    ball->pos.x += ball->dx;
    ball->pos.y += ball->dy;

    // Ball collision with top and bottom walls
    if (ball->pos.y <= 0 || ball->pos.y >= max_y - 1) {
        ball->dy = -ball->dy;
    }

    // Ball collision with left wall (game over)
    if (ball->pos.x <= 0) {
        // Check if the ball is not colliding with the paddle
        if (ball->pos.y < paddle->pos.y || ball->pos.y >= paddle->pos.y + paddle->height) {
            return 1; // Game over
        } else {
            ball->dx = -ball->dx;
        }
    }

    // Ball collision with right wall
    if (ball->pos.x >= max_x - 1) {
        ball->dx = -ball->dx;
    }

    // Ball collision with paddle
    if (ball->pos.x == paddle->pos.x && ball->pos.y >= paddle->pos.y && ball->pos.y < paddle->pos.y + paddle->height) {
        ball->dx = -ball->dx;
        (*score)++; // Increment score
    }

    return 0; // Game continues
}

void pong(Save *save) {
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    Paddle paddle;
    init_paddle(&paddle, 1, max_y / 2 - 2, 1, 4);

    Ball ball;
    init_ball(&ball, max_x / 2, max_y / 2, 1, 1);

    int score = 0;

    while (1) {
        clear();
        draw_paddle(&paddle);
        draw_ball(&ball);
        refresh();

        int ch = getch();
        if (ch == 'q') {
            break;
        }
        move_paddle(&paddle, ch, max_y);
        if (move_ball(&ball, &paddle, max_x, max_y, &score)) {
            // Game over
            clear();
            mvprintw(max_y / 2, (max_x - strlen("GAME OVER")) / 2, "GAME OVER");
            refresh();
            sleep(2); // Wait for 2 seconds
            break;
        }

        if (score >= 2) {
            // Challenge completed
            clear();
            mvprintw(max_y / 2, (max_x - strlen("CHALLENGE COMPLETED")) / 2, "CHALLENGE COMPLETED");
            refresh();
            usleep(2000000); // Wait for 2 seconds
            save->completedPong = (bool)true;
            break;
        }

        usleep(DELAY);
    }
    clear();
    refresh();
    nodelay(stdscr, FALSE);
    endwin();
    stageFive(save);
}
