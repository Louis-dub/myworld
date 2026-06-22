/*
** EPITECH PROJECT, 2026
** engineering
** File description:
** display_map
*/

#define _GNU_SOURCE

#include "myworld.h"

static sfTexture *find_good_texture(sfTexture **textures, double z)
{
    if (z < 0)
        return textures[0];
    if (0 <= z && z < 0.5)
        return textures[1];
    if (0.5 <= z && z < 1.5)
        return textures[2];
    if (1.5 <= z && z < 2)
        return textures[3];
    return textures[4];
}

sfColor get_land_color(double z)
{
    if (z < 0)
        return sfColor_fromRGB(30, 100, 200);
    if (0 <= z && z < 0.5)
        return sfColor_fromRGB(194, 178, 128);
    if (0.5 <= z && z < 3)
        return sfColor_fromRGB(34, 139, 34);
    if (3 <= z && z < 5)
        return sfColor_fromRGB(128, 128, 128);
    return sfColor_fromRGB(240, 240, 255);
}

static sfVertexArray *create_fill_square(square_t *square, textures_t *textures)
{
    sfVertexArray *va = sfVertexArray_create();
    sfVertex v1 = {.position = square->p1,
        .color = get_land_color(square->zs[0]), .texCoords = {0, 0}};
    sfVertex v2 = {.position = square->p2,
        .color = get_land_color(square->zs[1]), .texCoords = {256, 0}};
    sfVertex v3 = {.position = square->p3,
        .color = get_land_color(square->zs[2]), .texCoords = {256, 256}};
    sfVertex v4 = {.position = square->p4,
        .color = get_land_color(square->zs[3]), .texCoords = {0, 256}};

    sfVertexArray_setPrimitiveType(va, sfTriangles);
    sfVertexArray_append(va, v1);
    sfVertexArray_append(va, v2);
    sfVertexArray_append(va, v3);
    sfVertexArray_append(va, v1);
    sfVertexArray_append(va, v3);
    sfVertexArray_append(va, v4);
    return va;
}

static sfVertexArray *create_line(sfVector2f *point1, sfVector2f *point2)
{
    sfVertexArray *vertex_array = sfVertexArray_create();
    sfVertex vertex1 = {.position = *point1, .color = sfBlack};
    sfVertex vertex2 = {.position = *point2, .color = sfBlack};

    sfVertexArray_append(vertex_array, vertex1);
    sfVertexArray_append(vertex_array, vertex2);
    sfVertexArray_setPrimitiveType(vertex_array, sfLinesStrip);
    return (vertex_array);
}

static void print_line(sfRenderWindow *window,
    sfVector2f *point1, sfVector2f *point2)
{
    sfVertexArray *vertex = create_line(point1, point2);

    sfRenderWindow_drawVertexArray(window, vertex, NULL);
    sfVertexArray_destroy(vertex);
}

int compare_square(const void *a, const void *b, void *ctx)
{
    square_t *s1 = (square_t *)a;
    square_t *s2 = (square_t *)b;
    int sign = *(int *)ctx;

    if (s1->depth < s2->depth) {
        return -1 * sign;
    } else {
        return 1 * sign;
    }
}

void set_square(square_t *square, map_t *map, sfVector2f **two_d_map, int *coor)
{
    double avg_z;

    square->p1 = two_d_map[coor[0]][coor[1]];
    square->p2 = two_d_map[coor[0]][coor[1] + 1];
    square->p3 = two_d_map[coor[0] + 1][coor[1] + 1];
    square->p4 = two_d_map[coor[0] + 1][coor[1]];
    square->zs[0] = map->td_map[coor[0]][coor[1]];
    square->zs[1] = map->td_map[coor[0]][coor[1] + 1];
    square->zs[2] = map->td_map[coor[0] + 1][coor[1] + 1];
    square->zs[3] = map->td_map[coor[0] + 1][coor[1]];
    avg_z = (map->td_map[coor[0]][coor[1]] + map->td_map[coor[0]][coor[1] + 1]
        + map->td_map[coor[0] + 1][coor[1] + 1]
        + map->td_map[coor[0] + 1][coor[1]]) / 4.0;
    square->depth = coor[1] * sin(map->delta1 * M_PI / 180)
        + coor[0] * cos(map->delta1 * M_PI / 180)
        - avg_z * sin(map->delta2 * M_PI / 180);
    square->min = fmin(fmin(square->zs[0], square->zs[1]),
        fmin(square->zs[2], square->zs[3]));
}

static square_t *create_square(int total, world_t *world,
    sfVector2f **two_d_map, map_t *map)
{
    int ids = 0;
    square_t *squares = malloc(sizeof(square_t) * total);
    double avg_z;
    int coor[2];

    for (int i = 0; i + 1 < world->map_y; i++) {
        for (int j = 0; j + 1 < world->map_x; j++) {
            coor[0] = i;
            coor[1] = j;
            set_square(&squares[ids], map, two_d_map, coor);
            ids++;
        }
    }
    return squares;
}

static void print_elements(sfRenderWindow *window,
    world_t *world, square_t *squares, int i)
{
    sfRenderStates states = sfRenderStates_default();
    sfVertexArray *square = create_fill_square(&squares[i], world->textures);
    sfTexture *texture = find_good_texture(world->textures->land,
        squares[i].min);

    states.texture = texture;
    sfRenderWindow_drawVertexArray(window, square, &states);
    sfVertexArray_destroy(square);
    print_line(window, &squares[i].p1, &squares[i].p2);
    print_line(window, &squares[i].p2, &squares[i].p3);
    print_line(window, &squares[i].p3, &squares[i].p4);
    print_line(window, &squares[i].p4, &squares[i].p1);
}

int draw_2d_map(sfRenderWindow *window, sfVector2f **two_d_map,
    world_t *world, map_t *map)
{
    sfVertexArray *square;
    int total = (world->map_x - 1) * (world->map_y - 1);
    square_t *squares = create_square(total, world, two_d_map, map);
    int sign = cos(map->delta2 * M_PI / 180) >= 0 ? 1.0 : -1.0;
    sfTexture *texture;

    qsort_r(squares, total, sizeof(square_t), compare_square, &sign);
    for (int i = 0; i < total; i++)
        print_elements(window, world, squares, i);
    free(squares);
    return 0;
}
