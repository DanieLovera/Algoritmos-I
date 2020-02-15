#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define LARGO_STRING 100

int contar_palabra(char ruta_origen[], char palabra[LARGO_STRING]){
  FILE* archivo = fopen(ruta_origen, "r");
  if(archivo == NULL)
    return -1;

  int leidos;
  char palabra_actual[LARGO_STRING];
  int apariciones = 0;

  do {
    leidos = fscanf(archivo, "%[^;];\n", palabra_actual);
    if (leidos != -1){
      printf("%c\n", palabra_actual[0]);
}
      printf("%i\n",leidos );
    if(leidos > 0 && strcmp(palabra_actual, palabra) == 0){
      apariciones++;
    }
  } while(leidos > 0);

  fclose(archivo);
  return apariciones;
}

int main() {
  char palabra_ingresada[LARGO_STRING];
  //printf("Ingrese una palabra:");
  //scanf("%[^\n]", palabra_ingresada);
  printf("Cantidad de instancias en el texto: %i\n", contar_palabra("bee_movie.dat", "Aburrido"));
  return 0;
}
