#include "game.h"

void reset_game(Game *game, int dimension_v, int dimension_h, int bomb_number, int max_bomb_exploded) {
    if (game->squares != NULL) {
        free(game->squares);
        game->squares = NULL;
    }

    if (game->mirror_squares != NULL) {
        free(game->mirror_squares);
        game->mirror_squares = NULL;
    }

    init_game(game, dimension_v, dimension_h, bomb_number, max_bomb_exploded);
}

void init_game(Game *game, int dimension_v, int dimension_h, int bomb_number, int max_bomb_exploded) {
    game->bomb_exploded = 0;
    game->bomb_number = bomb_number;
    game->max_bomb_exploded = max_bomb_exploded;
    game->dimension_v = dimension_v;
    game->dimension_h = dimension_h;
    game->total_squares = dimension_v * dimension_h;
    game->squares = malloc (sizeof (int) * game->total_squares);
    game->mirror_squares = malloc (sizeof (int) * game->total_squares);

    for(int i = 0; i < game->total_squares; i++) {
        game->squares[i] = 0;
        game->mirror_squares[i] = MASK;
    }

    for(int i = 0; i < bomb_number; i++) {
        int square = rand() % game->total_squares;

        while (game->squares[square] == BOMB) {
            square = rand() % game->total_squares;
        }
        game->squares[square] = BOMB;

        int row = get_row(game->dimension_h, square);
        int col = get_col(game->dimension_h, square);

        // top
        if ( row > 0 && game->squares[square - game->dimension_h] != -1) {
            game->squares[square - game->dimension_h]++;
        }

        // top right
        if (row > 0 && col < game->dimension_h - 1 && game->squares[square - game->dimension_h + 1] != -1) {
            game->squares[square - game->dimension_h + 1]++;
        }

        // right
        if (col < game->dimension_h - 1 && game->squares[square + 1] != -1) {
            game->squares[square + 1]++;
        }

        // bottom right
        if (row < game->dimension_v - 1 && col < game->dimension_h - 1 && game->squares[square + game->dimension_h + 1] != -1) {
            game->squares[square + game->dimension_h + 1]++;
        }

        // bottom
        if (row < game->dimension_v - 1 && game->squares[square + game->dimension_h ] != -1) {
            game->squares[square + game->dimension_h ]++;
        }

        // bottom left
        if (row < game->dimension_v - 1 && col > 0 && game->squares[square + game->dimension_h - 1] != -1) {
            game->squares[square + game->dimension_h - 1]++;
        }

        // left
        if (col > 0 && game->squares[square - 1] != -1) {
            game->squares[square - 1]++;
        }

        // top left
        if (row > 0 && col > 0 && game->squares[square - game->dimension_h - 1] != -1) {
            game->squares[square - game->dimension_h - 1]++;
        }
    }
}

void cascade_effect(Game *game, int square) {
    if (square < 0 || square >=game->total_squares || game->mirror_squares[square] != MASK) return;

    game->mirror_squares[square] = CLICKED;

    if (game->squares[square] != 0) return;

    int row = get_row(game->dimension_h, square);
    int col = get_col(game->dimension_h, square);

    cascade_effect(game, square - game->dimension_h);
    if (col < game->dimension_h - 1) { cascade_effect(game, square + 1); }
    cascade_effect(game, square + game->dimension_h);
    if (col > 0) { cascade_effect(game, square - 1); }

    // essa parte é diagonal
    if (col < game->dimension_h - 1 && row > 0)                     { cascade_effect(game, square - game->dimension_h + 1); }
    if (col < game->dimension_h - 1 && row < game->dimension_v - 1) { cascade_effect(game, square + game->dimension_h + 1); }
    if (col > 0 && row < game->dimension_v - 1)                     { cascade_effect(game, square + game->dimension_h - 1); }
    if (col > 0 && row > 0)                                         { cascade_effect(game, square - game->dimension_h - 1); }
}

void click_square(Game *game, int square) {
    if (game->mirror_squares[square] != MASK) return;

    if(game->squares[square] == -1) {
        game->mirror_squares[square] = CLICKED;
        game->bomb_exploded++;
    }

    cascade_effect(game, square);
}

void flag_square(Game *game, int square) {
    if (game->mirror_squares[square] == CLICKED) return;

    if (game->mirror_squares[square] == FLAG) {
        game->mirror_squares[square] = MASK;

        return;
    }

    game->mirror_squares[square] = FLAG;
}

int game_status(Game *game) {
    if (game->max_bomb_exploded == game->bomb_exploded) return 1;

    int count = 0;

    for(int i = 0; i < game->total_squares; i++) {
        if (game->mirror_squares[i] == CLICKED && game->squares[i] != -1) {
            count++;
        }
    }

    if (count == game->total_squares - game->bomb_number) return 2;

    return 0;
}

int get_col(int dimension, int square) {
    return square % dimension;
}

int get_row(int dimension, int square) {
    return square / dimension;
}
