#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "prision.h"

#define FORMATO_LECTURA "%[^;];%u;%c;%u;%u;%[^;];%i\n"
#define FORMATO_ESCRITURA "%s\n"
#define UN_REGISTRO 1
#define MODO_LECTURA "r"
#define MODO_ESCRITURA "w"

/*
  - PRECONDICIONES: Recibe un caracter.
  - POSTCONDICIONES: Devuelve el valor representado por el caracter.
 */
int asignar_valores_conducta(char conducta){
  int valor_conducta = -1;
  if (conducta == CONDUCTA_BUENA){
    valor_conducta = VALOR_CONDUCTA_B;
  }else if (conducta == CONDUCTA_REGULAR){
    valor_conducta = VALOR_CONDUCTA_R;
  }else if (conducta == CONDUCTA_MALA){
    valor_conducta = VALOR_CONDUCTA_M;
  }
  return valor_conducta;
}

/*
  - PRECONDICIONES: Recibe un archivo de presos en texto abierto para
  lectura y un preso.
  - POSTCONDICIONES: Devuelve la cantidad de campos leidos por cada estructura
  del archivo, si ocurrio un error de lectura o el archivo llego a su fin
  devuelve EFO (-1)
  */
int leer_fpresos_txt(FILE* fpresos_txt, preso_t* preso){
  int campos_leidos;
  campos_leidos = fscanf( fpresos_txt, FORMATO_LECTURA, preso->nombre
    , &(preso->edad), &(preso->conducta), &(preso->pabellon), &(preso->celda)
      , preso->fecha, &(preso->maldicion_realizada) );

  return campos_leidos;
}

/*
  - PRECONDICIONES: Recibe un archivo de presos en texto abierto para
  escritura y un preso.
  - POSTCONDICIONES: Devuelve la cantidad de caracteres escritos al archivo,
  si ocurrio un error de escritura  devuelve un valor negativo.
  */
int escribir_fpresos_txt(FILE* fpresos_txt, preso_t preso){
  int caracteres_escritos;
  caracteres_escritos = fprintf(fpresos_txt,FORMATO_ESCRITURA,preso.nombre);

  return caracteres_escritos;
}

/*
  - PRECONDICIONES: Recibe un archivo de presos en binario abierto para
  lectura y un preso.
  - POSTCONDICIONES: Devuelve la cantidad de registros leidos, si ocurrio un error
  en la lectura o el archivo llego a su fin devuelve un valor menor.
 */
int leer_fpresos_bin (FILE* fpresos_bin, preso_t* preso){
  int registros_leidos;
  registros_leidos = (int) fread(preso,sizeof(preso_t),UN_REGISTRO,fpresos_bin);

  return registros_leidos;
}

/*
  -PRECONDICIONES: Recibe un archivo de presos en binario abierto para
  escritura y un preso.
  -POSTCONDICIONES: Devuelve la cantidad de registros escritos, si ocurrio un error
  en la lectura o el archivo llego a su fin devuelve un valor menor.
 */
int escribir_fpresos_bin (FILE* fpresos_bin, preso_t preso){
  int registros_escritos;
  registros_escritos = (int)fwrite(&preso, sizeof(preso_t), UN_REGISTRO, fpresos_bin);

  return registros_escritos;
}

/*
  - PRECONDICIONES: Recibe el nombre de un archivo de presos y el modo en que
  fue en que se abrio.
  - POSTCONDICIONES: Muestra en pantalla un mensaje con el error ocurrido en la apertura.
 */
void mensaje_error_apertura(char nombre_fpreso[], char modo[]){
  if (strcmp(modo,MODO_LECTURA) == 0){
    printf("[Error] no se pudo abrir para lectura el archivo %s\n",nombre_fpreso);
  }else if(strcmp(modo,MODO_ESCRITURA)){
    printf("[Error] no se pudo abrir para escritura el archivo %s\n",nombre_fpreso);
  }
}

/*
  - PRECONDICIONES: No recibe ningun paramametro.
  - POSTCONDICIONES: Muestra en pantalla un mensaje con el error ocurrido en el
  procesamiento de datos.
 */
