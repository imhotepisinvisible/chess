/****************************************************
*                                                   *
* 550 - Integrated Programming Laboratory           *
* Lab Assessment 2: C++ 3                           *
* Oliver Grubin, November/December 2014             *
* og514@ic.ac.uk                                    *
*                                                   *
* queen.cpp                                         *
* Implementation file for Queen class               *
*                                                   *
*****************************************************/

#include <iostream>
#include <cstdlib>

#include "ChessPiece.hpp"
#include "queen.hpp"

using namespace std;

bool queen::validDirection(int source, int destination)
{
  return (abs(destination - source) % VERTICAL || abs(destination-source) < HORIZONTAL
	   || abs(destination - source) % DIAGONAL || abs(destination-source) % ANTIDIAGONAL);
}

/*int queen::getDirection(int source, int destination) const
{
  if (!(abs(destination - source) % VERTICAL))
    return VERTICAL;
  else if (!(abs(destination-source) < HORIZONTAL))
    return 1;
  else if (!(abs(destination - source) % DIAGONAL))
    return DIAGONAL;
  else if (!(abs(destination-source) % ANTIDIAGONAL))
    return ANTIDIAGONAL;
  else
    return -1; //ERROR
    }*/

ostream &queen::output(ostream &out) const
{
  if (color == WHITE)
    out << "\xe2\x99\x95";
  else
    out << "\xe2\x99\x9b";
  return out;
}
