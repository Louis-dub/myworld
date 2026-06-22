/*
** EPITECH PROJECT, 2026
** create_menu
** File description:
** manage create_menu
*/

#include "myworld.h"

void free_create_menu(create_m_t *m)
{
    if (m == NULL)
        return;
    if (m->background != NULL)
        sfSprite_destroy(m->background);
    if (m->title != NULL)
        sfText_destroy(m->title);
    if (m->title_string != NULL)
        free(m->title_string);
    if (m->inputs != NULL) {
        if (m->inputs[0] != NULL)
            free_input_box(m->inputs[0]);
        if (m->inputs[1] != NULL)
            free_input_box(m->inputs[1]);
        if (m->inputs[2] != NULL)
            free_input_box(m->inputs[2]);
        free(m->inputs);
    }
    free(m);
}

void print_create_menu(create_m_t *m, sfRenderWindow *w)
{
    sfRenderWindow_drawSprite(w, m->background, NULL);
    sfRenderWindow_drawText(w, m->title, NULL);
    sfRenderWindow_drawRectangleShape(w, m->inputs[0]->rect, NULL);
    sfRenderWindow_drawRectangleShape(w, m->inputs[1]->rect, NULL);
    sfRenderWindow_drawRectangleShape(w, m->inputs[2]->rect, NULL);
    sfRenderWindow_drawText(w, m->inputs[0]->text, NULL);
    sfRenderWindow_drawText(w, m->inputs[1]->text, NULL);
    sfRenderWindow_drawText(w, m->inputs[2]->text, NULL);
}

void init_map_create(create_m_t **menu, world_t *world)
{
    int x = 0;
    int y = 0;

    if (world->name != NULL)
        free(world->name);
    world->name = NULL;
    world->name = my_strdup((*menu)->inputs[0]->str);
    world->opening = 'n';
    x = atoi((*menu)->inputs[1]->str);
    y = atoi((*menu)->inputs[2]->str);
    if (x <= 2 || y <= 2 || x > 42 || y > 42)
        return;
    world->map_x = x;
    world->map_y = y;
    free_create_menu(*menu);
    *menu = NULL;
    world->menu = 'e';
}

input_box_t **create_input_boxes(world_t *world)
{
    input_box_t **list = malloc(sizeof(input_box_t *) * 3);

    list[0] = create_input_box(820, 300, 20, world);
    list[1] = create_input_box(820, 500, 5, world);
    list[2] = create_input_box(820, 700, 5, world);
    return list;
}

static char *create_create_menu_str(void)
{
    char *str = malloc(sizeof(char) * 62);

    my_strcpy(str, "      Create World\n\n  Name\n\n\n\n\n\n  X");
    strcat(str, "\n\n\n\n\n\n  Y\n\n\n\n\n\nPress Enter to create");
    return str;
}

create_m_t *create_create_menu(world_t *world)
{
    create_m_t *menu = malloc(sizeof(create_m_t));
    sfVector2f title_pos = {810, 180};

    if (menu == NULL)
        return NULL;
    menu->background = sfSprite_create();
    menu->title = sfText_create();
    menu->title_string = create_create_menu_str();
    sfSprite_setTexture(menu->background,
        world->textures->create, sfTrue);
    sfText_setString(menu->title, menu->title_string);
    sfText_setPosition(menu->title, title_pos);
    sfText_setColor(menu->title, sfWhite);
    sfText_setFont(menu->title, world->font);
    menu->inputs = create_input_boxes(world);
    world->menu = 'c';
    return menu;
}
