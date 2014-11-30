/****************************************************
*                                                   *
* 550 - Integrated Programming Laboratory           *
* Lab Assessment 2: C++ 3                           *
* Oliver Grubin, November/December 2014             *
* og514@ic.ac.uk                                    *
*                                                   *
* ChessPiece.hpp                                    *
* Header file for ChessPiece class                  *
*                                                   *
*****************************************************/

#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <vector>

class ChessPiece
{
public:
  enum Color {WHITE, BLACK};

  ChessPiece(Color _color);
  virtual ~ChessPiece();

  virtual bool canMove(int source, int destination, ChessPiece **board);
  virtual std::vector<int> generateMoves(int source, ChessPiece **board);
  std::vector<int> getPossDirs() const;
  Color getColor() const;
  friend std::ostream &operator<<(std::ostream &out, const ChessPiece &cp);
  std::ostream &operator>>(std::ostream &out) const;
  virtual std::ostream &output(std::ostream &out) const = 0;
  virtual std::ostream &outputS(std::ostream &out) const = 0;

protected:
  Color color;
  std::vector<int> possDirs;
  static const int VERTICAL;
  static const int HORIZONTAL;
  static const int DIAGONAL;
  static const int ANTIDIAGONAL;
  static const int L_LEFT_HIGH;
  static const int L_LEFT_LOW;
  static const int L_RIGHT_HIGH;
  static const int L_RIGHT_LOW;
  static const int JUMP;

  virtual bool validDirection(int source, int destination) = 0;
  bool routeBlocked(int source, int destination, ChessPiece **board);
  virtual int getDirection(int source, int destination) const;

};

#endif
