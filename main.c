#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

#include "core/game.h"
#include "draw/drawer.h"


int main() {
    InitWindow(1400, 800, "MinesWeeper");
    SetTargetFPS(30);

    Vector2 mouse_position;
    int square = -1;
    Game game;
    init_game(&game, 10, 10, 10, 1);
    init_images();
    PanelValues panel_values;
    panel_values.status = 0;
    panel_values.type_game = 0;
    panel_values.restart = false;

    while (!WindowShouldClose())
    {
        if (panel_values.status == 0) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                mouse_position = GetMousePosition();

                square = get_pos_by_mouse_event(mouse_position, &game);
                if (square != -1) {
                    click_square(&game, square);
                }

                square = -1;
            } else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                mouse_position = GetMousePosition();

                square = get_pos_by_mouse_event(mouse_position, &game);
                if (square != -1) {
                    flag_square(&game, square);
                }

                square = -1;
            }

            panel_values.status = game_status(&game);
        }

        draw_game(&panel_values, &game);

        if (panel_values.restart == true) {
            switch(panel_values.type_game) {
                case 0:
                    reset_game(&game, 10, 10, 10, 1);
                    break;
                case 1:
                    reset_game(&game, 20, 20, 50, 2);
                    break;
                case 2:
                    reset_game(&game, 30, 30, 100, 3);
                    break;
            }
            panel_values.status = 0;
            panel_values.restart = false;
        }
    }
}
