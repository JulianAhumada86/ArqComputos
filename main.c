#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ncurses.h>
#include <unistd.h>
#include <signal.h>
int retardo(int velocidad, int *ch) {
    unsigned long int a = velocidad;

    while (a > 0) {
        *ch = getch(); // Captura la entrada del teclado
        if (*ch == KEY_DOWN) {
            velocidad += 500000;
            a += 500000;
        } else if (*ch == KEY_UP) {
            if ((velocidad - 500000) >= 500000) {
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

/*
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
*/

/*
char* mostrar2(unsigned char dato) {
    char* resultado = malloc(9);  // Reservar espacio para 8 caracteres y el car�cter nulo
    if (resultado == NULL) {
        return NULL;  // Manejo simple de errores de asignaci�n de memoria
    }

    for (unsigned char mascara = 128, i = 0; mascara > 0; mascara >>= 1, i++) {
        if (dato & mascara) {
            resultado[i] = '*';
        } else {
            resultado[i] = '_';
        }
    }
    resultado[8] = '\0';  // Terminar la cadena con el car�cter nulo

    return resultado;
}
*/

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
        mvprintw(row, 0, "Velocidad= %d", velocidad);
        mvprintw(row + 1, 0, "Dibujando...%d",t); // Ejemplo de dibujo, reemplázalo con el verdadero dibujo



        velocidad = retardo(velocidad, &ch); //Retardo y lectura de teclas

        if (ch == 27) {
            break; // Sale del bucle si se presiona ESC
        }

        // Limpia la línea antes de imprimir la nueva velocidad
        move(row + 1, 0);
        clrtoeol();


        refresh(); // Refresca la pantalla para mostrar cambios
        t++;
        if(t>100){
          t=0;
        }
    }
    endwin(); // Finaliza ncurses
}

void choque(unsigned long int velocidad) {

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
      mvprintw(row, 0, "Velocidad= %d", velocidad);
      mvprintw(row + 1, 0, "Dibujando...%d",t); // Ejemplo de dibujo, reemplázalo con el verdadero dibujo



      velocidad = retardo(velocidad, &ch); //Retardo y lectura de teclas

      if (ch == 27) {
          break; // Sale del bucle si se presiona ESC
      }

      // Limpia la línea antes de imprimir la nueva velocidad
      move(row + 1, 0);
      clrtoeol();


      refresh(); // Refresca la pantalla para mostrar cambios
      t++;
      if(t>100){
        t=0;
      }
  }
  endwin(); // Finaliza ncurses
  /*
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
    */
}



void cerrar_terminal() {
    // Obtener el PID del proceso de la terminal
    pid_t terminal_pid = getppid();

    // Enviar la señal SIGHUP al proceso de la terminal
    kill(terminal_pid, SIGHUP);
}

int main() {

    char contra[20];
    char pw[20] = {0};
    int v = 0;
    int contador = 0, intentos = 3;
    int contrasenia;

    while (intentos != 0) {
        printf("Ingrese la contrasenia");
        scanf("%s",&contra );
        intentos--;
    }

    if (contador < 3) {

        printf("Bienvenido al sistema\n");
    } else {
          //cerrar_terminal();

    }

    int opcion;
    unsigned long int velocidadAux = 5000000;
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
            scanf("%d",&opcion );

            while (opcion < 1 || opcion > 6) {
                printf("Valor erroneo, ingrese nuevamente: ");

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
                    //carrera(velocidad);
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
                    //bateriaDescargandose(velocidad);
                    opcion = 0;
                    velocidad = velocidadAux;
                    break;
                case 5:
                    system("cls");
                    //chocaLos5(velocidad);
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
