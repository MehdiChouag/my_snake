//
// Lib.hh for Lib.hh in /home/david_c/B4/cppProgramming/nibbler/new/SDL/src
// 
// Made by DAVID Flavien
// Login   <david_c@epitech.net>
// 
// Started on  Wed Mar 19 14:48:33 2014 DAVID Flavien
// Last update Sat Apr  5 20:49:25 2014 Mehdi Chouag
//

#ifndef LIBSDL_HH_
# define LIBSDL_HH_

# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <SDL/SDL_mixer.h>
# include <SDL/SDL_ttf.h>
# include "Exception.hh"
# include <iostream>

namespace Lib
{
  SDL_Surface	*loadImage(const std::string&);
  void		applySurface(int, int, SDL_Surface*, SDL_Surface*);
  void		changeMusic(Mix_Music*);
  void		xSDL_Init(Uint32 flags);
  SDL_Surface	*xSDL_SetVideoMode(int, int, int, Uint32);
  void		xTTF_Init();
  void		xSDL_Flip(SDL_Surface*);
}

#endif /* LIBSDL_HH_ */