void mensaje_error_procesamiento(){
  printf("Ocurrio un error durante el procesamiento de los datos, tus archivos ");
  printf("no fueron leidos/escritos correctamente.\n");
}

/*
- PRECONDICIONES: Recibe los nombres de los archivos con los presos por crucio,
imperius y perdonables.
- POSTCONDICIONES: Devuelve 1 si se creo correctamente el archivo de presos
perdonables o -1 si ocurrio algun error que evito que se creara.
*/
int generar_fpresos_perdonables(char nombre_fcrucio_bin[], char nombre_fimperius_bin[], char nombre_fperdonables_bin[]){
  int retorno_fcrucio = UN_REGISTRO;
  int retorno_fimperius = UN_REGISTRO;
  int retorno_fperdonables = UN_REGISTRO;
  FILE* fpresos_crucio_bin;
  FILE* fpresos_imperius_bin;
  FILE* fpresos_perdonables_bin;
  preso_t preso_crucio;
  preso_t preso_imperius;

  fpresos_crucio_bin = fopen(nombre_fcrucio_bin, MODO_LECTURA);
  if (fpresos_crucio_bin == NULL){
    mensaje_error_apertura(nombre_fcrucio_bin, MODO_LECTURA);
    return -1;
  }
  fpresos_imperius_bin = fopen(nombre_fimperius_bin, MODO_LECTURA);
  if (fpresos_imperius_bin == NULL){
    mensaje_error_apertura(nombre_fcrucio_bin, MODO_LECTURA);
    fclose(fpresos_crucio_bin);
    return -1;
  }
  fpresos_perdonables_bin = fopen(nombre_fperdonables_bin, MODO_ESCRITURA);
  if (fpresos_perdonables_bin == NULL){
    mensaje_error_apertura(nombre_fperdonables_bin, MODO_ESCRITURA);
    fclose(fpresos_crucio_bin);
    fclose(fpresos_imperius_bin);
    return -1;
  }
  retorno_fcrucio = leer_fpresos_bin(fpresos_crucio_bin, &preso_crucio);
  retorno_fimperius = leer_fpresos_bin(fpresos_imperius_bin, &preso_imperius);
  while( !feof(fpresos_crucio_bin) && !feof(fpresos_imperius_bin) ){
   if (retorno_fcrucio != UN_REGISTRO || retorno_fimperius != UN_REGISTRO
     || retorno_fperdonables != UN_REGISTRO){
    mensaje_error_procesamiento();
    return -1;
   }
   if (strcmp(preso_crucio.nombre,preso_imperius.nombre) > 0){
     retorno_fperdonables = escribir_fpresos_bin(fpresos_perdonables_bin,preso_imperius);
     retorno_fimperius = leer_fpresos_bin(fpresos_imperius_bin, &preso_imperius);

   }else if(strcmp(preso_crucio.nombre,preso_imperius.nombre) < 0){
     retorno_fperdonables = escribir_fpresos_bin(fpresos_perdonables_bin,preso_crucio);
     retorno_fcrucio = leer_fpresos_bin(fpresos_crucio_bin, &preso_crucio);

   }else{
     retorno_fcrucio = leer_fpresos_bin(fpresos_crucio_bin, &preso_crucio);
     retorno_fimperius = leer_fpresos_bin(fpresos_imperius_bin, &preso_imperius);
   }
 }
 while(!feof(fpresos_crucio_bin)){
   if(retorno_fperdonables != UN_REGISTRO || retorno_fcrucio != UN_REGISTRO){
     return -1;
   }
   retorno_fperdonables = escribir_fpresos_bin(fpresos_perdonables_bin,preso_crucio);
   retorno_fcrucio = leer_fpresos_bin(fpresos_crucio_bin, &preso_crucio);
 }
 while(!feof(fpresos_imperius_bin)){
   if(retorno_fperdonables != UN_REGISTRO || retorno_fimperius != UN_REGISTRO){
     return -1;
   }
   retorno_fperdonables = escribir_fpresos_bin(fpresos_perdonables_bin,preso_imperius);
   retorno_fimperius = leer_fpresos_bin(fpresos_imperius_bin, &preso_imperius);
 }
 fclose(fpresos_crucio_bin);
 fclose(fpresos_imperius_bin);
 fclose(fpresos_perdonables_bin);

 return 1;
}

