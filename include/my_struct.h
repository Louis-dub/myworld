/*
** EPITECH PROJECT, 2026
** engineering
** File description:
** my_struct
*/

#ifndef INCLUDED_MY_STRUCT_H
    #define INCLUDED_MY_STRUCT_H
    #include <SFML/Graphics.h>
    #include <SFML/System.h>
    #include <SFML/Audio/Music.h>

typedef struct square {
    sfVector2f p1;
    sfVector2f p2;
    sfVector2f p3;
    sfVector2f p4;
    double depth;
    double min;
    double zs[4];
} square_t;

typedef struct cursor {
    sfSprite *cursor_s;
    sfTexture *cursor_t;
} cursor_t;

typedef struct button_size {
    sfText *text;
    sfVector2f corners[4];
    int pressed;
    int size;
    double x;
    double y;
    double x3D;
    double y3D;
} button_size_t;

typedef struct button {
    sfSprite *sprite;
    sfText *text;
    sfVector2f pos;
    char *str;
    int size;
    char pressed;
    int has_press;
} button_t;

typedef struct input_box {
    sfRectangleShape *rect;
    sfText *text;
    sfVector2f pos;
    char *str;
    int max_length;
    int is_selected;
} input_box_t;

typedef struct map {
    sfVector2f **dd_map;
    button_t **buttons;
    button_size_t btn_edit_map[4];
    double **td_map;
    int distance;
    int buttonClickPoint;
    int buttonClickMove;
    int *coor_p;
    double delta1;
    double delta2;
    double initial_x;
    double initial_y;
    double initial_z;
    double screen_x;
    double screen_y;
} map_t;

typedef struct map_button {
    char *filename;
    char *display_name;
    button_t *play_button;
    sfText *name_text;
} map_button_t;

typedef struct map_list {
    sfSprite *background;
    button_t **map_buttons;
    int nb_levels;
} map_list_t;

typedef struct create_menu {
    input_box_t **inputs;
    sfSprite *background;
    sfText *title;
    char *title_string;
} create_m_t;

typedef struct main_menu {
    sfSprite *background;
    button_t *play;
    sfText *title;
    char *title_string;
} main_m_t;

typedef struct musics {
    sfMusic *main;
    sfMusic *editor;
} musics_t;

typedef struct textures {
    sfTexture *main_background;
    sfTexture *select_background;
    sfTexture *play_button;
    sfTexture *click_me_button;
    sfTexture *land[5];
    sfTexture *clicked_button;
    sfTexture *hover_button;
    sfTexture *map_button;
    sfTexture *over_map_b;
    sfTexture *create;
} textures_t;

typedef struct world {
    sfRenderWindow *w;
    sfEvent *event;
    textures_t *textures;
    musics_t *musics;
    sfFont *font;
    char *name;
    char opening;
    int map_x;
    int map_y;
    char menu;
} world_t;

typedef enum buttons {
    QUIT,
    SAVE,
    RESET_M,
    RESET_V,
    PLUS,
    LESS,
    END
} buttons_enum_t;

#endif
