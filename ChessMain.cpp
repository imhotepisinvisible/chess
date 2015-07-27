#include <iostream>

using namespace std;

#include "ChessBoard.hpp"

int main() {

  cout << "================" << endl;
  cout << "Welcome to Chess" << endl;
  cout << "================" << endl;
  cout << endl;

  ChessBoard cb;

#ifdef DEBUG
  cb.printBoard();
#endif

  string source, dest;

  while (source != "FI" || dest != "FI")
  {
    cout << "Enter move:";
    cin >> source >> dest;

    cb.submitMove(source, dest);
   }

  return 0;
}
