#include "GameExceptions.h"
#include "GameBoard.h"
#include "GameView.h"
#include "GameMove.h"
#include "OthelloBoard.h"
#include "OthelloView.h"
#include "OthelloMove.h"
#include "TicTacToeBoard.h"
#include "TicTacToeView.h"
#include "TicTacToeMove.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;


int main(int argc, char* argv[]) {
   // Initialization
   GameBoard *board;   // Generic game board
   GameView *v;   // Generic GameBoard output
   string userInput;   // Holds user input
   vector<GameMove *> possMoves;   // List of possible moves

   // Master loop
   do {
      // Prompt user which game they want to play
      // Extracting correct variable from user input
      int choice = 0;
      string buffer;   // 7 lines

      // Input validation
      while (choice < 1 || choice > 3) {
         cout << "Which game would you like to play?" << endl;
         cout << "1. Othello" << "\n2. Tic Tac Toe" << "\n3. Exit" << endl;
         cout << "Enter your choice: ";
         getline(cin, userInput);
         istringstream iss(userInput);
         iss >> choice;
      }

      // If user wants to play Othello
      if (choice == 1) {
         board = new OthelloBoard();
         v = new OthelloView(board);
      }
      else if (choice == 2) { // If user wants to play TicTacToe
         board = new TicTacToeBoard();
         v = new TicTacToeView(board);   // 20 lines
      }
      else
         return 0; // Exit program

      // Main loop
      do {
         // Print the game board using the GameView object
         cout << *v << endl;

         //typedef to make readability easier on the for loops
         typedef vector<GameMove *>::iterator vectorItr;
         typedef vector<GameMove *>::const_iterator vectorcItr;
         typedef vector<GameMove *>::const_reverse_iterator crItr;

         // Ask to input a command
         cout << board->GetPlayerString(board->GetNextPlayer())
            << "'s turn." << endl;

         // Print all possible moves
         board->GetPossibleMoves(&possMoves);   // 30 lines

         cout << "Possible moves: " << endl;
         for (vectorcItr itr = possMoves.cbegin();
            itr != possMoves.cend(); itr++)
            cout << (string)**itr << " ";
         cout << endl;

         // isValid represents a valid command and move
         // prevents possible moves list from displaying too many times
         bool isValid;

         // Used for quitting a game
         bool gameQuit = false;

         // Command loop:
         do {

            // Get input
            cout << "Enter a command: ";
            getline(cin, userInput);   // 40 lines

            // default loop condition
            isValid = false;

            // move (r,c)
            if (userInput.find("move") == 0) {
               GameMove *move = board->CreateMove();
               const int substrStart = 5, substrLength = 5;

               // operator= can throw GameException when (r,c) is out of bounds
               // When exception is thrown, free up memory
               try {
                  // GameMove is assigned to input (r,c)
                  *move = userInput.substr(substrStart, substrLength);

                  // Check to make sure inputted move is in possMoves
                  // If it is, it is a valid command and the move is applied
                  // else don't apply the move and free memory
                  for (vectorcItr itr = possMoves.cbegin();
                     itr != possMoves.cend(); itr++) {
                     if (*move == **itr) {
                        board->ApplyMove(move);  // 50 lines
                        isValid = true;
                        break;
                     }
                  }

                  if (!isValid) {
                     cout << "Invalid move." << endl;
                     delete move;
                  }
               }
               catch (GameException &oe) {
                  cout << oe.what() << endl;
                  delete move;
               }
            }

            // undo n
            // Valid command
            if (userInput.find("undo") == 0) {
               istringstream iss(userInput);   // 60 lines
               string buffer;
               int numOfUndos = 0;

               // Obtain the int n from the input
               iss >> buffer >> numOfUndos;

               // Run undo n times
               // If n > move history's size, return to beginning
               while (numOfUndos > 0 && !board->GetMoveHistory()->empty()) {
                  board->UndoLastMove();
                  numOfUndos--;
               }
               isValid = true;
            }

            // showValue
            // Shows the current value of the board
            if (userInput == "showValue")
               cout << "\nValue of the board: " << board->GetValue() << endl;

            // showHistory
            // shows the move history, displaying the most recent one first
            if (userInput == "showHistory") {   // 70 lines
               char player = board->GetNextPlayer();

               // Display the history backwards (most recent move first)
               for (crItr itr = board->GetMoveHistory()->crbegin();
                  itr != board->GetMoveHistory()->crend(); itr++) {
                  // last player's move is the opposite of next player
                  player = -player;
                  cout << board->GetPlayerString(player) << ": " <<
                     (string)**itr << endl;
               }

               // If history is empty
               if (board->GetMoveCount() == 0)
                  cout << "None." << endl;
            }

            // quit
            // valid command
            if (userInput == "quit") {
               gameQuit = true;   // 80 lines
               break;
            }

         } while (!isValid);

         // Free memory from possMoves and clear the list
         for (vectorItr itr = possMoves.begin(); itr != possMoves.end(); itr++)
            delete *itr;
         possMoves.clear();

         if (gameQuit)
            break;

      } while (!board->IsFinished());

      // display the board one last time
      cout << *v << endl;

      // Determine winner with the board's value
      if (board->GetValue() > 0)   // 90 lines
         cout << endl << board->GetPlayerString(1) << " wins!" << endl;
      else if (board->GetValue() < 0)
         cout << endl << board->GetPlayerString(-1) << " wins!" << endl;
      else
         cout << "\nThe game is a tie!" << endl;

      // Clean up memory
      delete board;
      delete v;

   } while (1);   // Program keeps running until 3.Exit command is entered
}