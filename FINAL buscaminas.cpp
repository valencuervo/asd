#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int WIDTH = 5;   // Ancho del tablero
const int HEIGHT = 5;  // Alto del tablero
const int MINES = 5;   // Número de minas

enum Cell { HIDDEN, REVEALED, FLAGGED };

struct CellInfo {
    int mineCount;
    Cell state;
    bool hasMine;
};

class SimpleMinesweeper {
public:
    SimpleMinesweeper();
    void Run();

private:
    vector<vector<CellInfo>> board;
    vector<vector<CellInfo>> displayBoard;
    bool gameOver;

    void Setup();
    void DrawBoard();
    void Input();
    void RevealCell(int x, int y);
    void FlagCell(int x, int y);
    void RevealAdjacentCells(int x, int y);
    bool IsWin();
    void PlaceMines();
    void CalculateMineCounts();
};

SimpleMinesweeper::SimpleMinesweeper() : gameOver(false) {
    Setup();
}

void SimpleMinesweeper::Setup() {
    board.resize(HEIGHT, vector<CellInfo>(WIDTH));
    displayBoard.resize(HEIGHT, vector<CellInfo>(WIDTH));

    PlaceMines();
    CalculateMineCounts();
}

void SimpleMinesweeper::PlaceMines() {
    srand(time(0));
    int minesPlaced = 0;
    while (minesPlaced < MINES) {
        int x = rand() % HEIGHT;
        int y = rand() % WIDTH;
        if (!board[x][y].hasMine) {
            board[x][y].hasMine = true;
            ++minesPlaced;
        }
    }
}

void SimpleMinesweeper::CalculateMineCounts() {
    for (int x = 0; x < HEIGHT; ++x) {
        for (int y = 0; y < WIDTH; ++y) {
            if (board[x][y].hasMine) continue;
            int mineCount = 0;
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx >= 0 && nx < HEIGHT && ny >= 0 && ny < WIDTH && board[nx][ny].hasMine) {
                        ++mineCount;
                    }
                }
            }
            board[x][y].mineCount = mineCount;
        }
    }
}

void SimpleMinesweeper::DrawBoard() {
    system("cls");  // Limpia la pantalla (específico de Windows)
    for (int x = 0; x < HEIGHT; ++x) {
        for (int y = 0; y < WIDTH; ++y) {
            if (displayBoard[x][y].state == HIDDEN) {
                cout << "# ";
            } else if (displayBoard[x][y].state == FLAGGED) {
                cout << "F ";
            } else {
                if (board[x][y].hasMine) {
                    cout << "* ";
                } else {
                    cout << board[x][y].mineCount << ' ';
                }
            }
        }
        cout << endl;
    }
}

void SimpleMinesweeper::Input() {
    char command;
    int x, y;
    cout << "Enter command (r for reveal, f for flag), and coordinates (x y): ";
    cin >> command >> x >> y;

    if (x < 0 || x >= HEIGHT || y < 0 || y >= WIDTH) {
        cout << "Invalid coordinates. Try again." << endl;
        return;
    }

    if (command == 'r') {
        RevealCell(x, y);
    } else if (command == 'f') {
        FlagCell(x, y);
    }
}

void SimpleMinesweeper::RevealCell(int x, int y) {
    if (displayBoard[x][y].state != HIDDEN) return;

    displayBoard[x][y].state = REVEALED;

    if (board[x][y].hasMine) {
        gameOver = true;
        return;
    }

    if (board[x][y].mineCount == 0) {
        RevealAdjacentCells(x, y);
    }

    if (IsWin()) {
        gameOver = true;
    }
}

void SimpleMinesweeper::FlagCell(int x, int y) {
    if (displayBoard[x][y].state == HIDDEN) {
        displayBoard[x][y].state = FLAGGED;
    } else if (displayBoard[x][y].state == FLAGGED) {
        displayBoard[x][y].state = HIDDEN;
    }
}

void SimpleMinesweeper::RevealAdjacentCells(int x, int y) {
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < HEIGHT && ny >= 0 && ny < WIDTH) {
                RevealCell(nx, ny);
            }
        }
    }
}

bool SimpleMinesweeper::IsWin() {
    for (int x = 0; x < HEIGHT; ++x) {
        for (int y = 0; y < WIDTH; ++y) {
            if (!board[x][y].hasMine && displayBoard[x][y].state == HIDDEN) {
                return false;
            }
        }
    }
    return true;
}

void SimpleMinesweeper::Run() {
    while (!gameOver) {
        DrawBoard();
        Input();
    }

    DrawBoard();
    if (gameOver && IsWin()) {
        cout << "Congratulations! You've won!" << endl;
    } else if (gameOver) {
        cout << "Game Over! You hit a mine." << endl;
    }
}

int main() {
    SimpleMinesweeper game;
    game.Run();
    return 0;
}


