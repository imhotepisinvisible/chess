/****************************************************
*                                                   *
* 550 - Integrated Programming Laboratory           *
* Lab Assessment 2: C++ 3                           *
* Oliver Grubin, November/December 2014             *
* og514@ic.ac.uk                                    *
*                                                   *
* rook.hpp                                          *
* Header file for Rook class                        *
*                                                   *
*****************************************************/

#ifndef ROOK_H
#define ROOK_H

#include "ChessPiece.hpp"

class rook : public ChessPiece
{
public:
  // Constructor.  Sets up the rook's color and the vector of possible directions
  rook(Color _color);

private:
  // Returns true if the rook can move from source to destination.
  bool validDirection(int source, int destination) const;

  // Outputs the string "Rook"
  std::ostream &output(std::ostream &out) const;

  // Outputs the unicode symbol for the rook
  std::ostream &outputS(std::ostream &out) const;
};

#endif
