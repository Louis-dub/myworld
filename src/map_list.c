/*
** EPITECH PROJECT, 2026
** level_list_menu
** File description:
** manage level_list_menu
*/

#include "myworld.h"

void free_map_list(map_list_t *map_list)
{
    int i = 0;

    if (map_list->map_buttons != NULL) {
        i = 0;
        while (i < map_list->nb_levels) {
            free_button(map_list->map_buttons[i]);
            i += 1;
        }
        free(map_list->map_buttons);
    }
    sfSprite_destroy(map_list->background);
    free(map_list);
}

static int mouse_over_map(sfVector2i *mv, button_t *b, world_t *world)
{
    if (world->textures->hover_button == NULL)
        return 0;
    if (mv->x >= b->pos.x && mv->x <= b->pos.x + b->size * 7) {
        if (mv->y >= b->pos.y && mv->y <= b->pos.y + b->size) {
            return 1;
        }
    }
    return 0;
}

void print_map_list(map_list_t *map_list, sfRenderWindow *w, world_t *world)
{
    sfVector2i mv = sfMouse_getPositionRenderWindow(w);

    sfRenderWindow_drawSprite(w, map_list->background, NULL);
    for (int i = 0; map_list->map_buttons[i] != NULL; i++) {
        if (mouse_over_map(&mv, map_list->map_buttons[i], world) == 1 &&
            map_list->map_buttons[i]->sprite != NULL)
            sfSprite_setTexture(map_list->map_buttons[i]->sprite,
                world->textures->over_map_b, sfTrue);
        if (map_list->map_buttons[i]->sprite != NULL) {
            sfRenderWindow_drawSprite(w, map_list->map_buttons[i]->sprite,
                NULL);
            sfSprite_setTexture(map_list->map_buttons[i]->sprite,
                world->textures->map_button, sfTrue);
        }
        if (map_list->map_buttons[i]->text != NULL)
            sfRenderWindow_drawText(w, map_list->map_buttons[i]->text, NULL);
    }
}

static int count_maps(void)
{
    int nb = 0;
    DIR *d = opendir("maps");
    struct dirent *dir;

    if (d == NULL)
        return 0;
    dir = readdir(d);
    while (dir != NULL) {
        if (dir->d_name[0] != '.')
            nb += 1;
        dir = readdir(d);
    }
    closedir(d);
    return nb;
}

static void init_sprite_text_mbutton(button_t *b, world_t *world)
{
    sfVector2f text_pos = {b->pos.x + 80, b->pos.y + 15};

    if (b->str != NULL && b->text != NULL) {
        sfText_setString(b->text, b->str);
        if (world->font != NULL)
            sfText_setFont(b->text, world->font);
        sfText_setPosition(b->text, text_pos);
        sfText_setColor(b->text, sfWhite);
    }
    if (b->sprite != NULL) {
        sfSprite_setTexture(b->sprite, world->textures->map_button, sfTrue);
        sfSprite_setPosition(b->sprite, b->pos);
    }
}

button_t *create_map_button(char *name, int i, world_t *world)
{
    button_t *b = malloc(sizeof(button_t));

    if (b == NULL)
        return NULL;
    b->pos = (sfVector2f){700, 200 + i * 100};
    b->pressed = '0';
    b->size = 75;
    b->sprite = sfSprite_create();
    b->str = my_strdup(name);
    b->text = sfText_create();
    init_sprite_text_mbutton(b, world);
    return b;
}

void create_button_list(map_list_t *menu, world_t *world)
{
    int i = 0;
    DIR *d = opendir("maps");
    struct dirent *dir;

    if (d == NULL)
        return;
    dir = readdir(d);
    while (i < menu->nb_levels && dir != NULL) {
        if (dir->d_name[0] != '.') {
            menu->map_buttons[i] = create_map_button(dir->d_name, i, world);
            i += 1;
        }
        dir = readdir(d);
    }
    menu->map_buttons[i] = NULL;
    closedir(d);
}

map_list_t *create_map_list(world_t *world)
{
    map_list_t *menu = malloc(sizeof(map_list_t));
    int i = 0;

    menu->background = sfSprite_create();
    if (menu->background != NULL)
        sfSprite_setTexture(menu->background,
            world->textures->select_background, sfTrue);
    menu->nb_levels = count_maps();
    menu->map_buttons = malloc(sizeof(button_t *) * (menu->nb_levels + 1));
    create_button_list(menu, world);
    return menu;
}
