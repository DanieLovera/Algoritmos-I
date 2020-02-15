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
   FILE* avistamientos = fopen(ARCHIVO_AVISTAMIENTOS, "w");
   if (avistamientos == NULL) {
      printf("Error al abrir el archivo de avistamientos\n");
      return -1;
   }

   avistamiento_t avistamiento;

   avistamiento.latitud = 1.3485;
   avistamiento.longitud = 1.234234;
   avistamiento.duracion = 0.0234;
   strcpy(avistamiento.investigador, "Varyan Wrynn");
   fwrite(&avistamiento, sizeof(avistamiento), 1, avistamientos);

   avistamiento.latitud = 20.6516;
   avistamiento.longitud = -0.874;
   avistamiento.duracion = 35.874;
   strcpy(avistamiento.investigador, "Garrosh Hellscream");
   fwrite(&avistamiento, sizeof(avistamiento), 1, avistamientos);

   fclose(avistamientos);

   return 0;
}
