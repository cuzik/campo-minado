#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>

#define BOMB -1

#define MASK 0
#define CLICKED 1
#define FLAG 2

typedef struct ${
    int *squares;
    int *mirror_squares;
    int bomb_exploded;
    int max_bomb_exploded;
    int bomb_number;
    int dimension_v;
    int dimension_h;
    int total_squares;
} Game;

void reset_game(Game *game, int dimension_v, int dimension_h, int bomb_number, int max_bomb_exploded);
void init_game(Game *game, int dimension_v, int dimension_h, int bomb_number, int max_bomb_exploded);
void click_square(Game *game, int square);
void flag_square(Game *game, int square);
int get_col(int dimension, int square);
int get_row(int dimension, int square);
int game_status(Game *game);
#endif
