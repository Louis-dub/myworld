/*
** EPITECH PROJECT, 2026
** engineering
** File description:
** main
*/

#include "myworld.h"
#include "my_struct.h"

static void free_main_loop(main_m_t *main_menu, map_list_t *map_list,
    map_t *map, world_t *world)
{
    if (main_menu != NULL)
        free_main_menu(main_menu);
    if (map_list != NULL)
        free_map_list(map_list);
    if (map != NULL)
        free_map(map, world);
}

int base_menus(world_t *world, main_m_t **main_menu,
    map_list_t **map_list, map_t **map)
{
    if (world->menu == 'm') {
        handle_main_menu(world, main_menu);
        return 1;
    }
    if (world->menu == 'l') {
        handle_map_list(world, map_list);
        return 1;
    }
    if (world->menu == 'e') {
        handle_editing_map(world, map);
        return 1;
    }
    return 0;
}

void special_menus(world_t *world, create_m_t **create_menu)
{
    if (world->menu == 'c') {
        handle_create_menu(world, create_menu);
    }
}

int main_loop(world_t *world)
{
    main_m_t *main_menu = NULL;
    map_list_t *map_list = NULL;
    map_t *map = NULL;
    create_m_t *create_menu = NULL;
    sfColor color = sfColor_fromRGB(131, 132, 135);

    if (world == NULL)
        return 84;
    play_music(world->musics, 0);
    while (sfRenderWindow_isOpen(world->w)) {
        sfRenderWindow_clear(world->w, color);
        if (base_menus(world, &main_menu, &map_list, &map) == 0)
            special_menus(world, &create_menu);
        sfRenderWindow_display(world->w);
    }
    free_create_menu(create_menu);
    free_main_loop(main_menu, map_list, map, world);
    free_world(world);
    return 0;
}

static int info(char *argv)
{
    if (argv[0] == '-' && argv[1] == 'h') {
        printf("my_world\n");
        printf("3D map editing simulator\n");
        return 0;
    }
    write(2, "wrong arguments, try : ""./my_world -h or ./my_world\n", 54);
    return 84;
}

int main(int argc, char **argv)
{
    world_t *world;

    if (argc == 1) {
        world = create_world();
        return main_loop(world);
    }
    if (argc > 2) {
        write(2, "too many arguments, try : ", 27);
        write(2, "./my_world -h or ./my_world\n", 31);
        return 84;
    }
    if (strlen(argv[1]) == 2)
        return info(argv[1]);
    write(2, "wrong arguments, try : ""./my_world -h or ./my_world\n", 54);
    return 84;
}
