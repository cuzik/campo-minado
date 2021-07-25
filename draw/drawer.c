#include "drawer.h"
#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "../external/raygui.h"

const char* menu_type_game[] = {"10 x 10", "20 x 20", "30 x 30"};

Texture2D IMAGE_BOMB;
Texture2D IMAGE_FLAG;

void init_images() {
    Image image;
    image = LoadImage("sprites/bomb_2.png");
    ImageResize(&image, square_size(), square_size());
    IMAGE_BOMB = LoadTextureFromImage(image);

    image = LoadImage("sprites/flag.png");
    ImageResize(&image, square_size(), square_size());
    IMAGE_FLAG = LoadTextureFromImage(image);
}

void draw_game(PanelValues *panel_values, Game *game) {
    BeginDrawing();
        ClearBackground((Color) { 220, 220, 220, 255 });
        draw_squares(game);
        draw_game_status(panel_values, game);
        draw_panel(panel_values, game);
    EndDrawing();
}

int distance_to_left(Game *game, int square) {
    int aditional_padding = (GetScreenWidth() - 2 * (PANEL_WIDTH + PADDING_GAME_WIDTH) - game->dimension_h * SQUARE_SIZE) / 2;

    return get_col(game->dimension_h, square) * SQUARE_SIZE + PANEL_WIDTH + PADDING_GAME_WIDTH + PADDING_SQUARE_SIZE + aditional_padding;
}

int distance_to_top(Game *game, int square) {
    return get_row(game->dimension_h, square) * SQUARE_SIZE + PADDING_GAME_HEIGHT + PADDING_SQUARE_SIZE;
}

int square_size() {
    return SQUARE_SIZE - (2 * PADDING_SQUARE_SIZE);
}

void draw_border_square(Game *game, int square) {
    DrawRectangleLines(distance_to_left(game, square), distance_to_top(game, square), square_size(), square_size(), COLOR_SQUARE_BORDER);
}

void draw_squares(Game * game) {
    for(int i = 0; i < game->total_squares; i++) {
        if (game->mirror_squares[i] == CLICKED) {
            if (game->squares[i] == BOMB) {
                DrawTexture(IMAGE_BOMB, distance_to_left(game, i), distance_to_top(game, i), WHITE );
            } else if (game->squares[i] != 0) {
                DrawRectangle(distance_to_left(game, i), distance_to_top(game, i), square_size(), square_size(), COLOR_BACKGROUNGD_SQUARE);
                char text[4];
                sprintf(text, "%i", game->squares[i]);
                DrawText(text, distance_to_left(game, i) + 5, distance_to_top(game, i) + 2, 15, COLOR_SQUARE_BY_NUMBER[game->squares[i]]);
                draw_border_square(game, i);
            } else {
                DrawRectangle(distance_to_left(game, i), distance_to_top(game, i), square_size(), square_size(), COLOR_BACKGROUNGD_SQUARE);
                draw_border_square(game, i);
            }
        } else if (game->mirror_squares[i] == FLAG){
            DrawTexture(IMAGE_FLAG, distance_to_left(game, i), distance_to_top(game, i), WHITE);
        } else {
            DrawRectangle(distance_to_left(game, i), distance_to_top(game, i), square_size(), square_size(), COLOR_MASK_SQUARE);
            draw_border_square(game, i);
        }
    }
}

void draw_game_status(PanelValues *panel_values, Game *game) {
    if (panel_values->status != 0) {
        DrawRectangle(PANEL_WIDTH, 0, GetScreenWidth() - PANEL_WIDTH, GetScreenHeight(), Fade(BLACK, 0.8));
        if (panel_values->status == 1) {
            DrawText("GAME OVER", 600, 350, 55, RED);
        } else {
            DrawText("GANHOU", 600, 350, 55, DARKGREEN);
        }
    }
}

int active_menu = false;

void draw_panel(PanelValues *panel_values, Game *game) {
    GuiPanel((Rectangle) { 0, 0, PANEL_WIDTH, GetScreenHeight() });

    panel_values->restart = GuiButton((Rectangle) { 20, 20, 260, 50 }, "Restart");

    // panel_values->type_game = GuiListViewEx((Rectangle) { 20, 120, 260, 100 }, (const char**) menu_type_game , 3, NULL, NULL, panel_values->type_game);

    // active_menu = GuiDropdownBox((Rectangle) { 20, 120, 260, 50 }, "10 x 10; 20 x 20; 30 x 30" , &panel_values->type_game, active_menu);
    panel_values->type_game = GuiComboBox((Rectangle) { 20, 120, 260, 50 }, "10 x 10; 20 x 20; 30 x 30" , panel_values->type_game);


    GuiPanel((Rectangle) { GetScreenWidth() - PANEL_WIDTH, 0, PANEL_WIDTH, GetScreenHeight() });
}

int get_pos_by_mouse_event(Vector2 mouse_position, Game *game) {
    int square;
    int aditional_padding = (GetScreenWidth() - 2 * (PANEL_WIDTH + PADDING_GAME_WIDTH) - game->dimension_h * SQUARE_SIZE) / 2;

    int relative_x = (mouse_position.x - (PANEL_WIDTH + PADDING_GAME_WIDTH + PADDING_SQUARE_SIZE + aditional_padding)) / SQUARE_SIZE;
    int relative_y = (mouse_position.y - (PADDING_GAME_HEIGHT + PADDING_SQUARE_SIZE)) / SQUARE_SIZE;

    if (relative_x < 0 || relative_y < 0 || relative_x >= game->dimension_h || relative_y >= game->dimension_v) {
        return -1;
    }

    return relative_y * game->dimension_h + relative_x;
}
