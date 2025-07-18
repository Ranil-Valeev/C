#include <stdio.h>
#define N 15
#define M 13

void transform(int *buf, int **matr, int n, int m);
void make_picture(int **picture, int n, int m);
void reset_picture(int **picture, int n, int m);
void print_picture(int **picture, int n, int m);

int main() {
    int picture_data[N][M];
    int *picture[N];
    transform((int *)picture_data, picture, N, M);

    make_picture(picture, N, M);
    print_picture(picture, N, M);
    return 0;
}

void make_picture(int **picture, int n, int m) {
    int frame_w[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int frame_h[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int tree_trunk[] = {7, 7, 7, 7};
    int tree_foliage[] = {3, 3, 3, 3};
    int sun_data[6][5] = {{0, 6, 6, 6, 6}, {0, 0, 6, 6, 6}, {0, 0, 6, 6, 6},
                          {0, 6, 0, 0, 6}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}};

    reset_picture(picture, n, m);

    for (int i = 0; i < n; i++) {
        picture[i][0] = frame_h[i];
        picture[i][m - 1] = frame_h[i];
    }
    for (int j = 0; j < m; j++) {
        picture[0][j] = frame_w[j];
        picture[n - 1][j] = frame_w[j];
    }

    for (int i = 1; i < n - 1; i++) {
        picture[i][6] = 1;
    }

    for (int i = 0; i < 4; i++) {
        picture[6 + i][3] = tree_trunk[i];
        picture[6 + i][4] = tree_trunk[i];
    }

    picture[2][3] = 3;
    picture[2][4] = 3;
    picture[3][2] = 3;
    picture[3][3] = 3;
    picture[3][4] = 3;
    picture[3][5] = 3;
    picture[4][2] = 3;
    picture[4][3] = 3;
    picture[4][4] = 3;
    picture[4][5] = 3;
    picture[5][3] = 3;
    picture[5][4] = 3;

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 5; j++) {
            picture[1 + i][7 + j] = sun_data[i][j];
        }
    }
}

void reset_picture(int **picture, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            picture[i][j] = 0;
        }
    }
}

void transform(int *buf, int **matr, int n, int m) {
    for (int i = 0; i < n; i++) {
        matr[i] = buf + i * m;
    }
}

void print_picture(int **picture, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d", picture[i][j]);
            if (j < m - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}