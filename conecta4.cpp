#include <iostream>

using namespace std;

const int FILA = 6;  
const int COLUM = 7; 


void incializartablero(char board[FILA][COLUM]) {
    for (int i = 0; i < FILA; i++) {
        for (int j = 0; j < COLUM; j++) {
            board[i][j] = ' ';
        }
    }
}


void visualizartablero(const char board[FILA][COLUM]) {
  
     cout << " ";
    for (int col = 0; col < COLUM; col++) {
        cout << "|" << col + 1;
    }
    cout << "|" << endl;

    for (int fila = 0; fila < FILA; fila++) {
        cout << " ";
        for (int col = 0; col < COLUM; col++) {
            cout << "|" << board[fila][col];
        }
        cout << "|" << endl;
    }
    //cout << "" << endl;  // Empty line for spacing
}

// Function to validate if you can play in a column (checks range and if full)
bool columnallena(const char board[FILA][COLUM], int column) {
    if (column < 1 || column > COLUM) {
        cout << "La columna debe estar entre 1 y 7 BABOSA!!" << endl;
        return false;
    } else if (board[0][column - 1] != ' ') {
        cout << "Columna " << column << " está llena, elija otra columna BABOSA!!" << endl;
        return false;
    }
    return true;
}

// Function to simulate gravity (place piece in the lowest empty spot)
void gravedad(char board[FILA][COLUM], int column, char player) {
    for (int fila = FILA - 1; fila >= 0; fila--) {
        if (board[fila][column] == ' ') {
            board[fila][column] = player;
            break;
        }
    }
}

// Function to verify victory horizontally
bool winhorizontal(const char board[FILA][COLUM], char player) {
    for (int fila = 0; fila < FILA; fila++) {
        for (int col = 0; col < COLUM - 3; col++) {
            if (board[fila][col] == player &&
                board[fila][col + 1] == player &&
                board[fila][col + 2] == player &&
                board[fila][col + 3] == player) {
                return true;
            }
        }
    }
    return false;
}

// Function to verify victory vertically
bool winvertical(const char board[FILA][COLUM], char player) {
    for (int fila = 0; fila < FILA - 3; fila++) {
        for (int col = 0; col < COLUM; col++) {
            if (board[fila][col] == player &&
                board[fila + 1][col] == player &&
                board[fila + 2][col] == player &&
                board[fila + 3][col] == player) {
                return true;
            }
        }
    }
    return false;
}

// Function to verify victory on ascendent diagonal (top-left to bottom-right)
bool windiagonal(const char board[FILA][COLUM], char player) {
    for (int fila = 0; fila < FILA - 3; fila++) {
        for (int col = 0; col < COLUM - 3; col++) {
            if (board[fila][col] == player &&
                board[fila + 1][col + 1] == player &&
                board[fila + 2][col + 2] == player &&
                board[fila + 3][col + 3] == player) {
                return true;
            }
        }
    }
    return false;
}

bool windiagonalarriba(const char board[FILA][COLUM], char player) {
for (int fila = 0; fila < FILA  && -3; fila++) {
            for (int col = 3; col < COLUM && -3; col++) {
                if (board[fila][col] == player &&
                    board[fila + 1][col - 1] == player &&
                    board[fila + 2][col - 2] == player &&
                    board[fila + 3][col - 3] == player) {
                    return true;
                }
            }
        }
      return false;
}

// Function to check for draw (board is full)
bool empate(const char board[FILA][COLUM]) {
    for (int col = 0; col < COLUM; col++) {
        if (board[0][col] == ' ') {
            return false;  // Not full
        }
    }
    return true;  // Full
}

// Function to alternate turns
void cambiarturno(char& player) {
    if (player == 'X') {
        player = 'O';
    } else {
        player = 'X';
    }
}

void play() {
    char tabla[FILA][COLUM];
    char jugadorActual = 'X';
    bool gameOver = false;

    // Initialize the board
    incializartablero(tabla);

    cout << "=== CONNECTA 4 ===" << endl;

    while (!gameOver) {
        // Visualize the board
        visualizartablero(tabla);

        int column;
        while (true) {
            cout << "Jugador: " << jugadorActual << ", ingrese la columna a jugar (1-7): ";
            cin >> column;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Please enter a valid number!" << endl;
                continue;
            }

            if (columnallena(tabla, column)) {
                break;  // Valid column
            }
            // If not valid, the loop continues
        }
        column -= 1;  // Convert to 0-based index

        // Apply gravity to place the piece
        gravedad(tabla, column, jugadorActual);

        // Verify victory in all directions
        if (winhorizontal(tabla, jugadorActual) ||
            winvertical(tabla, jugadorActual) ||
            windiagonal(tabla, jugadorActual) ||
            windiagonalarriba(tabla,jugadorActual)){
            visualizartablero(tabla);  // Show final board
            cout << "Jugador: " << jugadorActual << " GANASTE!!!" << endl;
            gameOver = true;
            continue;
        }

        // Check for draw
        if (empate(tabla)) {
            visualizartablero(tabla);
            cout << "Empataron chikes" << endl;
            gameOver = true;
            continue;
        }

        // Alternate turns
        cambiarturno(jugadorActual);
    }
    
}
    
int main() {
    play();

    return 0;
}