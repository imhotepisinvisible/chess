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

class ChessPiece;

class ChessBoard
{
public:
  ChessBoard();
  ~ChessBoard();
  ChessPiece **getBoard();
  bool submitMove(std::string source, std::string dest);
  bool resetBoard();
  void printBoard();

private:
  ChessPiece **board;
  int moveCounter;

  bool initBoard();
  bool deleteBoard();
  bool initPieces();
  int parse(std::string square);
  ChessPiece::Color moveColor();

};

#endif
