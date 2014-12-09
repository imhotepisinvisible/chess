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
  // Constructor. Initialize board, counter and game over state
  ChessBoard();

  // Destructor. Deallocate memory allocated for the board and pieces
  ~ChessBoard();

  // Processes a move.  Returns true if the move succeeds, false if the move fails
  bool submitMove(std::string sourceStr, std::string destStr);

  // Resets the board to its initial state.  Returns false if memory can't be
  // allocated for any reason
  bool resetBoard();

  // For future use.  Prints out the current points total of both players
  void printPoints() const;

private:
  // Consts
  static const int NUM_PIECES;
  static const int ARRAY_LENGTH;
  static const int ARRAY_COL_LENGTH;
  static const int ARRAY_ROW_LENGTH;

  // The board array.  Using an 0x88 board (a one dimensional array of length 128)
  // because of the nice ability it gives you in generating moves and checking
  // for invalid input by doing a bitwise AND with 0x88
  // http://web.archive.org/web/20071026130204/http://www.seanet.com/~brucemo/topics/0x88.htm
  ChessPiece **board;

  // Counts the number of moves (by black and white combined) in the game
  // You can deduce whose turn it is by doing modulo-2 on this number
  int moveCounter;

  // An integer array of the location of all the white pieces on the board
  int whitePieceLocs[16];

  // An integer array of the location of all the black pieces on the board
  int blackPieceLocs[16];

  // Total white points
  int whitePoints;

  // Total black points
  int blackPoints;

  // Boolean flag to determine if the game has finished or not
  bool gameOver;

  // Boolean flag to determine if a specific move is an attempted castle
  bool castleAttempt;

  // Boolean flag to determine if a specific move is an attempted En Passant
  bool enPassantAttempt;

  // Boolean flag to determine if a specific move is an attempted promotion
  bool promotionAttempt;

  // Pointer to the location array of the current player's pieces
  int *player;

  // Pointer to the location array of the current opponent's pieces
  int *opponent;

  // Pointer to the player's points
  int *playerPoints;

  // String of the current player's color
  std::string playerColor;

  // String of the current opponent's color
  std::string opponentColor;

  // Two integers used for implementing the fifty-move rule.
  // Contain the move number where the last pawn was moved and the last
  // capture was made
  int pawnMoved;
  int captureMade;

  // Initialize the board.  Returns false if memory can't be allocated for
  // any reason.  Sets up the pieces on the board array and their locations
  // in the location arrays.  Anywhere without a piece on the board is NULL
  bool initBoard();

  // Deallocate all memory given to the pieces and the board
  void deleteBoard();

  // Parse an input string into an integer referring to an index on my board
  // Returns -1 on bad input
  int parse(std::string square) const;

  // Returns the color of the current move's player
  ChessPiece::Color moveColor() const;

  // Updates either the player or opponent's location array, changing the
  // source location to the dest location
  void updateLocationArray(int *&locArray, int source, int dest);

  // Overloaded function.  The first one tests a move from source to dest
  // and returns true if it will result in the king being in check.
  // The second returns true if the king is in check in the current board state
  // kingLoc is the location of the king, pieces is the location array of the
  // opposing player
  bool inCheck(int source, int dest, int *&pieces, int kingLoc) const;
  bool inCheck(int *&pieces, int kingLoc) const;

  // Loops over every piece checking if it can make a legal move (i.e. a move
  // that doesn't result in one's king being in check).  Returns true if this
  // is possible, false if not
  bool legalMovesExist(int *&player, int *&opponent) const;

  // Processes a regular move.  Returns true if the move succeeded, false if not
  bool makeMove(int source, int dest);

  // Processes a castle move, either king side or queen side.  Returns true
  // if the castle is possible, false if not, i.e. if the king has not moved,
  // the rook it is swapping with has not moved, the route is not blocked,
  // and the king is not in check, will not move through check and will not
  // end up in check
  bool castle(int source, int dest);

  // Processes an en passant move.  Returns true if the en passant succeeded,
  // false if not
  bool enPassant(int source, int dest);

  // Processes a promotion.  Returns true if the promotion succeeded,
  // false if not
  bool promote(int source, int dest, char promoteTo);

  // Checks for errors on either the source or destination inputs.  Returns true
  // on error, false on no error
  bool inputError(int source, int dest) const;

  // Sets up the pointers and string for the current move's player and opponent
  void setupColors();

  // Debug only.  Prints out the board so you can see the state of the game at a
  // specified point
#ifdef DEBUG
  void printBoard() const;
#endif

};

#endif
