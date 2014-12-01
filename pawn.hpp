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
  pawn(Color _color);
  bool canMove(int source, int destination, ChessPiece **board) const;
  std::vector<int> generateMoves(int source, ChessPiece **board);

private:
  bool validDirection(int source, int destination) const;
  std::ostream &output(std::ostream &out) const;
  std::ostream &outputS(std::ostream &out) const;
};

#endif
