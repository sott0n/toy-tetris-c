#include "tetris.h"

static const chtype BLOCK = ' ' | A_REVERSE;

static WINDOW *game_win, *score_win, *title_win;

char screen[Y][X];

static const char TITLE[] =
    "toy --------  ------  -----  -------     ||  ------ \n"
    "       ||     ||____    |    ||    ||    ||  |      \n"
    "       ||     ||        |    ||-----     ||  |-----|\n"
    "       ||     ------    |    ||    ||    ||        |\n"
    "       ||                    ||     ||   ||  ------|\n";

static const char CONTROLS[] =
    "LEFT/RIGHT (h/l): move left/right\n"
    "UP (k): rotate piece             \n"
    "DOWN (j): move down              \n"
    "SPACE: fast down                 \n"
    "P: pause game                    \n"
    "Q: quit                          \n";

static void print_title(void) {
    const char *c;

    for (c = TITLE; *c != '\0'; c++) {
        if (*c == '\n' || *c == ' ') {
            waddch(title_win, (chtype)*c);
        } else {
            wattron(title_win, COLOR_PAIR(*c - 48));
            waddch(title_win, BLOCK);
            wattroff(title_win, COLOR_PAIR(*c - 48));
        }
    }

    wrefresh(title_win);
}

static void print_matrix(void) {
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            if (screen[y][x]) {
                wattron(game_win, COLOR_PAIR(screen[y][x]));
                mvwaddch(game_win, y + 1, x * 2 + 1, BLOCK);
                mvwaddch(game_win, y + 1, x * 2 + 2, BLOCK);
                wattron(game_win, COLOR_PAIR(screen[y][x]));
            } else {
                mvwaddch(game_win, y + 1, x * 2 + 1, ' ');
                mvwaddch(game_win, y + 1, x * 2 + 2, ' ');
            }
        }
    }

    wrefresh(game_win);
}

static void refresh_screen(void) {
    print_score();
    print_matrix();
}

static void draw_windows(void) {
    int center = COLS / 2;

    int title_win_width = 44;
    int title_win_height = 5;
    int title_win_start_x = center - title_win_width / 2 - 5;
    int title_win_start_y = 1;

    int game_win_start_x = center - X * 2 - 1;
    int game_win_start_y = title_win_height + 2;
    int game_win_width = X * 2 + 2;
    int game_win_height = Y + 2;

    int score_win_start_x = game_win_start_x + game_win_width + 3;
    int score_win_start_y = game_win_start_y;
    int score_win_width = COLS - score_win_start_x;
    int score_win_height = game_win_height - 1;

    score_win = newwin(score_win_height, score_win_width, score_win_start_y, score_win_start_x);
    title_win = newwin(title_win_height, title_win_width, title_win_start_y, score_win_start_x);
    print_title();
    game_win = newwin(game_win_height, game_win_width, game_win_start_y, game_win_start_x);
    box(game_win, 0, 0);
}

static void init_graphics(void) {
    initscr();
    cbreak();
    keypad(stdscr, 1);
    noecho();
    curs_set(0);
    timeout(100);

    atexit((void (*)(void)) endwin);

    use_default_colors();
    start_color();
    init_pair(1, COLOR_CYAN, -1);
    init_pair(2, COLOR_YELLOW, -1);
    init_pair(3, 203, -1);
    init_pair(4, COLOR_BLUE, -1);
    init_pair(5, COLOR_MAGENTA, -1);
    init_pair(6, COLOR_GREEN, -1);
    init_pair(7, COLOR_RED, -1);

    refresh();
    draw_windows();
//    refresh_screen();
}

int main(void) {
    srand((unsigned) time(NULL));
    init_graphics();
    printf("hello\n");
}
