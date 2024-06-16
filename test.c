#include <ncurses.h>
#include <stdio.h>

// Declaración de la función retardo
int retardo(int velocidad, int *ch);

void auto_fantastico(int velocidad) {
    initscr();            // Inicia ncurses
    noecho();             // No muestra los caracteres en pantalla
    cbreak();             // Desactiva el modo de buffer de línea
    keypad(stdscr, TRUE); // Permite la captura de teclas especiales
    nodelay(stdscr, TRUE); // No espera a que se presione una tecla

    int row = 0;
    int ch = 0;
    clear(); // Limpiar la pantalla para que no se acumulen las impresiones

    mvprintw(row++, 0, "El auto fantastico");
    mvprintw(row++, 0, "Presione ESC para regresar al menu principal");
    mvprintw(row++, 0, "Pulse la flecha hacia arriba para incrementar la velocidad, o hacia abajo para disminuirla");
    row++; // Deja una línea en blanco
    int t=0;
    while (1) {
        // Dibujar algo en la pantalla (ejemplo simple)
        mvprintw(row, 0, "Dibujando...%d",t); // Ejemplo de dibujo, reemplázalo con el verdadero dibujo
        refresh(); // Refresca la pantalla para mostrar cambios

        // Controlar la velocidad de actualización
        velocidad = retardo(velocidad, &ch);

        if (ch == 27) { // 27 es el código ASCII para ESC
            break; // Sale del bucle si se presiona ESC
        }

        // Limpia la línea antes de imprimir la nueva velocidad
        move(row + 1, 0);
        clrtoeol();
        mvprintw(row + 1, 0, "Velocidad= %d", velocidad);

        refresh(); // Refresca la pantalla para mostrar cambios
        t++;
        if(t>100){
          t=0;
        }
    }
    endwin(); // Finaliza ncurses
}

int retardo(int velocidad, int *ch) {
    unsigned long int a = velocidad;

    while (a > 0) {
        *ch = getch(); // Captura la entrada del teclado
        if (*ch == KEY_DOWN) {
            velocidad += 500000;
            a += 500000;
        } else if (*ch == KEY_UP) {
            if (velocidad - 500000 >= 500000) {
                velocidad -= 500000;
                a -= 500000;
            }
        } else if (*ch == 27) {
            break; // Sale del bucle si se presiona ESC
        }
        a--;
    }

    return velocidad;
}

int main() {
    int contrasenia;
    scanf("%d",&contrasenia );
    printf("\n%d\n",contrasenia );
    //auto_fantastico(5000000);
    return 0;
}
