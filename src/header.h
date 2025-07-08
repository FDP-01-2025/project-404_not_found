#ifndef HEADER_H
#define HEADER_H


/**
 * ESTRUCTURA DE PIEZA:
 * - x, y: Posición en el tablero
 * - t: Tipo de pieza (0-3)
 * - r: Rotación actual (0-3)
 * - Constructor para inicializar fácilmente
 */
struct Piece {
    int x, y, t, r; 
    Piece(int _x = 0, int _y = 0, int _t = 0, int _r = 0) : x(_x), y(_y), t(_t), r(_r) {}
};


#endif