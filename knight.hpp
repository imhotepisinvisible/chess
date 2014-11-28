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

class knight : public ChessPiece
{
public:
  knight(Color _color) : ChessPiece(_color){}

private:
  bool validDirection(int source, int destination);
  int getDirection(int source, int destination) const;
  std::ostream &output(std::ostream &out) const;
};

#endif
