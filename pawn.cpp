/****************************************************
*                                                   *
* 550 - Integrated Programming Laboratory           *
* Lab Assessment 2: C++ 3                           *
* Oliver Grubin, November/December 2014             *
* og514@ic.ac.uk                                    *
*                                                   *
* pawn.cpp                                          *
* Implementation file for Pawn class                *
*                                                   *
*****************************************************/

#include <iostream>

#include "pawn.hpp"

using namespace std;

pawn::pawn(Color _color)
  : ChessPiece(_color)
{
  pointsValue = 1;
  possDirs.push_back(VERTICAL);
  possDirs.push_back(DIAGONAL);
  possDirs.push_back(ANTIDIAGONAL);
  possDirs.push_back(-VERTICAL);
  possDirs.push_back(-DIAGONAL);
  possDirs.push_back(-ANTIDIAGONAL);
}

bool pawn::validDirection(int source, int destination) const
{
  if (color == WHITE)
    return ((destination - source) == VERTICAL 
	    || (source >= 16 && source <= 23 && (destination - source) == VERTICAL*2)
	    || (destination - source) == DIAGONAL
	    || (destination - source) == ANTIDIAGONAL);
  else
    return ((source - destination) == VERTICAL
	    || (source >= 96 && source <= 103 && (source - destination) == VERTICAL*2)
	    || (source - destination) == DIAGONAL
	    || (source - destination) == ANTIDIAGONAL);
}

bool pawn::canMove(int source, int destination, ChessPiece **board) const
{
  if (!validDirection(source, destination))
    return false;

  if (board[destination] != NULL
      && getDirection(source, destination) != DIAGONAL
      && getDirection(source, destination) != ANTIDIAGONAL)
    return false;
  else if (board[destination] == NULL
	   && getDirection(source, destination) != VERTICAL)
    return false;

  return true;
}

bool pawn::canEnPassant(int source, int dest, ChessPiece **board) const
{
  if ((getDirection(source, dest) == DIAGONAL
       || getDirection(source, dest) == ANTIDIAGONAL)
      && board[dest] == NULL)
    {
      if (color == WHITE && source >= 64 && source <= 71)
	    return true;
      else if (color == BLACK && source >= 48 && source <= 55)
	    return true;
    }

  return false;
}

bool pawn::canPromote(int source) const
{
  if (color == WHITE && source >= 96 && source <= 103)
    return true;
  else if (color == BLACK && source >= 16 && source <= 23)
    return true;

  return false;
}

vector<int> pawn::generateMoves(int source, ChessPiece **board)
{
  // Generate a vector containing every possible square this piece can move to
  // Radiate out, stopping if it reaches the edge of the board, or an occupied square
  vector<int> result;
  if (color == WHITE)
    {
      if (source >=16 && source <=23)
	{
	  if (!((source + VERTICAL*2) & 0x88)
	      && board[source + VERTICAL] == NULL
	      && board[source + VERTICAL*2] == NULL)
	    {
	      result.push_back(source + VERTICAL*2);
	    }
	}
      if (!((source + VERTICAL) & 0x88)
	  && board[source + VERTICAL] == NULL)
	{
	  result.push_back(source + VERTICAL);
	}
      if (!((source + DIAGONAL) & 0x88)
	  && board[source + DIAGONAL] != NULL
	  && board[source + DIAGONAL]->getColor() == BLACK)
	{
	  result.push_back(source + DIAGONAL);
	}
      if (!((source + ANTIDIAGONAL) & 0x88)
	  && board[source + ANTIDIAGONAL] != NULL
	  && board[source + ANTIDIAGONAL]->getColor() == BLACK)
	{
	  result.push_back(source + ANTIDIAGONAL);
	}
    }
  else
    {
      if (source >= 96 && source <= 103)
	{
	  if (!((source - VERTICAL*2) & 0x88)
	      && board[source - VERTICAL] == NULL
	      && board[source - VERTICAL*2] == NULL)
	    {
	      result.push_back(source - VERTICAL*2);
	    }
	}
      if (!((source - VERTICAL) & 0x88)
	  && board[source - VERTICAL] == NULL)
	{
	  result.push_back(source - VERTICAL);
	}
      if (!((source - DIAGONAL) & 0x88)
	  && board[source - DIAGONAL] != NULL
	  && board[source - DIAGONAL]->getColor() == WHITE)
	{
	  result.push_back(source - DIAGONAL);
	}
      if (!((source - ANTIDIAGONAL) & 0x88)
	  && board[source - ANTIDIAGONAL] != NULL
	  && board[source - ANTIDIAGONAL]->getColor() == WHITE)
	{
	  result.push_back(source - ANTIDIAGONAL);
	}
    }

  return result;
}

ostream &pawn::output(ostream &out) const
{
  out << "Pawn";
  return out;
}

ostream &pawn::outputS(ostream &out) const
{
  if (color == WHITE)
    out << "\u2659";
  else
    out << "\u265f";
  return out;
}
