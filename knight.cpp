/****************************************************
*                                                   *
* 550 - Integrated Programming Laboratory           *
* Lab Assessment 2: C++ 3                           *
* Oliver Grubin, November/December 2014             *
* og514@ic.ac.uk                                    *
*                                                   *
* knight.cpp                                        *
* Implementation file for Knight class              *
*                                                   *
*****************************************************/

#include <iostream>
#include <cstdlib>

#include "ChessPiece.hpp"
#include "knight.hpp"

using namespace std;

bool knight::validDirection(int source, int destination)
{
  return (abs(destination - source) % L_LEFT_HIGH || abs(destination-source) % L_LEFT_LOW
	   || abs(destination - source) % L_RIGHT_HIGH || abs(destination-source) % L_RIGHT_LOW);
}

int knight::getDirection(int source, int destination) const
{
  return 0; //MAGIC NUMBER = JUMP?
}

ostream &knight::output(ostream &out) const
{
  if (color == WHITE)
    out << "\xe2\x99\x98";
  else
    out << "\xe2\x99\x9e";
  return out;
}
