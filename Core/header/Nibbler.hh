//
// Nibbler.hh for Nibbler in /home/chouag_m/rendu/cpp_nibbler
// 
// Made by Mehdi Chouag
// Login   <chouag_m@epitech.net>
// 
// Started on  Mon Mar 17 19:06:32 2014 Mehdi Chouag
// Last update Sat Apr  5 15:53:10 2014 Mehdi Chouag
//

#ifndef NIBBLER_HH_
# define NIBBLER_HH_

# include <dlfcn.h>
# include <unistd.h>
# include <cstdlib>
# include <list>
# include <map>
# include "Exception.hh"
# include "ILibrary.hh"

class	Nibbler
{
public:
  Nibbler();
  ~Nibbler();
  bool		OpenLibrary(std::string const &, const int&, const int&);
  void		MakeSnake(const int&, const int&, const Direction&, const Type&);
  void		calculs();
  void		loop();
  void		loopMenu();
  void		loopGame();
  int		getTimeTicks();
  void		generateApple();

private:
  void		moveLeft();
  void		moveRight();
  void		moveUp();
  void		moveDown();
  void		changeDir(t_snake&);
  void		growSnake();
  bool		collision();
  bool		collisionUp(t_snake&);
  bool		collisionDown(t_snake&);
  bool		collisionLeft(t_snake&);
  bool		collisionRight(t_snake&);

private:
  ILibrary	*_lib;
  int		_width;
  int		_height;
  int		_step;
  int		_timeToDisplay;
  int		_timeToCalcul;
  int		_x;
  int		_y;
  int		_xApple;
  int		_yApple;
  int		_fruit;
  int		_score;
  int		_speed;
  bool		_appleIsTaken;
  bool		_fullScreen;
  void		*_dlhandle;
  std::map<int, void(Nibbler::*)()>	defaultMove;
  std::map<int, void(Nibbler::*)()>	otherMove;
  std::map<int, bool(Nibbler::*)(t_snake&)> mapCollision;		 
  std::list<t_snake>	_pos;
  std::vector<t_snake> _snakeTrace;
};

#endif /* !NIBBLER_HH_ */
