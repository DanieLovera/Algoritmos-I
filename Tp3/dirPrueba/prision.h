#ifndef _PRISION_H_
#define _PRISION_H_

#define CONDUCTA_BUENA 'B'
#define CONDUCTA_REGULAR 'R'
#define CONDUCTA_MALA 'M'
#define VALOR_CONDUCTA_B 100
#define VALOR_CONDUCTA_R 50
#define VALOR_CONDUCTA_M 0

#define MAX_NOMBRE 200
#define MAX_FECHA 7

typedef struct preso {

  char nombre[MAX_NOMBRE];
  unsigned int edad;
  char conducta;
  unsigned int pabellon;
  unsigned int celda;
  char fecha[MAX_FECHA];
  int maldicion_realizada;

}preso_t;

int generar_fpresos_perdonables(char nombre_fcrucio[], char nombre_fimperius[], char nombre_fperdonables[]);

int generar_fpresos_liberados(char nombre_fliberados_txt[], char nombre_fperdonables_bin[], char fecha_ingresada[], char conducta_necesaria);

int actualizar_archivos(char nombre_fcrucio[], char nombre_fimperius[],char nombre_fliberados[]);

int mostrar_liberados(char nombre_fliberados_txt[]);

void mostrar_ayuda();

#endif
