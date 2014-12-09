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

#include "queen.hpp"

using namespace std;

queen::queen(Color _color)
  : ChessPiece(_color)
{
  pointsValue = 9;
  possDirs.push_back(VERTICAL);
  possDirs.push_back(-VERTICAL);
  possDirs.push_back(1);
  possDirs.push_back(-1);
  possDirs.push_back(DIAGONAL);
  possDirs.push_back(-DIAGONAL);
  possDirs.push_back(ANTIDIAGONAL);
  possDirs.push_back(-ANTIDIAGONAL);
}

bool queen::validDirection(int source, int destination) const
{
  return (abs(destination - source) % VERTICAL == 0
	  || abs(destination-source) < HORIZONTAL
	  || abs(destination - source) % DIAGONAL == 0
	  || abs(destination-source) % ANTIDIAGONAL == 0);
}

ostream &queen::output(ostream &out) const
{
  out << "Queen";
  return out;
}

ostream &queen::outputS(ostream &out) const
{
  if (color == WHITE)
    out << "\u2655";
  else
    out << "\u265b";
  return out;
}
