/*
** EPITECH PROJECT, 2026
** events
** File description:
** functions for events like key press
*/

#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <SFML/Window/Event.h>
#define _GNU_SOURCE
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "myworld.h"

void go_back_editor_list(map_t **map, world_t *world)
{
    free_map(*map, world);
    *map = NULL;
    world->menu = 'l';
}

static void mouse_wheel(sfEvent *event, map_t *map)
{
    if (event->type == sfEvtMouseWheelScrolled) {
        if (event->mouseWheelScroll.delta > 0.1)
            map->distance += 2;
        else
            map->distance -= 2;
        if (map->distance <= 1)
            map->distance = 1;
        if (map->distance >= 50)
            map->distance = 50;
    }
}

static void move_map_arrows(sfEvent *event, map_t *map, world_t *world)
{
    if (event->type == sfEvtKeyPressed) {
        if (event->key.code == sfKeyUp)
            map->screen_y -= 10;
        if (event->key.code == sfKeyDown)
            map->screen_y += 10;
        if (event->key.code == sfKeyLeft)
            map->screen_x -= 10;
        if (event->key.code == sfKeyRight)
            map->screen_x += 10;
    }
}

void mouse_events(sfEvent *event, map_t **map, world_t *world)
{
    if (event->type == sfEvtMouseButtonPressed) {
        if (check_map_buttons(&event->mouseButton, map, world) == 1)
            return;
    }
    mouse_wheel(event, *map);
    mouse_click(event, *map, world);
    move_map_arrows(event, *map, world);
}

void keyboard_events_editing_map(map_t **map, world_t *world)
{
    while (sfRenderWindow_pollEvent(world->w, world->event)) {
        if (world->event->type == sfEvtClosed) {
            close_window(world->w);
            return;
        }
        if (world->event->type == sfEvtKeyPressed &&
            world->event->key.code == sfKeyEscape) {
            go_back_editor_list(map, world);
            return;
        }
        if (world->event->type == sfEvtKeyPressed &&
            world->event->key.code == sfKeyR) {
            reinit((*map)->td_map, world);
            return;
        }
        mouse_events(world->event, map, world);
    }
}
