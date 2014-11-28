/****************************************************
*                                                   *
* 550 - Integrated Programming Laboratory           *
* Lab Assessment 2: C++ 3                           *
* Oliver Grubin, November/December 2014             *
* og514@ic.ac.uk                                    *
*                                                   *
* pawn.hpp                                          *
* Header file for Pawn class                        *
*                                                   *
*****************************************************/

#ifndef PAWN_H
#define PAWN_H

class pawn : public ChessPiece
{
public:
  pawn(Color _color) : ChessPiece(_color){}
  bool canMove(int source, int destination, ChessPiece **board);

private:
  bool validDirection(int source, int destination);
  //int getDirection(int source, int destination) const;
  std::ostream &output(std::ostream &out) const;
};

#endif
