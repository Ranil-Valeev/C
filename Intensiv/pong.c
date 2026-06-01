#include <stdio.h>

#define ROW 80
#define STR 25
#define res 21
#define RACKET 3

int game();
void clear();
int check_result(int player1, int player2);
void graphics(int left_racket, int right_racket, int x, int y, int player1, int player2);

int main() {
    game();
    return 0;
}

int game() {
    int left_racket = STR / 2 - 3 / 2;
    int right_racket = STR / 2 - 3 / 2;

    int ball_x = ROW / 2;
    int ball_y = STR / 2;

    int ball_direction_x = 1;
    int ball_direction_y = 1;

    int player1 = 0;
    int player2 = 0;

    char user_input;

    while (1) {
        graphics(left_racket, right_racket, ball_x, ball_y, player1, player2);
        if (check_result(player1, player2)) {
            break;
        }
        scanf(" %c", &user_input);
        switch (user_input) {
            case 'a':
            case 'A':
                if (left_racket > 0) left_racket--;
                break;
            case 'z':
            case 'Z':
                if (left_racket < STR - 3) left_racket++;
                break;
            case 'k':
            case 'K':
                if (right_racket > 0) right_racket--;
                break;
            case 'm':
            case 'M':
                if (right_racket < STR - 3) right_racket++;
                break;
            case 'v':
                break;
            default:
                continue;
        }
        ball_x += ball_direction_x;
        ball_y += ball_direction_y;

        if (ball_y <= 0 || ball_y >= STR - 1) {
            ball_direction_y *= -1;
        }

        if (ball_x == 1 && ball_y >= left_racket && ball_y < left_racket + RACKET) {
            ball_direction_x = 1;
        }
        if (ball_x == ROW - 2 && ball_y >= right_racket && ball_y < right_racket + RACKET) {
            ball_direction_x = -1;
        }

        if (ball_x <= 0) {
            player2++;
            ball_x = ROW / 2;
            ball_y = STR / 2;
            ball_direction_x = 1;
        } else if (ball_x >= ROW - 1) {
            player1++;
            ball_x = ROW / 2;
            ball_y = STR / 2;
            ball_direction_x = -1;
        }
    }
    return 0;
}

void clear() { printf("\033[0d\033[2J"); }

void graphics(int left_racket, int right_racket, int x, int y, int player1, int player2) {
    clear();
    for (int j = 0; j < ROW; j++) {
        printf("-");
    }
    printf("\n");
    for (int i = 0; i < STR; i++) {
        printf("#");
        for (int j = 1; j < ROW - 1; j++) {
            if (j == 1 && i >= left_racket && i < left_racket + RACKET) {
                printf("|");
            } else if (j == ROW - 2 && i >= right_racket && i < right_racket + RACKET) {
                printf("|");
            } else if (j == x && i == y) {
                printf("*");
            } else if (j == ROW / 2) {
                printf(".");
            } else {
                printf(" ");
            }
        }
        printf("#\n");
    }
    for (int j = 0; j < ROW; j++) printf("-");
    printf("\n");
    printf("Player 1: %02d | Player 2: %02d\n", player1, player2);
    printf("Controls: A/Z (player 1), K/M (player 2), V - skip turn\n");
}

int check_result(int player1, int player2) {
    if (player1 == res) {
        printf("Player 1 WIN");
        return 1;
    }
    if (player2 == res) {
        printf("player 2 win:%d:%d!\n", player2, player1);
        return 1;
    }
    return 0;
}