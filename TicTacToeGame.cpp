#include <iostream>
#include <string>
using namespace std;

char board[3][3] = { {'1','2','3'}, {'4','5','6'}, {'7','8','9'} };
char current_marker;
int current_player;

void drawBoard() {
    cout << "\n";
    cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << "\n";
    cout << "---|---|---\n";
    cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << "\n";
    cout << "---|---|---\n";
    cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << "\n\n";
}

bool placeMarker(int slot) {
    int row = (slot - 1) / 3;
    int col = (slot - 1) % 3;

    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = current_marker;
        return true;
    }
    return false;
}

int checkWinner() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return current_player;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return current_player;
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return current_player;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return current_player;

    return 0;
}

void switchPlayer() {
    current_player = (current_player == 1) ? 2 : 1;
    current_marker = (current_marker == 'X') ? 'O' : 'X';
}

void game() {
    cout << "Enter name of Player 1: ";
    string p1, p2;
    cin >> p1;
    cout << "Enter name of Player 2: ";
    cin >> p2;

    current_player = 1;
    current_marker = 'X';
    int winner = 0;

    for (int i = 0; i < 9; i++) {
        drawBoard();
        cout << "Player " << current_player << " (" << current_marker << "), choose your slot (1–9): ";
        int slot;
        cin >> slot;

        if (slot < 1 || slot > 9) {
            cout << "⚡ Invalid choice! Try again.\n";
            i--;
            continue;
        }

        if (!placeMarker(slot)) {
            cout << "🚫 That spot is already filled. Pick another.\n";
            i--;
            continue;
        }

        winner = checkWinner();
        if (winner == 1 || winner == 2) {
            drawBoard();
            cout << "🎉 Congratulations " << ((winner == 1) ? p1 : p2) << "! You are the winner! 🏅\n";
            return;
        }

        switchPlayer();
    }

    drawBoard();
    cout << "🤝 It's a tie! Well played both!\n";
}

int main() {
    system("chcp 65001 > nul"); // Enable UTF-8 for emojis on Windows

    cout << "🕹️  Welcome to Classic Tic Tac Toe 🕹️\n";
    game();

    return 0;
}
