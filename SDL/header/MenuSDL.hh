//
// Snake.hh for Snake in /home/chouag_m/rendu/Snake
// 
// Made by Mehdi Chouag
// Login   <chouag_m@epitech.net>
// 
// Started on  Mon Mar 10 16:28:12 2014 Mehdi Chouag
// Last update Sat Apr  5 20:48:33 2014 Mehdi Chouag
//

#ifndef MENUSDL_HH_
# define MENUSDL_HH_

# include <iostream>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <SDL/SDL_ttf.h>
# include <SDL/SDL_mixer.h>
# include <vector>
# include <stdlib.h>
# include <map>
# include "LibSDL.hh"
# include "ILibrary.hh"

# define BUTTON_A 0
# define BUTTON_SELECT 6
# define BUTTON_START 7

class Menu
{
public:
  Menu(const int&, const int&);
  ~Menu();
  Step		loop();
  int		getLevel() const;
  bool		getSound() const;
  bool		getMusic() const;
  SDL_Surface	*getScreen() const;

private:
  void		initAll();
  void		freeAll() const;
  void		initSDL();
  void		initFont();
  void		print_menu() const;
  void	        Keyboard();
  void	        Button();
  void		refresh_menu() const;
  void		main_menu();
  SDL_Surface	*make_font(std::string const &, SDL_Color) const;
  void	        up();
  void	        down();
  void	        left();
  void	        right();

private:
  int		_x;
  int		_y;
  Step		_return;
  SDL_Surface	*_screen;
  SDL_Surface	*_fond;
  SDL_Event	_event;
  bool	        _loop;
  SDL_Color     _black;
  SDL_Color	_red;
  TTF_Font	*_font;
  SDL_Joystick	*_joystick;
  size_t	_choise;
  size_t	_optionMusic;
  size_t	_optionLevel;
  size_t	_optionSound;
  Mix_Music	*_music;
  bool		_isMusic;
  bool		_isSound;
  int		_isLevel;
  std::vector<SDL_Surface *>  _message;
  std::vector<SDL_Surface *> _response;
  std::vector<SDL_Surface *> _responseMessage;
  std::vector<std::string> _name;
  std::vector<std::string> _responseName;
  std::vector<std::string> _responseLevel;
  std::map<int, void(Menu::*)()> _movek;
  std::map<int, void(Menu::*)()> _movej;
};

#endif /* !MENUOPENGL_HH */
