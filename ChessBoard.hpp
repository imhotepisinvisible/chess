/****************************************************
*                                                   *
* 550 - Integrated Programming Laboratory           *
* Lab Assessment 2: C++ 3                           *
* Oliver Grubin, November/December 2014             *
* og514@ic.ac.uk                                    *
*                                                   *
* ChessBoard.hpp                                    *
* Header file for ChessBoard class                  *
*                                                   *
*****************************************************/

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "ChessPiece.hpp"

class ChessBoard
{
public:
  ChessBoard();
  ~ChessBoard();
  ChessPiece **getBoard() const;
  bool submitMove(std::string source, std::string dest);
  bool resetBoard();

private:
  ChessPiece **board;
  int moveCounter;
  int whitePieceLocs[16];
  int blackPieceLocs[16];
  bool gameOver;

  bool initBoard();
  bool deleteBoard();
  bool initPieces();
  int parse(std::string square) const;
  ChessPiece::Color moveColor() const;
  void updateLocationArray(int *&locArray, int source, int dest);
  bool checkForCheck(int source, int dest, int *&pieces, int kingLoc) const;
  bool checkForCheck(int source, int *&pieces, int kingLoc) const;
  bool checkForLegalMoves(int *&player, int *&opponent) const;
#ifdef DEBUG
  void printBoard() const;
#endif

};

#endif
