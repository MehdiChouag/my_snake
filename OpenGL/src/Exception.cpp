//
// Exception.cpp for Exception in /home/chouag_m/rendu/Abstract_VM
// 
// Made by Mehdi Chouag
// Login   <chouag_m@epitech.net>
// 
// Started on  Thu Feb 20 20:00:46 2014 Mehdi Chouag
// Last update Sat Apr  5 18:56:56 2014 DAVID Flavien
//

#include "Exception.hh"

Erreur::Erreur(const std::string &err) throw()
{
  _err = err;
}

Erreur::~Erreur() throw() {}

const char * Erreur::what() const throw()
{
  return (_err.c_str());
}
