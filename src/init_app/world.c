/*
** EPITECH PROJECT, 2026
** world.c
** File description:
** my_world main file
*/

#include "myworld.h"

void free_world(world_t *world)
{
    if (world->event != NULL)
        free(world->event);
    if (world->w != NULL)
        destroy_all(world->w);
    if (world->font != NULL)
        sfFont_destroy(world->font);
    if (world->textures != NULL) {
        free_all_texture(world->textures);
        free(world->textures);
    }
    if (world->musics != NULL)
        free_musics(world->musics);
    free(world);
}

world_t *create_world(void)
{
    world_t *world = malloc(sizeof(world_t));
    sfEvent *event = malloc(sizeof(sfEvent));

    world->w = create_window(1920, 1080);
    world->event = event;
    world->menu = 'm';
    world->textures = load_textures();
    world->musics = init_musics();
    world->font = sfFont_createFromFile("res/Minecraft.ttf");
    world->name = NULL;
    world->opening = 'n';
    world->map_x = 6;
    world->map_y = 6;
    return world;
}
