/*
** EPITECH PROJECT, 2026
** button
** File description:
** functions to create and manage a button
*/

#include "myworld.h"

void free_button(button_t *b)
{
    if (b == NULL)
        return;
    if (b->sprite != NULL)
        sfSprite_destroy(b->sprite);
    if (b->str != NULL)
        free(b->str);
    if (b->text != NULL)
        sfText_destroy(b->text);
    free(b);
}

void print_button(button_t *b, sfRenderWindow *w)
{
    sfRenderWindow_drawSprite(w, b->sprite, NULL);
}

button_t *create_button(float x, float y, int size, sfTexture *texture)
{
    button_t *b = malloc(sizeof(button_t));

    b->text = NULL;
    b->str = NULL;
    b->pos = create_vector_f(x, y);
    b->pressed = '0';
    b->size = size;
    b->sprite = sfSprite_create();
    sfSprite_setPosition(b->sprite, b->pos);
    sfSprite_setTexture(b->sprite, texture, sfTrue);
    return b;
}

static button_size_t create_button_size(int size, sfTexture *texture,
    char *str, world_t *world)
{
    button_size_t b;

    b.text = NULL;
    b.pressed = 0;
    b.size = size;
    b.text = sfText_create();
    sfText_setString(b.text, str);
    if (world->font != NULL)
        sfText_setFont(b.text, world->font);
    sfText_setColor(b.text, sfBlack);
    return b;
}

static void init_button_texts(button_t **list, world_t *world)
{
    list[QUIT]->str = my_strdup("            QUIT");
    list[SAVE]->str = my_strdup("            SAVE");
    list[RESET_M]->str = my_strdup("       RESET MAP");
    list[RESET_V]->str = my_strdup("      RESET VIEW");
    list[PLUS]->str = my_strdup("        ADD LINE");
    list[LESS]->str = my_strdup("     DELETE LINE");
    for (int i = 0; i != END; i++) {
        list[i]->text = sfText_create();
        sfText_setString(list[i]->text, list[i]->str);
        if (world->font != NULL)
            sfText_setFont(list[i]->text, world->font);
        sfText_setPosition(list[i]->text, list[i]->pos);
        sfText_setColor(list[i]->text, sfBlack);
        list[i]->has_press = 0;
    }
}

void create_btn_edit(world_t *world, map_t *map)
{
    map->btn_edit_map[0] = create_button_size(
        48, world->textures->click_me_button, "+", world);
    map->btn_edit_map[1] = create_button_size(
        48, world->textures->click_me_button, "+", world);
    map->btn_edit_map[2] = create_button_size(
        48, world->textures->click_me_button, "+", world);
    map->btn_edit_map[3] = create_button_size(
        48, world->textures->click_me_button, "+", world);
}

button_t **create_buttons(world_t *world)
{
    button_t **list = malloc(sizeof(button_t *) * 7);

    list[QUIT] = create_button(0, 0, 50, world->textures->click_me_button);
    list[SAVE] = create_button(0, 50, 50, world->textures->click_me_button);
    list[RESET_M] = create_button(0, 100, 50, world->textures->click_me_button);
    list[RESET_V] = create_button(0, 150, 50, world->textures->click_me_button);
    list[PLUS] = create_button(1620, 0, 50, world->textures->click_me_button);
    list[LESS] = create_button(1620, 50, 50, world->textures->click_me_button);
    list[END] = NULL;
    init_button_texts(list, world);
    return list;
}
