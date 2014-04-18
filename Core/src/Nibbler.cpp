//
// Nibbler.cpp for Nibbler.cpp in /home/chouag_m/rendu/cpp_nibbler
// 
// Made by Mehdi Chouag
// Login   <chouag_m@epitech.net>
// 
// Started on  Mon Mar 17 19:20:34 2014 Mehdi Chouag
// Last update Sat Apr  5 15:41:25 2014 Mehdi Chouag
//

#include "Nibbler.hh"


Nibbler::Nibbler()
{
  _dlhandle = NULL;
  _score = 0;
  defaultMove[GAUCHE] = &Nibbler::moveLeft;
  defaultMove[DROITE] = &Nibbler::moveRight;
  otherMove[HAUT] = &Nibbler::moveUp;
  otherMove[BAS] = &Nibbler::moveDown;
  otherMove[GAUCHE] = &Nibbler::moveLeft;
  otherMove[DROITE] = &Nibbler::moveRight;
  mapCollision[UP] = &Nibbler::collisionUp;
  mapCollision[DOWN] = &Nibbler::collisionDown;
  mapCollision[LEFT] = &Nibbler::collisionLeft;
  mapCollision[RIGHT] = &Nibbler::collisionRight;
  _fullScreen = false;
}

Nibbler::~Nibbler()
{
  if (_dlhandle != NULL)
    dlclose(_dlhandle);
}

bool	Nibbler::OpenLibrary(std::string const &lib, const int &x, const int &y)
{
  ILibrary	*(*external_creator)();

  _dlhandle = dlopen(lib.c_str(), RTLD_LAZY);
  if (_dlhandle == NULL || dlerror() != NULL)
    throw Erreur(dlerror());
  external_creator = reinterpret_cast<ILibrary* (*)()>(dlsym(_dlhandle, "createLib"));
  if (external_creator == NULL)
    {
      throw Erreur(dlerror());
      dlclose(_dlhandle);
    }
  _lib = external_creator();
  _x = x;
  _y = y;
  MakeSnake((x/2 * BLOCK), (y/2 * BLOCK), RIGHT, HEAD_R);
  MakeSnake((x/2 * BLOCK) - 32, (y/2 * BLOCK), RIGHT, BODY_L);
  MakeSnake((x/2 * BLOCK) - 64, (y/2 * BLOCK), RIGHT, BODY_L);
  MakeSnake((x/2 * BLOCK) - 96, (y/2 * BLOCK), RIGHT, TAIL_R);
  return (true);
}

void	Nibbler::loop()
{
  _step = _lib->loopMenu(_x, _y);
  _speed = _lib->getSpeed();
  if (_x * BLOCK == 1920 && _y * BLOCK >= 960)
    _fullScreen = true;
  if (_step == GAME)
    {
      _lib->initLib(_x, _y, _snakeTrace);
      generateApple();
      while (_step != END)
	{
	  loopGame();
	  if (_step == FEAR)
	    break;
	}
      if (_step == FEAR)
	_lib->endGame();
      _lib->freeLib();
      std::cout << "Score : " << _score << std::endl;
    }
}

void		Nibbler::loopGame()
{
  int		key;

  while (this->_step == GAME)
    {
      key = _lib->getEvent();
      if (key == ECHAP)
	this->_step = END;
      if (!_lib->switchMove() && (key == GAUCHE || key == DROITE))
	(this->*defaultMove[key])();
      else if (key >= 0 && key <= 3 && _lib->switchMove())
        (this->*otherMove[key])();
      calculs();
      if (collision())
	_lib->displaySnake(_snakeTrace, _xApple, _yApple, _fruit, _speed);
    }
}

