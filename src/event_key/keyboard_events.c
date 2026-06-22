/*
** EPITECH PROJECT, 2026
** events
** File description:
** functions for events like key press
*/

#include "myworld.h"

static void play_button(main_m_t **menu, world_t *world)
{
    free_main_menu(*menu);
    *menu = NULL;
    world->menu = 'l';
}

static void buttons_menu(main_m_t **menu, world_t *world, int mx, int my)
{
    if (mx >= (*menu)->play->pos.x && mx <= (*menu)->play->pos.x +
        (*menu)->play->size * 3) {
        if (my >= (*menu)->play->pos.y && my <= (*menu)->play->pos.y +
            (*menu)->play->size) {
            play_button(menu, world);
            return;
        }
    }
}

void keyboard_events_main_menu(main_m_t **menu, world_t *world)
{
    while (sfRenderWindow_pollEvent(world->w, world->event)) {
        if (world->event->type == sfEvtClosed) {
            return close_window(world->w);
        }
        if (world->event->type == sfEvtKeyPressed &&
            world->event->key.code == sfKeyEscape) {
            close_window(world->w);
            return;
        }
        if (world->event->type == sfEvtKeyPressed &&
            world->event->key.code == sfKeySpace) {
            play_button(menu, world);
            return;
        }
        if (world->event->type == sfEvtMouseButtonPressed
            && world->event->mouseButton.button == sfMouseLeft) {
            buttons_menu(menu, world,
                world->event->mouseButton.x, world->event->mouseButton.y);
        }
    }
}

static void go_back_list_main(map_list_t **map_list, world_t *world)
{
    free_map_list(*map_list);
    *map_list = NULL;
    world->menu = 'm';
}

static void edit_button(map_list_t **map_list, world_t *world)
{
    free_map_list(*map_list);
    *map_list = NULL;
    world->menu = 'e';
    play_music(world->musics, 1);
}

static void start_create(map_list_t **map_list, world_t *world)
{
    free_map_list(*map_list);
    *map_list = NULL;
    world->menu = 'c';
}

static int list_button_clicked(sfMouseButtonEvent *event, button_t *button)
{
    if (event->x >= button->pos.x &&
        event->x <= button->pos.x + button->size * 7) {
        if (event->y >= button->pos.y &&
            event->y <= button->pos.y + button->size)
            return 1;
    }
    return 0;
}

static void start_map(map_list_t **map_list, world_t *world, int i)
{
    if (world->name != NULL)
        free(world->name);
    world->name = NULL;
    world->name = my_strdup((*map_list)->map_buttons[i]->str);
    world->opening = 'y';
    edit_button(map_list, world);
}

void check_map_list_buttons(sfMouseButtonEvent *event,
    map_list_t **map_list, world_t *world)
{
    for (int i = 0; (*map_list)->map_buttons[i] != NULL; i++) {
        if (list_button_clicked(event, (*map_list)->map_buttons[i]) == 1) {
            return start_map(map_list, world, i);
        }
    }
    if (event->x >= 1000 && event->x <= 1650) {
        if (event->y >= 850 && event->y <= 950)
            return start_create(map_list, world);
    }
    if (event->x >= 1325 && event->x <= 1650) {
        if (event->y >= 955 && event->y <= 1055)
            return go_back_list_main(map_list, world);
    }
}

void keyboard_events_map_list(map_list_t **map_list, world_t *world)
{
    while (sfRenderWindow_pollEvent(world->w, world->event)) {
        if (world->event->type == sfEvtClosed)
            return close_window(world->w);
        if (world->event->type == sfEvtKeyPressed &&
            world->event->key.code == sfKeyEscape) {
            go_back_list_main(map_list, world);
            return;
        }
        if (world->event->type == sfEvtMouseButtonPressed
            && world->event->mouseButton.button == sfMouseLeft) {
            check_map_list_buttons(&(world->event->mouseButton),
                map_list, world);
        }
    }
}
