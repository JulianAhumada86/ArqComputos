#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <stdint.h>

int retardo(unsigned long int a) {
    unsigned int velocidad=a;
    while (a>0){
        if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
            velocidad += 5000;
            a += 5000;
        }
        if ((velocidad - 5000) >= 50000 && (a - 5000) >= 50000) {
            if (GetAsyncKeyState(VK_UP) & 0x0001) {
                velocidad -= 5000;
                a-= 5000;
            }
        }else{
            break;
        }

        a--;
    }
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
    printf("El AUTO FANTASTICO");
    printf("Presione ESC para regresar al menu principal\n");
    printf("Pulse la flecha para arriba para incrementar la velocidad, o para abajo para disminuirla\n");
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
            if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) {
                system("cls");
                return;
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

            if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) {
                system("cls");
                return;
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

            if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) {
                system("cls");
                return;
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


            if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) {
                system("cls");
                return;
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
            if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) {
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

            if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) {
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

    while (intentos != 0) {
        printf("Ingrese su contrasena: ");
        for (int i = 0; i < 5; i++) {
            v = getch();
            pw[i] = v;
            printf("*");
        }
        pw[5] = '\0';

        if (strcmp(pw, "abc10") != 0) {
            contador++;
            intentos--;
            system("cls");
            memset(pw, 0, sizeof(pw));
            printf("Contrasenia incorrecta, le quedan %d intentos\n", intentos);
        } else {
            intentos = 0;
        }
    }

    if (contador < 3) {
        system("cls");
        printf("Bienvenido al sistema\n");
    } else {
        ExitProcess(0);
    }

    int opcion = 0;
    unsigned long int velocidadAux = 500000;
    unsigned long int velocidad = velocidadAux;

    do {
        if (contador < 3) {
            printf("\n(1) Autos fantastico\n");
            printf("(2) La carrera\n");
            printf("(3) El choque\n");
            printf("(4) Bateria descargandose\n");
            printf("(5) Choca los 5\n");
            printf("(6) Salir\n");

            printf("\nIngrese la opcion que desee visualizar: ");
            scanf("%d", &opcion);
            while (opcion < 1 || opcion > 6) {
                printf("Valor erroneo, ingrese nuevamente: ");
                scanf("%d", &opcion);
            }

            switch (opcion) {
                case 1:
                    system("cls");
                    auto_fantastico(velocidad);
                    opcion = 0;
                    velocidad = velocidadAux;
                    break;
                case 2:
                    system("cls");
                    carrera(velocidad);
                    opcion = 0;
                    velocidad = velocidadAux;
                    break;
                case 3:
                    system("cls");
                    choque(velocidad);
                    opcion = 0;
                    velocidad = velocidadAux;
                    break;
                case 4:
                    system("cls");
                    bateriaDescargandose(velocidad);
                    opcion = 0;
                    velocidad = velocidadAux;
                    break;
                case 5:
                    system("cls");
                    chocaLos5(velocidad);
                    opcion = 0;
                    velocidad = velocidadAux;
                    break;
                case 6:
                    system("cls");
                    printf("Sistema apagado\n");
                    break;
                default:
                    system("cls");
                    printf("No existe secuencia para ese numero\n");
                    opcion = 0;
            }
        }
    } while (opcion != 6);

    return 0;
}
