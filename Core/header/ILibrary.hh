//
// ILibrary.hh for ILibrary.hh in /home/david_c/B4/cppProgramming/nibbler
// 
// Made by DAVID Flavien
// Login   <david_c@epitech.net>
// 
// Started on  Thu Mar 13 13:47:57 2014 DAVID Flavien
// Last update Sun Apr  6 14:20:25 2014 Mehdi Chouag
//

#ifndef ILIBRARY_HH_
# define ILIBRARY_HH_

# include <iostream>
# include <sstream>
# include <vector>

# define BLOCK 32

enum Direction {UP, LEFT, DOWN, RIGHT};
enum Type {HEAD_L, HEAD_U, HEAD_R, HEAD_D, HEAD, BODY_L, BODY_U, TAIL_L, TAIL_U, TAIL_R, TAIL_D, TURN_1, TURN_2, TURN_3, TURN_4};
enum Key {HAUT, GAUCHE, BAS, DROITE, ECHAP};
enum Step {MENU, GAME, END, FEAR};

typedef struct s_snake
{
  int		x;
  int		y;
  int		old_x;
  int		old_y;
  Direction	dir;
  Direction	old_dir;
  Type		type;
}		t_snake;

typedef struct s_pos
{
  int		x;
  int		y;
}		t_pos;

class	ILibrary
{
public:
  virtual Step		loopMenu(const int&, const int&) = 0;
  virtual void	        initLib(int&, int&, std::vector<t_snake>&) = 0;
  virtual int		getEvent() = 0;
  virtual void		displaySnake(std::vector<t_snake>&, const int&, const int&, const int&, const int&) = 0;
  virtual bool		switchMove() const = 0;
  virtual int		getSpeed() const = 0;
  virtual void		freeLib() = 0;
  virtual void		playSound() const = 0;
  virtual void		endGame() = 0;
  virtual		~ILibrary() {};
};

#endif /* ILIBRARY_HH_ */
