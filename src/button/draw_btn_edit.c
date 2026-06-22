/*
** EPITECH PROJECT, 2026
** engineering
** File description:
** draw_btn_edit
*/

#define _GNU_SOURCE

#include "myworld.h"
#include "my_struct.h"

static sfVertexArray *create_fill_btn_zero(button_size_t *btn,
    sfVector2f *corners)
{
    sfVertexArray *va = sfVertexArray_create();
    sfVertex v1 = {.position = corners[0],
        .color = sfWhite, .texCoords = {0, 0}};
    sfVertex v2 = {.position = corners[1],
        .color = sfWhite, .texCoords = {300, 0}};
    sfVertex v3 = {.position = corners[2],
        .color = sfWhite, .texCoords = {300, 48}};
    sfVertex v4 = {.position = corners[3],
        .color = sfWhite, .texCoords = {0, 48}};

    sfVertexArray_setPrimitiveType(va, sfQuads);
    sfVertexArray_append(va, v1);
    sfVertexArray_append(va, v2);
    sfVertexArray_append(va, v3);
    sfVertexArray_append(va, v4);
    return va;
}

static sfVertexArray *create_fill_btn_one(button_size_t *btn,
    sfVector2f *corners)
{
    sfVertexArray *va = sfVertexArray_create();
    sfVertex v1 = {.position = corners[0],
        .color = sfWhite, .texCoords = {300, 0}};
    sfVertex v2 = {.position = corners[1],
        .color = sfWhite, .texCoords = {300, 48}};
    sfVertex v3 = {.position = corners[2],
        .color = sfWhite, .texCoords = {0, 48}};
    sfVertex v4 = {.position = corners[3],
        .color = sfWhite, .texCoords = {0, 0}};

    sfVertexArray_setPrimitiveType(va, sfQuads);
    sfVertexArray_append(va, v1);
    sfVertexArray_append(va, v2);
    sfVertexArray_append(va, v3);
    sfVertexArray_append(va, v4);
    return va;
}

static void display_text(button_size_t *btn, sfVector2f *corners,
    world_t *world, double angle)
{
    sfVector2f center;
    sfFloatRect bounds = sfText_getLocalBounds(btn->text);

    center.x = (corners[0].x + corners[2].x) / 2.0;
    center.y = (corners[0].y + corners[2].y) / 2.0;
    if (btn->text != NULL) {
        sfText_setOrigin(btn->text, (sfVector2f){
                .x = bounds.width / 2,
                .y = bounds.height / 2 + bounds.top
        });
        angle = angle * 180 / M_PI;
        sfText_setRotation(btn->text, angle);
        sfText_setPosition(btn->text, center);
        sfRenderWindow_drawText(world->w, btn->text, NULL);
    }
}

static double find_min_z(double **td_map, world_t *world)
{
    double min = td_map[0][0];

    for (int i = 0; i < world->map_y; i++)
        for (int j = 0; j < world->map_x; j++)
            min = fmin(min, td_map[i][j]);
    return min;
}

static sfTexture *find_good_text(sfEvent *event, sfVector2f *corners,
    world_t *world, int pressed)
{
    sfVector2i mv = sfMouse_getPositionRenderWindow(world->w);
    sfVector2f mouse = {
        .x = (float){mv.x},
        .y = (float){mv.y}
    };

    if (pressed == 1)
        return world->textures->clicked_button;
    if (point_in_quad(&mouse, corners) == 1)
        return world->textures->hover_button;
    return world->textures->click_me_button;
}

void set_button_zero(button_size_t *btn, map_t *map, world_t *world,
    sfRenderStates *states)
{
    sfVertexArray *btn_v;
    double angle;
    double z = find_min_z(map->td_map, world);

    btn->corners[0] = project_iso_point(btn->x, btn->y, z, map);
    btn->corners[1] = project_iso_point(btn->x + btn->x3D, btn->y, z, map);
    btn->corners[2] = project_iso_point(btn->x + btn->x3D,
        btn->y + btn->y3D, z, map);
    btn->corners[3] = project_iso_point(btn->x, btn->y + btn->y3D, z, map);
    btn_v = create_fill_btn_zero(btn, btn->corners);
    angle = atan2(btn->corners[1].y - btn->corners[0].y,
        btn->corners[1].x - btn->corners[0].x);
    states->texture = find_good_text(world->event, btn->corners, world,
        btn->pressed);
    sfRenderWindow_drawVertexArray(world->w, btn_v, states);
    display_text(btn, btn->corners, world, angle);
    sfVertexArray_destroy(btn_v);
}

void set_button_one(button_size_t *btn, map_t *map, world_t *world,
    sfRenderStates *states)
{
    sfVertexArray *btn_v;
    double angle;
    double z = find_min_z(map->td_map, world);

    btn->corners[0] = project_iso_point(btn->x,
        btn->y, z, map);
    btn->corners[1] = project_iso_point(btn->x +
        btn->y3D, btn->y, z, map);
    btn->corners[2] = project_iso_point(btn->x + btn->y3D,
        btn->y + btn->x3D, z, map);
    btn->corners[3] = project_iso_point(btn->x,
        btn->y + btn->x3D, z, map);
    btn_v = create_fill_btn_one(btn, btn->corners);
    angle = atan2(btn->corners[3].y - btn->corners[0].y,
        btn->corners[3].x - btn->corners[0].x);
    states->texture = find_good_text(world->event, btn->corners, world,
        btn->pressed);
    sfRenderWindow_drawVertexArray(world->w, btn_v, states);
    display_text(btn, btn->corners, world, angle);
    sfVertexArray_destroy(btn_v);
}

void draw_button_size(button_size_t *btns, map_t *map, world_t *world)
{
    sfRenderStates states = sfRenderStates_default();
    double angle;

    states.texture = world->textures->click_me_button;
    for (int i = 0; i < 4; i++) {
        if (i % 2 == 0) {
            set_button_zero(&btns[i], map, world, &states);
        } else {
            set_button_one(&btns[i], map, world, &states);
        }
        btns[i].pressed = 0;
    }
}
