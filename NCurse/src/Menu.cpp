//
// Menu.cpp for Menu.cpp in /home/chouag_m/rendu/cpp_nibbler/NCurse
// 
// Made by Mehdi Chouag
// Login   <chouag_m@epitech.net>
// 
// Started on  Sat Mar 15 22:14:34 2014 Mehdi Chouag
// Last update Sat Apr  5 20:53:23 2014 Mehdi Chouag
//

#include "MenuNCurse.hh"

Menu::Menu()
{
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  _x = w.ws_col;
  _y = w.ws_row;
  curPos = 0;
  _numlevel = 0;
  _option.push_back("1. Start the Game");
  _option.push_back("2. Difficulty");
  _option.push_back("3. Exit the Game");
  _level.push_back("< EASY >  ");
  _level.push_back("< MEDIUM >");
  _level.push_back("< HARD >  ");
  _loop = true;
  _move[KEY_UP] = &Menu::up;
  _move[KEY_DOWN] = &Menu::down;
  _movel[KEY_LEFT] = &Menu::left;
  _movel[KEY_RIGHT] = &Menu::right;
}

Menu::~Menu() {}

void	Menu::freeAll() const
{
  clrtoeol();
  refresh();
  endwin();
  delwin(_menuWin);
}

Step	Menu::loop()
{
  initscr();
  clear();
  noecho();
  cbreak();
  curs_set(0);
  _menuWin = newwin(15, 40, (_y / 2) - 20, _x / 2 - 20);
  refresh();
  keypad(_menuWin, TRUE);
  print_menu();
  while (_loop)
    {
      _key = wgetch(_menuWin);
      if (_key == 27)
      	_loop = false;
      if (_key == KEY_UP || _key == KEY_DOWN)
	(this->*_move[_key])();
      if (_key == KEY_LEFT || _key == KEY_RIGHT)
	(this->*_movel[_key])();
      if (_key == 10)
	enter();
    }
  freeAll();
  return (_return);
}

void	Menu::down()
{
  if (curPos < 2)
    {
      curPos++;
      print_menu();
      refresh();
    }
}

void	Menu::up()
{
  if (curPos > 0)
    {
      curPos--;
      print_menu();
      refresh();
    }
}

void	Menu::right()
{
  if (_numlevel < 2 && curPos == 1)
    {
      _numlevel++;
      print_menu();
      refresh();
    }
}

void	Menu::left()
{
  if (_numlevel > 0 && curPos == 1)
    {
      _numlevel--;
      print_menu();
      refresh();
    }
}


void	Menu::print_menu()
{
  int x, y;

  box(_menuWin, 0, 0);
  x = 10;
  y = 4;
  for(int i(0); (size_t)i < _option.size(); ++i)
    {
      if (curPos == i)
	{
	  wattron(_menuWin, A_REVERSE);
	  mvwprintw(_menuWin, y, x, "%s", _option[i].c_str());
	  wattroff(_menuWin, A_REVERSE);
	}
      else
	mvwprintw(_menuWin, y, x, "%s", _option[i].c_str());
      ++y;
    }
  mvwprintw(_menuWin, y + 2, x + 5, "%s", _level[_numlevel].c_str());
  wrefresh(_menuWin);
}

void	Menu::enter()
{
  if (curPos == 2)
    {
      _return = END;
      _loop = false;
    }
  if (curPos == 0)
    {
      _return = GAME;
      _loop = false;
    }
}

int	Menu::getLevel() const
{
  return (_numlevel + 1);
}
