##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## compile
##

MAIN	=		src/main.c

SRC		=		src/sokoban.c				\
				src/get_map.c				\
				src/game.c					\
				src/move_player.c			\
				src/end.c

GRAPHICAL	=	bonus/src/graphical_end.c		\
				bonus/src/graphical_game.c		\
				bonus/src/init_all.c			\
				bonus/src/move_player_r.c		\
				src/get_map.c					\
				src/sokoban.c

OBJ		=		$(SRC:.c=.o) $(MAIN:.c=.o)

GOBJ	=		$(GRAPHICAL:.c=.o) $(MAIN:.c=.o)

TESTS	=		tests/my_strtok.c

NAME	=		my_sokoban

LIB		=		lib/libmy.a

CFLAGS 	=		-W -Wall -Wextra -g

CPPFLAGS	=	-I./include

LDFLAGS	=	-Llib/

LDIBS	=	-lmy -lcurses

LGRAPHICAL	=	-lmy -lcsfml-graphics -lcsfml-window -lcsfml-system

all:		$(NAME)

$(NAME):	$(OBJ) $(LIB)
			gcc -o $(NAME) $(OBJ) $(CPPFLAGS) $(LDFLAGS) $(LDIBS)

$(LIB):
			make -C lib/my

run:		$(NAME)
			./$(NAME)

graphical:	$(GOBJ) $(LIB)
			gcc -o $(NAME) $(GOBJ) $(CPPFLAGS) $(LDFLAGS) $(LGRAPHICAL)

tests_run:	LDIBS += -lcriterion --coverage
tests_run:	all
			gcc -o $@ $(SRC) $(TESTS) $(CPPFLAGS) $(LDFLAGS) $(LDIBS)
			-./$@
			gcovr --branches

clean:
		$(RM) -f src/*.o
		$(RM) *~
		$(RM) *.gc*

fclean:	clean
		$(RM) tests_run
		$(RM) $(NAME)
		$(RM) $(LIB)
		make -C lib/my fclean

re:		fclean all

.PHONY: re fclean clean tests_run run all