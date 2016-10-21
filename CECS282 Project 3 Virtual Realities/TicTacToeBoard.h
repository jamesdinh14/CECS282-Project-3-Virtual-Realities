#ifndef __TICTACTOEBOARD_H
#define __TICTACTOEBOARD_H

#include <vector>
#include "TicTacToeMove.h"
#include "GameBoard.h"
#include "GameMove.h"

const int BOARD_SIZE_T = 3;

class TicTacToeBoard : public GameBoard {

public:
   enum Player { EMPTY = 0, X = 1, O = -1 };

   // Default constructor that sets up the initial state of the board
   TicTacToeBoard();

   // Obtains all the possible moves
   virtual void GetPossibleMoves(std::vector<GameMove *> *list) const;

   // Applies a move in TicTacToe
   virtual void ApplyMove(GameMove *move);

   // Undos the previous apply
   virtual void UndoLastMove();

   // Create GameMove on heap
   virtual GameMove *CreateMove() const { return new TicTacToeMove; }

   // Game ending condition
   virtual bool IsFinished() const {
      return mTurns >= 9 || mValue != 0;
   }

   // String representation of TicTacToe players
   virtual std::string GetPlayerString(char player) {
      return (player == 1 ? "X" : "O");
   }

   inline static bool InBounds(int row, int col) {
      return row >= 0 && row < BOARD_SIZE_T && col >= 0 && col < BOARD_SIZE_T;
   }

   

private:
   friend class TicTacToeView;

   bool CheckWinner() const;

   int mTurns;
   char mBoard[BOARD_SIZE_T][BOARD_SIZE_T];
};
#endif