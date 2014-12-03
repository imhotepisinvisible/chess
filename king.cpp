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

#include "king.hpp"

using namespace std;

king::king(Color _color)
  : ChessPiece(_color)
{
  possDirs.push_back(VERTICAL);
  possDirs.push_back(-VERTICAL);
  possDirs.push_back(DIAGONAL);
  possDirs.push_back(-DIAGONAL);
  possDirs.push_back(ANTIDIAGONAL);
  possDirs.push_back(-ANTIDIAGONAL);
  possDirs.push_back(1);
  possDirs.push_back(-1);
}

bool king::validDirection(int source, int destination) const
{
  return (abs(destination - source) == VERTICAL
	  || abs(destination - source) == DIAGONAL
	  || abs(destination - source) == ANTIDIAGONAL
	  || abs(destination - source) == 1);
}

bool king::canCastle(int source, int destination, ChessPiece **board) const
{
  if (destination == source+2
      && !getMoved()
      && board[source+1] == NULL
      && board[source+2] == NULL
      && board[source+3] != NULL && !board[source+3]->getMoved()) // King side
    return true;
  else if (destination == source-2
	   && !getMoved()
	   && board[source-1] == NULL
	   && board[source-2] == NULL
	   && board[source-3] == NULL
	   && board[source-4] != NULL && !board[source-4]->getMoved()) // Queen side
    return true;

  return false;
}

vector<int> king::generateMoves(int source, ChessPiece **board)
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

ostream &king::output(ostream &out) const
{
  out << "King";
  return out;
}

ostream &king::outputS(ostream &out) const
{
  if (color == WHITE)
    out << "\u2654";
  else
    out << "\u265a";
  return out;
}
