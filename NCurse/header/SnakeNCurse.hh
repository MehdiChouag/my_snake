//
// Snake.hh for Snake.hh in /home/chouag_m/rendu/cpp_nibbler/SDL/header
// 
// Made by Mehdi Chouag
// Login   <chouag_m@epitech.net>
// 
// Started on  Fri Mar 14 14:16:10 2014 Mehdi Chouag
// Last update Sun Apr  6 14:17:35 2014 Mehdi Chouag
//

#ifndef SNAKENCURSE_HH_
# define SNAKENCURSE_HH_

# include <map>
# include <vector>
# include <ncurses.h>
# include <curses.h>
# include <sys/ioctl.h>
# include <stdio.h>
# include <unistd.h>
# include "ILibrary.hh"
# include "MenuNCurse.hh"

class	Snake: public	ILibrary
{
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
  void		drawBackground() const;
  void		displayFruit(int, int) const;

private:
  std::vector<t_snake>	_snakeTrace;
  int			_width;
  int			_height;
  bool			_appleIsTaken;
  WINDOW		*_win;
  int			_x;
  int			_y;
  int			_key;
  bool			_otherMove;
  Menu			*_menu;

};

#endif /* SNAKENCURSE_HH_ */
