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

bool bishop::validDirection(int source, int destination)
{
  return (abs(destination - source) % DIAGONAL == 0 || abs(destination-source) % ANTIDIAGONAL == 0);
}

/*vector<int> bishop::generateMoves(int source, ChessPiece **board)
{
  // Generate a vector containing every possible square this piece can move to
  // Radiate out, stopping if it reaches the edge of the board, or an occupied square
  vector<int> result;
  for (int i = source; !(i & 0x88) && board[i] != NULL; i += DIAGONAL)
    {
      result.push_back(i);
    }
  for (int i = source; !(i & 0x88) && board[i] != NULL; i -= DIAGONAL)
    {
      result.push_back(i);
    }
  for (int i = source; !(i & 0x88) && board[i] != NULL; i += ANTIDIAGONAL)
    {
      result.push_back(i);
    }
  for (int i = source; !(i & 0x88) && board[i] != NULL; i -= ANTIDIAGONAL)
    {
      result.push_back(i);
    }
  return result;
}

int bishop::getDirection(int source, int destination) const
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
