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
#include <vector>

#include "ChessBoard.hpp"
#include "ChessPiece.hpp"
#include "pawn.hpp"
#include "knight.hpp"
#include "bishop.hpp"
#include "rook.hpp"
#include "queen.hpp"
#include "king.hpp"

using namespace std;

const int ChessBoard::NUM_PIECES = 16;
const int ChessBoard::ARRAY_LENGTH = 128;
const int ChessBoard::ARRAY_COL_LENGTH = 8;
const int ChessBoard::ARRAY_ROW_LENGTH = 16;
const int ChessBoard::OFFBOARD = -1;

ChessBoard::ChessBoard()
  : moveCounter(0), whitePoints(0), blackPoints(0),
    gameOver(false), pawnMoved(0), captureMade(0)
{
  initBoard();
}

ChessBoard::~ChessBoard()
{
  deleteBoard();
}

bool ChessBoard::submitMove(string sourceStr, string destStr)
{
  // Check for promotion special case
  bool promotionAttempt = (destStr.length() == 3);
  char promoteTo;
  if (promotionAttempt)
    {
      promoteTo = toupper(destStr[2]);
      destStr = destStr.substr(0, 2);
    }

  // Turn the input string into an int that will index to our board
  // and check if the input was valid
  int source = parse(sourceStr);
  int dest = parse(destStr);

  // Initialize player/opponent vars
  setupColors();

  // Check for errors in the input
  if (inputError(source, dest))
      return false;

  // Check for castling special case
  bool castleAttempt = (((source == 4 && (dest == 6 || dest == 2))
		    || (source == 116 && (dest == 118 || dest == 114)))
		   && board[source] != NULL
		   && board[source]->canCastle(source, dest, board));

  // Check for En Passant special case
  bool enPassantAttempt = (board[source] != NULL
		      && board[source]->canEnPassant(source, dest, board));

  // Process the move
  if ( (!castleAttempt && !enPassantAttempt
	&& !promotionAttempt && makeMove(source, dest))
       || (castleAttempt && castle(source, dest))
       || (enPassantAttempt && enPassant(source, dest))
       || (promotionAttempt && promote(source, dest, promoteTo)) )
    {
      moveCounter++;
    }
  else
    {
      cout << playerColor << "'s " << *board[source] << " cannot move to "
	   << destStr << "!" << endl;
      return false;
    }

  // Now check for Check/Checkmate/Stalemate
  if (inCheck(player, opponent[15]))
    {
      cout << opponentColor << " is in check";
      if (!legalMovesExist(opponent, player))
	{
	  cout << "mate";
	  gameOver = true;
	} 
      cout << endl;
    }
  else if (!legalMovesExist(opponent, player))
    {
      cout << "Stalemate" << endl;
      gameOver = true;
    }
  else if ((moveCounter-pawnMoved) >= 100 || (moveCounter-captureMade) >=100)
    {
      cout << "Draw because of the fifty-move rule" << endl;
      gameOver = true;
    }

#ifdef DEBUG
  printBoard();
#endif

  return true;
}

int ChessBoard::parse(string square) const
{
  // Check for errors in the input
  if (square.length() != 2)
    return OFFBOARD;
  square[0] = toupper(square[0]);
  if (square[0] < 'A' || square[0] > 'H')
    return OFFBOARD;
  if (square[1] < '1' || square[1] > '8')
    return OFFBOARD;

  int file = square[0] - 'A';
  int rank = square[1] - '1';

  // Multiply rank by 16 because of the 0x88 board and add the file
  return (rank*16 + file);
}

ChessPiece::Color ChessBoard::moveColor() const
{
  if (moveCounter % 2 == 0)
    return ChessPiece::WHITE;
  else
    return ChessPiece::BLACK;
}

void ChessBoard::updateLocationArray(int *&locArray, int source, int dest)
{
  for (int i = 0; i < NUM_PIECES; i++)
    {
      if (locArray[i] == source)
	{	
	  locArray[i] = dest;
	  return;
	}
    }

  return;
}

bool ChessBoard::inCheck(int source, int dest, int *&pieces, int kingLoc) const
{
  // Temporarily move the piece
  // It doesn't count as a move if you leave your finger on it!
  ChessPiece *temp = board[dest];
  board[dest] = board[source];
  board[source] = NULL;

  // If we're trying to move the king, move the king's location too!
  if (source == kingLoc)
    kingLoc = dest;

  // Run through all of the pieces, checking if they attack the king
  for (int i = 0; i < NUM_PIECES; i++)
    {
      if (pieces[i] != OFFBOARD && pieces[i] != dest
	  && board[pieces[i]]->canMove(pieces[i], kingLoc, board))
	{
	  // Put the pieces back where they were
	  board[source] = board[dest];
	  board[dest] = temp;
	  return true;
	}
    }

  // Put the pieces back where they were
  board[source] = board[dest];
  board[dest] = temp;
  return false;
}

