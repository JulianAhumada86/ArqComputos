#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ncurses.h>

int retardo(unsigned long int a) {
    unsigned int velocidad = a;

    return velocidad;
}

void mostrar(unsigned char dato) {
    for (unsigned char mascara = 128; mascara > 0; mascara >>= 1) {
        if (dato & mascara) {
            printf("*");
        } else {
            printf("_");
        }
    }
    printf("\n");
}

char* mostrar2(unsigned char dato) {
    char* resultado = malloc(9);  // Reservar espacio para 8 caracteres y el carácter nulo
    if (resultado == NULL) {
        return NULL;  // Manejo simple de errores de asignación de memoria
    }

    for (unsigned char mascara = 128, i = 0; mascara > 0; mascara >>= 1, i++) {
        if (dato & mascara) {
            resultado[i] = '*';
        } else {
            resultado[i] = '_';
        }
    }
    resultado[8] = '\0';  // Terminar la cadena con el carácter nulo

    return resultado;
}

void auto_fantastico(unsigned long int velocidad) {
    unsigned int dato;
    printf("El AUTO FANTASTICO\n");
    printf("Presione ESC para regresar al menu principal\n");
    printf("\n");
    while (1) {
        dato = 0x80;
        for (int t = 0; t < 8; t++) {
            printf("\033[A");
            printf("\rDemora: %lu", velocidad);
            char* texto = mostrar2(dato);  // Aca tendria que llamar a asembly
            printf("\033[B");
            printf("\r%s",texto);
            velocidad = retardo(velocidad);
            dato = dato >> 1;
            // No se pueden leer las teclas, asumimos que no están presionadas
            if (0) {
                // Reemplace 0 con la función de verificación de tecla apropiada
                // Si la tecla ESC es presionada, salimos del bucle
                break;
            }
        }
        dato = 0x01;
        for (int i = 0; i < 6; i++) {
            printf("\033[A");
            printf("\r                ");
            printf("\rDemora: %lu\n", velocidad);
            dato = dato << 1;

            char* texto = mostrar2(dato);

            printf("\r%s",texto);
            velocidad = retardo(velocidad);
            // No se pueden leer las teclas, asumimos que no están presionadas
            if (0) {
                // Reemplace 0 con la función de verificación de tecla apropiada
                // Si la tecla ESC es presionada, salimos del bucle
                break;
            }
        }
    }
}

void choque(unsigned long int velocidad) {
    printf("Choque\n");
    printf("Presione ESC para regresar al menu principal\n");
    printf("Pulse la flecha para arriba para incrementar la velocidad, o para abajo para disminuirla\n");
    printf("\n");
    uint8_t tabla[] = {
        0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42
    };

    while (1) {
        for (int i = 0; i < 7; ++i) {
            printf("\033[A");
            printf("\r                ");
            printf("\rDemora: %lu\n", velocidad);

            char* texto = mostrar2(tabla[i]);
            printf("\r%s",texto);
            velocidad = retardo(velocidad);


            if (0) {
                // Reemplace 0 con la función de verificación de tecla apropiada
                // Si la tecla ESC es presionada, salimos del bucle
                break;
            }
        }
    }
}


void carrera(unsigned long int velocidad) {
    printf("La Carrera\n");
    printf("Presione ESC para regresar al menu principal\n");
    printf("Pulse la flecha para arriba para incrementar la velocidad, o para abajo para disminuirla\n");
    printf("\n");

    uint8_t tabla[] = {
        0x80, 0x80, 0x40, 0x40, 0x20, 0x20, 0x10, 0x10, 0x88, 0x48, 0x24, 0x14, 0x0A, 0x06, 0x03, 0x01
    };

    while (1) {
        for (int i = 0; i < 16; ++i) {
            printf("\033[A");
            printf("\r                   ");
            printf("\rDemora: %lu\n", velocidad);


            char* texto = mostrar2(tabla[i]);

            printf("\r%s",texto);
            velocidad  = retardo(velocidad);

            if (0) {
                // Reemplace 0 con la función de verificación de tecla apropiada
                // Si la tecla ESC es presionada, salimos del bucle
                break;
            }
        }
    }
}

void bateriaDescargandose(unsigned long int velocidad) {
    unsigned int dato = 0xFF;
    while (1) {
        for (int i = 0; i < 9; ++i) {
            printf("Presione ESC para regresar al menu principal\n");
            printf("Demora: %lu\n", velocidad);
            mostrar(dato);
            dato <<= 1;
            velocidad = retardo(velocidad);
            system("cls");
            if (0) {
                // Reemplace 0 con la función de verificación de tecla apropiada
                // Si la tecla ESC es presionada, salimos del bucle
                return;
            }
        }
        dato = 0xFF;
    }
}

void chocaLos5(unsigned long int velocidad) {
    unsigned char tabla[] = {
        0x00, 0x81, 0xC3, 0xE7, 0xFF, 0xE7, 0xC3, 0x81
    };

    while (1) {
        for (int i = 0; i < 8; i++) {
            printf("Presione ESC para regresar al menu principal\n");
            printf("Pulse la flecha para arriba para incrementar la velocidad, o para abajo para disminuirla\n");
            printf("Demora: %lu\n", velocidad);
            mostrar(tabla[i]);
            velocidad = retardo(velocidad);
            system("cls");

            if (0) {
                // Reemplace 0 con la función de ver
