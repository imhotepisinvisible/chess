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

class king : public ChessPiece
{
public:
  king(Color _color) : ChessPiece(_color){}

private:
  bool validDirection(int source, int destination);
  //int getDirection(int source, int destination) const;
  std::ostream &output(std::ostream &out) const;
};

#endif
