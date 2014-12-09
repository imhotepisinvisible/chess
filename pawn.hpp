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

#include "ChessPiece.hpp"

class pawn : public ChessPiece
{
public:
  // Constructor.  Sets up the pawn's color and the vector of possible directions
  pawn(Color _color);

  // Overridden function because a pawn moves differently to other pieces:
  // A pawn can move two squares on its first turn, one square if its route
  // is not blocked, or diagonally if it can take an opposing piece
  bool canMove(int source, int destination, ChessPiece **board) const;

  // Returns true if the pawn is able to make an en passant move, false if not
  bool canEnPassant(int source, int dest, ChessPiece **board) const;

  // Returns true if the pawn is able to be promoted, false if not
  bool canPromote(int source) const;

private:
  // Returns true if the pawn can move from source to destination.
  // Pawns can only move forward, so this differs depending on color
  bool validDirection(int source, int destination) const;

  // Returns a vector of all the moves a pawn can make from a given position on a
  // given board
  std::vector<int> generateMoves(int source, ChessPiece **board);

  // Outputs the string "Pawn"
  std::ostream &output(std::ostream &out) const;

  // Outputs the unicode symbol for the pawn
  std::ostream &outputS(std::ostream &out) const;
};

#endif
