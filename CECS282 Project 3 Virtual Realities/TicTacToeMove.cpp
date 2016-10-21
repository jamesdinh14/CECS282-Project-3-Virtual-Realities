#include "TicTacToeMove.h"
#include "TicTacToeBoard.h"
#include "GameExceptions.h"
#include <sstream>

using namespace std;

int TicTacToeMove::mOnHeap = 0;

TicTacToeMove::TicTacToeMove() : mRow(-1), mCol(-1) {
   
}

TicTacToeMove::TicTacToeMove(int row, int col) : mRow(row), mCol(col) {

}

TicTacToeMove::~TicTacToeMove() {

}

GameMove& TicTacToeMove::operator=(const string &input) {
   istringstream inputReader(input);
   char buffer;

   // Parse the string for the two integers
   inputReader >> buffer >> mRow >> buffer >> mCol;

   // If the move is not in bounds, throw exception
   if (!TicTacToeBoard::InBounds(mRow, mCol))
      throw TicTacToeException("Out of bounds.");

   return *this;
}

TicTacToeMove::operator std::string() const {
   return "(" + to_string(mRow) + "," + to_string(mCol) + ")";
}

bool TicTacToeMove::Equals(const GameMove &other) const {
   const TicTacToeMove &otherMove = dynamic_cast<const TicTacToeMove&>(other);
   return (mRow == otherMove.mRow) && (mCol == otherMove.mCol);
}