#include <iostream>
#include <vector>

using namespace std;

// Function prototypes
void displayBoard(const vector<vector<char>>& board);
bool makeMove(vector<vector<char>>& board, char currentPlayer, int row, int col);
bool checkWin(const vector<vector<char>>& board, char currentPlayer);
bool checkDraw(const vector<vector<char>>& board);
bool playAgain();

int main() {
    do {
        vector<vector<char>> board(3, vector<char>(3, ' '));
        char currentPlayer = 'X';
        bool gameWon = false;
        bool gameDraw = false;

        cout << "Welcome to Tic-Tac-Toe!\n";

        do {
            displayBoard(board);

            int row, col;
            cout << "Player " << currentPlayer << ", enter your move (row and column, separated by a space): ";
            cin >> row >> col;

            if (row >= 1 && row <= 3 && col >= 1 && col <= 3) {
                if (board[row - 1][col - 1] == ' ') {
                    if (makeMove(board, currentPlayer, row - 1, col - 1)) {
                        gameWon = checkWin(board, currentPlayer);
                        gameDraw = checkDraw(board);

                        if (!gameWon && !gameDraw) {
                            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                        }
                    } else {
                        cout << "Invalid move. Try again.\n";
                    }
                } else {
                    cout << "Cell already taken. Try again.\n";
                }
            } else {
                cout << "Invalid input. Row and column must be between 1 and 3.\n";
            }

        } while (!gameWon && !gameDraw);

        displayBoard(board);

        if (gameWon) {
            cout << "Player " << currentPlayer << " wins!\n";
        } else {
            cout << "It's a draw!\n";
        }

    } while (playAgain());

    return 0;
}

void displayBoard(const vector<vector<char>>& board) {
    cout << "\n  1 2 3\n";
    for (int i = 0; i < 3; ++i) {
        cout << i + 1 << " ";
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j];
            if (j < 2) {
                cout << "|";
            }
        }
        cout << "\n";
        if (i < 2) {
            cout << "  -----\n";
        }
    }
    cout << "\n";
}

bool makeMove(vector<vector<char>>& board, char currentPlayer, int row, int col) {
    if (board[row][col] == ' ') {
        board[row][col] = currentPlayer;
        return true;
    }
    return false;
}

bool checkWin(const vector<vector<char>>& board, char currentPlayer) {
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) {
            return true; // Check rows
        }
        if (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer) {
            return true; // Check columns
        }
    }
    if (board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) {
        return true; // Check diagonal (top-left to bottom-right)
    }
    if (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer) {
        return true; // Check diagonal (top-right to bottom-left)
    }
    return false;
}

bool checkDraw(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell == ' ') {
                return false; // The board is not full
            }
        }
    }
    return true; // All cells are filled, but no player has won
}

bool playAgain() {
    char choice;
    cout << "Do you want to play again? (y/n): ";
    cin >> choice;
    return (choice == 'y' || choice == 'Y');
}
