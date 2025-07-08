#include "header.h" // Asegúrate de que la ruta sea correcta si el compilador no la encuentra

#include <iostream>
#include <conio.h>    // Para _kbhit() y _getch() (entrada de teclado)
#include <windows.h>  // Para Sleep() y funciones de consola
#include <ctime>      // Para time() y srand()

using namespace std;

// CONSTANTES DEL JUEGO
const int W = 8;      // Ancho del tablero (8 bloques)
const int H = 12;     // Alto del tablero (12 bloques)
const int GAMEOVER_LINE = H - 10; // Línea de game over (a 10 bloques del fondo)

// Matriz que representa el tablero (0 = vacío, >0 = bloque fijo)
int board[H][W] = {0};

// CARACTERES VISUALES
const char BLOCK_MOVING = 219;    // Carácter ASCII para bloque en movimiento (█)
const char BLOCK_FIXED = 176;     // Carácter ASCII para bloque fijo (░)
const char EMPTY_SPACE = ' ';     // Espacio vacío
const char GAMEOVER_MARKER = '.'; // Marcador visual para línea de game over

/**
 * FORMAS DE LAS PIEZAS:
 * - 4 piezas diferentes (I, O, T, L)
 * - Cada pieza tiene 4 rotaciones posibles
 * - Cada rotación es una matriz 4x4 donde 1 = bloque y 0 = espacio vacío
 */

int shapes[4][4][4][4] = {
    // Pieza I (forma de palo)
    {
        {{0,0,0,0}, {1,1,1,1}, {0,0,0,0}, {0,0,0,0}}, // Horizontal
        {{0,0,1,0}, {0,0,1,0}, {0,0,1,0}, {0,0,1,0}}, // Vertical
        {{0,0,0,0}, {0,0,0,0}, {1,1,1,1}, {0,0,0,0}}, // Horizontal (alternativa)
        {{0,1,0,0}, {0,1,0,0}, {0,1,0,0}, {0,1,0,0}}  // Vertical (alternativa)
    },
    // Pieza O (cuadrado)
    {
        {{0,0,0,0}, {0,1,1,0}, {0,1,1,0}, {0,0,0,0}}, // Todas las rotaciones iguales
        {{0,0,0,0}, {0,1,1,0}, {0,1,1,0}, {0,0,0,0}},
        {{0,0,0,0}, {0,1,1,0}, {0,1,1,0}, {0,0,0,0}},
        {{0,0,0,0}, {0,1,1,0}, {0,1,1,0}, {0,0,0,0}}
    },
    // Pieza T
    {
        {{0,0,0,0}, {0,1,0,0}, {1,1,1,0}, {0,0,0,0}}, // T normal
        {{0,0,0,0}, {0,1,0,0}, {0,1,1,0}, {0,1,0,0}}, // Rotada 90°
        {{0,0,0,0}, {0,0,0,0}, {1,1,1,0}, {0,1,0,0}}, // Rotada 180°
        {{0,0,0,0}, {0,1,0,0}, {1,1,0,0}, {0,1,0,0}}  // Rotada 270°
    },
    // Pieza L
    {
        {{0,0,0,0}, {1,0,0,0}, {1,1,1,0}, {0,0,0,0}}, // L normal
        {{0,0,0,0}, {0,1,1,0}, {0,1,0,0}, {0,1,0,0}}, // Rotada 90°
        {{0,0,0,0}, {0,0,0,0}, {1,1,1,0}, {0,0,1,0}}, // Rotada 180°
        {{0,0,0,0}, {0,1,0,0}, {0,1,0,0}, {1,1,0,0}}  // Rotada 270°
    }
};

/**
 * FUNCIÓN: checkCollision
 * OBJETIVO: Verificar si la pieza colisiona con bordes u otros bloques
 * PARÁMETROS:
 * - piece: La pieza a verificar
 * RETORNO:
 * - true si hay colisión, false si no
 * FUNCIONAMIENTO:
 * 1. Recorre la matriz 4x4 de la pieza
 * 2. Para cada bloque de la pieza:
 *    a. Calcula su posición en el tablero
 *    b. Verifica si está fuera de los límites
 *    c. Verifica si choca con un bloque ya existente
 */
bool checkCollision(const Piece& piece) {
        for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (shapes[piece.t][piece.r][y][x]) {
                int boardX = piece.x + x;
                int boardY = piece.y + y;

                // Verificar límites del tablero
                if (boardX < 0 || boardX >= W || boardY >= H) 
                    return true;
                    
                // Verificar colisión con bloques existentes (solo si está dentro del tablero)
                if (boardY >= 0 && board[boardY][boardX])
                    return true;
            }
        }
    }
    return false;
}

/**
 * FUNCIÓN: checkGameOver
 * OBJETIVO: Verificar si el juego debe terminar
 * RETORNO:
 * - true si hay bloques en la línea de game over
 * FUNCIONAMIENTO:
 * 1. Recorre la línea de game over (GAMEOVER_LINE)
 * 2. Si encuentra cualquier bloque fijo, retorna true
 */
bool checkGameOver() {
    for (int x = 0; x < W; x++) {
        if (board[GAMEOVER_LINE][x] != 0) {
            return true;
        }
    }
    return false;
}

void draw(const Piece& p) { // 'p' es const aquí, lo cual es correcto para dibujar
    system("cls"); // Limpiar pantalla
    
    // Dibujar borde superior
    cout << "+";
    for (int x = 0; x < W; x++) cout << "-";
    cout << "+\n";
// Dibujar cada fila del tablero
    for (int y = 0; y < H; y++) {
        cout << "|"; // Borde izquierdo
        
        for (int x = 0; x < W; x++) {
            bool isPiece = false;
            
            // Verificar si esta posición es parte de la pieza actual
            for (int py = 0; py < 4 && !isPiece; py++) {
                for (int px = 0; px < 4; px++) {
                    if (p.y + py == y && p.x + px == x && shapes[p.t][p.r][py][px]) {
                        isPiece = true;
                        break;
                    }
                }
            }
            // Dibujar el contenido de la celda
            if (board[y][x]) {
                // Bloque fijo (o marcador en línea de game over)
                cout << (y == GAMEOVER_LINE ? GAMEOVER_MARKER : BLOCK_FIXED);
            } else {
                // Espacio vacío o bloque móvil (con marcador en línea de game over)
                cout << (y == GAMEOVER_LINE ? GAMEOVER_MARKER : 
                       (isPiece ? BLOCK_MOVING : EMPTY_SPACE));
            }
        }
        cout << "|\n"; // Borde derecho
    }
    
    // Dibujar borde inferior
    cout << "+";
    for (int x = 0; x < W; x++) cout << "-";
    cout << "+\n";
}
