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

class rook : public ChessPiece
{
public:
  rook(Color _color) : ChessPiece(_color){}

private:
  bool validDirection(int source, int destination);
  //int getDirection(int source, int destination) const;
  std::ostream &output(std::ostream &out) const;
};

#endif
