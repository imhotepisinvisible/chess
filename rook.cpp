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
#include <vector>

#include "ChessPiece.hpp"
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

bool rook::validDirection(int source, int destination)
{
  return (abs(destination - source) % VERTICAL == 0 || abs(destination-source) < HORIZONTAL);
}

/*vector<int> rook::generateMoves(int source, ChessPiece **board)
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
  return result;
}

int rook::getDirection(int source, int destination) const
{
  if (!(abs(destination - source) % VERTICAL))
    return VERTICAL;
  else if (!(abs(destination-source) < HORIZONTAL))
    return 1;
  else
    return -1;
    }*/


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
