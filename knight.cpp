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

#include "knight.hpp"

using namespace std;

knight::knight(Color _color)
  : ChessPiece(_color)
{
  possDirs.push_back(L_LEFT_HIGH);
  possDirs.push_back(-L_LEFT_HIGH);
  possDirs.push_back(L_LEFT_LOW);
  possDirs.push_back(-L_LEFT_LOW);
  possDirs.push_back(L_RIGHT_HIGH);
  possDirs.push_back(-L_RIGHT_HIGH);
  possDirs.push_back(L_RIGHT_LOW);
  possDirs.push_back(-L_RIGHT_LOW);
}

bool knight::validDirection(int source, int destination) const
{
  return (abs(destination - source) == L_LEFT_HIGH
	  || abs(destination-source) == L_LEFT_LOW
	  || abs(destination - source) == L_RIGHT_HIGH
	  || abs(destination-source) == L_RIGHT_LOW);
}

vector<int> knight::generateMoves(int source, ChessPiece **board)
{
  // Generate a vector containing every possible square this piece can move to
  // Radiate out, stopping if it reaches the edge of the board, or an occupied square
  vector<int> result;
  vector<int> possDirs = getPossDirs();
  for (vector<int>::iterator it = possDirs.begin(); it != possDirs.end(); ++it)
    {
      if (!((source + *it) & 0x88)
	  && (board[source + *it] == NULL
	      || (board[source + *it] != NULL && board[source + *it]->getColor() != color)))
	{
	  result.push_back(source + *it);
	}
    }
  return result;
}

int knight::getDirection(int source, int destination) const
{
  return JUMP;
}

ostream &knight::output(ostream &out) const
{
  out << "Knight";
  return out;
}

ostream &knight::outputS(ostream &out) const
{
  if (color == WHITE)
    out << "\u2658";
  else
    out << "\u265e";
  return out;
}
