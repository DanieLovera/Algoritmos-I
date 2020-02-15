#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define TAMANIO_PERIODO 100
#define TAMANIO_CONTINENTE 100
#define TAMANIO_PAIS 100

typedef struct hogar {
    char periodo[TAMANIO_PERIODO];
    char continente[TAMANIO_CONTINENTE];
    char pais[TAMANIO_PAIS];
    int cantidad_anios;
} hogar_t;

void leer_hogar(FILE* fhogares, hogar_t* hogar, bool* es_eof) {
   int cantidad_leidos = fscanf(fhogares, "%[^;];%[^;];%[^;];%i\n", hogar->periodo,
      hogar->continente, hogar->pais, &(hogar->cantidad_anios));
   *es_eof = (cantidad_leidos == 0);
}

void imprimir_informe_hogares(FILE* fhogares) {
   hogar_t hogar_leido;
   bool eof_fhogares;

   printf("Informe de hogares de la Chiqui\n");
   int cantidad_anios_total = 0;
   leer_hogar(fhogares, &hogar_leido, &eof_fhogares);
   while (!eof_fhogares) {

      printf("Período: %s\n", hogar_leido.periodo);
      int cantidad_anios_por_periodo = 0;
      char periodo_actual[TAMANIO_PERIODO];
      strcpy(periodo_actual, hogar_leido.periodo);
      while (!eof_fhogares && (strcmp(periodo_actual, hogar_leido.periodo) == 0)) {

         printf("\tContinente: %s\n", hogar_leido.continente);
         int cantidad_anios_por_continente = 0;
         char continente_actual[TAMANIO_CONTINENTE];
         strcpy(continente_actual, hogar_leido.continente);
         while (!eof_fhogares && (strcmp(periodo_actual, hogar_leido.periodo) == 0) &&
            (strcmp(continente_actual, hogar_leido.continente) == 0)) {

            printf("\t\tPaís: %s - Cantidad de años vividos acá: %i\n",
               hogar_leido.pais, hogar_leido.cantidad_anios);
            cantidad_anios_por_continente += hogar_leido.cantidad_anios;
            leer_hogar(fhogares, &hogar_leido, &eof_fhogares);
         }
         printf("\t\tCantidad de años vividos en el continente %s: %i\n", continente_actual,
            cantidad_anios_por_continente);
         cantidad_anios_por_periodo += cantidad_anios_por_continente;
      }
      printf("\tCantidad de años vividos en el período %s: %i\n", periodo_actual,
         cantidad_anios_por_periodo);
      cantidad_anios_total += cantidad_anios_por_periodo;
   }
   printf("Cantidad de años vividos en total: %i\n", cantidad_anios_total);
}

int main(){

  FILE* prueba = fopen("manejo_archivos.dat","r"); 
  imprimir_informe_hogares(prueba);
}