void		Nibbler::calculs()
{
  std::list<t_snake>::const_iterator	it;
  bool					rm = false;

  for (unsigned int i = 0; i < this->_snakeTrace.size(); i++)
    changeDir(_snakeTrace[i]);
  if (_snakeTrace[0].x == _xApple && _snakeTrace[0].y == _yApple)
    growSnake();
  for (size_t z(0); z < this->_snakeTrace.size(); z++)
    {
      for (it = this->_pos.begin(); it != this->_pos.end(); ++it)
	{
	  if (_snakeTrace[z].x == (*it).x && _snakeTrace[z].y == (*it).y)
	    {
	      if (z == _snakeTrace.size() - 1)
		rm = true;
	      _snakeTrace[z].old_dir = _snakeTrace[z].dir;
	      _snakeTrace[z].dir = (*it).dir;
	      if (_snakeTrace[z].type != HEAD_R && _snakeTrace[z].type != TAIL_R)
		_snakeTrace[z].type = TURN_1;
	    }
	}
      if (rm == true)
	_pos.pop_front();
    }
}

void		Nibbler::MakeSnake(const int &x, const int &y, const Direction &dir, const Type &type)
{
  t_snake	tmp;
  
  tmp.x = x;
  tmp.y = y;
  tmp.dir = dir;
  tmp.type = type;
  _snakeTrace.push_back(tmp);
}

void		Nibbler::moveLeft()
{
  t_snake	p;

  p.x = _snakeTrace[0].x;
  p.y = _snakeTrace[0].y;
  if (!_lib->switchMove())
    switch (_snakeTrace[0].dir)
      {
      case UP:
	_snakeTrace[0].dir = LEFT;
	break;
      case LEFT:
	_snakeTrace[0].dir = DOWN;
	break;
      case RIGHT:
	_snakeTrace[0].dir = UP;
	break;
      case DOWN:
	_snakeTrace[0].dir = RIGHT;
      }
  else
    if (_snakeTrace[0].dir == UP || _snakeTrace[0].dir == DOWN)
      _snakeTrace[0].dir = LEFT;
  p.dir = _snakeTrace[0].dir;
  _pos.push_back(p);
}

void            Nibbler::moveRight()
{
  t_snake	p;

  p.x = _snakeTrace[0].x;
  p.y = _snakeTrace[0].y;
  if (!_lib->switchMove())
    switch (_snakeTrace[0].dir)
      {
      case UP:
	_snakeTrace[0].dir = RIGHT;
	break;
      case LEFT:
	_snakeTrace[0].dir = UP;
	break;
      case RIGHT:
	_snakeTrace[0].dir = DOWN;
	break;
      case DOWN:
	_snakeTrace[0].dir = LEFT;
      }
  else
    if (_snakeTrace[0].dir == UP || _snakeTrace[0].dir == DOWN)
      _snakeTrace[0].dir = RIGHT;
  p.dir = _snakeTrace[0].dir;
  _pos.push_back(p);
}

void		Nibbler::moveUp()
{
  t_snake	p;

  p.x = _snakeTrace[0].x;
  p.y = _snakeTrace[0].y;
  if (_snakeTrace[0].dir == RIGHT || _snakeTrace[0].dir == LEFT)
    _snakeTrace[0].dir = UP;
  p.dir = _snakeTrace[0].dir;
  _pos.push_back(p);
}

void		Nibbler::moveDown()
{
    t_snake	p;

  p.x = _snakeTrace[0].x;
  p.y = _snakeTrace[0].y;
  if (_snakeTrace[0].dir == RIGHT || _snakeTrace[0].dir == LEFT)
    _snakeTrace[0].dir = DOWN;
  p.dir = _snakeTrace[0].dir;
  _pos.push_back(p);
}


void		Nibbler::generateApple()
{
  std::vector<t_snake>::const_iterator	it;
  bool		isGood = false;
  
  while (isGood == false)
    {
      _xApple = (rand() % _x) * BLOCK;
      _yApple = (rand() % _y) * BLOCK;
      _fruit = rand() % 3;
      isGood = true;
      for (it = _snakeTrace.begin(); it != _snakeTrace.end(); ++it)
	{
	  if ((*it).x == _xApple && (*it).y == _yApple)
	    isGood = false;
	}
    }
}

