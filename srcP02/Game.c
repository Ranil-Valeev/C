#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

#define WIDTH 80
#define HEIGHT 25
#define MINSPEED 100000
#define MAXSPEED 1000000

int game();
void graphic(int matrix[][WIDTH]);
void load_initial(int matrix[][WIDTH]);
int count_neighbors(int matrix[][WIDTH], int x, int y);
void update_game(int matrix1[][WIDTH], int matrix2[][WIDTH]);

int main() {
    game();
    return 0;
}

int game() {
    int matrix1[HEIGHT][WIDTH], matrix2[HEIGHT][WIDTH];
    int ch, speed = 500000;
    load_initial(matrix1);
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    curs_set(0);
    while (1) {
        ch = getch();
        switch (ch) {
            case 'a':
            case 'A':
                if (speed > MINSPEED) speed -= 100000;
                break;
            case 'z':
            case 'Z':
                if (speed < MAXSPEED) speed += 100000;
                break;
            case ' ':
                endwin();
                return 0;
        }
        graphic(matrix1);
        update_game(matrix1, matrix2);
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                matrix1[i][j] = matrix2[i][j];
            }
        }
        usleep(speed);
    }
    endwin();
    return 0;
}

void load_initial(int matrix[][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            matrix[y][x] = 0;
        }
    }
    matrix[1][2] = 1;
    matrix[2][3] = 1;
    matrix[3][1] = 1;
    matrix[3][2] = 1;
    matrix[3][3] = 1;
}

void graphic(int matrix[][WIDTH]) {
    clear();
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (matrix[i][j] == 0) {
                printw(".");
            } else {
                printw("*");
            }
        }
        printw("\n");
    }
    refresh();
}

void update_game(int matrix1[][WIDTH], int matrix2[][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int neighbors = count_neighbors(matrix1, x, y);
            if (matrix1[y][x]) {
                matrix2[y][x] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
            } else {
                matrix2[y][x] = (neighbors == 3) ? 1 : 0;
            }
        }
    }
}

int count_neighbors(int matrix[][WIDTH], int x, int y) {
    int count = 0;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) continue;
            int nx = (x + dx + WIDTH) % WIDTH;
            int ny = (y + dy + HEIGHT) % HEIGHT;
            count += matrix[ny][nx];
        }
    }
    return count;
}