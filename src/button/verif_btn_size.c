/*
** EPITECH PROJECT, 2026
** engineering
** File description:
** edit_size_map
*/

#include "myworld.h"
#include "my_struct.h"

int point_in_quad(sfVector2f *point, sfVector2f *corners)
{
    int inside = 0;
    int j = 3;

    for (int i = 0; i < 4; i++) {
        if (((corners[i].y > point->y) != (corners[j].y > point->y)) &&
            (point->x < (corners[j].x - corners[i].x)
                * (point->y - corners[i].y)
                / (corners[j].y - corners[i].y) + corners[i].x))
            inside = !inside;
        j = i;
    }
    return inside;
}

int verif_btn(sfEvent *event, button_size_t *btns, world_t *world,
    map_t *map)
{
    sfVector2f pos = {event->mouseButton.x, event->mouseButton.y};

    for (int i = 0; i < 4; i++) {
        if (point_in_quad(&pos, btns[i].corners) == 1) {
            edit_map(map, world, i);
            set_btn(world, map, map->btn_edit_map);
            return 1;
        }
    }
    return 0;
}
