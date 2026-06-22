/*
** EPITECH PROJECT, 2026
** world.c
** File description:
** my_world main file
*/

#include "myworld.h"

void free_musics(musics_t *musics)
{
    if (musics->editor != NULL) {
        sfMusic_stop(musics->editor);
        sfMusic_destroy(musics->editor);
    }
    if (musics->main != NULL) {
        sfMusic_stop(musics->main);
        sfMusic_destroy(musics->main);
    }
    free(musics);
}

void play_music(musics_t *musics, int which)
{
    if (musics == NULL)
        return;
    if (which == 0) {
        if (musics->editor != NULL)
            sfMusic_stop(musics->editor);
        if (musics->main == NULL)
            return;
        sfMusic_play(musics->main);
        return;
    }
    if (musics->main != NULL)
        sfMusic_stop(musics->main);
    if (musics->editor == NULL)
        return;
    sfMusic_play(musics->editor);
}

musics_t *init_musics(void)
{
    musics_t *musics = malloc(sizeof(musics_t));

    if (musics == NULL)
        return NULL;
    musics->editor = sfMusic_createFromFile("res/editor_m.mp3");
    musics->main = sfMusic_createFromFile("res/main_m.mp3");
    if (musics->editor != NULL) {
        sfMusic_setLoop(musics->editor, sfTrue);
    }
    if (musics->main != NULL) {
        sfMusic_setLoop(musics->main, sfTrue);
    }
    return musics;
}
