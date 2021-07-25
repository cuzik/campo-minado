#ifndef DRAWER_H
#define DRAWER_H

#include <raylib.h>
#include "../core/game.h"

#define PADDING_GAME_WIDTH 10
#define PADDING_GAME_HEIGHT 50
#define PANEL_WIDTH 300
#define SQUARE_SIZE 20
#define PADDING_SQUARE_SIZE 1

#define COLOR_BACKGROUNGD_SQUARE (Color) { 160, 140, 140, 255 }
#define COLOR_MASK_SQUARE (Color) { 200, 180, 180, 255 }
#define COLOR_SQUARE_BORDER (Color) { 120, 120, 120, 255 }

#define COLOR_SQUARE_BY_NUMBER (Color[]) { YELLOW, DARKBLUE, DARKGREEN, RED, ORANGE }

typedef struct pv {
    int type_game;
    bool restart;
    int status;
} PanelValues;

void init_images();
void draw_game(PanelValues *panel_values, Game *game);
void draw_game_status(PanelValues *panel_values, Game *game);
void draw_squares(Game *game);
void draw_panel(PanelValues *panel_values, Game *game);

int distance_to_top(Game *game, int square);
int distance_to_left(Game *game, int square);
int square_size();
int get_pos_by_mouse_event(Vector2 mouse_position, Game *game);
#endif
