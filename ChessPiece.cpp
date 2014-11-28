/****************************************************
*                                                   *
* 550 - Integrated Programming Laboratory           *
* Lab Assessment 2: C++ 3                           *
* Oliver Grubin, November/December 2014             *
* og514@ic.ac.uk                                    *
*                                                   *
* ChessPiece.cpp                                    *
* Implementation file for ChessPiece class          *
*                                                   *
*****************************************************/

#include <iostream>
#include <cstdlib>

#include "ChessPiece.hpp"

using namespace std;

const int ChessPiece::VERTICAL = 16;
const int ChessPiece::HORIZONTAL = 8; //check this!
const int ChessPiece::DIAGONAL = 17;
const int ChessPiece::ANTIDIAGONAL = 15;
const int ChessPiece::L_LEFT_HIGH = 31;
const int ChessPiece::L_LEFT_LOW = 14;
const int ChessPiece::L_RIGHT_HIGH = 33;
const int ChessPiece::L_RIGHT_LOW = 18;

ChessPiece::ChessPiece(Color _color)
  : color(_color)
{
}

ChessPiece::~ChessPiece()
{
}

bool ChessPiece::canMove(int source, int destination, ChessPiece **board)
{
  if (!validDirection(source, destination))
    return false;

  if (routeBlocked(source, destination, board))
    return false;

  return true;
}

bool ChessPiece::routeBlocked(int source, int destination, ChessPiece **board)
{
  int direction = getDirection(source, destination);
  if (direction == 0)
    return false;
  int squares = abs(source - destination) / direction;
  if (squares > 1 && direction > 1)
    {
      for (int i = 1; i < squares; i++)
	{
	  if (source < destination)
	    {
	      if (board[source + direction*i] != NULL)
		return true;
	    }
	  else if (destination < source)
	    {
	      if (board[source - direction*i] != NULL)
		return true;
	    }
	}
    }
  return false;
}

int ChessPiece::getDirection(int source, int destination) const
{
  if (!(abs(destination - source) % VERTICAL))
    return VERTICAL;
  else if (!(abs(destination - source) % DIAGONAL))
    return DIAGONAL;
  else if (!(abs(destination-source) % ANTIDIAGONAL))
    return ANTIDIAGONAL;
  else if (!(abs(destination-source) < HORIZONTAL))
    return 1;
  else
    return -1; //ERROR
}

ChessPiece::Color ChessPiece::getColor() const
{
  return color;
}

ostream &operator<<(ostream &out, const ChessPiece &cp)
{
  cp.output(out);
  return out;
}