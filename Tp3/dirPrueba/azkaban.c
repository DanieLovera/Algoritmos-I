#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "prision.h"

#define COMANDO_PERDONAR "perdonables"
#define COMANDO_LIBERAR "liberar"
#define COMANDO_ACTUALIZAR "actualizar"
#define COMANDO_MOSTRAR_LIBERADOS "mostrar_liberados"
#define COMANDO_AYUDA "ayuda"
#define ARGC_PERDONAR 3
#define ARGC_LIBERAR 5
#define ARGC_ACTUALIZAR 3
#define ARGC_MOSTRAR_LIBERADOS 3
#define ARGC_AYUDA 2
#define ARGC_MAXIMOS 5

#define NOMBRE_PARCIAL_FLIBERADOS "liberados_"
#define NOMBRE_FCRUCIO_BIN "crucio.dat"
#define NOMBRE_FIMPERIUS_BIN "imperius.dat"

/*
  - PRECONDICIONES: Recibe un caracter con la conducta del preso.
  - POSTCONDICIONES: Devuelve true si la conducta esta en los parametros validos
  y false si no es valida.
 */
bool validar_conducta (char conducta){
  if (!(conducta == CONDUCTA_BUENA
    || conducta == CONDUCTA_REGULAR || conducta == CONDUCTA_MALA)){
      return false;
  }
  return true;
}

/*
  - PRECONDICIONES: Recibe un string con el comando ejecutado y un entero con la
  cantidad de argumentos del comando.
  - POSTCONDICIONES: Muestra en pantalla el rror ocurrido por falta o excesos de
  parametros en el comando.
 */
void mensaje_error_argc(char comando[], int cantidad_argumentos){
  printf("[ADVERTENCIA] El comando \"%s\" requiere %i argumentos.\n",comando,cantidad_argumentos);
}

int main(int argc, char* argv[]){
  char nombre_fpresos_perdonables[MAX_NOMBRE];
  char nombre_fpresos_liberados[MAX_NOMBRE];
  char comando[MAX_NOMBRE];
  char fecha[MAX_FECHA];
  char conducta;
  int cantidad_argumentos;
  int valor_control;

  cantidad_argumentos = argc;
  if (cantidad_argumentos == 1){
    mostrar_ayuda();
    printf("[ADVERTENCIA] No ingresaste ningun comando, el programa no puede funcionar sin alguna instruccion.\n");

  }else if(cantidad_argumentos <= ARGC_MAXIMOS){
    strcpy(comando,argv[1]);

    if(strcmp(comando,COMANDO_PERDONAR) == 0){
      if(cantidad_argumentos == ARGC_PERDONAR){
        strcpy(nombre_fpresos_perdonables,argv[2]);
        valor_control = generar_fpresos_perdonables(NOMBRE_FCRUCIO_BIN,NOMBRE_FIMPERIUS_BIN,nombre_fpresos_perdonables);
        if (valor_control == 1){
          printf("Archivo %s creado exitosamente.\n", nombre_fpresos_perdonables);
        }else{
          printf("Fallo la creacion del archivo %s\n",nombre_fpresos_perdonables);
        }
      }else{
        mostrar_ayuda();
        mensaje_error_argc(comando, ARGC_PERDONAR);
      }

    }else if(strcmp(comando,COMANDO_LIBERAR) == 0){
      if(cantidad_argumentos == ARGC_LIBERAR){
        strcpy(nombre_fpresos_perdonables,argv[2]);
        strcpy(fecha, argv[3]);
        strcpy(nombre_fpresos_liberados,NOMBRE_PARCIAL_FLIBERADOS);
        strcat(nombre_fpresos_liberados,fecha);
        strcat(nombre_fpresos_liberados,".txt");
        conducta = *(argv[4]);

        if(!validar_conducta(conducta)){
          mostrar_ayuda();
          printf("[ADVERTENCIA] Conducta ingresada inválida.\n");
          return 0;
        }
        valor_control = generar_fpresos_liberados(nombre_fpresos_liberados, nombre_fpresos_perdonables, fecha, conducta);
        if (valor_control == 1){
          printf("Archivo %s creado exitosamente.\n", nombre_fpresos_liberados);
        }else{
          printf("Fallo la creacion del archivo %s\n",nombre_fpresos_liberados);
        }
      }else{
        mostrar_ayuda();
        mensaje_error_argc(comando, ARGC_LIBERAR);

      }

    }else if(strcmp(comando,COMANDO_ACTUALIZAR) == 0){
      if(cantidad_argumentos == ARGC_ACTUALIZAR){
        strcpy(fecha, argv[2]);
        strcpy(nombre_fpresos_liberados,NOMBRE_PARCIAL_FLIBERADOS);
        strcat(nombre_fpresos_liberados,fecha);
        strcat(nombre_fpresos_liberados,".txt");

        valor_control = actualizar_archivos(NOMBRE_FCRUCIO_BIN,NOMBRE_FIMPERIUS_BIN,nombre_fpresos_liberados);
        if (valor_control == 1){
          printf("Se actualizaron correctamente los archivos %s y %s\n", NOMBRE_FCRUCIO_BIN,NOMBRE_FIMPERIUS_BIN);
        }else{
          printf("Fallo la actualizacion de los archivos %s y %s\n",NOMBRE_FCRUCIO_BIN,NOMBRE_FIMPERIUS_BIN);
        }
      }else{
        mostrar_ayuda();
        mensaje_error_argc(comando, ARGC_ACTUALIZAR);
      }

    }else if(strcmp(comando,COMANDO_MOSTRAR_LIBERADOS) == 0){
      if(cantidad_argumentos == ARGC_MOSTRAR_LIBERADOS){
        strcpy(fecha, argv[2]);
        strcpy(nombre_fpresos_liberados,NOMBRE_PARCIAL_FLIBERADOS);
        strcat(nombre_fpresos_liberados,fecha);
        strcat(nombre_fpresos_liberados,".txt");

        valor_control = mostrar_liberados(nombre_fpresos_liberados);
        if(valor_control == -1){
          printf("[Error] no se pueden mostrar los presos liberados.\n");
        }

      }else{
        mostrar_ayuda();
        mensaje_error_argc(comando, ARGC_MOSTRAR_LIBERADOS);
      }

    }else if(strcmp(comando,COMANDO_AYUDA) == 0){
      mostrar_ayuda();
      if(cantidad_argumentos != ARGC_AYUDA){
        mensaje_error_argc(comando,ARGC_AYUDA);
      }

    }else{
      mostrar_ayuda();
      printf("[ADVERTENCIA] El comando ingresado es invalido, no existe.\n");
    }

  }else{
    mostrar_ayuda();
    printf("[ADVERTENCIA] La cantidad de parametros excede lo necesario para el funcionamiento del programa.\n");
  }
  printf("\n");
  return 0;
}
