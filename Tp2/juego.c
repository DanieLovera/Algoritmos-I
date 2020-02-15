#include <stdio.h>
#include <string.h>
#include "copa.h"
#include "laberinto.h"
#include <stdlib.h>
#include <time.h>

/*
 - PRECONDICIONES: Recibe un vector de caracteres con el nombre del jugador
 - POSTCONDICIONES: Muestra un mensaje de bienvenida al jugador.
 */

void mensaje_inicio(char nombre_jugador[]){

  printf("\nBienvenido %s haz sido elegido para representar a tu escuela ",nombre_jugador);
  printf("en el \"Torneo de los Tres Magos\".\n");
  printf("- El laberinto esta lleno de extrañas criaturas que dificultarán tu recorrido ");
  printf("y podrán herirte.\n");
  printf("- También se encuentran hechizos que podrás aprender, ");
  printf("te servirán para defenderte de las criaturas del laberinto.\n");
  printf("- Inicialmente cuentas con %i puntos de vida, por cada paso que avances ",VIDA_INICIAL_JUGADOR);
  printf("perderas 3 puntos.\n");
  printf("- El Torneo se acaba cuando te quedes sin puntos de vida, o alguno de tus ");
  printf("rivales encuentra la Copa.\n\n");
}

/*
 - PRECONDICIONES: Recibe un registro del jugador
 - POSTCONDICIONES: Muestra las ayudas con las que cuenta el jugador.
 */

void mostrar_ayudas(jugador_t jugador){

  if (jugador.tope_ayudas == 0){
    printf("\n- No has aprendido ningún hechizo de defensa.\n");
  }else{
    printf("\n- Hechizos aprendidos [");
    for (int i = 0; i < jugador.tope_ayudas; i++){
      if (i == jugador.tope_ayudas -1){
        printf("%c", jugador.ayudas[i].codigo);
      }else{
        printf("%c,", jugador.ayudas[i].codigo);
      }
    }
    printf("]\n");
  }
}

/*
 - PRECONDICIONES: El movimiento recibido por teclado debera ser un caracter.
 - POSTCONDICIONES: Asigna el movimiento recibido.
 */

void pedir_movimiento(char nombre_jugador[],char* movimiento){

  printf("\n%s, te toca moverte [a,s,d,w]: ",nombre_jugador);
  scanf(" %c",movimiento);
}

/*
 - PRECONDICIONES: Ingresar un nombre menor a 30 caracteres.
 - POSTCONDICIONES: Devuelve el resultado final del torneo.
 */

int main(){

  char movimiento;
  bool movimiento_valido;
  char laberinto[TAMANIO][TAMANIO];
  char nombre_jugador[31];
  juego_t juego;

  printf("\nIngresa tu nombre: ");
  scanf("%[^\n]", nombre_jugador);
  mensaje_inicio(nombre_jugador);

  inicializar_laberinto(&juego);
  actualizar_laberinto(juego,laberinto);
  mostrar_laberinto(laberinto);

  int estado = estado_juego(juego);
  while(estado == 0){
      pedir_movimiento(nombre_jugador,&movimiento);
      movimiento_valido = es_movimiento_valido(&juego,movimiento);
      while(!movimiento_valido){
        printf("Movimiento inválido, ingresa nuevamente una dirección.\n");
        pedir_movimiento(nombre_jugador,&movimiento);
        movimiento_valido = es_movimiento_valido(&juego,movimiento);
      }
      mover_jugador(&(juego.jugador),movimiento);
      mover_rival(&juego);
      actualizar_juego(&juego);
      actualizar_laberinto(juego,laberinto);
      printf("\n    -Laberinto actualizado-\n");
      mostrar_laberinto(laberinto);
      printf("\n- Avanzaste en la dirección \"%c\".", movimiento);
      mostrar_ayudas(juego.jugador);
      if (juego.jugador.vida >0){
        printf("- Tienes %i puntos de vida.\n", juego.jugador.vida);
      }
      estado = estado_juego(juego);
  }

  if(estado == 1){
    printf("\n¡Felicidades encontraste la copa. Ganaste el Torneo de los Tres Magos! =)\n");
  }else{
    if((juego.jugador).vida <= 0){
      printf("\nTe quedaste sin vida. Perdiste el Torneo de los Tres Magos =(.\n");
    }else{
      printf("\nTu rival alcanzó la la copa. Perdiste el torneo de los tres Magos =(.\n");
    }
  }
  return 0;
}
