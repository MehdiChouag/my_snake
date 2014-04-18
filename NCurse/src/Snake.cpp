//
// Snake.cpp for Snake.cpp in /home/david_c/B4/cppProgramming/nibbler/new/SDL/src
// 
// Made by DAVID Flavien
// Login   <david_c@epitech.net>
// 
// Started on  Wed Mar 19 14:27:20 2014 DAVID Flavien
// Last update Sun Apr  6 14:17:58 2014 Mehdi Chouag
//

#include "SnakeNCurse.hh"

extern "C"
{
  ILibrary*	createLib()
  {
    return (new Snake());
  }
}

Snake::~Snake() {}

void	Snake::initLib(int &width, int &height, std::vector<t_snake> &snake)
{
  struct winsize w;

  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  this->_x = w.ws_col;
  this->_y = w.ws_row;
  this->_snakeTrace = snake;
  this->_width = width;
  this->_height = height;
  initscr();
  clear();
  noecho();
  cbreak();
  curs_set(0);
  _win = newwin(_height, _width, 1, 1);
  keypad(_win, TRUE);
  keypad(stdscr, TRUE);
  scrollok(_win, TRUE);
  nodelay(_win, TRUE);
  nodelay(stdscr, TRUE);
  this->drawBackground();
  wrefresh(_win);
}

int		Snake::getEvent()
{
  if (_key == 's')
    _otherMove = !_otherMove;
  if (_key == 27)
    return (ECHAP);
  if (_key == 0404)
    return (GAUCHE);
  if (_key == 0405)
    return (DROITE);
  if (_key == KEY_UP)
    return (HAUT);  
  if (_key == KEY_DOWN)
    return (BAS);
  return (-1);
}

void		Snake::displaySnake(std::vector<t_snake>& snakeTrace, const int &xApple, const int &yApple, const int &fruit , const int &speed)
{
  std::vector<t_snake>::const_iterator	it;

  usleep(speed * 1000);
  wtimeout(_win, 0);
  _key = getch();
  wclear(_win);
  drawBackground();
  for (it = snakeTrace.begin(); it != snakeTrace.end(); ++it)
    {
      wattron(_win, A_REVERSE);
      mvwprintw(_win, (*it).y / 32, (*it).x / 32, " ");
      wattroff(_win, A_REVERSE);
    }
  mvwprintw(_win, yApple / 32, xApple / 32, "0");
  wrefresh(_win);
}

void		Snake::drawBackground() const
{
  box(_win, 0, 0);
  wborder(_win, '|', '|', '-', '-', '+', '+', '+', '+');
}

bool		Snake::switchMove() const
{
  return (_otherMove);
}

Step		Snake::loopMenu(const int &x, const int &y)
{
  _menu = new Menu();
  return (_menu->loop());
}

void		Snake::freeLib()
{
  clrtoeol();
  wrefresh(_win);
  endwin();
  delwin(_win);
}

int		Snake::getSpeed() const
{
  int		speed;

  speed = _menu->getLevel();
  if (speed == 1)
    return (300);
  else if (speed == 2)
    return (200);
  else if (speed == 3)
    return (100);
  return (0);
}

void		Snake::playSound() const {}

void		Snake::endGame() {}
