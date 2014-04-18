//
// Snake.hh for Snake.hh in /home/chouag_m/rendu/cpp_nibbler/SDL/header
// 
// Made by Mehdi Chouag
// Login   <chouag_m@epitech.net>
// 
// Started on  Fri Mar 14 14:16:10 2014 Mehdi Chouag
// Last update Sun Apr  6 14:17:43 2014 Mehdi Chouag
//

#ifndef SNAKEOPENGL_HH_
# define SNAKEOPENGL_HH_

# include <SDL/SDL_ttf.h>
# include <SDL/SDL.h>
# include <map>
# include "ILibrary.hh"
# include "MenuOpenGL.hh"
# include "LibOpenGL.hh"

# define BUTTON_A 0
# define BUTTON_B 1
# define BUTTON_X 2
# define BUTTON_Y 3
# define NB_SURFACE 16

class	Snake: public	ILibrary
{
private:
  SDL_Surface	*_screen;
  SDL_Joystick	*_joystick;
  Menu		*_menu;
  Mix_Music	*_music;
  Mix_Chunk	*_effect;
  int		_width;
  int		_height;
  int		_step;
  int		_x;
  int		_y;
  bool		_appleIsTaken;
  bool		_otherMove;
  bool		_sound;
  bool		_isMusic;
  std::map<int, int>	keyK;
  std::map<int, int>	keyJ;
  std::vector<t_snake>	_snakeTrace;

public:
  virtual void	initLib(int&, int&, std::vector<t_snake>&);
  virtual Step	loopMenu(const int&, const int&);
  virtual	~Snake();
  virtual void  displaySnake(std::vector<t_snake>&, const int&, const int&, const int&, const int&);
  virtual int	getEvent();
  virtual int   getSpeed() const;
  virtual bool	switchMove() const;
  virtual void	freeLib();
  virtual void	playSound() const;
  virtual void	endGame();

private:
  void		initOpenGL();
  void		drawBackground() const;
  int		button(SDL_Event&);
  void		displayFruit(const int&, const int&, const int&) const;
  void	        keyboard(SDL_Event &);
};

#endif /* SNAKEOPENGL_HH_ */
