/*
** EPITECH PROJECT, 2026
** engineering
** File description:
** my_color
*/

#include <SFML/Graphics.h>
#include <SFML/Graphics/Image.h>

#include "myworld.h"
#include "my_struct.h"

void free_all_texture(textures_t *textures)
{
    if (textures->main_background != NULL)
        sfTexture_destroy(textures->main_background);
    if (textures->select_background != NULL)
        sfTexture_destroy(textures->select_background);
    if (textures->play_button != NULL)
        sfTexture_destroy(textures->play_button);
    if (textures->click_me_button != NULL)
        sfTexture_destroy(textures->click_me_button);
    if (textures->clicked_button != NULL)
        sfTexture_destroy(textures->clicked_button);
    if (textures->hover_button != NULL)
        sfTexture_destroy(textures->hover_button);
    if (textures->map_button != NULL)
        sfTexture_destroy(textures->map_button);
    if (textures->over_map_b != NULL)
        sfTexture_destroy(textures->over_map_b);
    if (textures->create != NULL)
        sfTexture_destroy(textures->create);
    for (int i = 0; i < 5; i++)
        sfTexture_destroy(textures->land[i]);
}

sfTexture *create_texture(sfColor *color)
{
    sfImage *image = sfImage_create(256, 256);
    sfTexture *texture;
    sfColor f_color;

    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            f_color = sfColor_fromRGB(
                (sfUint8)fmax(0, fmin(255, (int)color->r + rand() % 21 - 10)),
                (sfUint8)fmax(0, fmin(255, (int)color->g + rand() % 21 - 10)),
                (sfUint8)fmax(0, fmin(255, (int)color->b + rand() % 21 - 10))
            );
            sfImage_setPixel(image, i, j, f_color);
        }
    }
    texture = sfTexture_createFromImage(image, NULL);
    sfImage_destroy(image);
    return texture;
}

void generate_land_texture(textures_t *textures)
{
    sfColor color1 = sfColor_fromRGB(30, 100, 200);
    sfColor color2 = sfColor_fromRGB(194, 178, 128);
    sfColor color3 = sfColor_fromRGB(34, 139, 34);
    sfColor color4 = sfColor_fromRGB(128, 128, 128);
    sfColor color5 = sfColor_fromRGB(240, 240, 255);

    textures->land[0] = create_texture(&color1);
    textures->land[1] = create_texture(&color2);
    textures->land[2] = create_texture(&color3);
    textures->land[3] = create_texture(&color4);
    textures->land[4] = create_texture(&color5);
}

textures_t *load_textures(void)
{
    textures_t *textures = malloc(sizeof(textures_t));

    if (textures == NULL)
        return NULL;
    textures->main_background =
        sfTexture_createFromFile("res/main_background.jpg", NULL);
    textures->select_background =
        sfTexture_createFromFile("res/select_world.png", NULL);
    textures->play_button =
        sfTexture_createFromFile("res/play_button.png", NULL);
    textures->click_me_button = sfTexture_createFromFile("res/b.png", NULL);
    textures->clicked_button =
        sfTexture_createFromFile("res/hover_button.png", NULL);
    textures->hover_button =
        sfTexture_createFromFile("res/clicked_button.png", NULL);
    textures->map_button = sfTexture_createFromFile("res/map_b.png", NULL);
    textures->over_map_b = sfTexture_createFromFile("res/select_m.png", NULL);
    textures->create = sfTexture_createFromFile("res/create.png", NULL);
    generate_land_texture(textures);
    return textures;
}
