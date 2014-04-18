##
## Makefile for  in /home/aube_a/Documents/projet/avm
## 
## Made by Anthony Aube
## Login   <aube_a@epitech.net>
## 
## Started on  Thu Feb 20 02:24:13 2014 Mehdi Chouag
## Last update Sat Apr  5 18:07:40 2014 Mehdi Chouag
##

SRC		= main.c \
		xfunction.c

OBJ             = $(SRC:.c=.o)

NAME            = serveur

CPPFLAGS        = -Wall -Wextra -Werror -I ./header

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(OBJ) -o $(NAME) $(CPPFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
