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

#include "rook.hpp"

using namespace std;

rook::rook(Color _color)
  : ChessPiece(_color)
{
  possDirs.push_back(VERTICAL);
  possDirs.push_back(-VERTICAL);
  possDirs.push_back(1);
  possDirs.push_back(-1);
}

bool rook::validDirection(int source, int destination) const
{
  return (abs(destination - source) % VERTICAL == 0
	  || abs(destination-source) < HORIZONTAL);
}

ostream &rook::output(ostream &out) const
{
  out << "Rook";
  return out;
}

ostream &rook::outputS(ostream &out) const
{
  if (color == WHITE)
    out << "\u2656";
  else
    out << "\u265c";
  return out;
}