bool ChessBoard::inCheck(int *&pieces, int kingLoc) const
{
  // Run through all of the pieces, checking if they attack the king
  for (int i = 0; i < NUM_PIECES; i++)
    {
      if (pieces[i] != OFFBOARD && board[pieces[i]]->canMove(pieces[i], kingLoc, board))
	  return true;
    }

  return false;
}

bool ChessBoard::legalMovesExist(int *&player, int *&opponent) const
{
  // Loop over all of the pieces, checking if any of them can make a legal move
  // (i.e. one that doesn't result in check). If so return true, else return false
  for (int i = 0; i < NUM_PIECES; i++)
    {
      if (player[i] != OFFBOARD)
	{
	  vector<int> possDests = board[player[i]]->generateMoves(player[i], board);
	  for (vector<int>::iterator it = possDests.begin(); it != possDests.end(); ++it)
	    {
	      if (!inCheck(player[i], *it, opponent, player[15]))
		  return true;
	    }
	}
    }
  return false;
}

bool ChessBoard::makeMove(int source, int dest)
{
  // Let's see if there are any obstructions to the move, or if it's in a valid direction
  // A piece also can't move if it will result in leaving its own king in check
  if (board[source]->canMove(source, dest, board)
      && !inCheck(source, dest, opponent, player[15]))
    {
      printMove(source, dest);

      if (board[dest] != NULL) // Taking someone
	{
	  cout << " taking " << opponentColor << "'s " << *board[dest];
	  *playerPoints += board[dest]->getPointsValue();
	  delete board[dest];
	  updateLocationArray(opponent, dest, OFFBOARD);
	  captureMade = moveCounter+1;
	}

      // Update pawnMoved if we're moving a pawn
      for (int i = 7; i < 15; i++)
	if (source == player[i])
	  pawnMoved = moveCounter+1;

      // Update the array
      updateLocationArray(player, source, dest);

      // Update the counters
      if (board[source]->getNumMoves() == 0)
	board[source]->setFirstMoveNum(moveCounter);

      ++(*board[source]);

      // Move the piece
      board[dest] = board[source];
      board[source] = NULL;

      cout << endl;

      return true;
    }

  return false;
}

bool ChessBoard::castle(int source, int dest)
{
  if (board[source]->canCastle(source, dest, board)
      && !inCheck(opponent, player[15])
      && dest == source+2
      && !inCheck(opponent, source+1)
      && !inCheck(opponent, source+2)) // King side castle
    {
      cout << playerColor << " castles" << endl;

      // Update the arrays
      updateLocationArray(player, source, source+2);
      updateLocationArray(player, source+3, source+1);

      // Update the counters
      board[source]->setFirstMoveNum(moveCounter);
      board[source+3]->setFirstMoveNum(moveCounter);
      ++(*board[source]);
      ++(*board[source+3]);

      // Move the pieces
      board[source+2] = board[source];
      board[source] = NULL;
      board[source+1] = board[source+3];
      board[source+3] = NULL;

      return true;
    }
  else if (board[source]->canCastle(source, dest, board)
	   && !inCheck(opponent, player[15])
	   && dest == source-2
	   && !inCheck(opponent, source-1)
	   && !inCheck(opponent, source-2)) // Queen side castle
    {
      cout << playerColor << " castles" << endl;

      // Update the arrays
      updateLocationArray(player, source, source-2);
      updateLocationArray(player, source-4, source-1);

      // Update the counters
      board[source]->setFirstMoveNum(moveCounter);
      board[source-4]->setFirstMoveNum(moveCounter);
      ++(*board[source]);
      ++(*board[source-4]);

      // Move the pieces
      board[source-2] = board[source];
      board[source] = NULL;
      board[source-1] = board[source-4];
      board[source-4] = NULL;

      return true;
    }
  return false;
}

bool ChessBoard::enPassant(int source, int dest)
{
  int oppPawnLoc;
  if (moveColor() == ChessPiece::WHITE)
    oppPawnLoc = dest - 16; // VERTICAL
  else
    oppPawnLoc = dest + 16; // VERTICAL

  if (board[dest] == NULL && board[oppPawnLoc] != NULL
      && board[oppPawnLoc]->getNumMoves() == 1
      && !inCheck(source, dest, opponent, player[15]))
    {
      // Check if we're taking an opposing pawn
      bool oppPawn = false;
      for (int i = 7; i < 15; i++)
	{
	  if (oppPawnLoc == opponent[i])
	    {
	      oppPawn = true;
	      break;
	    }
	}

      if (!oppPawn)
	return false;
      if (board[oppPawnLoc]->getFirstMoveNum() != moveCounter-1)
	return false;

      printMove(source, dest);
      cout << " taking " << opponentColor << "'s "
	   << *board[oppPawnLoc] << " by en passant" << endl;

      // Take the piece and add the points to the total
      *playerPoints += board[oppPawnLoc]->getPointsValue();
      delete board[oppPawnLoc];
      board[oppPawnLoc] = NULL;
      updateLocationArray(opponent, oppPawnLoc, OFFBOARD);
      captureMade = moveCounter+1;

      // Update the counters
      updateLocationArray(player, source, dest);
      ++(*board[source]);

      // Move the piece
      board[dest] = board[source];
      board[source] = NULL;

      pawnMoved = moveCounter+1;
      return true;
    }
  return false;
}

