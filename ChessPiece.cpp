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
const int ChessPiece::HORIZONTAL = 8;
const int ChessPiece::DIAGONAL = 17;
const int ChessPiece::ANTIDIAGONAL = 15;
const int ChessPiece::L_LEFT_HIGH = 31;
const int ChessPiece::L_LEFT_LOW = 14;
const int ChessPiece::L_RIGHT_HIGH = 33;
const int ChessPiece::L_RIGHT_LOW = 18;
const int ChessPiece::JUMP = 0;

ChessPiece::ChessPiece(Color _color)
  : color(_color), moved(false)
{
}

ChessPiece::~ChessPiece()
{
}

bool ChessPiece::canMove(int source, int destination, ChessPiece **board) const
{
  // First check if the piece can even move in the direction vector
  if (!validDirection(source, destination))
    return false;

  // Now check if the destination square is already occupied by a
  // piece of the same color
  if (board[destination] != NULL
      && board[destination]->getColor() == board[source]->getColor())
    return false;

  // Now check if there are any obstructions to the destination
  if (routeBlocked(source, destination, board))
    return false;

  return true;
}

bool ChessPiece::routeBlocked(int source, int destination, ChessPiece **board) const
{
  // Loop over a route checking if there is anything in the way
  // If the piece can jump then it is never blocked
  int direction = getDirection(source, destination);

  if (direction == JUMP)
    return false;

  int squares = abs(source - destination) / direction;
  if (squares > 1 && direction >= 1)
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

vector<int> ChessPiece::generateMoves(int source, ChessPiece **board)
{
  // Generate a vector containing every possible square this piece can move to
  // Radiate out, stopping if it reaches the edge of the board, or an occupied square
  vector<int> result;
  vector<int> possDirs = getPossDirs();
  for (vector<int>::iterator it = possDirs.begin(); it != possDirs.end(); ++it)
    {
      for (int i = source+*it; !(i & 0x88); i += *it)
	{
	  if (board[i] == NULL)
	    result.push_back(i);
	  else
	    {
	      if (board[i]->getColor() != color)
		  result.push_back(i);

	      break;
	    }
	}
    }
  return result;
}

vector<int> ChessPiece::getPossDirs() const
{
  return possDirs;
}

int ChessPiece::getDirection(int source, int destination) const
{
  if (abs(destination - source) % VERTICAL == 0)
    return VERTICAL;
  else if (abs(destination - source) % DIAGONAL == 0)
    return DIAGONAL;
  else if (abs(destination-source) % ANTIDIAGONAL == 0)
    return ANTIDIAGONAL;
  else if (abs(destination-source) < HORIZONTAL)
    return 1;
  else
    return -1; //ERROR
}

ChessPiece::Color ChessPiece::getColor() const
{
  return color;
}

void ChessPiece::setMoved()
{
  moved = true;
  return;
}

bool ChessPiece::getMoved() const
{
  return moved;
}

bool ChessPiece::canCastle(int source, int destination, ChessPiece **board) const
{
  return false;
}

ostream &operator<<(ostream &out, const ChessPiece &cp)
{
  cp.output(out);
  return out;
}

#ifdef DEBUG
ostream &ChessPiece::operator>>(ostream &out) const
{
  outputS(out);
  return out;
}
#endif