/*
  - PRECONDICIONES: Recibe los nombres de los archivos con los presos perdonables y
  liberados, una fecha con formato AAAAMM como cadena de caracteres y un caracter
  con la conducta necesaria.
  - POSTCONDICIONES: Devuelve 1 si se creo correctamente el archivo de presos
  liberados o -1 si ocurrio algun error que evito que se creara.
 */
int generar_fpresos_liberados(char nombre_fliberados_txt[], char nombre_fperdonables_bin[], char fecha_ingresada[], char conducta_necesaria){
  int valor_conducta_necesaria;
  int valor_conducta_preso;
  int retorno_fperdonables;
  FILE* fpresos_perdonables_bin;
  FILE* fpresos_liberados_txt;
  preso_t preso;

  fpresos_liberados_txt = fopen(nombre_fliberados_txt,MODO_LECTURA);
  if (fpresos_liberados_txt != NULL){
    printf("El archivo %s que intentas crear ya existe.\n", nombre_fliberados_txt);
    return -1;
  }
  fpresos_perdonables_bin = fopen(nombre_fperdonables_bin,MODO_LECTURA);
  if(fpresos_perdonables_bin == NULL){
    mensaje_error_apertura(nombre_fperdonables_bin,MODO_LECTURA);
    return -1;
  }
  fpresos_liberados_txt = fopen(nombre_fliberados_txt,MODO_ESCRITURA);
  if(fpresos_liberados_txt == NULL){
    mensaje_error_apertura(nombre_fliberados_txt,MODO_ESCRITURA);
    fclose(fpresos_perdonables_bin);
    return -1;
  }

  retorno_fperdonables = leer_fpresos_bin(fpresos_perdonables_bin, &preso);
  while(!feof(fpresos_perdonables_bin)){
    if (retorno_fperdonables != UN_REGISTRO){
      mensaje_error_procesamiento();
      return -1;
    }
    valor_conducta_preso = asignar_valores_conducta(preso.conducta);
    valor_conducta_necesaria = asignar_valores_conducta(conducta_necesaria);
    if ((strcmp(fecha_ingresada,preso.fecha) >= 0) && (valor_conducta_preso >= valor_conducta_necesaria)){
      escribir_fpresos_txt(fpresos_liberados_txt,preso);
    }
    retorno_fperdonables = leer_fpresos_bin(fpresos_perdonables_bin, &preso);
  }
  fclose(fpresos_liberados_txt);
  fclose(fpresos_perdonables_bin);
  return 1;
}

/*
  - PRECONDICIONES: Recibe los nombres de los archivos con los presos por crucio,
  imperius y los liberados.
  - POSTCONDICIONES: Devuelve 1 si se actualizaron correctamente los archivos crucio e
  imperius o -1 si ocurrio un error durante la actualizacion.
 */
