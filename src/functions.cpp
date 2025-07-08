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

            }
        }
    }
}