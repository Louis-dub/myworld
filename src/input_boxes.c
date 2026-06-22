/*
** EPITECH PROJECT, 2026
** input_boxes
** File description:
** manage input boxes
*/

#include "myworld.h"

void free_input_box(input_box_t *ib)
{
    if (ib == NULL)
        return;
    if (ib->rect != NULL)
        sfRectangleShape_destroy(ib->rect);
    if (ib->text != NULL)
        sfText_destroy(ib->text);
    if (ib->str != NULL)
        free(ib->str);
    free(ib);
}

void print_input_box(input_box_t *ib, sfRenderWindow *w)
{
    if (ib->rect != NULL)
        sfRenderWindow_drawRectangleShape(w, ib->rect, NULL);
    if (ib->text != NULL)
        sfRenderWindow_drawText(w, ib->text, NULL);
}

static void init_input_rect(input_box_t *ib)
{
    ib->rect = sfRectangleShape_create();
    sfRectangleShape_setPosition(ib->rect, ib->pos);
    sfRectangleShape_setSize(ib->rect, create_vector_f(300, 50));
    sfRectangleShape_setFillColor(ib->rect, sfWhite);
    sfRectangleShape_setOutlineThickness(ib->rect, 2);
    sfRectangleShape_setOutlineColor(ib->rect, sfBlack);
}

input_box_t *create_input_box(float x, float y, int max_len, world_t *world)
{
    input_box_t *ib = malloc(sizeof(input_box_t));

    if (ib == NULL)
        return NULL;
    ib->pos = create_vector_f(x, y);
    ib->max_length = max_len;
    ib->is_selected = 0;
    ib->str = malloc(sizeof(char) * (max_len + 1));
    for (int i = 0; i <= max_len; i++)
        ib->str[i] = '\0';
    init_input_rect(ib);
    ib->text = sfText_create();
    if (world->font != NULL)
        sfText_setFont(ib->text, world->font);
    sfText_setCharacterSize(ib->text, 24);
    sfText_setColor(ib->text, sfBlack);
    sfText_setPosition(ib->text, create_vector_f(x + 10, y + 10));
    sfText_setString(ib->text, ib->str);
    return ib;
}
