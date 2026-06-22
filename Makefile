##                                                                                                                                                                                                                                     
## EPITECH PROJECT, 2025                                                                                                                                                                                                               
## Makefile                                                                                                                                                                                                                            
## File description:                                                                                                                                                                                                                   
## Makefile                                                                                                                                                                                                                            
##

NAME 	=	my_world

SRC		=	main.c	\
			src/cursor.c \
			src/input_boxes.c \
			src/handle_menus.c \
			src/main_menu.c \
			src/create_menu.c \
			src/map.c \
			src/map_list.c \
			src/maths.c \
			src/get_map.c \
			src/save_map.c \
			src/display_map.c	\
			src/init_app/world.c \
			src/init_app/window.c \
			src/init_app/load_texture.c	\
			src/init_app/music.c \
			src/my_lib/my_strdup.c \
			src/my_lib/my_str_to_wordarray.c \
			src/my_lib/utilitary.c \
			src/my_lib/my_strcpy.c \
			src/event_key/keyboard_events.c \
			src/event_key/keyboard_events_world.c \
			src/event_key/mouse_button_click.c \
			src/event_key/keyboard_events_create.c	\
			src/button/button.c \
			src/button/add_del_line.c	\
			src/button/map_buttons.c \
			src/button/draw_btn_edit.c	\
			src/button/verif_btn_size.c	\
			src/button/edit_size_map.c

OBJ 	=	$(SRC:.c=.o)

CC	=	epiclang

CFLAGS	:=	-Iinclude

LDFLAGS	:=	-l csfml-graphics -l csfml-window -lcsfml-system -lcsfml-audio -lm

RM	:=	rm -fr

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re
