//
// Snake.cpp for Snake in /home/chouag_m/rendu/Snake
// 
// Made by Mehdi Chouag
// Login   <chouag_m@epitech.net>
// 
// Started on  Mon Mar 10 16:45:13 2014 Mehdi Chouag
// Last update Sat Apr  5 20:44:28 2014 Mehdi Chouag
//

#include "MenuOpenGL.hh"

Menu::~Menu() {}

Menu::Menu(const int &x, const int &y)
{
  if (x != y)
    throw Erreur("Map must be a square");
  _x = x * 32;
  _y = y * 32;
  _isLevel = 1;
  _isMusic = true;
  _isSound = true;
  _black.r = 255;
  _black.g = 255;
  _black.b = 255;
  _red.r = 255;
  _red.g = 0;
  _red.b = 0;
  _fond = NULL;
  _screen = NULL;
  _loop = true;
  _choise = 0;
  _optionLevel = 0;
  _optionMusic = 0;
  _optionSound = 0;
  initSDL();
  initFont();
  _music = Mix_LoadMUS("./SDL/sound/theme.mp3");
  Mix_VolumeMusic(64);
  _movek[SDLK_UP] = &Menu::up;
  _movek[SDLK_DOWN] = &Menu::down;
  _movek[SDLK_LEFT] = &Menu::left;
  _movek[SDLK_RIGHT] = &Menu::right;
  _movej[SDL_HAT_UP] = &Menu::up;
  _movej[SDL_HAT_DOWN] = &Menu::down;
  _movej[SDL_HAT_LEFT] = &Menu::left;
  _movej[SDL_HAT_RIGHT] = &Menu::right;
}

void		Menu::freeAll() const
{
  SDL_FreeSurface(_screen);
  SDL_FreeSurface(_fond);
  Mix_FreeMusic(_music);
  TTF_CloseFont(_font);
  TTF_Quit();
  Mix_CloseAudio();
  SDL_Quit();
}

void		Menu::initSDL()
{
  Lib::xSDL_Init(SDL_INIT_VIDEO | SDL_DOUBLEBUF | SDL_INIT_JOYSTICK);
  SDL_WM_SetCaption("Nibbler", NULL);
  if (_x == 1920 && _y >= 960)
    _screen = Lib::xSDL_SetVideoMode(_x, _y, 32, SDL_FULLSCREEN | SDL_HWSURFACE);
  else
    _screen = Lib::xSDL_SetVideoMode(_x, _y, 32, SDL_HWSURFACE);
  Lib::xTTF_Init();
  if (SDL_NumJoysticks() >= 1)
    {
      _joystick = SDL_JoystickOpen(0);
      if (_joystick == NULL)
        throw Erreur("Can't init the joystick");
    }
  Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
  _fond = Lib::loadImage("./SDL/images/fond.jpg");
  _font = TTF_OpenFont("./SDL/font/leadcoat.ttf", 60);
}

Step		Menu::loop()
{
  Lib::applySurface(0, 0, _fond, _screen);
  print_menu();
  Mix_PlayMusic(_music, -1);
  Lib::xSDL_Flip(_screen);
  SDL_EnableKeyRepeat(100, 85);
  while (_loop)
    {
      SDL_WaitEvent(&_event);
      main_menu();
      if (_event.type == SDL_QUIT || _event.key.keysym.sym == SDLK_ESCAPE)
	_loop = false;
    }
  freeAll();
  return (_return);
}

SDL_Surface	*Menu::make_font(std::string const &name, SDL_Color color) const
{
  return (TTF_RenderText_Solid(_font, name.c_str(), color));
}

void		Menu::initFont()
{
  _name.push_back("Start");
  _name.push_back("Difficulty");
  _name.push_back("Sound");
  _name.push_back("Music");
  _name.push_back("Exit");
  _responseName.push_back("On");
  _responseName.push_back("Off");
  _responseLevel.push_back("Easy");
  _responseLevel.push_back("Medium");
  _responseLevel.push_back("Hard");
  for (size_t i(0); i != _name.size(); ++i)
    {
      if (i == 0)
	_message.push_back(make_font(_name[i], _red));
      else
        _message.push_back(make_font(_name[i], _black));
    }
  for (size_t k= 0; k != _responseName.size(); ++k)
    _response.push_back(make_font(_responseName[k], _black));
  for (size_t z= 0; z != _responseLevel.size(); ++z)
    _responseMessage.push_back(make_font(_responseLevel[z], _black));
}

