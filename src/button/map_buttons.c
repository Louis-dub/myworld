/*
** EPITECH PROJECT, 2026
** map_buttons
** File description:
** functions for checking button pressed
*/

#include "myworld.h"

void reinit(double **td_map, world_t *world)
{
    for (int i = 0; i < world->map_y; i++) {
        for (int j = 0; j < world->map_x; j++)
            td_map[i][j] = 0;
    }
}

void reset_view(map_t *map)
{
    map->distance = 10;
    map->delta1 = 35;
    map->delta2 = 24;
    map->initial_x = 0.0;
    map->initial_y = 0.0;
    map->initial_z = 0.0;
    map->screen_x = 960;
    map->screen_y = 540;
}

void button_function(map_t **map, world_t *world, int i)
{
    if (i == QUIT)
        go_back_editor_list(map, world);
    if (i == SAVE)
        save_map(*map, world);
    if (i == RESET_M)
        reinit((*map)->td_map, world);
    if (i == RESET_V)
        reset_view(*map);
    if (i == PLUS)
        add_line_map(world, *map);
    if (i == LESS)
        del_line_map(world, *map);
}

int button_clicked(sfMouseButtonEvent *event, button_t *button)
{
    if (event->x >= button->pos.x &&
        event->x <= button->pos.x + button->size * 6) {
        if (event->y >= button->pos.y &&
            event->y <= button->pos.y + button->size) {
            button->pressed = '9';
            return 1;
        }
    }
    return 0;
}

int check_map_buttons(sfMouseButtonEvent *event, map_t **map, world_t *world)
{
    for (int i = 0; (*map)->buttons[i] != NULL; i++) {
        if (button_clicked(event, (*map)->buttons[i]) == 1) {
            sfSprite_setTexture((*map)->buttons[i]->sprite,
                world->textures->clicked_button, sfTrue);
            button_function(map, world, i);
            return 1;
        }
    }
    return 0;
}
