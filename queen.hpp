/****************************************************
*                                                   *
* 550 - Integrated Programming Laboratory           *
* Lab Assessment 2: C++ 3                           *
* Oliver Grubin, November/December 2014             *
* og514@ic.ac.uk                                    *
*                                                   *
* queen.hpp                                         *
* Header file for Queen class                       *
*                                                   *
*****************************************************/

#ifndef QUEEN_H
#define QUEEN_H

#include "ChessPiece.hpp"

class queen : public ChessPiece
{
public:
  // Constructor.  Sets up the queen's color and the vector of possible directions
  queen(Color _color);

private:
  // Returns true if the queen can move from source to destination.
  bool validDirection(int source, int destination) const;

  // Outputs the string "Queen"
  std::ostream &output(std::ostream &out) const;

  // Outputs the unicode symbol for the queen
  std::ostream &outputS(std::ostream &out) const;
};

#endif
