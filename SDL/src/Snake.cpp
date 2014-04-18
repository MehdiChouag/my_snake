//
// Snake.cpp for Snake.cpp in /home/david_c/B4/cppProgramming/nibbler/new/SDL/src
// 
// Made by DAVID Flavien
// Login   <david_c@epitech.net>
// 
// Started on  Wed Mar 19 14:27:20 2014 DAVID Flavien
// Last update Sun Apr  6 14:17:52 2014 Mehdi Chouag
//

#include "SnakeSDL.hh"

extern "C"
{
  ILibrary*	createLib()
  {
    return (new Snake());
  }
}

Snake::~Snake() 
{
  delete _menu;
}

void	Snake::initLib(int &width, int &height, std::vector<t_snake> &snake)
{
  this->_snakeTrace = snake;
  this->_width = width * BLOCK;
  this->_height = height * BLOCK;
  this->_step = GAME;
  this->_appleIsTaken = 0;
  this->keyK[SDLK_UP] = HAUT;
  this->keyK[SDLK_DOWN] = BAS;
  this->keyK[SDLK_LEFT] = GAUCHE;
  this->keyK[SDLK_RIGHT] = DROITE;
  this->keyJ[SDL_HAT_UP] = HAUT;
  this->keyJ[SDL_HAT_DOWN] = BAS;
  this->keyJ[SDL_HAT_LEFT] = GAUCHE;
  this->keyJ[SDL_HAT_RIGHT] = DROITE;
  this->_otherMove = false;
  this->initSDL();
  _music = Mix_LoadMUS("./SDL/sound/theme.mp3");
  _effect = Mix_LoadWAV("./SDL/sound/eat.wav");
  _scary = Mix_LoadWAV("./SDL/sound/scary1.wav");
  _sound = _menu->getSound();
  _isMusic = _menu->getMusic();
  _font = TTF_OpenFont("./SDL/font/plasdrip.ttf", 120);
  if (_isMusic)
    Lib::changeMusic(_music);
  this->drawBackground();
}

//
/* PRIVATE */
//

void	Snake::initSDL()
{
  _screen = _menu->getScreen();
  Lib::xTTF_Init();
  if (SDL_NumJoysticks() >= 1)
    {
      _joystick = SDL_JoystickOpen(0);
      if (_joystick == NULL)
        std::cout << "Can't set video mode" << std::endl;
    }
  Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
  initTextures();
  drawBackground();
  SDL_Flip(_screen);
}

void		Snake::drawBackground() const
{
  int		x(0);
  int		y(0);

  while (x < _width)
    {
      while (y < _height)
	{
          Lib::applySurface(x, y, _floor, _screen);
	  y += BLOCK;
	}
      y = 0;
      x += BLOCK;
    }
}

int		Snake::getEvent()
{
  SDL_Event	event;
  int		key;
  int		joy;

  while (SDL_PollEvent(&event))
    {
      key = event.key.keysym.sym;
      joy = event.jhat.value;
      if (event.type == SDL_KEYDOWN)
	{
	  if (key >= 273 && key <= 276)
	    return (keyK[key]);
	  keyboard(event);
	}
      else if (event.type == SDL_JOYHATMOTION)
	if ((joy >= 1 && joy <= 2) || joy == 4 || joy == 8)
	  return (keyJ[joy]);
      if (event.type == SDL_QUIT || key == SDLK_ESCAPE)
	return (ECHAP);
      else if (event.type == SDL_JOYBUTTONDOWN)
	return (button(event));
    }
  return (-1);
}

void		Snake::drawHead(t_snake &snake) const
{
  switch (snake.dir)
    {
    case UP:
      Lib::applySurface(snake.x, snake.y, _snake[HEAD_U], _screen);
      break;
    case LEFT:
      Lib::applySurface(snake.x, snake.y, _snake[HEAD_L], _screen);
      break;
    case DOWN:
      Lib::applySurface(snake.x, snake.y, _snake[HEAD_D], _screen);
      break;
    case RIGHT:
      Lib::applySurface(snake.x, snake.y, _snake[HEAD_R], _screen);
      break;
    }
}

void		Snake::drawBody(t_snake &snake) const
{
  switch (snake.dir)
    {
    case UP:
      Lib::applySurface(snake.x, snake.y, _snake[BODY_U], _screen);
      break;
    case LEFT:
      Lib::applySurface(snake.x, snake.y, _snake[BODY_L], _screen);
      break;
    case DOWN:
      Lib::applySurface(snake.x, snake.y, _snake[BODY_U], _screen);
      break;
    case RIGHT:
      Lib::applySurface(snake.x, snake.y, _snake[BODY_L], _screen);
      break;
    }
}

void		Snake::drawTail(t_snake &snake) const
{
  switch (snake.dir)
    {
    case UP:
      Lib::applySurface(snake.x, snake.y, _snake[TAIL_U], _screen);
      break;
    case LEFT:
      Lib::applySurface(snake.x, snake.y, _snake[TAIL_L], _screen);
      break;
    case DOWN:
      Lib::applySurface(snake.x, snake.y, _snake[TAIL_D], _screen);
      break;
    case RIGHT:
      Lib::applySurface(snake.x, snake.y, _snake[TAIL_R], _screen);
      break;
    }
}

void		Snake::drawTurn(t_snake &s) const
{
  if ((s.old_dir == DOWN && s.dir == RIGHT) || (s.old_dir == LEFT && s.dir == UP))
    Lib::applySurface(s.x, s.y, _snake[TURN_1], _screen);
  else if ((s.old_dir == DOWN && s.dir == LEFT) || (s.old_dir == RIGHT && s.dir == UP))
    Lib::applySurface(s.x, s.y, _snake[TURN_2], _screen);
  else if ((s.old_dir == RIGHT && s.dir == DOWN) || (s.old_dir == UP && s.dir == LEFT))
    Lib::applySurface(s.x, s.y, _snake[TURN_3], _screen);
  else if ((s.old_dir == LEFT && s.dir == DOWN) || (s.old_dir == UP && s.dir == RIGHT))
    Lib::applySurface(s.x, s.y, _snake[TURN_4], _screen);
}

