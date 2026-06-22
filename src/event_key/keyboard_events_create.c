/*
** EPITECH PROJECT, 2026
** events
** File description:
** functions for events like key press
*/

#include "myworld.h"

static void go_back_create_list(create_m_t **create_m, world_t *world)
{
    free_create_menu(*create_m);
    *create_m = NULL;
    world->menu = 'l';
}

static void play_button(create_m_t **menu, world_t *world)
{
    free_create_menu(*menu);
    *menu = NULL;
    world->menu = 'l';
}

void check_input_box_click(input_box_t *ib, sfMouseButtonEvent *event)
{
    sfFloatRect bounds = sfRectangleShape_getGlobalBounds(ib->rect);

    if (sfFloatRect_contains(&bounds, event->x, event->y)) {
        ib->is_selected = 1;
        sfRectangleShape_setOutlineColor(ib->rect, sfRed);
    } else {
        ib->is_selected = 0;
        sfRectangleShape_setOutlineColor(ib->rect, sfBlack);
    }
}

static int find_ib(input_box_t **list)
{
    int i = 0;

    while (i < 3) {
        if (list[i]->is_selected == 1)
            return i;
        i += 1;
    }
    return -1;
}

void handle_text_entered(input_box_t **list, sfTextEvent *event)
{
    int len = 0;
    int i = find_ib(list);

    if (i < 0)
        return;
    len = my_strlen(list[i]->str);
    if (event->unicode == '\b') {
        if (len > 0)
            list[i]->str[len - 1] = '\0';
        sfText_setString(list[i]->text, list[i]->str);
        return;
    }
    if (event->unicode >= 32 && event->unicode < 128) {
        if (len < list[i]->max_length) {
            list[i]->str[len] = (char)event->unicode;
            list[i]->str[len + 1] = '\0';
        }
    }
    sfText_setString(list[i]->text, list[i]->str);
}

void check_click_ib(input_box_t **inputs, sfMouseButtonEvent *event)
{
    if (inputs == NULL)
        return;
    for (int i = 0; i < 3; i++) {
        if (inputs[i] == NULL)
            return;
        check_input_box_click(inputs[i], event);
    }
}

void keyboard_events_create_menu(create_m_t **menu, world_t *world)
{
    while (sfRenderWindow_pollEvent(world->w, world->event)) {
        if (world->event->type == sfEvtClosed) {
            return close_window(world->w);
        }
        if (world->event->type == sfEvtKeyPressed &&
            world->event->key.code == sfKeyEscape) {
            go_back_create_list(menu, world);
            return;
        }
        if (world->event->type == sfEvtMouseButtonPressed)
            check_click_ib((*menu)->inputs, &world->event->mouseButton);
        if (world->event->type == sfEvtTextEntered)
            handle_text_entered((*menu)->inputs, &world->event->text);
        if (sfKeyboard_isKeyPressed(sfKeyEnter) == sfTrue)
            init_map_create(menu, world);
    }
}
