//----------------Ping Pong----------------//
//             Step by step game           //
//  Control Player1: a - top; z - bottom;  //
//  Control Player2: k - top; m - bottiom; //
//               Field 25x80               //
//-----------------------------------------//

#include <stdio.h>

void draw_board(int width, int height, int racket1, int racket2, int ball_x, int ball_y, int score1,
                int score2);
int input1(char input, int racket1_1, int racket1_3);
int input2(char input, int racket2_1, int racket2_3);
int score_calculation(int score1, int score2);

int check_top_bottom_wall(int future_coord_y, int height, int ball_change_y);
int check_left_right_wall(int future_coord_x, int future_coord_y, int racket1, int racket2,
                          int ball_change_x);

void game(int width, int height, int ball_x, int ball_y, int ball_change_x, int ball_change_y, int score1,
          int score2);

int main() {
    game(80, 25, 40, 13, 1, 1, 0, 0);
    return 0;
}

void game(int width, int height, int ball_x, int ball_y, int ball_change_x, int ball_change_y, int score1,
          int score2) {
    char input;
    int racket1_1 = 12, racket1_2 = 13, racket1_3 = 14;
    int racket2_1 = 12, racket2_2 = 13, racket2_3 = 14;
    while (1) {
        int future_coord_x = ball_x + ball_change_x;
        int future_coord_y = ball_y + ball_change_y;
        // Collision with upper and lower wall
        ball_change_y = check_top_bottom_wall(future_coord_y, height, ball_change_y);
        // Collision with left and right racket
        ball_change_x =
            check_left_right_wall(future_coord_x, future_coord_y, racket1_2, racket2_2, ball_change_x);
        // Collision with left wall
        if (future_coord_x == 0) {
            score2++;
            ball_x = 40;
            ball_y = 13;
        }
        // Collision with right wall
        if (future_coord_x == width - 1) {
            score1++;
            ball_x = 40;
            ball_y = 13;
        }
        if (score_calculation(score1, score2) == 1 || score_calculation(score1, score2) == 2) {
            break;
        }
        // Moving ball
        ball_x += ball_change_x;
        ball_y += ball_change_y;
        // Draw field
        draw_board(width, height, racket1_2, racket2_2, ball_x, ball_y, score1, score2);
        // Responding to user input
        while (scanf("%c", &input) && input != '\n') {
            int num1 = input1(input, racket1_1, racket1_3);
            racket1_1 += num1;
            racket1_2 += num1;
            racket1_3 += num1;
            int num2 = input2(input, racket2_1, racket2_3);
            racket2_1 += num2;
            racket2_2 += num2;
            racket2_3 += num2;
        }
        printf("\e[1;1H\e[2J");
    }
}

void draw_board(int width, int height, int racket1Y, int racket2Y, int ball_x, int ball_y, int score1,
                int score2) {
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            if (i == 0 || i == height - 1) {
                printf("_");
            }  // Draw upper and lower wall
            else if (j == 0 || j == width - 1) {
                printf("|");
            }  // Draw left and right wall
            else if ((i == racket1Y - 1 || i == racket1Y + 1 || i == racket1Y) && j == 3) {
                printf("[");
            }  // Draw left racket
            else if ((i == racket2Y - 1 || i == racket2Y + 1 || i == racket2Y) && j == 76) {
                printf("]");
            }  // Draw right racket
            else if (j == ball_x && i == ball_y) {
                printf("o");
            }  // Draw ball
            else if (j == 41) {
                printf("|");
            }  // Draw middle line
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("Player 1 %23c Score %02d : %02d %23c Player 2\n", ' ', score1, score2, ' ');
}

int score_calculation(int score1, int score2) {
    if (score1 == 21 || score2 == 21) {
        if (score1 > score2) {
            printf("Great game! Player 1 win!");
            return 1;
        } else {
            printf("Great game! Player 2 win!");
            return 2;
        }
    }
    return 0;
}

int input1(char input, int racket1_1, int racket1_3) {
    int num = 0;
    if (input == 'a' && racket1_1 != 1) {
        num--;
    } else if (input == 'z' && racket1_3 != 23) {
        num++;
    }
    return num;
}

int input2(char input, int racket2_1, int racket2_3) {
    int num = 0;
    if (input == 'k' && racket2_1 != 1) {
        num--;
    } else if (input == 'm' && racket2_3 != 23) {
        num++;
    }
    return num;
}

int check_top_bottom_wall(int future_coord_y, int height, int ball_change_y) {
    if (future_coord_y == 0) {
        return 1;
    }

    else if (future_coord_y == height - 1) {
        return -1;
    }

    return ball_change_y;
}

int check_left_right_wall(int future_coord_x, int future_coord_y, int racket1, int racket2,
                          int ball_change_x) {
    if (future_coord_x == 3 &&
        (future_coord_y == racket1 || future_coord_y == racket1 - 1 || future_coord_y == racket1 + 1)) {
        return 1;
    }

    else if (future_coord_x == 76 &&
             (future_coord_y == racket2 || future_coord_y == racket2 - 1 || future_coord_y == racket2 + 1)) {
        return -1;
    }

    return ball_change_x;
}