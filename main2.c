#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <curses.h> // PDCurses

void init_curses() {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    timeout(0); // Non-blocking input
}

void end_curses() {
    endwin();
}

int kbhit() {
    int ch = getch();
    if (ch != ERR) {
        ungetch(ch);
        return 1;
    }
    return 0;
}

int retardo(unsigned long int a) {
    unsigned int velocidad = a;
    while (a > 0) {
        if (kbhit()) {
            int key = getch();
            if (key == KEY_DOWN) {
                velocidad += 5000;
                a += 5000;
            }
            if ((velocidad - 5000) >= 50000 && (a - 5000) >= 50000) {
                if (key == KEY_UP) {
                    velocidad -= 5000;
                    a -= 5000;
                }
            } else {
                break;
            }
        }
        a--;
        napms(1); // Retardo
    }
    return velocidad;
}

void mostrar(unsigned char dato) {
    for (unsigned char mascara = 128; mascara > 0; mascara >>= 1) {
        if (dato & mascara) {
            printw("*");
        } else {
            printw("_");
        }
    }
    printw("\n");
}

char* mostrar2(unsigned char dato) {
    char* resultado = malloc(9);
    if (resultado == NULL) {
        return NULL;
    }
    for (unsigned char mascara = 128, i = 0; mascara > 0; mascara >>= 1, i++) {
        if (dato & mascara) {
            resultado[i] = '*';
        } else {
            resultado[i] = '_';
        }
    }
    resultado[8] = '\0';
    return resultado;
}

void auto_fantastico(unsigned long int velocidad) {
    unsigned int dato;
    printw("El AUTO FANTASTICO\n");
    printw("Presione ESC para regresar al menu principal\n");
    printw("Pulse la flecha para arriba para incrementar la velocidad, o para abajo para disminuirla\n\n");
    while (1) {
        dato = 0x80;
        for (int t = 0; t < 8; t++) {
            move(0, 0);
            printw("Demora: %lu", velocidad);
            char* texto = mostrar2(dato);
            move(1, 0);
            printw("%s", texto);
            free(texto);
            velocidad = retardo(velocidad);
            dato >>= 1;
            if (kbhit() && getch() == 27) {
                clear();
                return;
            }
        }
        dato = 0x01;
        for (int i = 0; i < 6; i++) {
            move(0, 0);
            printw("                ");
            printw("Demora: %lu\n", velocidad);
            dato <<= 1;
            char* texto = mostrar2(dato);
            move(1, 0);
            printw("%s", texto);
            free(texto);
            velocidad = retardo(velocidad);
            if (kbhit() && getch() == 27) {
                clear();
                return;
            }
        }
    }
}

void choque(unsigned long int velocidad) {
    printw("Choque\n");
    printw("Presione ESC para regresar al menu principal\n");
    printw("Pulse la flecha para arriba para incrementar la velocidad, o para abajo para disminuirla\n\n");
    uint8_t tabla[] = {0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42};
    while (1) {
        for (int i = 0; i < 7; ++i) {
            move(0, 0);
            printw("                ");
            printw("Demora: %lu\n", velocidad);
            char* texto = mostrar2(tabla[i]);
            move(1, 0);
            printw("%s", texto);
            free(texto);
            velocidad = retardo(velocidad);
            if (kbhit() && getch() == 27) {
                clear();
                return;
            }
        }
    }
}

void carrera(unsigned long int velocidad) {
    printw("La Carrera\n");
    printw("Presione ESC para regresar al menu principal\n");
    printw("Pulse la flecha para arriba para incrementar la velocidad, o para abajo para disminuirla\n\n");
    uint8_t tabla[] = {0x80, 0x80, 0x40, 0x40, 0x20, 0x20, 0x10, 0x10, 0x88, 0x48, 0x24, 0x14, 0x0A, 0x06, 0x03, 0x01};
    while (1) {
        for (int i = 0; i < 16; ++i) {
            move(0, 0);
            printw("                   ");
            printw("Demora: %lu\n", velocidad);
            char* texto = mostrar2(tabla[i]);
            move(1, 0);
            printw("%s", texto);
            free(texto);
            velocidad = retardo(velocidad);
            if (kbhit() && getch() == 27) {
                clear();
                return;
            }
        }
    }
}