void		Snake::displaySnake(std::vector<t_snake>& snakeTrace, const int &xApple, const int &yApple, const int &fruit , const int &speed)
{
  std::vector<t_snake>::iterator	it;

  SDL_Delay(speed);
  this->_snakeTrace = snakeTrace;
  drawBackground();
  for (it = snakeTrace.begin(); it != snakeTrace.end(); ++it)
    {
      switch ((*it).type)
	{
	case HEAD_R:
	  drawHead((*it));
	  break;
	case BODY_L:
	  drawBody((*it));
	  break;
	case TAIL_R:
	  drawTail((*it));
	  break;
	case TURN_1:
	  drawTurn((*it));
	  (*it).type = BODY_L;
	  break;
	default:
	  break;
	}
      displayFruit(xApple, yApple, fruit);
    }
  SDL_Flip(_screen);
}

void		Snake::displayFruit(const int &xApple, const int &yApple, const int &fruit) const
{
  Lib::applySurface(xApple, yApple, _fruits[fruit], _screen);
}

int            Snake::button(SDL_Event &event)
{
  int           button;

  button = event.jbutton.button;
  if (button == BUTTON_A)
    return (ECHAP);
  if (button == BUTTON_Y)
    _otherMove = !_otherMove;
  if (button == BUTTON_X)
    Lib::changeMusic(_music);
  if (button == BUTTON_B)
    _sound = !_sound;
  return (-1);
}

void		Snake::initTextures()
{
  _floor = Lib::loadImage("./SDL/images/grass.bmp");
  _snake[HEAD_L] = Lib::loadImage("./SDL/images/sprite/head_l.png");
  _snake[HEAD_U] = Lib::loadImage("./SDL/images/sprite/head_u.png");
  _snake[HEAD_R] = Lib::loadImage("./SDL/images/sprite/head_r.png");
  _snake[HEAD_D] = Lib::loadImage("./SDL/images/sprite/head_d.png");
  _snake[BODY_L] = Lib::loadImage("./SDL/images/sprite/body_l.png");
  _snake[BODY_U] = Lib::loadImage("./SDL/images/sprite/body_u.png");
  _snake[TAIL_L] = Lib::loadImage("./SDL/images/sprite/tail_l.png");
  _snake[TAIL_U] = Lib::loadImage("./SDL/images/sprite/tail_u.png");
  _snake[TAIL_R] = Lib::loadImage("./SDL/images/sprite/tail_r.png");
  _snake[TAIL_D] = Lib::loadImage("./SDL/images/sprite/tail_d.png");
  _snake[TURN_1] = Lib::loadImage("./SDL/images/sprite/turn_1.png");
  _snake[TURN_2] = Lib::loadImage("./SDL/images/sprite/turn_2.png");
  _snake[TURN_3] = Lib::loadImage("./SDL/images/sprite/turn_3.png");
  _snake[TURN_4] = Lib::loadImage("./SDL/images/sprite/turn_4.png");
  _fruits[0] = Lib::loadImage("./SDL/images/apple1.png");  
  _fruits[1] = Lib::loadImage("./SDL/images/apple2.png");
  _fruits[2] = Lib::loadImage("./SDL/images/apple3.png");
  _fear = Lib::loadImage("./SDL/images/scream.jpg");
}

bool		Snake::switchMove() const
{
  return (_otherMove);
}

void		Snake::keyboard(SDL_Event &event)
{
  int		key;

  key = event.key.keysym.sym;
  if (key == SDLK_s)
    _otherMove = !_otherMove;
  else if (key == SDLK_m)
    Lib::changeMusic(_music);
  else if (key == SDLK_l)
    _sound = !_sound;
}

Step		Snake::loopMenu(const int &x, const int &y)
{
  _menu = new Menu(x, y);
  return (_menu->loop());
}

void		Snake::freeLib()
{
  for (int i(0); i != NB_SURFACE - 1; i++)
    SDL_FreeSurface(_snake[i]);
  SDL_FreeSurface(_fruits[0]);
  SDL_FreeSurface(_fruits[1]);
  SDL_FreeSurface(_fruits[2]);
  SDL_FreeSurface(_floor);
  SDL_FreeSurface(_screen);
  SDL_FreeSurface(_fear);
  Mix_FreeChunk(_effect);
  Mix_FreeChunk(_scary);
  Mix_FreeMusic(_music);
  Mix_CloseAudio();
  TTF_Quit();
  SDL_Quit();
}

int		Snake::getSpeed() const
{
  int		speed;

  speed = _menu->getLevel();
  if (speed == 1)
    return (150);
  else if (speed == 2)
    return (100);
  return (50);
}

void		Snake::playSound() const
{
  if (_sound)
    {
      Mix_VolumeChunk(_effect, 64);
      Mix_PlayChannel(-1, _effect, 0);
    }
}

void		Snake::endGame()
{
  SDL_Color	color;

  Mix_PauseMusic();
  Mix_VolumeChunk(_scary, 128);
  Mix_PlayChannel(-1, _scary, 0);
  color.r = 255;
  color.g = 0;
  color.b = 0;
  _fontSurface = TTF_RenderText_Solid(_font, "Game Over", color);
  Lib::applySurface(0, 0, _fear, _screen);
  Lib::applySurface(630, 70, _fontSurface, _screen);
  Lib::xSDL_Flip(_screen);
  SDL_Delay(3000);
}
