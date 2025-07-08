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