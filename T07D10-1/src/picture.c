
#include <stdio.h>

#define N 15
#define M 13

void transform(int *buf, int **matr, int n, int m);
void make_picture(int **picture, int n, int m);
void reset_picture(int **picture, int n, int m);

int main() {
    int picture_data[N][M];
    int *picture[N];
    transform((int *)picture_data, picture, N, M);

    make_picture(picture, N, M);

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

    // Рисуем солнце
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            picture[i + 1][j + 7] = sun_data[i][j];
        }
    }

    // Рисуем ствол
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            picture[i + 6][j + 3] = tree_trunk[j];
        }
    }
    for (int j = 0; j < 4; j++) {
        picture[10][j + 2] = tree_trunk[j];
    }

    // Рисуем листву
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            picture[2 + j][2 + i] = tree_foliage[1];
            if ((i == 0 && j == 0) || (i == 3 && j == 0) || (i == 0 && j == 3) || (i == 3 && j == 3)) {
                picture[2 + j][2 + i] = 0;
            }
        }
    }

    // Рисуем рамку
    for (int i = 0; i < m; i++) {
        picture[0][i] = frame_w[i];      // Верхняя линия
        picture[7][i] = frame_w[i];      // Верхняя линия
        picture[n - 1][i] = frame_w[i];  // Нижняя линия
    }
    for (int i = 1; i < n - 1; i++) {
        picture[i][0] = frame_h[i];      // Левая линия
        picture[i][6] = frame_h[i];      // Левая линия
        picture[i][m - 1] = frame_h[i];  // Правая линия
    }

    // Выводим картинку
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", picture[i][j]);
        }
        printf("\n");
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
