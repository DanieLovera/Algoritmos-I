#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define MAX_OBSTACULOS 10


typedef struct coordenada {
  int fil;
  int col;
} coordenada_t;

typedef struct obstaculo {
    char codigo;
    coordenada_t posicion;
    int danio;
} obstaculo_t;

void inicializar_obstaculos(obstaculo_t vector[]);

bool escribir_obstaculos(char ruta_destino[], obstaculo_t obstaculos[], int tope){
  obstaculo_t obstaculo;
  FILE* archivo = fopen(ruta_destino, "w");
  if(archivo == NULL)
    return false;

  FILE* archivo1 = fopen("escribo.dat", "a+");
  if(archivo == NULL)
    return false;

  for(int i = 0; i < tope; i++){
    fprintf(archivo, "Código: %c\n", obstaculos[i].codigo);
    fprintf(archivo, "Posición: [%i, %i]\n", obstaculos[i].posicion.fil, obstaculos[i].posicion.col);
    fprintf(archivo, "Daño: %i\n\n", obstaculos[i].danio);
    fwrite(&(obstaculos[i]),sizeof(obstaculo),1,archivo1);
    fread(&obstaculo,sizeof(obstaculos[i]),1,archivo1);
    printf("%li",sizeof(obstaculos[i]));
    printf("Código: %c\n", obstaculos[i].codigo);
    printf("Posición: [%i, %i]\n", obstaculos[i].posicion.fil, obstaculos[i].posicion.col);
    printf("Daño: %i\n\n", obstaculos[i].danio);

  }
  fclose(archivo1);
  fclose(archivo);
  return true;
}

int main(){
  obstaculo_t obstaculos[MAX_OBSTACULOS];

  inicializar_obstaculos(obstaculos);
  escribir_obstaculos("obstaculos.txt", obstaculos, 3);

  printf("Listo!\n");

  return 0;
}

void inicializar_obstaculos(obstaculo_t vector[]){
  vector[0].codigo = 'E';
  vector[0].posicion.fil = 10;
  vector[0].posicion.col = 5;
  vector[0].danio = 20;

  vector[1].codigo = 'A';
  vector[1].posicion.fil = 0;
  vector[1].posicion.col = 12;
  vector[1].danio = 10;

  vector[2].codigo = 'B';
  vector[2].posicion.fil = 3;
  vector[2].posicion.col = 9;
  vector[2].danio = 15;
}
