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

#include "ChessPiece.hpp"
#include "queen.hpp"

using namespace std;

queen::queen(Color _color)
  : ChessPiece(_color)
{
  possDirs.push_back(VERTICAL);
  possDirs.push_back(-VERTICAL);
  possDirs.push_back(1);
  possDirs.push_back(-1);
  possDirs.push_back(DIAGONAL);
  possDirs.push_back(-DIAGONAL);
  possDirs.push_back(ANTIDIAGONAL);
  possDirs.push_back(-ANTIDIAGONAL);
}

bool queen::validDirection(int source, int destination)
{
  return (abs(destination - source) % VERTICAL == 0 || abs(destination-source) < HORIZONTAL
	   || abs(destination - source) % DIAGONAL == 0 || abs(destination-source) % ANTIDIAGONAL == 0);
}

/*vector<int> queen::generateMoves(int source, ChessPiece **board)
{
  // Generate a vector containing every possible square this piece can move to
  // Radiate out, stopping if it reaches the edge of the board, or an occupied square
  vector<int> result;
  for (int i = source; !(i & 0x88) && board[i] != NULL; i += VERTICAL)
    {
      result.push_back(i);
    }
  for (int i = source; !(i & 0x88) && board[i] != NULL; i -= VERTICAL)
    {
      result.push_back(i);
    }
  for (int i = source; !(i & 0x88) && board[i] != NULL; i++)
    {
      result.push_back(i);
    }
  for (int i = source; !(i & 0x88) && board[i] != NULL; i--)
    {
      result.push_back(i);
    }
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

int queen::getDirection(int source, int destination) const
{
  if (!(abs(destination - source) % VERTICAL))
    return VERTICAL;
  else if (!(abs(destination-source) < HORIZONTAL))
    return 1;
  else if (!(abs(destination - source) % DIAGONAL))
    return DIAGONAL;
  else if (!(abs(destination-source) % ANTIDIAGONAL))
    return ANTIDIAGONAL;
  else
    return -1; //ERROR
    }*/

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
