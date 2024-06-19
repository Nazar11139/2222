#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

const int BOARD_SIZE = 10;
const string SAVE_FILE = "game_history.txt";


class Board {
private:
    char grid[BOARD_SIZE][BOARD_SIZE]; 

public:
    Board() {
        initializeGrid();
    }


    void initializeGrid() {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                grid[i][j] = ' ';
            }
        }
    }


    void display() {
        cout << "  ";
        for (int i = 0; i < BOARD_SIZE; ++i)
            cout << i << " ";
        cout << endl;

        for (int i = 0; i < BOARD_SIZE; ++i) {
            cout << i << " ";
            for (int j = 0; j < BOARD_SIZE; ++j) {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
    }


    bool isValidMove(int x, int y) {
        return (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE && grid[x][y] == ' ');
    }

 
    void makeMove(int x, int y, char symbol) {
        grid[x][y] = symbol;
    }

   
    char checkForWinner() {
       
        srand(time(nullptr));
        int random = rand() % 2;
        if (random == 0)
            return 'X';
        else
            return 'O';
    }

  
    bool isFull() {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (grid[i][j] == ' ')
                    return false;
            }
        }
        return true;
    }

 
    void saveGame() {
        ofstream file(SAVE_FILE, ios::app);
        if (file.is_open()) {
            for (int i = 0; i < BOARD_SIZE; ++i) {
                for (int j = 0; j < BOARD_SIZE; ++j) {
                    file << grid[i][j];
                }
                file << endl;
            }
            file << "===" << endl;
            file.close();
        } else {
            cerr << "Unable to open file for saving." << endl;
        }
    }


    void loadGame() {
        ifstream file(SAVE_FILE);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                if (line == "===") {
                    initializeGrid();
                } else {
                    for (int j = 0; j < BOARD_SIZE; ++j) {
                        grid[line.size() / BOARD_SIZE][j] = line[j];
                    }
                }
            }
            file.close();
        } else {
            cerr << "Unable to open file for loading." << endl;
        }
    }
};


int main() {
    Board game;
    char currentPlayer = 'X'; 
    int x, y;
    bool gameOn = true;

    while (!game.isFull()) {
        game.display();
        cout << "Current player: " << currentPlayer << endl;
        cout << "Enter coordinates (x y): ";
        cin >> x >> y;

        if (game.isValidMove(x, y)) {
            game.makeMove(x, y, currentPlayer);
            game.saveGame(); 

            char winner = game.checkForWinner();
            if (winner != ' ') {
                cout << "Player " << winner << " wins!" << endl;
                gameOn = false;
                break;
            }

            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X'; 
        } else {
            cout << "Invalid move! Try again." << endl;
        }
    }

    if (gameOn) {
        cout << "It's a draw!" << endl;
    }

    game.display();
    return 0;
}
