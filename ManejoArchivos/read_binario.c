#include <stdio.h>
#include <string.h>

#define TAMANIO_NOMBRE_INVESTIGADOR 31
#define ARCHIVO_AVISTAMIENTOS "aurobor.dat"

typedef struct avistamiento {
   double latitud;
   double longitud;
   double duracion;
   char investigador[TAMANIO_NOMBRE_INVESTIGADOR];
} avistamiento_t;

int main() {
   FILE* avistamientos = fopen(ARCHIVO_AVISTAMIENTOS, "r");
   if (avistamientos == NULL) {
      printf("Error al abrir el archivo de avistamientos\n");
      return -1;
   }

   avistamiento_t avistamiento;
   size_t leidos = fread(&avistamiento, sizeof(avistamiento), 1, avistamientos);
   while (leidos > 0) {
      printf("Avistamiento de aurora boreal\n");
      printf("Latitud     : %f\n", avistamiento.latitud);
      printf("Longitud    : %f\n", avistamiento.longitud);
      printf("Duracion    : %f\n", avistamiento.duracion);
      printf("Investigador: %s\n", avistamiento.investigador);

      leidos = fread(&avistamiento, sizeof(avistamiento), 1, avistamientos);
   }

   fclose(avistamientos);

   return 0;
}
