/*
** EPITECH PROJECT, 2026
** my_gd.h
** File description:
** header file for my_gd project
*/

#ifndef MY_WORLD_
    #define MY_WORLD_
    #include <SFML/Graphics/RenderWindow.h>
    #include <SFML/Graphics/Color.h>
    #include <SFML/Graphics/RenderTexture.h>
    #include <SFML/Graphics/Texture.h>
    #include <SFML/Graphics/Sprite.h>
    #include <SFML/Graphics.h>
    #include <SFML/System/Export.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <SFML/System.h>
    #include <SFML/Config.h>
    #include <stdlib.h>
    #include <SFML/Window/Mouse.h>
    #include <SFML/Window/Keyboard.h>
    #include <SFML/Audio.h>
    #include <SFML/Audio/Types.h>
    #include <SFML/Audio/Export.h>
    #include <SFML/Audio/Sound.h>
    #include <SFML/Audio/Music.h>
    #include <SFML/Audio/SoundBuffer.h>
    #include <SFML/System/InputStream.h>
    #include <SFML/System/Time.h>
    #include <SFML/Audio/SoundStatus.h>
    #include <stdio.h>
    #include <math.h>
    #include <string.h>
    #include <time.h>
    #include <dirent.h>
    #include "my_struct.h"

void free_arr(char **ar);

int my_strlen(char *str);
char *my_strdup(char *str);
char *my_strcpy(char *dest, char const *src);
char **my_str_to_word_array(char *str);
char **my_str_word_array_delim(char *str, char *delim);
char *int_to_str(int nb);
char *float_to_str(float nb);

sfVector2u create_vector(int x, int y);
sfVector2f create_vector_f(float x, float y);

void window_disp_clear(sfRenderWindow *window);
void close_window(sfRenderWindow *window);
void destroy_all(sfRenderWindow *window);
sfRenderWindow *create_window(unsigned int width,
    unsigned int height);
world_t *create_world(void);
void free_world(world_t *world);

textures_t *load_textures(void);
void free_all_texture(textures_t *textures);

cursor_t *create_cursor(void);
void print_cursor(cursor_t *cursor, sfRenderWindow *window);
void free_cursor(cursor_t *cursor);

void free_musics(musics_t *musics);
void play_music(musics_t *musics, int which);
musics_t *init_musics(void);

void free_input_box(input_box_t *ib);
void print_input_box(input_box_t *ib, sfRenderWindow *w);
input_box_t *create_input_box(float x, float y, int max_len, world_t *world);

void handle_editing_map(world_t *world, map_t **map);
void handle_map_list(world_t *world, map_list_t **map_list);
void handle_main_menu(world_t *world, main_m_t **menu);
void handle_create_menu(world_t *world, create_m_t **menu);

void keyboard_events_main_menu(main_m_t **menu, world_t *world);
void keyboard_events_editing_map(map_t **map, world_t *world);
void keyboard_events_map_list(map_list_t **map_list, world_t *world);
void keyboard_events_create_menu(create_m_t **menu, world_t *world);

void free_main_menu(main_m_t *m);
void print_main_menu(main_m_t *m, sfRenderWindow *w);
main_m_t *create_main_menu(world_t *world);

void free_create_menu(create_m_t *m);
void print_create_menu(create_m_t *m, sfRenderWindow *w);
create_m_t *create_create_menu(world_t *world);
void init_map_create(create_m_t **menu, world_t *world);

void free_map_list(map_list_t *map_list);
void print_map_list(map_list_t *map_list, sfRenderWindow *w, world_t *world);
map_list_t *create_map_list(world_t *world);

void free_button(button_t *b);
void print_button(button_t *b, sfRenderWindow *w);
button_t *create_button(float x, float y, int size, sfTexture *texture);
button_t **create_buttons(world_t *world);
int check_map_buttons(sfMouseButtonEvent *event, map_t **map, world_t *world);
void create_btn_edit(world_t *world, map_t *map);
void add_line_map(world_t *world, map_t *map);
void del_line_map(world_t *world, map_t *map);
void draw_button_size(button_size_t *btns, map_t *map, world_t *world);
void reset_view(map_t *map);

int verif_btn(sfEvent *event, button_size_t *btns, world_t *world, map_t *map);
int point_in_quad(sfVector2f *point, sfVector2f *corners);
void set_btn(world_t *world, map_t *map, button_size_t *btn);
void edit_map(map_t *map, world_t *world, int i);

void go_back_editor_list(map_t **map, world_t *world);
map_t *create_map(world_t *world);
void reinit(double **td_map, world_t *world);
void free_map(map_t *map, world_t *world);
void print_editing_map(map_t *map, world_t *world);
sfVector2f project_iso_point(double x, double y, double z, map_t *map);
sfVector2f **create_2d_map(double **three_d_map, world_t *world, map_t *map);
int draw_2d_map(sfRenderWindow *window, sfVector2f **two_d_map,
    world_t *world, map_t *map);
void load_map_data(char *levelname, map_t *map, world_t *world);
void save_map(map_t *map, world_t *world);
void mouse_click(sfEvent *event, map_t *map, world_t *world);

#endif
