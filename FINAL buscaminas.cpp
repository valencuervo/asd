#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int ANCHO = 5;   // Ancho del tablero
const int ALTO = 5;    // Alto del tablero
const int MINAS = 5;   // Número de minas

enum Estado { OCULTO, REVELADO, MARCADO };

struct Celda {
    int cantidadMinas;
    Estado estado;
    bool tieneMina;
};

class Buscaminas {
public:
    Buscaminas();
    void Ejecutar();

private:
    vector<vector<Celda>> tablero;
    vector<vector<Celda>> tableroMostrado;
    bool juegoTerminado;

    void InicializarTablero();
    void MostrarTablero();
    void RealizarAccion();
    void RevelarCelda(int x, int y);
    void MarcarCelda(int x, int y);
    void RevelarCeldasAdyacentes(int x, int y);
    bool VerificarVictoria();
    void ColocarMinas();
    void CalcularMinasAdyacentes();
};

Buscaminas::Buscaminas() : juegoTerminado(false) {
    InicializarTablero();
}

void Buscaminas::InicializarTablero() {
    tablero.resize(ALTO, vector<Celda>(ANCHO));
    tableroMostrado.resize(ALTO, vector<Celda>(ANCHO));

    ColocarMinas();
    CalcularMinasAdyacentes();
}

void Buscaminas::ColocarMinas() {
    srand(time(0));
    int minasColocadas = 0;
    while (minasColocadas < MINAS) {
        int x = rand() % ALTO;
        int y = rand() % ANCHO;
        if (!tablero[x][y].tieneMina) {
            tablero[x][y].tieneMina = true;
            ++minasColocadas;
        }
    }
}

void Buscaminas::CalcularMinasAdyacentes() {
    for (int x = 0; x < ALTO; ++x) {
        for (int y = 0; y < ANCHO; ++y) {
            if (tablero[x][y].tieneMina) continue;
            int cantidad = 0;
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx >= 0 && nx < ALTO && ny >= 0 && ny < ANCHO && tablero[nx][ny].tieneMina) {
                        ++cantidad;
                    }
                }
            }
            tablero[x][y].cantidadMinas = cantidad;
        }
    }
}

void Buscaminas::MostrarTablero() {
    system("cls");  // Limpia la pantalla (específico de Windows)
    for (int x = 0; x < ALTO; ++x) {
        for (int y = 0; y < ANCHO; ++y) {
            if (tableroMostrado[x][y].estado == OCULTO) {
                cout << "# ";
            } else if (tableroMostrado[x][y].estado == MARCADO) {
                cout << "F ";
            } else {
                if (tablero[x][y].tieneMina) {
                    cout << "* ";
                } else {
                    cout << tablero[x][y].cantidadMinas << ' ';
                }
            }
        }
        cout << endl;
    }
}

void Buscaminas::RealizarAccion() {
    char accion;
    int x, y;
    cout << "Ingresa acción (r para revelar, m para marcar) y coordenadas (fila columna): ";
    cin >> accion >> x >> y;

    if (x < 0 || x >= ALTO || y < 0 || y >= ANCHO) {
        cout << "Coordenadas inválidas. Intenta de nuevo." << endl;
        return;
    }

    if (accion == 'r') {
        RevelarCelda(x, y);
    } else if (accion == 'm') {
        MarcarCelda(x, y);
    }
}

void Buscaminas::RevelarCelda(int x, int y) {
    if (tableroMostrado[x][y].estado != OCULTO) return;

    tableroMostrado[x][y].estado = REVELADO;

    if (tablero[x][y].tieneMina) {
        juegoTerminado = true;
        return;
    }

    if (tablero[x][y].cantidadMinas == 0) {
        RevelarCeldasAdyacentes(x, y);
    }

    if (VerificarVictoria()) {
        juegoTerminado = true;
    }
}

void Buscaminas::MarcarCelda(int x, int y) {
    if (tableroMostrado[x][y].estado == OCULTO) {
        tableroMostrado[x][y].estado = MARCADO;
    } else if (tableroMostrado[x][y].estado == MARCADO) {
        tableroMostrado[x][y].estado = OCULTO;
    }
}

void Buscaminas::RevelarCeldasAdyacentes(int x, int y) {
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < ALTO && ny >= 0 && ny < ANCHO) {
                RevelarCelda(nx, ny);
            }
        }
    }
}

bool Buscaminas::VerificarVictoria() {
    for (int x = 0; x < ALTO; ++x) {
        for (int y = 0; y < ANCHO; ++y) {
            if (!tablero[x][y].tieneMina && tableroMostrado[x][y].estado == OCULTO) {
                return false;
            }
        }
    }
    return true;
}

void Buscaminas::Ejecutar() {
    while (!juegoTerminado) {
        MostrarTablero();
        RealizarAccion();
    }

    MostrarTablero();
    if (juegoTerminado && VerificarVictoria()) {
        cout << "¡Felicidades! Has ganado." << endl;
    } else if (juegoTerminado) {
        cout << "¡Juego terminado! Has pisado una mina." << endl;
    }
}

int main() {
    Buscaminas juego;
    juego.Ejecutar();
    return 0;
}



