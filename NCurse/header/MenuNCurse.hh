//
// Menu.hh for Menu.hh in /home/chouag_m/rendu/cpp_nibbler/NCurse
// 
// Made by Mehdi Chouag
// Login   <chouag_m@epitech.net>
// 
// Started on  Sat Mar 15 22:09:52 2014 Mehdi Chouag
// Last update Sat Apr  5 20:52:32 2014 Mehdi Chouag
//

#ifndef MENUNCURSE_HH_
# define MENUNCURSE_HH_

# include <iostream>
# include <ncurses.h>
# include <curses.h>
# include <vector>
# include <sys/ioctl.h>
# include <stdio.h>
# include <unistd.h>
# include <map>
# include "ILibrary.hh"

class Menu
{
public:
  Menu();
  ~Menu();
  Step	loop();
  int	getLevel() const;

private:
  void	print_menu();
  void	up();
  void	down();
  void	left();
  void	right();
  void	enter();
  void  freeAll() const;

private:
  WINDOW			*_menuWin;
  int				_numlevel;
  int				curPos;
  bool				_loop;
  std::vector<std::string>	_option;
  std::vector<std::string>	_level;
  int				_x;
  int				_y;
  int				_key;
  std::map<int, void(Menu::*)()> _move;
  std::map<int, void(Menu::*)()> _movel;
  Step				_return;
};


#endif /* !MENUNCURSE_HH_ */
