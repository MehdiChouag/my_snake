##
## Makefile for Makefile in /home/david_c/B4/cppProgramming/nibbler
## 
## Made by DAVID Flavien
## Login   <david_c@epitech.net>
## 
## Started on  Thu Mar 13 13:54:58 2014 DAVID Flavien
## Last update Sun Apr  6 19:23:09 2014 Mehdi Chouag
##

NAME_EXE	= nibbler

SRC_EXE		= Core/src/main.cpp \
		  Core/src/Nibbler.cpp \
		  Core/src/Exception.cpp 

OBJ_EXE		= $(SRC_EXE:.cpp=.o)

NAME_LIB	= lib_nibbler_sdl.so

NAME_JOYSTICK	= Bonus/server

SRC_JOYSTICK	= Bonus/Serveur/main.c \
		  Bonus/Serveur/xfunction.c 

OBJ_JOYSTICK	= $(SRC_JOYSTICK:.c=.o)


SRC_LIB		= SDL/src/Lib.cpp \
		  SDL/src/Snake.cpp \
		  SDL/src/Menu.cpp \
		  SDL/src/Exception.cpp

NAME_LIB2	= lib_nibbler_ncurse.so

SRC_LIB2	= NCurse/src/Snake.cpp \
		  NCurse/src/Menu.cpp \
		  NCurse/src/Exception.cpp

NAME_LIB3	= lib_nibbler_opengl.so

SRC_LIB3	= OpenGL/src/Lib.cpp \
		  OpenGL/src/Snake.cpp \
		  OpenGL/src/Menu.cpp \
		  OpenGL/src/Exception.cpp

SDL_FLAG	= -lSDL -lSDL_image -lSDL_gfx -lSDL_ttf -lSDL_mixer

SDL_FLAG2	= -lSDL -lSDL_image -lSDL_gfx -lSDL_ttf -lSDL_mixer -lGL -lGLU

NCURSE_FLAG	= -lncurses

OBJ_LIB		= $(SRC_LIB:.cpp=.o)

OBJ_LIB2	= $(SRC_LIB2:.cpp=.o)

OBJ_LIB3	= $(SRC_LIB3:.cpp=.o)

LDFLAGS		+= -ldl

CXXFLAGS	+= -fPIC -Wall -Werror -Werror -I ./SDL/header -I ./OpenGL/header -I ./Core/header -I ./NCurse/header

CXX		= g++

all: $(NAME_LIB) $(NAME_EXE) $(NAME_JOYSTICK)

$(NAME_EXE): $(OBJ_EXE)
	$(CXX) -o $(NAME_EXE) $(OBJ_EXE) $(LDFLAGS)

$(NAME_JOYSTICK): $(OBJ_JOYSTICK)
	gcc $(OBJ_JOYSTICK) -o $(NAME_JOYSTICK)

$(NAME_LIB): $(OBJ_LIB) $(OBJ_LIB2) $(OBJ_LIB3)
	$(CXX) -shared -o $(NAME_LIB) $(OBJ_LIB) $(SDL_FLAG)
	$(CXX) -shared -o $(NAME_LIB2) $(OBJ_LIB2) $(NCURSE_FLAG)
	$(CXX) -shared -o $(NAME_LIB3) $(OBJ_LIB3) $(SDL_FLAG2)

clean:
	rm -f $(OBJ_LIB) $(OBJ_EXE) $(OBJ_LIB2) $(OBJ_LIB3) $(OBJ_JOYSTICK)

fclean: clean
	rm -f $(NAME_EXE) $(NAME_LIB) $(NAME_LIB2) $(NAME_LIB3) $(NAME_JOYSTICK)

re: fclean all
