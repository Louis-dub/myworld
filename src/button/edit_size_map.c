/*
** EPITECH PROJECT, 2026
** engineering
** File description:
** set_line
*/

#include "myworld.h"
#include "my_struct.h"

static void add_row_back(map_t *map, world_t *world)
{
    if (world->map_y < 42) {
        world->map_y++;
        map->td_map = realloc(map->td_map, sizeof(double*) * world->map_y);
        map->dd_map = realloc(map->dd_map, sizeof(sfVector2f*) * world->map_y);
        memmove(&map->td_map[1], &map->td_map[0],
            sizeof(double*) * (world->map_y - 1));
        memmove(&map->dd_map[1], &map->dd_map[0],
            sizeof(sfVector2f*) * (world->map_y - 1));
        map->td_map[0] = malloc(sizeof(double) * world->map_x);
        map->dd_map[0] = malloc(sizeof(sfVector2f) * world->map_x);
        for (int i = 0; i < world->map_x; i++)
            map->td_map[0][i] = 0.0;
    }
}

static void add_col_back(map_t *map, world_t *world)
{
    if (world->map_x < 42) {
        for (int i = 0; i < world->map_y; i++) {
            map->td_map[i] = realloc(map->td_map[i],
                sizeof(double) * (world->map_x + 1));
            map->dd_map[i] = realloc(map->dd_map[i],
                sizeof(sfVector2f) * (world->map_x + 1));
            memmove(&map->td_map[i][1], &map->td_map[i][0],
                sizeof(double) * world->map_x);
            map->td_map[i][0] = 0.0;
        }
        world->map_x++;
    }
}

static void add_row_front(map_t *map, world_t *world)
{
    if (world->map_y < 42) {
        map->dd_map = realloc(map->dd_map, sizeof(sfVector2f*)
            * (world->map_y + 1));
        map->dd_map[world->map_y] = malloc(sizeof(sfVector2f) * world->map_x);
        map->td_map = realloc(map->td_map,
            sizeof(double*) * (world->map_y + 1));
        world->map_y++;
        map->td_map[world->map_y - 1] = malloc(sizeof(double) * world->map_x);
        for (int i = 0; i < world->map_x; i++)
            map->td_map[world->map_y - 1][i] = 0;
    }
}

static void add_col_front(map_t *map, world_t *world)
{
    if (world->map_x < 42) {
        for (int i = 0; i < world->map_y; i++) {
            map->td_map[i] = realloc(map->td_map[i],
                sizeof(double) * (world->map_x + 1));
            map->dd_map[i] = realloc(map->dd_map[i],
                sizeof(sfVector2f) * (world->map_x + 1));
            map->td_map[i][world->map_x] = 0.0;
        }
        world->map_x++;
    }
}

static void del_row_back(map_t *map, world_t *world)
{
    if (world->map_y > 2) {
        free(map->td_map[0]);
        free(map->dd_map[0]);
        world->map_y--;
        memmove(map->td_map, (map->td_map + 1), sizeof(double*) * world->map_y);
        memmove(map->dd_map, (map->dd_map + 1),
            sizeof(sfVector2f*) * world->map_y);
    }
}

static void del_col_back(map_t *map, world_t *world)
{
    if (world->map_x > 2) {
        world->map_x--;
        for (int i = 0; i < world->map_y; i++) {
            memmove(map->td_map[i], (map->td_map[i] + 1),
                sizeof(double) * world->map_x);
            memmove(map->dd_map[i], (map->dd_map[i] + 1),
                sizeof(sfVector2f) * world->map_x);
        }
    }
}

static void del_row_front(map_t *map, world_t *world)
{
    if (world->map_y > 2) {
        world->map_y--;
        free(map->td_map[world->map_y]);
        free(map->dd_map[world->map_y]);
        map->td_map = realloc(map->td_map, sizeof(double*) * world->map_y);
        map->dd_map = realloc(map->dd_map, sizeof(sfVector2f*) * world->map_y);
    }
}

static void del_col_front(map_t *map, world_t *world)
{
    if (world->map_x > 2) {
        world->map_x--;
        for (int i = 0; i < world->map_y; i++) {
            map->td_map[i] = realloc(map->td_map[i],
                sizeof(double) * world->map_x);
            map->dd_map[i] = realloc(map->dd_map[i],
                sizeof(sfVector2f) * world->map_x);
        }
    }
}

void edit_map(map_t *map, world_t *world, int i)
{
    void (*add_line[4])(map_t *map, world_t *world) = {
        add_col_front, add_row_front,
        add_col_back, add_row_back
    };
    void (*del_line[4])(map_t *map, world_t *world) = {
        del_col_front, del_row_front,
        del_col_back, del_row_back
    };

    if (map->buttons[PLUS]->has_press == 1)
        add_line[3 - i](map, world);
    if (map->buttons[LESS]->has_press == 1)
        del_line[3 - i](map, world);
}
