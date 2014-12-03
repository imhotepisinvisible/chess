/****************************************************
*                                                   *
* 550 - Integrated Programming Laboratory           *
* Lab Assessment 2: C++ 3                           *
* Oliver Grubin, November/December 2014             *
* og514@ic.ac.uk                                    *
*                                                   *
* king.hpp                                          *
* Header file for King class                        *
*                                                   *
*****************************************************/

#ifndef KING_H
#define KING_H

#include "ChessPiece.hpp"

class king : public ChessPiece
{
public:
  // Constructor.  Sets up the king's color and the vector of possible directions
  king(Color _color);

private:
  // Returns true if the king can move from source to destination.
  bool validDirection(int source, int destination) const;

  // Returns true if the king can castle, i.e. if it has not yet moved, if it
  // can move from source to destination on the given board without being
  // obstructed, and if it can switch places with a rook that also has not moved
  bool canCastle(int source, int destination, ChessPiece **board) const;

  // Returns a vector of all the moves a king can make from a given position on a
  // given board
  std::vector<int> generateMoves(int source, ChessPiece **board);

  // Outputs the string "King"
  std::ostream &output(std::ostream &out) const;

  // Outputs the unicode symbol for the king
  std::ostream &outputS(std::ostream &out) const;
};

#endif