bool		Nibbler::collision()
{
  return ((this->*mapCollision[_snakeTrace[0].dir])(_snakeTrace[0]));
}

void		Nibbler::changeDir(t_snake &snake)
{
  switch (snake.dir)
    {
    case UP:
      snake.old_y = snake.y;
      snake.old_x = -1;
      snake.y -= BLOCK;
      break;
    case LEFT:
      snake.old_x = snake.x;
      snake.old_y = -1;
      snake.x -= BLOCK;
      break;
    case DOWN:
      snake.old_y = snake.y;
      snake.old_x = -1;
      snake.y += BLOCK;
      break;  
    case RIGHT:
      snake.old_x = snake.x;
      snake.old_y = -1;
      snake.x += BLOCK;
      break;
    }
}

bool		Nibbler::collisionUp(t_snake &tmp)
{
  if ((tmp.y - BLOCK) < -BLOCK)
    {
      this->_step = _fullScreen ? FEAR : END;
      return (false);
    }
  for (size_t i(1); i != _snakeTrace.size(); i++)
    if (tmp.y - BLOCK == _snakeTrace[i].y && tmp.x == _snakeTrace[i].x)
      {
	this->_step = _fullScreen ? FEAR : END;
	return (false);
      }
  return (true);
}

bool		Nibbler::collisionDown(t_snake &tmp)
{
  if (tmp.y + BLOCK > (_y * BLOCK))
    {
      this->_step = _fullScreen ? FEAR : END;
      return (false);
    }
  for (size_t i(1); i != _snakeTrace.size(); i++)
    if (tmp.y + BLOCK == _snakeTrace[i].y && tmp.x == _snakeTrace[i].x)
      {
	this->_step = _fullScreen ? FEAR : END;
	return (false);
      }
  return (true);
}

bool		Nibbler::collisionLeft(t_snake &tmp)
{
  if ((tmp.x - BLOCK) < -BLOCK)
    {
      this->_step = _fullScreen ? FEAR : END;
      return (false);
    }
  for (size_t i(1); i != _snakeTrace.size(); i++)
    if (tmp.x - BLOCK == _snakeTrace[i].x && tmp.y == _snakeTrace[i].y)
      {
	this->_step = _fullScreen ? FEAR : END;
	return (false);
      }
  return (true);
}

bool		Nibbler::collisionRight(t_snake &tmp)
{
  if (tmp.x + BLOCK > (_x * BLOCK))
    {
      this->_step = _fullScreen ? FEAR : END;
      return (false);
    }
  for (size_t i(1); i != _snakeTrace.size(); i++)
    if (tmp.x + BLOCK == _snakeTrace[i].x && tmp.y == _snakeTrace[i].y)
      {
	this->_step = _fullScreen ? FEAR : END;
	return (false);
      }
  return (true);
}

void		Nibbler::growSnake()
{
  t_snake	addBlock;

  _lib->playSound();
  if (_snakeTrace[_snakeTrace.size() - 1].old_x != -1)
    addBlock.x = _snakeTrace[_snakeTrace.size() - 1].old_x;
  else
    addBlock.x = _snakeTrace[_snakeTrace.size() - 1].x;
  if (_snakeTrace[_snakeTrace.size() - 1].old_y != -1)
    addBlock.y = _snakeTrace[_snakeTrace.size() - 1].old_y;
  else
    addBlock.y = _snakeTrace[_snakeTrace.size() - 1].y;
  addBlock.dir = _snakeTrace[_snakeTrace.size() - 1].dir;
  addBlock.type = TAIL_R;
  _snakeTrace[_snakeTrace.size() - 1].type = BODY_L;
  addBlock.old_x = -1;
  addBlock.old_y = -1;
  _snakeTrace.push_back(addBlock);
  generateApple();
  _score += 10;
  if (_speed > 10)
    _speed -= 10;
}