int actualizar_archivos(char nombre_fcrucio_bin[], char nombre_fimperius_bin[],char nombre_fliberados_txt[]){
  preso_t preso_crucio;
  preso_t preso_imperius;
  preso_t preso_liberado;
  FILE* fimperius_bin_aux;
  FILE* fcrucio_bin_aux;
  FILE* fliberados_txt;
  FILE* fimperius_bin;
  FILE* fcrucio_bin;
  int retorno_fliberados_txt;

  fimperius_bin = fopen(nombre_fimperius_bin,MODO_LECTURA);
  if(fimperius_bin == NULL){
    mensaje_error_apertura(nombre_fimperius_bin,MODO_LECTURA);
    return -1;
  }
  fcrucio_bin = fopen(nombre_fcrucio_bin,MODO_LECTURA);
  if(fcrucio_bin == NULL){
    mensaje_error_apertura(nombre_fcrucio_bin,MODO_LECTURA);
    fclose(fimperius_bin);
    return -1;
  }
  fliberados_txt = fopen(nombre_fliberados_txt,MODO_LECTURA);
  if(fliberados_txt == NULL){
    mensaje_error_apertura(nombre_fliberados_txt,MODO_LECTURA);
    fclose(fimperius_bin);
    fclose(fcrucio_bin);
    return -1;
  }
  fimperius_bin_aux = fopen("imperius_aux",MODO_ESCRITURA);
  if(fimperius_bin_aux == NULL){
    mensaje_error_apertura("imperius_aux",MODO_ESCRITURA);
    fclose(fimperius_bin);
    fclose(fcrucio_bin);
    fclose(fliberados_txt);
    return -1;
  }
  fcrucio_bin_aux = fopen("crucio_aux",MODO_ESCRITURA);
  if(fcrucio_bin_aux == NULL){
    mensaje_error_apertura("crucio_aux",MODO_ESCRITURA);
    fclose(fimperius_bin);
    fclose(fcrucio_bin);
    fclose(fliberados_txt);
    fclose(fimperius_bin_aux);
    return -1;
  }

  leer_fpresos_bin(fcrucio_bin, &preso_crucio);
  leer_fpresos_bin(fimperius_bin, &preso_imperius);
  retorno_fliberados_txt = fscanf(fliberados_txt,"%[^\n]\n", preso_liberado.nombre);

  while(!feof(fcrucio_bin) && !feof(fimperius_bin) && retorno_fliberados_txt != EOF){
    if(strcmp(preso_liberado.nombre, preso_crucio.nombre) > 0 && strcmp(preso_liberado.nombre, preso_imperius.nombre) > 0){
      escribir_fpresos_bin(fcrucio_bin_aux, preso_crucio);
      escribir_fpresos_bin(fimperius_bin_aux, preso_imperius);
      leer_fpresos_bin(fcrucio_bin, &preso_crucio);
      leer_fpresos_bin(fimperius_bin, &preso_imperius);
    }
    else if(strcmp(preso_liberado.nombre,preso_imperius.nombre) < 0 && strcmp(preso_liberado.nombre,preso_crucio.nombre) < 0){
      retorno_fliberados_txt = fscanf(fliberados_txt,"%[^\n]\n", preso_liberado.nombre);
    }
    else if(strcmp(preso_liberado.nombre, preso_crucio.nombre) > 0 && strcmp(preso_liberado.nombre, preso_imperius.nombre) == 0){
      escribir_fpresos_bin(fcrucio_bin_aux, preso_crucio);
      leer_fpresos_bin(fcrucio_bin, &preso_crucio);
      leer_fpresos_bin(fimperius_bin, &preso_imperius);
    }
    else if(strcmp(preso_liberado.nombre, preso_imperius.nombre) > 0 && strcmp(preso_liberado.nombre, preso_crucio.nombre) == 0){
      escribir_fpresos_bin(fimperius_bin_aux, preso_imperius);
      leer_fpresos_bin(fimperius_bin, &preso_imperius);
      leer_fpresos_bin(fcrucio_bin, &preso_crucio);
    }
    else if(strcmp(preso_liberado.nombre, preso_crucio.nombre) < 0 && strcmp(preso_liberado.nombre, preso_imperius.nombre) == 0){
      leer_fpresos_bin(fimperius_bin, &preso_imperius);
      retorno_fliberados_txt = fscanf(fliberados_txt,"%[^\n]\n", preso_liberado.nombre);
    }
    else if(strcmp(preso_liberado.nombre, preso_imperius.nombre) < 0 && strcmp(preso_liberado.nombre, preso_crucio.nombre) == 0){
      leer_fpresos_bin(fcrucio_bin, &preso_crucio);
      retorno_fliberados_txt = fscanf(fliberados_txt,"%[^\n]\n", preso_liberado.nombre);
    }
    else if(strcmp(preso_liberado.nombre,preso_crucio.nombre) > 0 && strcmp(preso_liberado.nombre,preso_imperius.nombre) < 0){
      escribir_fpresos_bin(fcrucio_bin_aux, preso_crucio);
      leer_fpresos_bin(fcrucio_bin, &preso_crucio);
      retorno_fliberados_txt = fscanf(fliberados_txt,"%[^\n]\n", preso_liberado.nombre);
    }
    else if(strcmp(preso_liberado.nombre,preso_imperius.nombre) > 0 && strcmp(preso_liberado.nombre,preso_crucio.nombre) < 0){
      escribir_fpresos_bin(fimperius_bin_aux, preso_imperius);
      leer_fpresos_bin(fimperius_bin, &preso_imperius);
      retorno_fliberados_txt = fscanf(fliberados_txt,"%[^\n]\n", preso_liberado.nombre);
    }
  }
  while(!feof(fcrucio_bin) && retorno_fliberados_txt != EOF){
    if(strcmp(preso_liberado.nombre,preso_crucio.nombre) > 0){
      escribir_fpresos_bin(fcrucio_bin_aux, preso_crucio);
      leer_fpresos_bin(fcrucio_bin, &preso_crucio);
    }
    else if(strcmp(preso_liberado.nombre,preso_crucio.nombre) < 0){
      retorno_fliberados_txt = fscanf(fliberados_txt,"%[^\n]\n", preso_liberado.nombre);
    }
    else{
      leer_fpresos_bin(fcrucio_bin, &preso_crucio);
      retorno_fliberados_txt = fscanf(fliberados_txt,"%[^\n]\n", preso_liberado.nombre);
    }
  }
  while(!feof(fimperius_bin) && retorno_fliberados_txt != EOF){
    if(strcmp(preso_liberado.nombre,preso_imperius.nombre) > 0){
      escribir_fpresos_bin(fimperius_bin_aux, preso_imperius);
      leer_fpresos_bin(fimperius_bin, &preso_imperius);
    }
    else if(strcmp(preso_liberado.nombre,preso_imperius.nombre) < 0){
      retorno_fliberados_txt = fscanf(fliberados_txt,"%[^\n]\n", preso_liberado.nombre);
    }
    else{
      leer_fpresos_bin(fimperius_bin, &preso_imperius);
      retorno_fliberados_txt = fscanf(fliberados_txt,"%[^\n]\n", preso_liberado.nombre);
    }
  }
  while(!feof(fcrucio_bin)){
    escribir_fpresos_bin(fcrucio_bin_aux, preso_crucio);
    leer_fpresos_bin(fcrucio_bin, &preso_crucio);
  }
  while(!feof(fimperius_bin)){
    escribir_fpresos_bin(fimperius_bin_aux, preso_imperius);
    leer_fpresos_bin(fimperius_bin, &preso_imperius);
  }
  fclose(fcrucio_bin);
  fclose(fimperius_bin);
  fclose(fcrucio_bin_aux);
  fclose(fimperius_bin_aux);
  fclose(fliberados_txt);
  remove(nombre_fcrucio_bin);
  remove(nombre_fimperius_bin);
  rename("crucio_aux",nombre_fcrucio_bin);
  rename("imperius_aux",nombre_fimperius_bin);
  return 1;
}

