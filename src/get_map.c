/*
** EPITECH PROJECT, 2026
** get_map
** File description:
** load data from a map.legend file
*/

#include "myworld.h"

void manage_first_line(char *line, map_t *map, world_t *world)
{
    char **arr = my_str_to_word_array(line);

    world->map_x = atoi(arr[0]);
    world->map_y = atoi(arr[1]);
    free_arr(arr);
    map->td_map = malloc(sizeof(double *) * world->map_y);
    for (int i = 0; i < world->map_y; i++) {
        map->td_map[i] = malloc(sizeof(double) * world->map_x);
        for (int j = 0; j < world->map_x; j++) {
            map->td_map[i][j] = 0;
        }
    }
}

void put_data_in_map(char *line, map_t *map, world_t *world)
{
    char **arr = my_str_word_array_delim(line, " \n\t\0");

    map->td_map[atoi(arr[0])][atoi(arr[1])] = atof(arr[2]);
    free_arr(arr);
}

void load_map_data(char *levelname, map_t *map, world_t *world)
{
    FILE *f = fopen(levelname, "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    if (f == NULL)
        return;
    nread = getline(&line, &len, f);
    if (nread <= 0) {
        fclose(f);
        return;
    }
    manage_first_line(line, map, world);
    nread = getline(&line, &len, f);
    while (nread > 0) {
        put_data_in_map(line, map, world);
        nread = getline(&line, &len, f);
    }
    free(line);
    fclose(f);
}
