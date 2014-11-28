/****************************************************
*                                                   *
* 550 - Integrated Programming Laboratory           *
* Lab Assessment 2: C++ 3                           *
* Oliver Grubin, November/December 2014             *
* og514@ic.ac.uk                                    *
*                                                   *
* bishop.cpp                                        *
* Implementation file for Bishop class              *
*                                                   *
*****************************************************/

#include <iostream>
#include <cstdlib>

#include "ChessPiece.hpp"
#include "bishop.hpp"

using namespace std;

bool bishop::validDirection(int source, int destination)
{
  return (abs(destination - source) % DIAGONAL || abs(destination-source) % ANTIDIAGONAL);
}

/*int bishop::getDirection(int source, int destination) const
{
  if (!(abs(destination - source) % DIAGONAL))
    return DIAGONAL;
  else if (!(abs(destination-source) % ANTIDIAGONAL))
    return ANTIDIAGONAL;
  else
    return -1;
    }*/

ostream &bishop::output(ostream &out) const
{
  if (color == WHITE)
    out << "\xe2\x99\x97";
  else
    out << "\xe2\x99\x9d";
  return out;
}
