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
//#define DEBUG

#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <vector>

class ChessPiece
{
public:
  // Enum to make it easier to distinguish between white and black colors
  enum Color {WHITE, BLACK};

  // Constructor.  Sets up a piece's color and that it has not yet moved
  ChessPiece(Color _color);

  // Destructor.
  virtual ~ChessPiece();

  // Returns true if the piece can move from source to destination on the
  // specified board
  virtual bool canMove(int source, int destination, ChessPiece **board) const;

  // Returns a vector of all the possible moves a piece can make given a starting
  // location of source on a given board
  virtual std::vector<int> generateMoves(int source, ChessPiece **board);

  // Returns the vector of possible directions a piece can move
  std::vector<int> getPossDirs() const;

  // Returns the color of the piece
  Color getColor() const;

  // Sets moved to true
  void setMoved();

  // Returns whether a piece has moved or not
  bool getMoved() const;

  // Returns true if a piece is able to castle, false if not.  All pieces other than king
  // will always return false
  virtual bool canCastle(int source, int destination, ChessPiece **board) const;

  // Output operator outputs the name of the piece
  friend std::ostream &operator<<(std::ostream &out, const ChessPiece &cp);

  // Debug only.  Used for outputting the unicode symbol of the piece
#ifdef DEBUG
  std::ostream &operator>>(std::ostream &out) const;
#endif

protected:
  // Definitions of one square directions on the 0x88 board
  static const int VERTICAL;
  static const int HORIZONTAL;
  static const int DIAGONAL;
  static const int ANTIDIAGONAL;
  static const int L_LEFT_HIGH;
  static const int L_LEFT_LOW;
  static const int L_RIGHT_HIGH;
  static const int L_RIGHT_LOW;
  static const int JUMP;

  // The color of the piece
  Color color;

  // Boolean flag that returns whether a piece has moved or not
  bool moved;

  // Vector of possible directions a piece can move
  std::vector<int> possDirs;

  // Returns true if a piece can move in the vector of source to destination
  virtual bool validDirection(int source, int destination) const = 0;

  // Returns true if the route from source to destination is blocked on a
  // given board
  bool routeBlocked(int source, int destination, ChessPiece **board) const;

  // Returns the direction a piece will move from the source to the destination
  // A knight will jump.
  virtual int getDirection(int source, int destination) const;

  // Outputs a string of the piece's name
  virtual std::ostream &output(std::ostream &out) const = 0;

  // Outputs the piece's unicode symbol
  virtual std::ostream &outputS(std::ostream &out) const = 0;

};

#endif
