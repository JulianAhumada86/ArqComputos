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
        } else if ((velocidad - 500000) >= 500000) {
            if  (*ch == KEY_UP){
                velocidad -= 500000;
                a -= 500000;
            }
        }else{
          break;
        }

        if (*ch == 27) {
            break; // Sale del bucle si se presiona ESC
        }
        a--;
    }

    return velocidad;
}

void mostrarTesteo(unsigned char dato) {
    for (unsigned char mascara = 128; mascara > 0; mascara >>= 1) {
        if (dato & mascara) {
            printf("*");
        } else {
            printf("_");
        }
    }
    printf("\n");
}

char* mostrar(unsigned char dato) {
    char* resultado = malloc(9);  // Reservar espacio para 8 caracteres y el caracter nulo
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

void auto_fantastico(int velocidad) {
    initscr();            // Inicia ncurses
    noecho();             // No muestra los caracteres en pantalla
    cbreak();             // Desactiva el modo de buffer de línea
    keypad(stdscr, TRUE); // Permite la captura de teclas especiales
    nodelay(stdscr, TRUE); // No espera a que se presione una tecla

    unsigned int dato;
    int row = 0;
    int ch;
    char* texto;
    clear(); // Limpiar la pantalla para que no se acumulen las impresiones

    mvprintw(row++, 0, "El auto fantastico");
    mvprintw(row++, 0, "Presione ESC para regresar al menu principal");
    mvprintw(row++, 0, "Pulse la flecha hacia arriba para incrementar la velocidad, o hacia abajo para disminuirla");
    row++; // Deja una línea en blanco
    int t=0;
    while (1) {
        dato =0x80;
        for(int i=0;i<8;i++){

          mvprintw(row, 0, "Velocidad=                ");
          mvprintw(row, 0, "Velocidad= %d", velocidad);

          texto = mostrar(dato);
          mvprintw(row + 1, 0, "%s ",texto); // Ejemplo de dibujo, reemplázalo con el verdadero dibujo
          refresh();

          velocidad = retardo(velocidad, &ch); //Retardo y lectura de teclas
          dato = dato >> 1;

          if (ch == 27) {
              break;
          }
          move(row + 1, 0);
          clrtoeol();
          refresh();
      }

      if (ch == 27) {
        break;
      }

      dato=0x01;
      for(int j=0;j<6;j++){

        mvprintw(row, 0, "Velocidad=                ");
        mvprintw(row, 0, "Velocidad= %d", velocidad);

        dato = dato << 1;

        texto = mostrar(dato);
        mvprintw(row + 1, 0, "%s ",texto); // Ejemplo de dibujo, reemplázalo con el verdadero dibujo
        refresh();

        velocidad = retardo(velocidad, &ch); //Retardo y lectura de teclas

        if (ch == 27) {
            break;
        }
        move(row + 1, 0);
        clrtoeol();
        refresh();
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
  char* texto;
  uint8_t tabla[] = {
      0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42
  };
  int t=0;


  clear(); // Limpiar la pantalla para que no se acumulen las impresiones

  mvprintw(row++, 0, "El Choque");
  mvprintw(row++, 0, "Presione ESC para regresar al menu principal");
  mvprintw(row++, 0, "Pulse la flecha hacia arriba para incrementar la velocidad, o hacia abajo para disminuirla");
  row++; // Deja una línea en blanco

  while (1) {
      // Dibujar algo en la pantalla (ejemplo simple)
      for (int i = 0; i < 7; ++i){
        mvprintw(row, 0, "Velocidad= %d", velocidad);

        texto = mostrar(tabla[i]);
        mvprintw(row + 1, 0, "%s ",texto);

        velocidad = retardo(velocidad, &ch); //Retardo y lectura de teclas

        if (ch == 27) {
            break; // Sale del bucle si se presiona ESC
        }

        move(row + 1, 0);
        clrtoeol();
        refresh(); // Refresca la pantalla para mostrar cambios
      }

      if (ch == 27) {
          break; // Sale del bucle si se presiona ESC
      }



  }
  endwin(); // Finaliza ncurses

}

void cerrar_terminal() {
    // Obtener el PID del proceso de la terminal
    pid_t terminal_pid = getppid();

    // Enviar la señal SIGHUP al proceso de la terminal
    kill(terminal_pid, SIGHUP);
}

int main() {
    char contra[20];
    char contrasenia[20] = "abc10";
    int intentos = 3;

    while (intentos > 0) {
        printf("Ingrese la contrasenia: ");
        scanf("%19s", contra); // Limitar el tamaño para evitar desbordamiento

        if (strcmp(contra, contrasenia) == 0) {
            printf("Contraseña correcta. Acceso concedido.\n");
            break;
        } else {
            intentos--;
            printf("Contraseña incorrecta. Te quedan %d intentos.\n", intentos);
        }

        if (intentos == 0) {
            printf("Se han agotado los intentos. Acceso denegado.\n");
            //cerrar_terminal
        }
    }

    int opcion;
    unsigned long int velocidadAux = 5000000;
    unsigned long int velocidad = velocidadAux;

    do {
        if (intentos > 0) {
            printf("\n(1) Autos fantastico\n");
            printf("(2) El choque\n");
            printf("(3) La carrera\n");
            printf("(4) Meter funcion\n");
            printf("(5) Meter funcion\n");
            printf("(6) Salir\n");

            printf("\nIngrese la opcion que desee visualizar: ");
            scanf("%d",&opcion );

            while (opcion < 1 || opcion > 6) {
                printf("Valor erroneo, ingrese nuevamente: ");

            }


            switch (opcion) {
                case 1:
                    auto_fantastico(velocidad);
                    opcion = 0;
                    velocidad = velocidadAux;
                    break;
                case 2:
                    choque(velocidad);
                    opcion = 0;
                    velocidad = velocidadAux;
                    break;
                case 3:
                    opcion = 0;
                    velocidad = velocidadAux;
                    break;
                case 4:
                    //bateriaDescargandose(velocidad);
                    opcion = 0;
                    velocidad = velocidadAux;
                    break;
                case 5:
                    //chocaLos5(velocidad);
                    opcion = 0;
                    velocidad = velocidadAux;
                    break;
                case 6:
                    printf("Sistema apagado\n");
                    break;


                default:
                    printf("No existe secuencia para ese numero\n");
                    opcion = 0;
            }
        }
    } while (opcion != 6);

    return 0;
}
