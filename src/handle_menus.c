/*
** EPITECH PROJECT, 2026
** handle_menus.c
** File description:
** functions to manage the different menus
*/

#include "myworld.h"

void handle_editing_map(world_t *world, map_t **map)
{
    if (*map == NULL)
        *map = create_map(world);
    print_editing_map(*map, world);
    keyboard_events_editing_map(map, world);
}

void handle_map_list(world_t *world, map_list_t **map_list)
{
    if (*map_list == NULL)
        *map_list = create_map_list(world);
    print_map_list(*map_list, world->w, world);
    keyboard_events_map_list(map_list, world);
}

void handle_main_menu(world_t *world, main_m_t **menu)
{
    if (*menu == NULL)
        *menu = create_main_menu(world);
    print_main_menu(*menu, world->w);
    keyboard_events_main_menu(menu, world);
}

void handle_create_menu(world_t *world, create_m_t **menu)
{
    if (*menu == NULL)
        *menu = create_create_menu(world);
    print_create_menu(*menu, world->w);
    keyboard_events_create_menu(menu, world);
}
