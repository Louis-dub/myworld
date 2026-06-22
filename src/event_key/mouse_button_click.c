/*
** EPITECH PROJECT, 2026
** engineering
** File description:
** mouse_button_click
*/

#define _GNU_SOURCE

#include "myworld.h"
#include "my_struct.h"

static int point_coordinates(map_t *map, sfMouseButtonEvent *event,
    int i, int j)
{
    int x = event->x;
    int y = event->y;

    if (map->dd_map[i][j].x + 20 >= x && map->dd_map[i][j].x - 20 <= x) {
        if (map->dd_map[i][j].y + 20 >= y && map->dd_map[i][j].y - 20 <= y) {
            map->coor_p[0] = i;
            map->coor_p[1] = j;
            return 1;
        }
    }
    return 0;
}

static int detect_point_x(sfMouseButtonEvent *event, map_t *map,
    world_t *world, int i)
{
    for (int j = 0; j < world->map_x; j++) {
        if (point_coordinates(map, event, i, j) == 1)
            return 1;
    }
    return 0;
}

static int detect_point(sfMouseButtonEvent *event, map_t *map,
    world_t *world)
{
    for (int i = 0; i < world->map_y; i++) {
        if (detect_point_x(event, map, world, i) == 1)
            return 1;
    }
    return 0;
}

static void detect_nearest_point(world_t *world, map_t *map, int x, int y)
{
    if (x != world->map_y - 1)
        if (map->td_map[x][y] <= map->td_map[x + 1][y] + 0.1
            && map->td_map[x][y] >= map->td_map[x + 1][y] - 0.1)
            map->td_map[x][y] = map->td_map[x + 1][y];
    if (y != world->map_x - 1)
        if (map->td_map[x][y] <= map->td_map[x][y + 1] + 0.1
            && map->td_map[x][y] >= map->td_map[x][y + 1] - 0.1)
            map->td_map[x][y] = map->td_map[x][y + 1];
    if (x != 0)
        if (map->td_map[x][y] <= map->td_map[x - 1][y] + 0.1
            && map->td_map[x][y] >= map->td_map[x - 1][y] - 0.1)
            map->td_map[x][y] = map->td_map[x - 1][y];
    if (y != 0)
        if (map->td_map[x][y] <= map->td_map[x][y - 1] + 0.1
            && map->td_map[x][y] >= map->td_map[x][y - 1] - 0.1)
            map->td_map[x][y] = map->td_map[x][y - 1];
}

static void move_point(world_t *world, map_t *map, sfEvent *event)
{
    int x;
    int y;
    int delta_y;
    float sign = cos(map->delta2 * M_PI / 180) >= 0 ? 1.0 : -1.0;

    x = map->coor_p[0];
    y = map->coor_p[1];
    delta_y = (event->mouseMove.y - map->initial_y) * sign;
    map->td_map[x][y] = map->initial_z - delta_y / (10.0 * map->distance);
    detect_nearest_point(world, map, x, y);
    if (10 < map->td_map[x][y])
        map->td_map[x][y] = 10;
    if (-5 > map->td_map[x][y])
        map->td_map[x][y] = -5;
}

static void move_map(map_t *map, sfEvent *event)
{
    double delta_x = event->mouseMove.x - map->initial_x;
    double delta_y = event->mouseMove.y - map->initial_y;
    float sign = cos(map->delta2 * M_PI / 180) >= 0 ? 1.0 : -1.0;

    map->delta1 += delta_x * -0.1 * sign;
    map->initial_x = event->mouseMove.x;
    if (map->buttons[PLUS]->has_press == 0
        && map->buttons[LESS]->has_press == 0) {
        map->delta2 += delta_y * -0.1;
        map->initial_y = event->mouseMove.y;
    }
}

static void set_or_move(sfEvent *event, map_t *map, world_t *world)
{
    int v = 0;

    if (map->buttons[PLUS]->has_press == 1) {
        v = verif_btn(event, map->btn_edit_map, world, map);
    } else if (map->buttons[LESS]->has_press) {
        v = verif_btn(event, map->btn_edit_map, world, map);
    }
    if (v == 0) {
        map->initial_x = event->mouseButton.x;
        map->buttonClickMove = 1;
    }
}

static void mouse_button_press(sfEvent *event, map_t *map, world_t *world)
{
    if (detect_point(&event->mouseButton, map, world) == 1
        && map->buttons[PLUS]->has_press == 0
        && map->buttons[LESS]->has_press == 0) {
        map->buttonClickPoint = 1;
        map->initial_z = map->td_map[map->coor_p[0]][map->coor_p[1]];
    } else {
        set_or_move(event, map, world);
    }
}

void mouse_click(sfEvent *event, map_t *map, world_t *world)
{
    int x;
    int y;
    int delta_y;

    if (event->type == sfEvtMouseButtonPressed) {
        map->initial_y = event->mouseButton.y;
        mouse_button_press(event, map, world);
    }
    if (event->type == sfEvtMouseButtonReleased) {
        map->buttonClickPoint = 0;
        map->buttonClickMove = 0;
    }
    if (event->type == sfEvtMouseMoved) {
        if (map->buttonClickPoint == 1)
            move_point(world, map, event);
        if (map->buttonClickMove == 1)
            move_map(map, event);
    }
}
