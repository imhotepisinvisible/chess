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

class queen : public ChessPiece
{
public:
  queen(Color _color) : ChessPiece(_color){}

private:
  bool validDirection(int source, int destination);
  //int getDirection(int source, int destination) const;
  std::ostream &output(std::ostream &out) const;
};

#endif
