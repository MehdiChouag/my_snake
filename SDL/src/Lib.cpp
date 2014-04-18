//
// Lib.cpp for Lib in /home/chouag_m/rendu/cpp_nibbler/NEW/SDL/header
// 
// Made by Mehdi Chouag
// Login   <chouag_m@epitech.net>
// 
// Started on  Wed Mar 19 15:25:37 2014 Mehdi Chouag
// Last update Sat Apr  5 19:23:09 2014 Mehdi Chouag
//

#include "LibSDL.hh"

SDL_Surface     *Lib::loadImage(const std::string &file)
{
  SDL_Surface   *loading;

  loading = NULL;
  loading = IMG_Load(file.c_str());
  if (loading == NULL)
    {
      printf("Can't load the surface : %s\n", SDL_GetError());
      exit(EXIT_FAILURE);
    }
  return (loading);
}

void            Lib::applySurface(int x, int y, SDL_Surface *source, SDL_Surface *dest)
{
  SDL_Rect      offset;

  offset.x = x;
  offset.y = y;
  SDL_BlitSurface(source, NULL, dest, &offset);
}

void            Lib::changeMusic(Mix_Music *music)
{
  Mix_VolumeMusic(64);
  if (Mix_PlayingMusic() == 0)
    Mix_PlayMusic(music, -1);
  else
    {
      if (Mix_PausedMusic() == 1)
        Mix_ResumeMusic();
      else
        Mix_PauseMusic();
    }
}

void		Lib::xSDL_Init(Uint32 flags)
{
  int		ret;
  
  if ((ret = SDL_Init(flags)) == -1)
    throw Erreur("Can't init the SDL");
}

SDL_Surface	*Lib::xSDL_SetVideoMode(int width, int height, int bits, Uint32 flags)
{
  SDL_Surface	*ret;

  if ((ret = SDL_SetVideoMode(width, height, bits, flags)) == NULL)
    throw Erreur("Can't set the video mode");
  return (ret);
}

void		Lib::xTTF_Init()
{
  if (TTF_Init() == -1)
    throw Erreur("Can't init TTF");
}

void		Lib::xSDL_Flip(SDL_Surface *screen)
{
  if (SDL_Flip(screen) == -1)
    throw Erreur("Can't flip the screen");
}