bool ChessBoard::promote(int source, int dest, char promoteTo)
{
  if (board[source]->canPromote(source)
      && board[source]->canMove(source, dest, board)
      && !inCheck(source, dest, opponent, player[15]))
    {
      ChessPiece *promotedPiece;
      switch (promoteTo)
	{
	case 'Q':
	  promotedPiece = new queen(moveColor());
	  break;
	case 'R':
	  promotedPiece = new rook(moveColor());
	  break;
	case 'B':
	  promotedPiece = new bishop(moveColor());
	  break;
	case 'N':
	  promotedPiece = new knight(moveColor());
	  break;
	default:
	  cout << "Error! Pawn can't promote to a " << promoteTo << endl;
	  return false;
	  break;
	}

      printMove(source, dest);

      if (board[dest] != NULL) // Taking someone
	{
	  cout << " taking " << opponentColor << "'s " << *board[dest];
	  *playerPoints += board[dest]->getPointsValue();
	  delete board[dest];
	  updateLocationArray(opponent, dest, OFFBOARD);
	  captureMade = moveCounter+1;
	}

      // Move the piece
      pawnMoved = moveCounter+1;
      updateLocationArray(player, source, dest);
      ++(*board[source]);

      board[dest] = promotedPiece;
      delete board[source];
      board[source] = NULL;

      cout << " and is promoted to a " << *board[dest] << endl;

      return true;
    }
  return false;
}

bool ChessBoard::inputError(int source, int dest) const
{
  // Check for an invalid move
  if (source == OFFBOARD || dest == OFFBOARD)
    {
      cout << "Error! Invalid move submitted!" << endl;
      return true;
    }

  // Check if the game is over
  if (gameOver)
    {
      cout << "Error! The game is already over!" << endl;
      return true;
    }

  // Check if there's a piece at the source square
  if (board[source] == NULL)
    {
      cout << "There is no piece at position "
	   << (char)(source%ARRAY_COL_LENGTH + 'A')
	   << (char)(source/ARRAY_ROW_LENGTH + '1')
	   << "!" << endl;
      return true;
    }

  // Check if destination is different from source
  if (source == dest)
    {
      cout << "Destination must be different from source" << endl;
      return true;
    }

  // Check if it's the right color for the player
  if (board[source]->getColor() != moveColor())
    {
      cout << "It is not " << opponentColor <<  "'s turn to move!" << endl;
      return true;
    }

  return false;
}

void ChessBoard::setupColors()
{
  switch (moveColor())
    {
    case ChessPiece::WHITE:
      player = whitePieceLocs;
      opponent = blackPieceLocs;
      playerColor = "White";
      opponentColor = "Black";
      playerPoints = &whitePoints;
      break;
    case ChessPiece::BLACK:
      player = blackPieceLocs;
      opponent = whitePieceLocs;
      playerColor = "Black";
      opponentColor = "White";
      playerPoints = &blackPoints;
      break;
    default:
      break;
    }
  return;
}

