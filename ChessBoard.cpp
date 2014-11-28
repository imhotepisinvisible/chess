/****************************************************
*                                                   *
* 550 - Integrated Programming Laboratory           *
* Lab Assessment 2: C++ 3                           *
* Oliver Grubin, November/December 2014             *
* og514@ic.ac.uk                                    *
*                                                   *
* ChessBoard.cpp                                    *
* Implementation file for ChessBoard class          *
*                                                   *
*****************************************************/

#include <iostream>

#include "ChessBoard.hpp"
#include "ChessPiece.hpp"
#include "pawn.hpp"
#include "knight.hpp"
#include "bishop.hpp"
#include "rook.hpp"
#include "queen.hpp"
#include "king.hpp"

using namespace std;

ChessBoard::ChessBoard()
  : moveCounter(0)
{
  //initPieces();
  initBoard();
}

ChessBoard::~ChessBoard()
{
  deleteBoard();
}

bool ChessBoard::submitMove(string source, string dest)
{
  // Turn the input string into an int that will index to our board
  // and check if the input was valid
  int intSource = parse(source);
  int intDest = parse(dest);
  if (intSource == -1 || intDest == -1)
    {
      cout << "Error! Invalid move submitted!" << endl;
      return false;
    }

  // Check if there's a piece at the source square
  if (board[intSource] == NULL)
    {
      cout << "There is no piece at position " << source << "!" << endl;
      return false;
    }
  // Check if destination is different from source
  if (intSource == intDest)
    {
      cout << "Destination must different from source" << endl;
      return false;
    }
  // Check if it's the right color for the player
  if (board[intSource]->getColor() != moveColor())
    {
      cout << "It is not " << (moveColor() == ChessPiece::WHITE ? "Black" : "White") <<  "'s turn to move!" << endl;
      return false;
    }
  // Check if the destination square is already occupied by a piece of the same color
  if (board[intDest] != NULL && board[intDest]->getColor() == moveColor())
    {
      cout << (moveColor() == ChessPiece::WHITE ? "White" : "Black") << "'s " << *board[intSource] << " cannot move to " << dest << "!" << endl;
    }

  // Let's see if there are any obstructions to the move, or if it's in a valid direction
  if (board[intSource]->canMove(intSource, intDest, board))
    {
      cout << (moveColor() == ChessPiece::WHITE ? "White" : "Black") << "'s " << *board[intSource] << " moves from " << source << " to " << dest;
      //TODO: if we're taking someone, delete their memory
      if (board[intDest] != NULL)
	{
	  cout << " taking " << (moveColor() == ChessPiece::WHITE ? "Black" : "White") << "'s " << *board[intDest];
	  delete board[intDest];
	}
      board[intDest] = board[intSource];
      board[intSource] = NULL;
      moveCounter++;
      cout << endl;
    }
  else
    {
      cout << (moveColor() == ChessPiece::WHITE ? "White" : "Black") << "'s " << *board[intSource] << " cannot move to " << dest << "!" << endl;
      return false;
    }

  // Now check for Check/Checkmate/Stalemate

  printBoard();
  return true;
}

int ChessBoard::parse(string square)
{
  if (square.length() != 2)
    return -1;
  if (square[0] < 'A' && square[0] > 'H')
    return -1;
  if (square[1] < 1 && square[1] > 8)
    return -1;
  int file = square[0] - 'A';
  int rank = square[1] - '1';

  return (rank*16 + file);
}

ChessPiece::Color ChessBoard::moveColor()
{
  if (moveCounter % 2 == 0)
    return ChessPiece::WHITE;
  else
    return ChessPiece::BLACK;
}

bool ChessBoard::initBoard()
{
  cout << "A new chess game is started!" << endl;
  // Set up a fresh board.  Return false if it fails for some reason.
  board = new ChessPiece*[128]; //TODO remove magic number, and do assertion (or (nothrow))
  for (int i = 0; i < 128; i++)
    board[i] = NULL;
  board[0] = new rook(ChessPiece::WHITE);
  board[1] = new knight(ChessPiece::WHITE);
  board[2] = new bishop(ChessPiece::WHITE);
  board[3] = new queen(ChessPiece::WHITE);
  board[4] = new king(ChessPiece::WHITE);
  board[5] = new bishop(ChessPiece::WHITE);
  board[6] = new knight(ChessPiece::WHITE);
  board[7] = new rook(ChessPiece::WHITE);
  board[16] = new pawn(ChessPiece::WHITE);
  board[17] = new pawn(ChessPiece::WHITE);
  board[18] = new pawn(ChessPiece::WHITE);
  board[19] = new pawn(ChessPiece::WHITE);
  board[20] = new pawn(ChessPiece::WHITE);
  board[21] = new pawn(ChessPiece::WHITE);
  board[22] = new pawn(ChessPiece::WHITE);
  board[23] = new pawn(ChessPiece::WHITE);
  board[96] = new pawn(ChessPiece::BLACK);
  board[97] = new pawn(ChessPiece::BLACK);
  board[98] = new pawn(ChessPiece::BLACK);
  board[99] = new pawn(ChessPiece::BLACK);
  board[100] = new pawn(ChessPiece::BLACK);
  board[101] = new pawn(ChessPiece::BLACK);
  board[102] = new pawn(ChessPiece::BLACK);
  board[103] = new pawn(ChessPiece::BLACK);
  board[112] = new rook(ChessPiece::BLACK);
  board[113] = new knight(ChessPiece::BLACK);
  board[114] = new bishop(ChessPiece::BLACK);
  board[115] = new queen(ChessPiece::BLACK);
  board[116] = new king(ChessPiece::BLACK);
  board[117] = new bishop(ChessPiece::BLACK);
  board[118] = new knight(ChessPiece::BLACK);
  board[119] = new rook(ChessPiece::BLACK);
  return true;
}

bool ChessBoard::deleteBoard()
{
  for (int i = 0; i < 128; i++)
    {
    if (board[i] != NULL)
      {
	delete board[i];
	board[i] = NULL;
      }
    }
  delete [] board;
  return true;
}

bool ChessBoard::resetBoard()
{
  deleteBoard();
  initBoard();
  moveCounter = 0;
  return true;
}

ChessPiece **ChessBoard::getBoard()
{
  return board;
}

void ChessBoard::printBoard()
{
  cout << "   ---------------------------------" << endl;
  for (int i = 7; i >= 0; i--)
    {
      cout << i+1 << "  |";
      for (int j = 0; j < 8; j++)
	{
	  if (board[i*16+j] != NULL)
	    cout << " " << *board[i*16+j] << " ";
	  else
	    cout << "   ";
	  cout << "|";
	}
      cout << endl << "   ---------------------------------" << endl;
    }
  cout << "     A   B   C   D   E   F   G   H" << endl;

  return;

}
