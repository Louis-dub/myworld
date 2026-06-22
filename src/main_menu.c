/*
** EPITECH PROJECT, 2026
** main_menu
** File description:
** manage main_menu
*/

#include "myworld.h"

void free_main_menu(main_m_t *m)
{
    if (m == NULL)
        return;
    if (m->background != NULL)
        sfSprite_destroy(m->background);
    if (m->play != NULL)
        free_button(m->play);
    if (m->title != NULL)
        sfText_destroy(m->title);
    if (m->title_string != NULL)
        free(m->title_string);
    free(m);
}

void print_main_menu(main_m_t *m, sfRenderWindow *w)
{
    sfRenderWindow_drawSprite(w, m->background, NULL);
    print_button(m->play, w);
    sfRenderWindow_drawText(w, m->title, NULL);
}

main_m_t *create_main_menu(world_t *world)
{
    main_m_t *menu = malloc(sizeof(main_m_t));
    sfVector2f title_pos = {720, 220};

    if (menu == NULL)
        return NULL;
    menu->background = sfSprite_create();
    menu->title = sfText_create();
    menu->title_string = strdup("My_World");
    sfSprite_setTexture(menu->background,
        world->textures->main_background, sfTrue);
    sfText_setString(menu->title, menu->title_string);
    sfText_setCharacterSize(menu->title, 140);
    sfText_setPosition(menu->title, title_pos);
    sfText_setOutlineThickness(menu->title, 5);
    menu->play = create_button(510, 550, 300, world->textures->play_button);
    world->menu = 'm';
    return menu;
}
