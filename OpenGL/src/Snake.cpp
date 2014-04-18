//
// Snake.cpp for Snake.cpp in /home/david_c/B4/cppProgramming/nibbler/new/SDL/src
// 
// Made by DAVID Flavien
// Login   <david_c@epitech.net>
// 
// Started on  Wed Mar 19 14:27:20 2014 DAVID Flavien
// Last update Sun Apr  6 14:17:49 2014 Mehdi Chouag
//

#include <GL/gl.h>
#include <GL/glu.h>
#include "SnakeOpenGL.hh"

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
  this->_x = width;
  this->_y = height;
  this->_step = GAME;
  this->_appleIsTaken = 0;
  this->keyK[SDLK_DOWN] = HAUT;
  this->keyK[SDLK_UP] = BAS;
  this->keyK[SDLK_RIGHT] = GAUCHE;
  this->keyK[SDLK_LEFT] = DROITE;
  this->keyJ[SDL_HAT_DOWN] = HAUT;
  this->keyJ[SDL_HAT_UP] = BAS;
  this->keyJ[SDL_HAT_RIGHT] = GAUCHE;
  this->keyJ[SDL_HAT_LEFT] = DROITE;
  this->_otherMove = false;
  this->initOpenGL();
  _music = Mix_LoadMUS("./SDL/sound/theme.mp3");
  _effect = Mix_LoadWAV("./SDL/sound/eat.wav");
  _sound = _menu->getSound();
  _isMusic = _menu->getMusic();
  if (_isMusic)
    Lib::changeMusic(_music);
}

//
/* PRIVATE */
//

void	Snake::initOpenGL()
{
  Lib::xSDL_Init(SDL_INIT_VIDEO | SDL_DOUBLEBUF | SDL_INIT_JOYSTICK);
  SDL_WM_SetCaption("Nibbler", NULL);
  _screen = Lib::xSDL_SetVideoMode(_width, _height, 32, SDL_OPENGL);
  if (SDL_NumJoysticks() >= 1)
    {
      _joystick = SDL_JoystickOpen(0);
      if (_joystick == NULL)
        std::cout << "Can't set video mode" << std::endl;
    }
  Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
  glMatrixMode(GL_PROJECTION);
  glClearDepth(1);
  glEnable(GL_DEPTH_TEST);
  glLoadIdentity();
  gluPerspective(70, (double)(_width)/(_height), 1, 1000);
  glMatrixMode(GL_MODELVIEW);
}

void		Snake::drawBackground() const
{
  glBegin(GL_QUADS);
  glColor3ub(239, 208, 56);
  glVertex3d(-1, -1, -1);
  glVertex3d(-1, _y + 2, -1);
  glVertex3d(_x + 2,  _y + 2, -1);
  glVertex3d(_y + 2, -1, -1);
  glEnd();
}

void		Snake::displaySnake(std::vector<t_snake>& snakeTrace, const int &xApple, const int &yApple, const int &fruit , const int &speed)
{
  std::vector<t_snake>::const_iterator	it;
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(-_x/5, -_x/5, _x, (_y/2 - _y/8), 
  	    (_x/2 - _x/8), 0, 0, 0, 1);
  SDL_Delay(speed);
  this->_snakeTrace = snakeTrace;
  drawBackground();
  Lib::drawCube(xApple / 32, yApple / 32, rand() % 255, rand() % 255, rand() % 255);
  for (it = _snakeTrace.begin(); it != _snakeTrace.end(); ++it)
    {
      if ((*it).type == HEAD_R)
	Lib::drawCube((*it).x / 32, (*it).y / 32, 41, 89, 0);
      else
	Lib::drawCube((*it).x / 32, (*it).y / 32, 70, 151, 0);
    }
  glFlush();
  SDL_GL_SwapBuffers();
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

int		Snake::button(SDL_Event &event)
{
  int		button;

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
  SDL_FreeSurface(_screen);
  Mix_FreeChunk(_effect);
  Mix_FreeMusic(_music);
  Mix_CloseAudio();
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

void		Snake::endGame() {}
