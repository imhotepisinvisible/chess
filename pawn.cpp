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

#include "ChessPiece.hpp"
#include "pawn.hpp"

using namespace std;

bool pawn::validDirection(int source, int destination)
{
  if (color == WHITE)
    return ((destination - source) == VERTICAL || (source >= 16 && source <= 23 && (destination - source) == VERTICAL*2) || (destination - source) == DIAGONAL || (destination - source) == ANTIDIAGONAL);
  else
    return ((source - destination) == VERTICAL || (source >= 96 && source <= 103 && (source - destination) == VERTICAL*2) || (source - destination) == DIAGONAL || (source - destination) == ANTIDIAGONAL);
}

bool pawn::canMove(int source, int destination, ChessPiece **board)
{
  if (!validDirection(source, destination))
    return false;

  if (board[destination] != NULL && getDirection(source, destination) != DIAGONAL && getDirection(source, destination) != ANTIDIAGONAL)
    return false;
  else if (board[destination] == NULL && getDirection(source, destination) != VERTICAL)
    return false;

  return true;
}

/*int pawn::getDirection(int source, int destination) const
{
  return VERTICAL;
  }*/

ostream &pawn::output(ostream &out) const
{
  if (color == WHITE)
    out << "\xe2\x99\x99";
  else
    out << "\xe2\x99\x9f";
  return out;
}
