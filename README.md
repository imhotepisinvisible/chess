# Chess

A simple Player vs Player console based chess game created as part of Imperial College Computing Science MSc Module 550 - Integrated Programming Laboratory.

    White's Bishop moves from D3 to G6
    Black is in checkmate
       ┌───┬───┬───┬───┬───┬───┬───┬───┐
    8  │ ♜ │   │ ♝ │ ♛ │ ♚ │   │   │ ♜ │
       ├───┼───┼───┼───┼───┼───┼───┼───┤
    7  │ ♟ │   │ ♟ │ ♞ │   │   │ ♟ │   │
       ├───┼───┼───┼───┼───┼───┼───┼───┤
    6  │   │ ♟ │   │   │ ♟ │ ♞ │ ♗ │ ♟ │
       ├───┼───┼───┼───┼───┼───┼───┼───┤
    5  │   │   │   │   │   │   │   │   │
       ├───┼───┼───┼───┼───┼───┼───┼───┤
    4  │   │   │   │ ♙ │   │   │   │   │
       ├───┼───┼───┼───┼───┼───┼───┼───┤
    3  │ ♗ │   │ ♙ │   │   │   │   │   │
       ├───┼───┼───┼───┼───┼───┼───┼───┤
    2  │ ♙ │   │ ♙ │   │   │ ♙ │ ♙ │ ♙ │
       ├───┼───┼───┼───┼───┼───┼───┼───┤
    1  │ ♖ │   │   │   │ ♔ │   │ ♘ │ ♖ │
       └───┴───┴───┴───┴───┴───┴───┴───┘
         A   B   C   D   E   F   G   H
    White has 5 points.
    Black has 13 points.
    
All rules are implemented, including Castling, Promotion, En Passant and scoring.

## Playing The Game

Enter the starting square followed by the destination square.  Enter `FI` to quit.

## Compilation

Very simple, just type `make` in the console and run with `./chess`