bool ChessBoard::initBoard()
{
  cout << "A new chess game is started!" << endl;
  // Set up a fresh board.  Return false if it fails for some reason.
  board = new (nothrow) ChessPiece*[ARRAY_LENGTH];
  if (board == NULL)
    {
      cout << "Error allocating memory for ChessBoard" << endl;
      return false;
    }
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
  for (int i = 0; i < 120; i++)
    {
      if (board[i] == NULL)
	{
	  cout << "Error allocating memory for ChessPiece" << endl;
	  return false;
	}
      if (i == 7)
	i = 15;
      if (i == 23)
	i = 95;
      if (i == 103)
	i = 111;
    }

  // We can set up the pieces array too.  Ordered by most powerful piece.
  whitePieceLocs[0] = 3; // Queen
  whitePieceLocs[1] = 0; // Rook
  whitePieceLocs[2] = 7; // Rook
  whitePieceLocs[3] = 2; // Light Square Bishop
  whitePieceLocs[4] = 5; // Dark Square Bishop
  whitePieceLocs[5] = 1; // Knight
  whitePieceLocs[6] = 6; // Knight
  whitePieceLocs[7] = 16; // Pawn
  whitePieceLocs[8] = 17; // Pawn
  whitePieceLocs[9] = 18; // Pawn
  whitePieceLocs[10] = 19; // Pawn
  whitePieceLocs[11] = 20; // Pawn
  whitePieceLocs[12] = 21; // Pawn
  whitePieceLocs[13] = 22; // Pawn
  whitePieceLocs[14] = 23; // Pawn
  whitePieceLocs[15] = 4; // King

  blackPieceLocs[0] = 115; // Queen
  blackPieceLocs[1] = 112; // Rook
  blackPieceLocs[2] = 119; // Rook
  blackPieceLocs[3] = 117; // Light Square Bishop
  blackPieceLocs[4] = 114; // Dark Square Bishop
  blackPieceLocs[5] = 113; // Knight
  blackPieceLocs[6] = 118; // Knight
  blackPieceLocs[7] = 96; // Pawn
  blackPieceLocs[8] = 97; // Pawn
  blackPieceLocs[9] = 98; // Pawn
  blackPieceLocs[10] = 99; // Pawn
  blackPieceLocs[11] = 100; // Pawn
  blackPieceLocs[12] = 101; // Pawn
  blackPieceLocs[13] = 102; // Pawn
  blackPieceLocs[14] = 103; // Pawn
  blackPieceLocs[15] = 116; // King

  return true;
}

void ChessBoard::deleteBoard()
{
  for (int i = 0; i < ARRAY_LENGTH; i++)
    {
    if (board[i] != NULL)
      {
	delete board[i];
	board[i] = NULL;
      }
    }
  delete [] board;
  return;
}

bool ChessBoard::resetBoard()
{
  deleteBoard();
  if (!initBoard())
    return false;
  moveCounter = 0;
  whitePoints = 0;
  blackPoints = 0;
  pawnMoved = 0;
  captureMade = 0;
  gameOver = false;
  return true;
}

void ChessBoard::printMove(int source, int dest) const
{
  cout << playerColor << "'s " << *board[source] << " moves from "
       << (char)(source%ARRAY_COL_LENGTH + 'A')
       << (char)(source/ARRAY_ROW_LENGTH + '1')
       << " to " << (char)(dest%ARRAY_COL_LENGTH + 'A')
       << (char)(dest/ARRAY_ROW_LENGTH + '1');

  return;
}

void ChessBoard::printPoints() const
{
  cout << "White has " << whitePoints << " points." << endl;
  cout << "Black has " << blackPoints << " points." << endl;
  return;
}

#ifdef DEBUG
void ChessBoard::printBoard() const
{
  cout << "   "
       << "\u250c\u2500\u2500\u2500\u252c"
       << "\u2500\u2500\u2500\u252c"
       << "\u2500\u2500\u2500\u252c"
       << "\u2500\u2500\u2500\u252c"
       << "\u2500\u2500\u2500\u252c"
       << "\u2500\u2500\u2500\u252c"
       << "\u2500\u2500\u2500\u252c"
       << "\u2500\u2500\u2500\u2510"
       << endl;
  for (int i = 7; i >= 0; i--)
    {
      cout << i+1 << "  \u2502";
      for (int j = 0; j < ARRAY_COL_LENGTH; j++)
	{
	  if (board[i*ARRAY_ROW_LENGTH+j] != NULL)
	    {
	      cout << " ";
	      *board[i*ARRAY_ROW_LENGTH+j] >> cout << " ";
	    }
	  else
	    cout << "   ";
	  cout << "\u2502";
	}
      if (i > 0)
	{
	  cout << endl << "   "
	       << "\u251c\u2500\u2500\u2500\u253c"
	       << "\u2500\u2500\u2500\u253c"
	       << "\u2500\u2500\u2500\u253c"
	       << "\u2500\u2500\u2500\u253c"
	       << "\u2500\u2500\u2500\u253c"
	       << "\u2500\u2500\u2500\u253c"
	       << "\u2500\u2500\u2500\u253c"
	       << "\u2500\u2500\u2500\u2524"
	       << endl;
	}
    }
  cout << endl << "   "
       << "\u2514\u2500\u2500\u2500\u2534"
       << "\u2500\u2500\u2500\u2534"
       << "\u2500\u2500\u2500\u2534"
       << "\u2500\u2500\u2500\u2534"
       << "\u2500\u2500\u2500\u2534"
       << "\u2500\u2500\u2500\u2534"
       << "\u2500\u2500\u2500\u2534"
       << "\u2500\u2500\u2500\u2518"
       << endl;
  cout << "     A   B   C   D   E   F   G   H" << endl;
  printPoints();
  cout << (moveColor() == ChessPiece::WHITE ? "White" : "Black") << "'s turn" << endl;
  return;

}
#endif
