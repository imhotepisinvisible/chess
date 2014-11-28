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

class bishop : public ChessPiece
{
public:
  bishop(Color _color) : ChessPiece(_color){}

private:
  bool validDirection(int source, int destination);
  //int getDirection(int source, int destination) const;
  std::ostream &output(std::ostream &out) const;
};

#endif
