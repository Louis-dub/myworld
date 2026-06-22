/*
** EPITECH PROJECT, 2026
** level
** File description:
** functions to create and manage a level
*/

#include <SFML/Graphics/Text.h>
#include <stdlib.h>

#include "my_struct.h"
#include "myworld.h"

void free_map(map_t *map, world_t *world)
{
    if (map == NULL)
        return;
    if (map->buttons != NULL) {
        for (int k = 0; map->buttons[k] != NULL; k++)
            free_button(map->buttons[k]);
        free(map->buttons);
    }
    if (map->td_map != NULL) {
        for (int i = 0; i < world->map_y; i++)
            free(map->td_map[i]);
        free(map->td_map);
    }
    if (map->dd_map != NULL) {
        for (int j = 0; j < world->map_y; j++)
            free(map->dd_map[j]);
        free(map->dd_map);
    }
    free(map->coor_p);
    free(map);
}

void update_2d_map(map_t *map, world_t *world)
{
    double cx = world->map_x / 2.0 - 0.5;
    double cy = world->map_y / 2.0 - 0.5;

    for (int i = 0; i < world->map_y; i++) {
        for (int j = 0; j < world->map_x; j++)
            map->dd_map[i][j] = project_iso_point(j - cx, i - cy,
                map->td_map[i][j], map);
    }
}

static int mouse_over_button(sfVector2i *mv, button_t *b, world_t *world)
{
    if (b->sprite == NULL || world->textures->hover_button == NULL)
        return 0;
    if (mv->x >= b->pos.x && mv->x <= b->pos.x + b->size * 6) {
        if (mv->y >= b->pos.y && mv->y <= b->pos.y + b->size) {
            return 1;
        }
    }
    return 0;
}

static void draw_buttons(button_t **list, world_t *world)
{
    int i = 0;
    sfVector2i mv = sfMouse_getPositionRenderWindow(world->w);

    while (list[i] != NULL) {
        if (mouse_over_button(&mv, list[i], world) == 1 &&
            list[i]->pressed == '0')
            sfSprite_setTexture(list[i]->sprite,
                world->textures->hover_button, sfTrue);
        if (list[i]->sprite != NULL) {
            sfRenderWindow_drawSprite(world->w, list[i]->sprite, NULL);
            sfSprite_setTexture(list[i]->sprite,
                world->textures->click_me_button, sfTrue);
        }
        if (list[i]->text != NULL)
            sfRenderWindow_drawText(world->w, list[i]->text, NULL);
        list[i]->pressed -= 1;
        if (list[i]->pressed < '0')
            list[i]->pressed = '0';
        i += 1;
    }
}

void print_editing_map(map_t *map, world_t *world)
{
    update_2d_map(map, world);
    if (map->buttons[PLUS]->has_press == 1
        || map->buttons[LESS]->has_press == 1)
        draw_button_size(map->btn_edit_map, map, world);
    draw_2d_map(world->w, map->dd_map, world, map);
    draw_buttons(map->buttons, world);
}

double **create_empty_map(world_t *world)
{
    double **map = malloc(sizeof(double *) * world->map_y);

    for (int i = 0; i < world->map_y; i++) {
        map[i] = malloc(sizeof(double) * world->map_x);
        for (int j = 0; j < world->map_x; j++) {
            map[i][j] = 0;
        }
    }
    return map;
}

static void init_int_double(map_t *map)
{
    map->distance = 10;
    map->buttonClickPoint = 0;
    map->buttonClickMove = 0;
    map->delta1 = 35;
    map->delta2 = 24;
    map->initial_x = 0.0;
    map->initial_y = 0.0;
    map->initial_z = 0.0;
    map->screen_x = 960;
    map->screen_y = 540;
}

map_t *create_map(world_t *world)
{
    map_t *map = malloc(sizeof(map_t));
    char mappath[256];

    map->buttons = create_buttons(world);
    map->td_map = NULL;
    map->dd_map = NULL;
    init_int_double(map);
    map->coor_p = malloc(sizeof(int) * 2);
    if (world->opening == 'y') {
        snprintf(mappath, 256, "maps/%s", world->name);
        load_map_data(mappath, map, world);
    } else {
        map->td_map = create_empty_map(world);
    }
    map->dd_map = create_2d_map(map->td_map, world, map);
    create_btn_edit(world, map);
    return map;
}
