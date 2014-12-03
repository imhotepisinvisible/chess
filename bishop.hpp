/****************************************************
*                                                   *
* 550 - Integrated Programming Laboratory           *
* Lab Assessment 2: C++ 3                           *
* Oliver Grubin, November/December 2014             *
* og514@ic.ac.uk                                    *
*                                                   *
* bishop.hpp                                        *
* Header file for Bishop class                      *
*                                                   *
*****************************************************/

#ifndef BISHOP_H
#define BISHOP_H

#include "ChessPiece.hpp"

class bishop : public ChessPiece
{
public:
  // Constructor.  Sets up the bishop's color and the vector of possible directions
  bishop(Color _color);

private:
  // Returns true if the bishop can move from source to destination.
  bool validDirection(int source, int destination) const;

  // Outputs the string "Bishop"
  std::ostream &output(std::ostream &out) const;

  // Outputs the unicode symbol for the bishop
  std::ostream &outputS(std::ostream &out) const;
};

#endif
