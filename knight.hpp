/****************************************************
*                                                   *
* 550 - Integrated Programming Laboratory           *
* Lab Assessment 2: C++ 3                           *
* Oliver Grubin, November/December 2014             *
* og514@ic.ac.uk                                    *
*                                                   *
* knight.hpp                                        *
* Header file for Knight class                      *
*                                                   *
*****************************************************/

#ifndef KNIGHT_H
#define KNIGHT_H

#include "ChessPiece.hpp"

class knight : public ChessPiece
{
public:
  // Constructor.  Sets up the knights's color and the vector of possible directions
  knight(Color _color);

private:
  // Returns true if the knight can move from source to destination.
  bool validDirection(int source, int destination) const;

  // Returns a vector of all the moves a knight can make from a given position on a
  // given board
  std::vector<int> generateMoves(int source, ChessPiece **board);

  // Overridden function to return the direction a knight will move from source
  // to destination.  A knight will always jump
  int getDirection(int source, int destination) const;

  // Outputs the string "Knight"
  std::ostream &output(std::ostream &out) const;

  // Outputs the unicode symbol for the knight
  std::ostream &outputS(std::ostream &out) const;
};

#endif
