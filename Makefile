# Adapted from Fidelis' magical Makefile

OBJ = ChessMain.o ChessBoard.o ChessPiece.o pawn.o knight.o bishop.o rook.o queen.o king.o
EXECUTABLE = chess
GCC = g++
CFLAGS = -g -Wall -MMD

$(EXECUTABLE): $(OBJ)
	$(GCC) $(CFLAGS) $(OBJ) -o $(EXECUTABLE)

%.o: %.cpp
	$(GCC) $(CFLAGS) -c $<

-include $(OBJ:.o=.d)

.PHONY: clean

clean:
	rm -f $(OBJ) $(EXECUTABLE) $(OBJ:.o=.d)