/*
  - PRECONDICIONES: Recibe el nombre del archivo de texto con presos liberados.
  - POSTCONDICIONES: Muestra la lista de los presos liberados y devuelve 1
  si todo funcion o -1 si ocurrio un error.
 */
int mostrar_liberados(char nombre_fliberados_txt[]){
  FILE* fliberados_txt;
  preso_t preso_liberado;
  int retorno_fliberados_txt;
  int contador_presos = 0;

  fliberados_txt = fopen(nombre_fliberados_txt,MODO_LECTURA);
  if(fliberados_txt == NULL){
    mensaje_error_apertura(nombre_fliberados_txt,MODO_LECTURA);
    return -1;
  }
  retorno_fliberados_txt = fscanf(fliberados_txt,"%[^\n]\n", preso_liberado.nombre);
  if(retorno_fliberados_txt != EOF){
    printf("-------------------- LISTA DE PRESOS LIBERADOS --------------------\n");
    while (retorno_fliberados_txt != EOF){
      contador_presos++;
      printf("%i. %s\n",contador_presos, preso_liberado.nombre);
      retorno_fliberados_txt = fscanf(fliberados_txt,"%[^\n]\n", preso_liberado.nombre);
    }
  }else{
    printf("No existe presos liberados en el archivo %s\n", nombre_fliberados_txt);
  }
  fclose(fliberados_txt);
  return 1;
}

