/*
** EPITECH PROJECT, 2026
** save_map
** File description:
** save map data into a map.legend file
*/

#include "myworld.h"

void fill_save(FILE *f, char *name, map_t *map, world_t *world)
{
    char line[500];
    int i = 0;
    int j = 0;

    snprintf(line, 500, "%d %d\n", world->map_x, world->map_y);
    fputs(line, f);
    while (i < world->map_y) {
        j = 0;
        while (j < world->map_x) {
            snprintf(line, 500, "%d %d %f\n", i, j, map->td_map[i][j]);
            fputs(line, f);
            j += 1;
        }
        i += 1;
    }
}

void save_map(map_t *map, world_t *world)
{
    FILE *f;
    char mappath[256];

    snprintf(mappath, 256, "maps/%s", world->name);
    remove(mappath);
    f = fopen(mappath, "w");
    if (f == NULL)
        return;
    fill_save(f, mappath, map, world);
    fclose(f);
}