void bateriaDescargandose(unsigned long int velocidad) {
    unsigned int dato = 0xFF;
    while (1) {
        for (int i = 0; i < 9; ++i) {
            printw("Presione ESC para regresar al menu principal\n");
            printw("Demora: %lu\n", velocidad);
            mostrar(dato);
            dato <<= 1;
            velocidad = retardo(velocidad);
            clear();
            if (kbhit() && getch() == 27) {
                return;
            }
        }
        dato = 0xFF;
    }
}

void chocaLos5(unsigned long int velocidad) {
    unsigned char tabla[] = {0x00, 0x81, 0xC3, 0xE7, 0xFF, 0xE7, 0xC3, 0x81};
    while (1) {
        for (int i = 0; i < 8; i++) {
            printw("Presione ESC para regresar al menu principal\n");
            printw("Pulse la flecha para arriba para incrementar la velocidad, o para abajo para disminuirla\n");
            printw("Demora: %lu\n", velocidad);
            mostrar(tabla[i]);
            velocidad = retardo(velocidad);
            clear();
            if (kbhit() && getch() == 27) {
                return;
            }
        }
    }
}

int main() {
    char contrasenia[] = {'a', 'b', 'c', '1', '0'};
    char contra[20];
    char pw[20] = {0};
    int v = 0;
    int contador = 0, intentos = 3;

    init_curses();

    while (intentos != 0) {
        printw("Ingrese su contrasena: ");
        refresh();
        for (int i = 0; i < 5; i++) {
            v = getch();
            pw[i] = v;
            printw("*");
            refresh();
        }
        pw[5] = '\0';

        if (strcmp(pw, "abc10") != 0) {
            contador++;
            intentos--;
            clear();
            memset(pw, 0, sizeof(pw));
            printw("Contrasenia incorrecta, le quedan %d intentos\n", intentos);
        } else {
            intentos = 0;
        }
        refresh();
    }

    if (contador < 3) {
        clear();
        printw("Bienvenido al sistema\n");
        refresh();
    } else {
        end_curses();
        exit(0);
    }

    int opcion = 0;
    unsigned long int velocidadAux = 500000;
    unsigned long int velocidad = velocidadAux;

    do {
        if (contador < 3) {
            printw("\n(1) Autos fantastico\n");
            printw("(2) La carrera\n");
            printw("(3) El choque\n");
            printw("(4) Bateria descargandose\n");
            printw("(5) Choca los 5\n");
            printw("(6) Salir\n");

            printw("\nIngrese la opcion que desee visualizar: ");
            refresh();
            scanw("%d", &opcion);
            while (opcion < 1 || opcion > 6) {
                printw("Valor erroneo, ingrese nuevamente: ");
                refresh();
                scanw("%d", &opcion);
            }

            switch (opcion) {
                case 1:
                    clear();
                    auto_fantastico(velocidad);
                    opcion = 0;
                    velocidad = velocidadAux;
                    break;
                case 2:
                    clear();
                    carrera(velocidad);
                    opcion = 0;
                    velocidad = velocidadAux;
                    break;
                case 3:
                    clear();
                    choque(velocidad);
                    opcion = 0;
                    velocidad = velocidadAux;
                    break;
                case 4:
                    clear();
                    bateriaDescargandose(velocidad);
                    opcion = 0;
                    velocidad = velocidadAux;
                    break;
                case 5:
                    clear();
                    chocaLos5(velocidad);
                    opcion = 0;
                    velocidad = velocidadAux;
                    break;
                case 6:
                    clear();
                    printw("Sistema apagado\n");
                    break;
                default:
                    clear();
                    printw("No existe secuencia para ese numero\n");
                    opcion = 0;
            }
            refresh();
        }
    } while (opcion != 6);

    end_curses();
    return 0;
}