/*
  - PRECONDICIONES: Ninguna.
  - POSTCONDICIONES: Muestra en pantalla informacion del comando perdonables.
 */
void mensaje_comando_perdonables(){
  printf("- Perdonables:\n");
  printf("\n\tEste comando genera un archivo binario con los presos de azkaban que podrian alguna ");
  printf("vez ser liberados.\n\tEl tercer argumento ingresado determina el nombre del archivo generado.\n");
  printf("\tSi la cantidad de argumentos es diferente de 3 o el formato es invalido ");
  printf("no se ejecutara el comando.\n");
  printf("\n\tEJEMPLO DE EJECUCION:\n\t./azkaban perdonables <nombre_archivo>\n\n");

}

/*
  - PRECONDICIONES: Ninguna.
  - POSTCONDICIONES: Muestra en pantalla informacion del comando liberar.
 */
void mensaje_comando_liberar(){
  printf("- Liberar:\n");
  printf("\n\tEste comando genera un archivo de texto con los presos de azkaban que pueden ");
  printf("ser liberados si cumplen con las condiciones necesarias.\n");
  printf("\tEl tercer argumento determina el archivo de presos perdonables que se usara.\n");
  printf("\tEl cuarto argumento determina la fecha de liberacion de los presos con formato AAAAMM.\n");
  printf("\tEl quinto argumento determina la conducta necesaria para la liberacion. ");
  printf("Conductas valida [B,R,M]\n");
  printf("\tSi los presos cumplen su condena para la fecha de liberacion y tienen una conducta ");
  printf("mejor o igual a la necesaria, seran ingresados al archivo.\n");
  printf("\tEl nombre del archivo generado sera liberados_AAAAMM.txt\n");
  printf("\tSi la cantidad de argumentos es diferente de 5 o el formato es invalido ");
  printf("no se ejecutara el comando.\n");
  printf("\tIMPORTANTE: Si ya existe un archivo de presos liberado para esa fecha, ");
  printf("no se generara uno nuevo.\n");
  printf("\n\tEJEMPLO DE EJECUCION:\n\t./azkaban liberar <archivo_perdonables> 203050 R\n\n");
}

/*
  - PRECONDICIONES: Ninguna.
  - POSTCONDICIONES: Muestra en pantalla informacion del comando actualizar.
 */
void mensaje_comando_actualizar(){
  printf("- Actualizar:\n");
  printf("\n\tEste comando actualizara los archivos de presos de azkaban posterior a su liberacion.");
  printf("liberados.\n");
  printf("\tEl tercer argumento determina la fecha del archivo de presos liberados a utilizar con formato AAAAMM.\n");
  printf("\tSi la cantidad de argumentos es diferente de 3 o el formato es invalido ");
  printf("no se ejecutara el comando.\n");
  printf("\n\tEJEMPLO DE EJECUCION:\n\t./azkaban actualizar 203050\n\n");
}

/*
  - PRECONDICIONES: Ninguna.
  - POSTCONDICIONES: Muestra en pantalla informacion del comando mostrar_liberados.
 */
void mensaje_mostrar_liberados(){
  printf("- Mostrar liberados:\n");
  printf("\n\tEste comando mostrara en pantalla los presos que hayan sido ");
  printf("liberados.\n");
  printf("\tEl tercer argumento determina la fecha del archivo de presos liberados a utilizar con formato AAAAMM.\n");
  printf("\tSi la cantidad de argumentos es diferente de 3 o el formato es invalido ");
  printf("no se ejecutara el comando.\n");
  printf("\n\tEJEMPLO DE EJECUCION:\n\t./azkaban mostrar_liberados 203050\n\n");
}

/*
  - PRECONDICIONES: Ninguna
  - POSTCONDICIONES: Muestra en pantalla informacion sobre los comandos del programa.
 */
void mostrar_ayuda(){
  printf("\n---------------------------------------------------------- LISTA DE COMANDOS DISPONIBLES --------------");
  printf("--------------------------------------------\n\n");
  mensaje_comando_perdonables();
  mensaje_comando_liberar();
  mensaje_comando_actualizar();
  mensaje_mostrar_liberados();
}
