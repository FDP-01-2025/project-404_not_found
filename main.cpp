#include "./src/functions.cpp"
/**
 * FUNCIÓN main - Bucle principal del juego
 * FUNCIONAMIENTO:
 * 1. Inicializa semilla aleatoria y pieza inicial
 * 2. Bucle principal:
 *    a. Maneja entrada del teclado
 *    b. Mueve la pieza hacia abajo automáticamente
 *    c. Cuando la pieza se fija:
 *       - Verifica y limpia líneas completas
 *       - Verifica game over
 *       - Crea nueva pieza
 *    d. Dibuja el estado actual
 */
 int main() {
    // Configurar consola para caracteres especiales
    SetConsoleOutputCP(65001);
    
    // Inicializar generador aleatorio
    srand(static_cast<unsigned>(time(nullptr)));
    
    // Crear primera pieza (centrada cerca del tope)
    Piece p(W/2-2, -2, rand()%4, 0);
    int speed = 20;    // Velocidad de caída (ciclos por movimiento)
    int counter = 0;   // Contador para movimiento automático

    // Bucle principal del juego
    while (true) {
        // Manejar entrada del teclado
        if (_kbhit()) {
            Piece tmp = p; // Copia temporal para probar movimiento
            
            switch (tolower(_getch())) {
                case 'a': tmp.x--; break; // Mover izquierda
                case 'd': tmp.x++; break; // Mover derecha
                case 's': tmp.y++; break; // Mover abajo
                case 'w': tmp.r = (tmp.r + 1) % 4; break; // Rotar
                case 'q': return 0; // Salir
            }
            
            // Aplicar movimiento si no hay colisión
            if (!checkCollision(tmp)) p = tmp;
        }

        // Movimiento automático hacia abajo
        if (++counter > speed) {
            p.y++; // Mover pieza hacia abajo
            
            // Verificar colisión después de mover
            if (checkCollision(p)) {
                p.y--; // Revertir movimiento si hay colisión
                
                // Fijar la pieza al tablero
                for (int y = 0; y < 4; y++) {
                    for (int x = 0; x < 4; x++) {
                        if (shapes[p.t][p.r][y][x] && p.y + y >= 0) {
                            board[p.y + y][p.x + x] = p.t + 1;
                        }
                    }
                }
                
                // Verificar y eliminar líneas completas
                clearLines(p); // 'p' se pasa por referencia no constante
                
                // Verificar condición de game over
                if (checkGameOver()) {
                    draw(p);
                    cout << "\nGAME OVER! Bloques alcanzaron la linea limite!\n";
                    system("pause");
                    return 0;
                }
                
                

    return 0;
}