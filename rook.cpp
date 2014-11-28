/****************************************************
*                                                   *
* 550 - Integrated Programming Laboratory           *
* Lab Assessment 2: C++ 3                           *
* Oliver Grubin, November/December 2014             *
* og514@ic.ac.uk                                    *
*                                                   *
* rook.cpp                                          *
* Implementation file for Rook class                *
*                                                   *
*****************************************************/

#include <iostream>
#include <cstdlib>

#include "ChessPiece.hpp"
#include "rook.hpp"

using namespace std;

bool rook::validDirection(int source, int destination)
{
  return (abs(destination - source) % VERTICAL || abs(destination-source) < HORIZONTAL);
}

/*int rook::getDirection(int source, int destination) const
{
  if (!(abs(destination - source) % VERTICAL))
    return VERTICAL;
  else if (!(abs(destination-source) < HORIZONTAL))
    return 1;
  else
    return -1;
    }*/

ostream &rook::output(ostream &out) const
{
  if (color == WHITE)
    out << "\xe2\x99\x96";
  else
    out << "\xe2\x99\x9c";
  return out;
}
