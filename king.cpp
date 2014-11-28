/****************************************************
*                                                   *
* 550 - Integrated Programming Laboratory           *
* Lab Assessment 2: C++ 3                           *
* Oliver Grubin, November/December 2014             *
* og514@ic.ac.uk                                    *
*                                                   *
* king.cpp                                          *
* Implementation file for King class                *
*                                                   *
*****************************************************/

#include <iostream>
#include <cstdlib>

#include "ChessPiece.hpp"
#include "king.hpp"

using namespace std;

bool king::validDirection(int source, int destination)
{
  return (abs(destination - source) == VERTICAL || abs(destination - source) == 1);
}

/*int king::getDirection(int source, int destination) const
{
  if (!(abs(destination - source) % VERTICAL))
    return VERTICAL;
  else if (abs(destination-source) == 1)
    return 1;
  else
    return -1;
    }*/

ostream &king::output(ostream &out) const
{
  if (color == WHITE)
    out << "\xe2\x99\x94";
  else
    out << "\xe2\x99\x9a";
  return out;
}
