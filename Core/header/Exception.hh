//
// Exception.hpp for Exception in /home/chouag_m/rendu/Abstract_VM
// 
// Made by Mehdi Chouag
// Login   <chouag_m@epitech.net>
// 
// Started on  Thu Feb 20 20:02:56 2014 Mehdi Chouag
// Last update Sat Apr  5 18:44:36 2014 Mehdi Chouag
//

#include <iostream>
#include <string>
#include <exception>
#include <sstream>

class Erreur : public std::exception
{
public:
  Erreur(const std::string &) throw();
  virtual const char * what() const throw ();
  virtual ~Erreur() throw();

private:
  std::string	_err;
};
