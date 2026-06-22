/*
** EPITECH PROJECT, 2026
** maths.c
** File description:
** functions from the bootstrap
*/

#define _GNU_SOURCE

#include "myworld.h"

sfVector2f project_iso_point(double x, double y, double z, map_t *map)
{
    sfVector2f two_d_point;
    double rx = 0.0;
    double ry = 0.0;
    double rz = 0.0;

    rx = x * cos(map->delta1 * M_PI / 180) - y * sin(map->delta1 * M_PI / 180);
    ry = x * sin(map->delta1 * M_PI / 180) + y * cos(map->delta1 * M_PI / 180);
    rz = ry * sin(map->delta2 * M_PI / 180) + z * cos(map->delta2 * M_PI / 180);
    ry = ry * cos(map->delta2 * M_PI / 180) - z * sin(map->delta2 * M_PI / 180);
    two_d_point.x = rx * (10 * map->distance) + map->screen_x;
    two_d_point.y = (ry - rz) * (10 * map->distance) + map->screen_y;
    return two_d_point;
}

sfVector2f **create_2d_map(double **three_d_map, world_t *world, map_t *map)
{
    sfVector2f **dmap = malloc(sizeof(sfVector2f*) * world->map_y);
    double cx = world->map_x / 2.0 - 0.5;
    double cy = world->map_y / 2.0 - 0.5;

    for (int i = 0; i < world->map_y; i++) {
        dmap[i] = malloc(sizeof(sfVector2f) * world->map_x);
        for (int j = 0; j < world->map_x; j++)
            dmap[i][j] = project_iso_point(j - cx, i - cy,
                three_d_map[i][j] / 2, map);
    }
    return dmap;
}
