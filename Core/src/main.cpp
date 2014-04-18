//
// main.cpp for  in /home/aube_a/rendu/cpp_nibbler
// 
// Made by Anthony Aube
// Login   <aube_a@epitech.net>
// 
// Started on  Tue Mar 18 10:45:00 2014 Anthony Aube
// Last update Sun Apr  6 19:15:35 2014 Mehdi Chouag
//

#include <iostream>
#include <cstdlib>
#include "Nibbler.hh"

int			main(int ac, char **av)
{
  Nibbler		nibbler;
  int			x;
  int		        y;

  try {
    if (ac < 4)
      throw Erreur("Usage: ./nibbler [x] [y] [lib_nibbler_XXX.so]:");
    x = std::atoi(av[1]);
    y = std::atoi(av[2]);
    if ((x * BLOCK > 1920 || y * BLOCK > 1080) || (x * BLOCK < 640 || y * BLOCK < 640))
      throw Erreur("The size is invalid");
    srand(time(0));
    if (nibbler.OpenLibrary(static_cast<std::string>(av[3]), x, y))
      nibbler.loop();
  }
  catch (const Erreur &e)
    { 
      std::cerr << e.what() << std::endl;
      return (-1);
    }
  return (0);
}
