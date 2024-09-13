#include <iostream>
#include <vector>

using namespace std;

const int TAM = 3;  // Tamaño del tablero
const char VACIO = ' ';
const char JUGADOR1 = 'X';
const char JUGADOR2 = 'O';

class TicTacToe {
public:
    TicTacToe();
    void Ejecutar();

private:
    vector<vector<char>> tablero;
    char turno;
    bool juegoTerminado;

    void MostrarTablero();
    void HacerMovimiento();
    bool VerificarGanador();
    bool VerificarEmpate();
    void CambiarTurno();
    bool EsMovimientoValido(int fila, int columna);
};

TicTacToe::TicTacToe() : turno(JUGADOR1), juegoTerminado(false) {
    tablero.resize(TAM, vector<char>(TAM, VACIO));
}

void TicTacToe::MostrarTablero() {
    system("cls");  // Limpia la pantalla (específico de Windows)
    cout << "  0 1 2\n";
    for (int i = 0; i < TAM; ++i) {
        cout << i << " ";
        for (int j = 0; j < TAM; ++j) {
            cout << tablero[i][j] << " ";
        }
        cout << endl;
    }
}

void TicTacToe::HacerMovimiento() {
    int fila, columna;
    cout << "Jugador " << turno << ", ingresa fila y columna (0-2): ";
    cin >> fila >> columna;

    if (EsMovimientoValido(fila, columna)) {
        tablero[fila][columna] = turno;
    } else {
        cout << "Movimiento inválido. Intenta de nuevo." << endl;
        HacerMovimiento();
    }
}

bool TicTacToe::VerificarGanador() {
    // Verificar filas
    for (int i = 0; i < TAM; ++i) {
        if (tablero[i][0] == turno && tablero[i][1] == turno && tablero[i][2] == turno) {
            return true;
        }
    }

    // Verificar columnas
    for (int i = 0; i < TAM; ++i) {
        if (tablero[0][i] == turno && tablero[1][i] == turno && tablero[2][i] == turno) {
            return true;
        }
    }

    // Verificar diagonales
    if (tablero[0][0] == turno && tablero[1][1] == turno && tablero[2][2] == turno) {
        return true;
    }
    if (tablero[0][2] == turno && tablero[1][1] == turno && tablero[2][0] == turno) {
        return true;
    }

    return false;
}

bool TicTacToe::VerificarEmpate() {
    for (int i = 0; i < TAM; ++i) {
        for (int j = 0; j < TAM; ++j) {
            if (tablero[i][j] == VACIO) {
                return false;
            }
        }
    }
    return true;
}

void TicTacToe::CambiarTurno() {
    turno = (turno == JUGADOR1) ? JUGADOR2 : JUGADOR1;
}

bool TicTacToe::EsMovimientoValido(int fila, int columna) {
    return fila >= 0 && fila < TAM && columna >= 0 && columna < TAM && tablero[fila][columna] == VACIO;
}

void TicTacToe::Ejecutar() {
    while (!juegoTerminado) {
        MostrarTablero();
        HacerMovimiento();
        if (VerificarGanador()) {
            MostrarTablero();
            cout << "¡Jugador " << turno << " gana!" << endl;
            juegoTerminado = true;
        } else if (VerificarEmpate()) {
            MostrarTablero();
            cout << "¡Empate!" << endl;
            juegoTerminado = true;
        } else {
            CambiarTurno();
        }
    }
}

int main() {
    TicTacToe juego;
    juego.Ejecutar();
    return 0;
}
