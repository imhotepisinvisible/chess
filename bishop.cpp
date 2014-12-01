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

bishop::bishop(Color _color)
  : ChessPiece(_color)
{
  possDirs.push_back(DIAGONAL);
  possDirs.push_back(-DIAGONAL);
  possDirs.push_back(ANTIDIAGONAL);
  possDirs.push_back(-ANTIDIAGONAL);
}

bool bishop::validDirection(int source, int destination) const
{
  return (abs(destination - source) % DIAGONAL == 0
	  || abs(destination-source) % ANTIDIAGONAL == 0);
}

ostream &bishop::output(ostream &out) const
{
  out << "Bishop";
  return out;
}

ostream &bishop::outputS(ostream &out) const
{
  if (color == WHITE)
    out << "\u2657";
  else
    out << "\u265d";
  return out;
}
