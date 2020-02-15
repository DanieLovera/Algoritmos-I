#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define LARGO_STRING 30

/*
 * Crear una funcion que dada la ruta de un archivo de texto y un palabra
 * cuente cuantas veces aparece en el archivo. Devuelve -1 si fallo.
 */

int contar_palabra(char ruta_origen[], char palabra[LARGO_STRING]){
  FILE* archivo = fopen(ruta_origen, "r");
  if(archivo == NULL)
    return -1;

  int leidos;
  char palabra_actual[LARGO_STRING];
  int apariciones = 0;

  do {
    leidos = fscanf(archivo, "%s", palabra_actual);
    if(leidos > 0 && strcmp(palabra_actual, palabra) == 0)
      apariciones++;
  } while(leidos > 0);

  fclose(archivo);
  return apariciones;
}

/* Crear una funcion que dado un vector de obstaculos los escriba a todos en un
 * archivo de texto con el siguiente formato:
 *
 * Codigo:
 * Posicion: [Fil, Col]
 * Daño:
 * \n
 *
 * Devuelve true si se ejecuto con exito.
 */

typedef struct coordenada {
  int fil;
  int col;
} coordenada_t;

typedef struct obstaculo {
    char codigo;
    coordenada_t posicion;
    int danio;
} obstaculo_t;

bool escribir_obstaculos(char ruta_destino[], obstaculo_t obstaculos[], int tope){
  FILE* archivo = fopen(ruta_destino, "a");
  if(archivo == NULL)
    return false;

  for(int i = 0; i < tope; i++){
    fprintf(archivo, "Código: %c\n", obstaculos[i].codigo);
    fprintf(archivo, "Posición: [%i, %i]\n", obstaculos[i].posicion.fil, obstaculos[i].posicion.col);
    fprintf(archivo, "Daño: %i\n", obstaculos[i].danio);
  }

  fclose(archivo);
  return true;
}