void		Menu::up()
{
  if (_choise > 0)
    {
      _message[_choise] = make_font(_name[_choise], _black);
      _message[_choise - 1] = make_font(_name[_choise - 1], _red);  
      refresh_menu();
      _choise--;
    }
}

void		Menu::down()
{
  if (_choise < (_name.size() - 1))
    {
      _message[_choise] = make_font(_name[_choise], _black);
      _message[_choise + 1] = make_font(_name[_choise + 1], _red);  
      refresh_menu();
      _choise++;
    }
}

void		Menu::right()
{
  if (_choise >= 1 && _choise <= 3)
    {
      if (_choise == 1 && _optionLevel < (_responseLevel.size() - 1))
	{
	  _responseMessage[_optionLevel + 1] = make_font(_responseLevel[_optionLevel + 1], _black);
	  _optionLevel++;
	  _isLevel += 1;
	}
      if (_choise == 2 && _optionSound < (_responseName.size() - 1))
	{
	  _response[_optionSound + 1] = make_font(_responseName[_optionSound + 1], _black);  
	  _isSound = false;
	  _optionSound++;
	}
      if (_choise == 3 && _optionMusic < (_responseName.size() - 1))
	{
	  _response[_optionMusic + 1] = make_font(_responseName[_optionMusic + 1], _black);
	  Lib::changeMusic(_music);
	  _isMusic = false;
	  _optionMusic++;
	}
      refresh_menu();
    }
}

void		Menu::left()
{
  if (_choise >= 1 && _choise <= 3)
    {
      if (_choise == 1 && _optionLevel > 0)
	{
	  _responseMessage[_optionLevel - 1] = make_font(_responseLevel[_optionLevel - 1], _black);
	  _optionLevel--;
	  _isLevel -= 1; 
	}
      if (_choise == 2 && _optionSound > 0)
	{
	  _response[_optionSound - 1] = make_font(_responseName[_optionSound - 1], _black);	  
	  _isSound = true;
	  _optionSound--;
	}
      if (_choise == 3 && _optionMusic > 0)
	{
	  _response[_optionMusic - 1] = make_font(_responseName[_optionMusic - 1], _black);	  
	  Lib::changeMusic(_music);
	  _isMusic = true;
	  _optionMusic--;
	}
      refresh_menu();
    }
}

void	        Menu::print_menu() const
{
  int		pos;
 
  pos = _y / 5;
  for (size_t i(0); i != _message.size(); ++i)
    {
      Lib::applySurface(_x / 2 - 150, pos, _message[i], _screen);
      pos += _y / 9;
    }
  Lib::applySurface(_x / 2 + 150, (_y / 5) + (_y / 9), _responseMessage[_optionLevel], _screen);
  Lib::applySurface(_x / 2 + 150, (_y / 5) + (_y / 9) * 2, _response[_optionSound], _screen);
  Lib::applySurface(_x / 2 + 150, (_y / 5) + (_y / 9) * 3, _response[_optionMusic], _screen);
}

void		Menu::main_menu()
{
  int	        k;
  int		j;	
  int		event;

  k = _event.key.keysym.sym;
  j = _event.jhat.value;
  event = _event.type;
  if (event == SDL_KEYDOWN)
    {
       if (k >= 273 && k <= 276)
	 (this->*_movek[k])();
      Keyboard();
    }
  else if (event == SDL_JOYHATMOTION)
    {
      if ((j >= 1 && j <= 2) || j == 4 || j == 8)
	  (this->*_movej[j])();
    }
  else if (event == SDL_JOYBUTTONDOWN)
    Button();
}

void		Menu::Keyboard()
{
  int		key;

  key = _event.key.keysym.sym;
  if (key == SDLK_RETURN)
    {
      if (_choise == 4)
	{
	  _return = END;
	  _loop = false;
	}
      if (_choise == 0)
	{
	  _return = GAME;
	  _loop = false;
	}
    }
}

void		Menu::Button()
{
  int		button;

  button = _event.jbutton.button;
  if (button == BUTTON_A && _choise == 4)
    {
      _return = END;
      _loop = false;
    }
  if (button == BUTTON_A && _choise == 0)
    {
      _return = GAME;
      _loop = false;
    }
}

void		Menu::refresh_menu() const
{
  SDL_FillRect(_screen, NULL, 0x000000);
  Lib::applySurface(0, 0, _fond, _screen);
  print_menu();
  Lib::xSDL_Flip(_screen);
}

bool		Menu::getMusic() const
{
  return (_isMusic);
}

bool		Menu::getSound() const
{
  return (_isSound);
}

int		Menu::getLevel() const
{
  return (_isLevel);
}
