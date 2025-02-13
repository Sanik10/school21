//-----------------Game of life------------------//
//                  Controls:                    //
//    w - increase spped;  s - decrease speed;   //
//                  q - quit;                    //
//                 Field 25x80                   //
//    Compiller: gcc game_of_life.c -lncurses    //
// Start: ./game_of_life.c < presets/preset1.txt //
//-----------------------------------------------//
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WIDTH 80
#define HEIGHT 25

void update(int grid[HEIGHT][WIDTH]);
int count_neighbors(int grid[HEIGHT][WIDTH], int x, int y);
void init_grid(int grid[HEIGHT][WIDTH]);
void rule_menu();
void display(int grid[HEIGHT][WIDTH]);

int main() {
    int grid[HEIGHT][WIDTH] = {0};
    int speed = 250;  // Game speed ms
    int flag = 0;

    init_grid(grid);
    if (freopen("/dev/tty", "r", stdin) == NULL) {
        printf("Ошибка чтения файла");
        flag = 1;
    }
    initscr();              // Init ncurses
    cbreak();               // Read without pressing enter
    nodelay(stdscr, TRUE);  // No delay mode
    keypad(stdscr, TRUE);   // Enable key pressing

    timeout(20000);
    rule_menu();
    int map;
    map = getch();
    noecho();  // Hides user input
    timeout(50);
    while (map != 'q' && flag == 0) {
        display(grid);
        update(grid);
        napms(speed);

        map = getch();
        if (map == 'w' && speed > 4) speed /= 2;    // Increase speed
        if (map == 's' && speed < 500) speed *= 2;  // Decrease speed
    }

    endwin();  // Free memory, clean screen

    return flag;
}

void rule_menu() {
    mvprintw(HEIGHT / 2 - 1, WIDTH / 2 - 5, "Enter w to increase speed");
    mvprintw(HEIGHT / 2, WIDTH / 2 - 5, "Enter s to decrease speed");
    mvprintw(HEIGHT / 2 + 1, WIDTH / 2 - 5, "Enter anything to start game");
    mvprintw(HEIGHT / 2 + 2, WIDTH / 2 - 5, "Enter q to quit game");
}

void update(int grid[HEIGHT][WIDTH]) {
    int new_grid[HEIGHT][WIDTH] = {0};

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int neighbors = count_neighbors(grid, i, j);
            if (grid[i][j] == 1) {
                new_grid[i][j] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
            } else {
                new_grid[i][j] = (neighbors == 3) ? 1 : 0;
            }
        }
    }

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            grid[i][j] = new_grid[i][j];
        }
    }
}

int count_neighbors(int grid[HEIGHT][WIDTH], int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i != 0 || j != 0) {
                int ni = (x + i + HEIGHT) % HEIGHT;
                int nj = (y + j + WIDTH) % WIDTH;
                count += grid[ni][nj];
            }
        }
    }
    return count;
}

void init_grid(int grid[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            scanf("%d", &grid[i][j]);
        }
    }
}

void display(int grid[HEIGHT][WIDTH]) {
    clear();
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            mvprintw(i, j, grid[i][j] ? "O" : "-");
        }
    }
    refresh();
}