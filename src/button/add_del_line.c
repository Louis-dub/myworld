/*
** EPITECH PROJECT, 2026
** engineering
** File description:
** add_del_line
*/

#include "myworld.h"
#include "my_struct.h"

void set_btn(world_t *world, map_t *map, button_size_t *btn)
{
    for (int i = 0; i < 4; i++) {
        btn[i].x3D = (300) / (10.0 * map->distance);
        btn[i].y3D = btn[i].size / (10.0 * map->distance);
    }
    btn[0].x = (world->map_x - 1) / 2.0 - btn[0].x3D / 2.0
        - (world->map_x - 1) / 2.0;
    btn[0].y = -1 - (world->map_y - 1) / 2.0;
    btn[1].x = -1 - (world->map_x - 1) / 2.0;
    btn[1].y = (world->map_y - 1) / 2.0 - btn[1].x3D / 2.0
        - (world->map_y - 1) / 2.0;
    btn[2].x = (world->map_x - 1) / 2.0 - btn[2].x3D / 2.0
        - (world->map_x - 1) / 2.0;
    btn[2].y = (world->map_y - 1) + 1 - world->map_y / 2.0;
    btn[3].x = (world->map_x - 1) + 1 - world->map_x / 2.0;
    btn[3].y = (world->map_y - 1) / 2.0 - btn[3].x3D / 2.0
        - (world->map_y - 1) / 2.0;
}

void add_line_map(world_t *world, map_t *map)
{
    if (map->buttons[LESS]->has_press == 0) {
        if (map->buttons[PLUS]->has_press == 0) {
            map->buttons[PLUS]->has_press = 1;
            reset_view(map);
        } else {
            map->buttons[PLUS]->has_press = 0;
        }
        for (int i = 0; i < 4; i++)
            sfText_setString(map->btn_edit_map[i].text, "+");
        set_btn(world, map, map->btn_edit_map);
    }
}

void del_line_map(world_t *world, map_t *map)
{
    if (map->buttons[PLUS]->has_press == 0) {
        if (map->buttons[LESS]->has_press == 0) {
            map->buttons[LESS]->has_press = 1;
            reset_view(map);
        } else {
            map->buttons[LESS]->has_press = 0;
        }
        for (int i = 0; i < 4; i++)
            sfText_setString(map->btn_edit_map[i].text, "-");
        set_btn(world, map, map->btn_edit_map);
    }
}
