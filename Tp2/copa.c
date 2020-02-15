#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "copa.h"
#include "laberinto.h"

#define SIN_OBJETO 'O'
#define CON_OBJETO 'X'
#define TOPE_OBSTACULOS_INICIAL 3
#define TOPE_AYUDAS_INICIAL 6
#define PASOS_MAX_RIVAL 4
#define DANIO_POR_CAMINAR 3
#define DISTANCIA_MIN_COPA 10

#define CODIGO_JUGADOR 'J'
#define CODIGO_RIVAL 'G'
#define CODIGO_COPA 'C'
#define CODIGO_POCION 'P'
#define CODIGO_IMPEDIMENTA 'I'
#define CODIGO_RIDDIKULUS 'R'
#define CODIGO_ESCREGUTO 'E'
#define CODIGO_ACROMANTULA 'A'
#define CODIGO_BOGGART 'B'
#define CODIGO_ESFINGE 'F'

#define VIDA_PARA_REVELAR_COPA 15
#define VIDA_INICIAL_JUGADOR 50
#define VIDA_POCION 15
#define DANIO_ACROMANTULA 10
#define DANIO_BOGGART 15
#define DANIO_ESCREGUTO 20

#define DERECHA 'd'
#define ABAJO 's'
#define IZQUIERDA 'a'
#define ARRIBA 'w'

/*
 - PRECONDICIONES: Recibe una matriz de caracteres de tamaño [15x15].
 - POSTCONDICIONES: Inicializa una matriz con las posiciones inicialmente vacias.
 */

void inicializar_pos_disponibles(char pos_disponibles[TAMANIO][TAMANIO]){

  for (int m = 0; m < TAMANIO; m++){
    for (int n = 0; n < TAMANIO; n++){
      pos_disponibles[m][n] = SIN_OBJETO;
    }
  }
}

/*
 - PRECONDICIONES: Recibe cuatro enteros, dos filas y dos columnas de una matriz.
 - POSTCONDICIONES: Devuelve la distancia de manhattan entre las coordenadas de la matriz.
 */

int distancia_manhattan(int fil_a,int fil_b, int col_a, int col_b){

  int distancia_manhattan = (abs(fil_a-fil_b) + abs(col_a-col_b));
  return distancia_manhattan;
}

/*
 - PRECONDICIONES: Recibe cuatro enteros, dos filas y dos columnas de una matriz.
 - POSTCONDICIONES: Devuelve true si la distancia entre un objeto y la copa, es
   mayor a la distancia minima permitida y false si es menor.
 */

bool validar_distancia(int fil_a, int fil_b, int col_a, int col_b){

  bool bandera = true;
  int distancia = distancia_manhattan(fil_a,fil_b,col_a,col_b);

  if (distancia <= DISTANCIA_MIN_COPA){
    bandera = false;
  }
  return bandera;
}

/*
 - PRECONDICIONES: Recibe el laberinto original, el laberinto de posiciones disponibles,
   y una coordenada que representa la posicion de un objeto.
 - POSTCONDICIONES: Devuelve true si la posicion del objeto esta disponible y false
   si no.
 */

bool validar_posicion(char laberinto_original[TAMANIO][TAMANIO]
    ,coordenada_t posicion, char pos_disponibles[TAMANIO][TAMANIO]){

  int fila = posicion.fil;
  int columna = posicion.col;
  bool es_valida = true;

  if (laberinto_original[fila][columna] != VACIO
      || pos_disponibles[fila][columna] != SIN_OBJETO){
    es_valida = false;
  }
  return es_valida;
 }

 /*
  - PRECONDICIONES: Recibe el laberinto original y el laberinto de posiciones disponibles.
  - POSTCONDICIONES: Devuelve una coordenada con la posicion final, del objeto
    dentro del laberinto.
  */

coordenada_t obtener_posicion_final(char laberinto_original[TAMANIO][TAMANIO]
  ,char pos_disponibles[TAMANIO][TAMANIO]){

  coordenada_t posicion = posicion_aleatoria();
  bool es_valida = validar_posicion (laberinto_original,posicion,pos_disponibles);

  while(!es_valida){
    posicion = posicion_aleatoria();
    es_valida = validar_posicion (laberinto_original,posicion,pos_disponibles);
  }
  return posicion;
}

/*
 - PRECONDICIONES: Recibe el laberinto original, el laberinto de posiciones disponibles y
   la un registro de copa.
 - POSTCONDICIONES: Inicializa los campos del registro copa.
 */

void inicializar_copa(copa_t* copa,char laberinto_original[TAMANIO][TAMANIO]
  , char pos_disponibles[TAMANIO][TAMANIO]){

  copa->codigo = CODIGO_COPA;
  coordenada_t pos_valida = obtener_posicion_final(laberinto_original,pos_disponibles);
  (copa->posicion).fil = pos_valida.fil;
  (copa->posicion).col = pos_valida.col;
  pos_disponibles[pos_valida.fil][pos_valida.col] = CON_OBJETO;
}

/*
 - PRECONDICIONES: Recibe el laberinto original, el laberinto de posiciones disponibles,
   el codigo del obstaculo y el daño que realiza.
 - POSTCONDICIONES: Devuelve un objeto de tipo obstaculo inicializado.
 */

obstaculo_t inicializar_obstaculo(char codigo, int danio
  , char laberinto_original[TAMANIO][TAMANIO],char pos_disponibles[TAMANIO][TAMANIO]){

  obstaculo_t obstaculo;
  obstaculo.codigo = codigo;
  coordenada_t pos_valida = obtener_posicion_final(laberinto_original,pos_disponibles);
  (obstaculo.posicion).fil = pos_valida.fil;
  (obstaculo.posicion).col = pos_valida.col;
  pos_disponibles[pos_valida.fil][pos_valida.col] = CON_OBJETO;
  obstaculo.danio = danio;

  return obstaculo;
}

/*
 - PRECONDICIONES: Recibe un registro juego y un laberinto con las posiciones disponibles.
 - POSTCONDICIONES: Guarda todos los obstaculos del laberinto en un vector de tipo obstaculo.
 */

void guardar_obstaculos(juego_t* juego,char pos_disponibles[TAMANIO][TAMANIO]){

  obstaculo_t escreguto = inicializar_obstaculo(CODIGO_ESCREGUTO,DANIO_ESCREGUTO
    ,juego->laberinto_original,pos_disponibles);
  juego->obstaculos[0] = escreguto;

  obstaculo_t acromantula = inicializar_obstaculo(CODIGO_ACROMANTULA,DANIO_ACROMANTULA
    ,juego->laberinto_original,pos_disponibles);
  juego->obstaculos[1] = acromantula;

  obstaculo_t boggart = inicializar_obstaculo(CODIGO_BOGGART,DANIO_BOGGART
    ,juego->laberinto_original,pos_disponibles);
  juego->obstaculos[2] = boggart;

  juego->tope_obstaculos = TOPE_OBSTACULOS_INICIAL;
}

/*
 - PRECONDICIONES: Recibe el laberinto original, el laberinto de posiciones disponibles,
   el codigo de la ayuda y la vida que recupera.
 - POSTCONDICIONES: Devuelve un objeto de tipo ayuda inicializado.
 */

ayuda_t inicializar_ayuda(char codigo, int vida_a_recuperar
  , char laberinto_original[TAMANIO][TAMANIO],char pos_disponibles[TAMANIO][TAMANIO]){

  ayuda_t ayuda;
  ayuda.codigo = codigo;
  coordenada_t pos_valida = obtener_posicion_final(laberinto_original,pos_disponibles);
  (ayuda.posicion).fil = pos_valida.fil;
  (ayuda.posicion).col = pos_valida.col;
  pos_disponibles[pos_valida.fil][pos_valida.col] = CON_OBJETO;
  ayuda.vida_a_recuperar = vida_a_recuperar;

  return ayuda;
}

/*
 - PRECONDICIONES: Recibe un registro juego y un laberinto con las posiciones disponibles.
 - POSTCONDICIONES: Guarda todas las ayudas del laberinto en un vector de tipo ayuda.
 */

void guardar_ayudas(juego_t* juego,char pos_disponibles[TAMANIO][TAMANIO]){

  ayuda_t impedimenta = inicializar_ayuda(CODIGO_IMPEDIMENTA,0
    ,juego->laberinto_original,pos_disponibles);
  juego->ayudas[0] = impedimenta;

  ayuda_t riddikulus = inicializar_ayuda(CODIGO_RIDDIKULUS,0
    ,juego->laberinto_original,pos_disponibles);
  juego->ayudas[1] = riddikulus;

  for (int i = 2; i <= 4; i++){
    ayuda_t pocion = inicializar_ayuda(CODIGO_POCION,VIDA_POCION
      ,juego->laberinto_original,pos_disponibles);
    juego->ayudas[i] = pocion;
  }

  ayuda_t esfinge = inicializar_ayuda(CODIGO_ESFINGE,0
    ,juego->laberinto_original,pos_disponibles);
  juego->ayudas[5] = esfinge;

  juego->tope_ayudas = TOPE_AYUDAS_INICIAL;

}

/*
 - PRECONDICIONES: Recibe un registro juego,un laberinto con las posiciones disponibles
   y un laberinto_original.
 - POSTCONDICIONES: Devuelve una coordenada final y corregida con respecto a la distancia
   minima de un objeto a la copa.
 */

coordenada_t corregir_posicion(juego_t* juego,char laberinto_original[TAMANIO][TAMANIO]
  , char pos_disponibles[TAMANIO][TAMANIO]){

  coordenada_t pos_final_corregida;
  coordenada_t pos_copa = (juego->copa).posicion;
  int fil_copa = pos_copa.fil;
  int col_copa = pos_copa.col;
  coordenada_t pos_final = obtener_posicion_final(laberinto_original,pos_disponibles);
  pos_final_corregida.fil = pos_final.fil;
  pos_final_corregida.col = pos_final.col;
  while(!validar_distancia(fil_copa, pos_final_corregida.fil, col_copa, pos_final_corregida.col)){
    pos_final = obtener_posicion_final(laberinto_original,pos_disponibles);
    pos_final_corregida.fil = pos_final.fil;
    pos_final_corregida.col = pos_final.col;
  }
  return pos_final_corregida;
}

/*
 - PRECONDICIONES: Recibe el laberinto original, el laberinto de posiciones disponibles y
   la un registro de juego.
 - POSTCONDICIONES: Inicializa los campos del registro rival.
 */

void inicializar_rival(juego_t* juego, char laberinto_original[TAMANIO][TAMANIO]
    ,char pos_disponibles[TAMANIO][TAMANIO]){

  (juego->rival).codigo = CODIGO_RIVAL;
  coordenada_t pos_adecuada_rival = corregir_posicion(juego,laberinto_original,pos_disponibles);
  ((juego->rival).posicion).fil = pos_adecuada_rival.fil;
  ((juego->rival).posicion).col = pos_adecuada_rival.col;
  pos_disponibles[pos_adecuada_rival.fil][pos_adecuada_rival.col] = CON_OBJETO;
  (juego->rival).direccion = DERECHA;
  (juego->rival).cantidad_pasos = 0;
 }

 /*
  - PRECONDICIONES: Recibe el laberinto original, el laberinto de posiciones disponibles y
    la un registro de juego.
  - POSTCONDICIONES: Inicializa los campos del registro jugador.
  */

void inicializar_jugador(juego_t* juego, char laberinto_original[TAMANIO][TAMANIO]
    ,char pos_disponibles[TAMANIO][TAMANIO]){

  (juego->jugador).codigo = CODIGO_JUGADOR;
  (juego->jugador).vida = VIDA_INICIAL_JUGADOR;
  coordenada_t pos_adecuada_jugador = corregir_posicion(juego,laberinto_original,pos_disponibles);
  ((juego->jugador).posicion).fil = pos_adecuada_jugador.fil;
  ((juego->jugador).posicion).col = pos_adecuada_jugador.col;
  pos_disponibles[pos_adecuada_jugador.fil][pos_adecuada_jugador.col] = CON_OBJETO;
  (juego->jugador).tope_ayudas = 0;
  }

/*
 * Inicializará todas las estructuras con los valores correspondientes,
 * creará el laberinto, posicionará todos los elementos, etc.
 */

void inicializar_laberinto(juego_t* juego){

  char pos_disponibles[TAMANIO][TAMANIO];
  inicializar_pos_disponibles(pos_disponibles);
  inicializar_paredes_laberinto(juego->laberinto_original);
  inicializar_copa((&(juego->copa)),juego->laberinto_original,pos_disponibles);
  guardar_obstaculos(juego,pos_disponibles);
  guardar_ayudas(juego,pos_disponibles);
  inicializar_rival(juego,juego->laberinto_original,pos_disponibles);
  inicializar_jugador(juego,juego->laberinto_original,pos_disponibles);
}

/*
 - PRECONDICIONES: Recibe un laberinto de caracteres de tamaño [15x15], y dos enteros
   que representan filas y columnas dentro del laberinto.
 - POSTCONDICIONES: Devuelve true, si la fila y columna ingresada es una posicion vacia
   y esta dentro del rango de la matriz,de lo contrario devuelve false.
 */

bool verificar_espacio_vacio(char laberinto [TAMANIO][TAMANIO], int fila, int columna){
  bool espacio_vacio = true;

  if (fila >= TAMANIO || fila < 0 || columna < 0 || columna >= TAMANIO){
    return !espacio_vacio;
  }else if (laberinto[fila][columna] != VACIO){
    return !espacio_vacio;
 }
 return espacio_vacio;
}

/*
 * Determinará si el caracter ingresado es válido, esto es, es el caracter ‘a’ o
 * ‘s’ o ‘d’ o ‘w’ y además el jugador puede moverse en esa dirección, o sea,
 * hay pasillo.
 */

bool es_movimiento_valido(juego_t* juego, char tecla){

  bool es_movimiento_valido = true;
  int fil_jugador = (((juego->jugador).posicion).fil);
  int col_jugador = (((juego->jugador).posicion).col);

  if ((tecla != DERECHA) && (tecla != ABAJO) && (tecla != IZQUIERDA) && (tecla != ARRIBA)){
    return (!es_movimiento_valido);
  }
  if (tecla == DERECHA){
    col_jugador++;
    if (!verificar_espacio_vacio(juego->laberinto_original,fil_jugador,col_jugador)){
      es_movimiento_valido = false;
    }
  }else if (tecla == ABAJO){
    fil_jugador++;
    if (!verificar_espacio_vacio(juego->laberinto_original,fil_jugador,col_jugador)){
      es_movimiento_valido = false;
    }
  }else if (tecla == IZQUIERDA){
    col_jugador--;
    if (!verificar_espacio_vacio(juego->laberinto_original,fil_jugador,col_jugador)){
      es_movimiento_valido = false;
    }
  }else{
    fil_jugador--;
    if (!verificar_espacio_vacio(juego->laberinto_original,fil_jugador,col_jugador)){
      es_movimiento_valido = false;
    }
  }
  if (!es_movimiento_valido){
  }
  return es_movimiento_valido;
}

/*
 * Moverá el jugador hacia la dirección especificada.
 * Dicho movimiento es válido.
 */

void mover_jugador(jugador_t* jugador, char direccion){

  if (direccion == DERECHA){
    ((jugador->posicion).col)++;
  }else if (direccion == ABAJO){
    ((jugador->posicion).fil)++;
  }else if (direccion == IZQUIERDA){
    ((jugador->posicion).col)--;
  }else{
    ((jugador->posicion).fil)--;
  }
}

/*
 - PRECONDICIONES: Recibe un char con la direccion actual del rival.
 - POSTCONDICIONES: Devuelve la siguiente direccion del rival.
 */

char cambiar_direccion_rival(char direccion){

  switch (direccion) {
   case 'd': direccion = 's';
   break;
   case 's': direccion = 'a';
   break;
   case 'a': direccion = 'w';
   break;
   case 'w': direccion = 'd';
   break;
 }
 return direccion;
}

 /*
  * Moverá el rival a la próxima posición.
  */

void mover_rival(juego_t* juego){

  bool puede_moverse = false;
  int fil_rival = (((juego->rival).posicion).fil);
  int col_rival = (((juego->rival).posicion).col);

  do{
    if ( (juego->rival).cantidad_pasos == PASOS_MAX_RIVAL ){
      (juego->rival).direccion = cambiar_direccion_rival((juego->rival).direccion);
      (juego->rival).cantidad_pasos = 0;
    }
    if ( (juego->rival).direccion == DERECHA ){
      col_rival++;
      if ( verificar_espacio_vacio(juego->laberinto_original,fil_rival,col_rival) ){
        puede_moverse = true;
        (((juego->rival).posicion).col)++;
      }else{
        col_rival --;
      }
    }else if ( (juego->rival).direccion == ABAJO ){
      fil_rival++;
      if ( verificar_espacio_vacio(juego->laberinto_original,fil_rival,col_rival) ){
        puede_moverse = true;
        ( ((juego->rival).posicion).fil )++;
      }else{
        fil_rival--;
      }
    }else if ( (juego->rival).direccion == IZQUIERDA ){
      col_rival--;
      if ( verificar_espacio_vacio(juego->laberinto_original,fil_rival,col_rival) ){
        puede_moverse = true;
        ( ((juego->rival).posicion).col )--;
      }else{
        col_rival++;
      }
    }else{
      fil_rival--;
      if ( verificar_espacio_vacio(juego->laberinto_original,fil_rival,col_rival) ){
        puede_moverse = true;
        ( ((juego->rival).posicion).fil )--;
      }else{
        fil_rival++;
      }
    }
    (juego->rival).cantidad_pasos++;
  }while (!puede_moverse);
}

/*
 - PRECONDICIONES: Recibe un registro jugador y ayuda.
 - POSTCONDICIONES: Agrega al vector ayudas del jugador la ayuda pasada por parametro.
 */

void aprender_hechizo(jugador_t* jugador, ayuda_t ayuda){

  jugador->ayudas[jugador->tope_ayudas] = ayuda;
  (jugador->tope_ayudas)++;
}

/*
 - PRECONDICIONES: Recibe un vector de ayudas del jugador, un entero con su tope
   y el codigo de la ayuda como char.
 - POSTCONDICIONES: Devuelve -1 si no encontro la ayuda en el vector, o un entero
   con la posicion de la ayuda dentro del vector.
 */

int buscar_ayuda(ayuda_t ayudas[],int tope_ayudas, char codigo_ayuda){

  int posicion_ayuda = -1;
  int i = 0;

  while( (i < tope_ayudas) && (posicion_ayuda == -1) ){
    if (ayudas[i].codigo == codigo_ayuda){
        posicion_ayuda = i;
      }
    i++;
  }
  return posicion_ayuda;
}

/*
 - PRECONDICIONES: Recibe un vector de ayudas del jugador, un entero con su tope
   y un entero con la posicion en que se encuentra.
 - POSTCONDICIONES: Elimina del vector ayudas, el elmento en la posicion ingresada.
 */

void eliminar_ayuda(ayuda_t ayudas[],int* tope_ayudas,int posicion_ayuda){

  for(int j = posicion_ayuda; j < (*tope_ayudas) - 1; j++){
    ayudas[j] = ayudas[j+1];
  }
  (*tope_ayudas)--;
}

/*
 - PRECONDICIONES: Recibe un vector de obstaculos del jugador, un entero con su tope
   y un entero con la posicion en que se encuentra.
 - POSTCONDICIONES: Elimina del vector obstaculos, el elmento en la posicion ingresada.
 */

void eliminar_obstaculo(obstaculo_t obstaculos[],int* tope_obstaculos, int posicion_obstaculo){

  for(int j = posicion_obstaculo; j < (*tope_obstaculos) - 1; j++){
    obstaculos[j] = obstaculos[j+1];
  }
  (*tope_obstaculos)--;
}

/*
 - PRECONDICIONES: Recibe un registro del jugador, un entero con el daño recibido
   y un entero con la vida a recuperar.
 - POSTCONDICIONES: Actualiza el campo vida del jugador dentro del registro.
 */

void actualizar_vida(jugador_t* jugador,int danio, int vida_recuperar){

  int vida_jugador = (jugador->vida);

  if ((vida_jugador + vida_recuperar) > VIDA_INICIAL_JUGADOR){
    vida_recuperar = (VIDA_INICIAL_JUGADOR - vida_jugador);
  }
  (jugador->vida) = (jugador->vida) + (vida_recuperar - danio);
}

/*
 - PRECONDICIONES: Recibe un vector de ayudas, un entero con su tope
   y un registro del jugador.
 - POSTCONDICIONES: Si el jugador se encuentra sobre una ayuda en el laberinto, devuelve la posicion
   de la ayuda dentro del vector, si no devuelve -1.
 */

int posicion_ayuda_pisada(ayuda_t ayudas[], int tope_ayudas, jugador_t jugador){

  int posicion_ayuda_pisada = -1;
  int i = 0;

  while(i < tope_ayudas && posicion_ayuda_pisada == -1){
    if (((ayudas[i].posicion).fil == (jugador.posicion).fil)
      && ((ayudas[i].posicion).col == (jugador.posicion).col)){
        posicion_ayuda_pisada = i;
      }
    i++;
  }
  return posicion_ayuda_pisada;
}

/*
 - PRECONDICIONES: Recibe un vector de obstaculos, un entero con su tope
   y un registro del jugador.
 - POSTCONDICIONES: Si el jugador se encuentra sobre un obstaculo en el laberinto, devuelve la posicion
   del obstaculo dentro del vector, si no devuelve -1.
 */

int posicion_obstaculo_pisado(obstaculo_t obstaculos[], int tope_obstaculos, jugador_t jugador){

  int posicion_obstaculo_pisado = -1;
  int i = 0;

  while(i < tope_obstaculos && posicion_obstaculo_pisado == -1){
    if (((obstaculos[i].posicion).fil == (jugador.posicion).fil)
      && ((obstaculos[i].posicion).col == (jugador.posicion).col)){
        posicion_obstaculo_pisado = i;
      }
    i++;
  }
  return posicion_obstaculo_pisado;
}

/*
 * Actualizará el juego. Restará vida si el jugador está sobre un obstáculo
 * o lo eliminará si cuenta con el hechizo, aprenderá hechizos y todo lo
 * que pueda suceder luego de un turno.
 */

void actualizar_juego(juego_t* juego){

  char codigo_ayuda;
  char codigo_obstaculo;
  int pos_ayuda_pisada = posicion_ayuda_pisada(juego->ayudas, juego->tope_ayudas, juego->jugador);
  int pos_obstaculo_pisado = posicion_obstaculo_pisado(juego->obstaculos, juego->tope_obstaculos, juego->jugador);

  actualizar_vida(&(juego->jugador),DANIO_POR_CAMINAR,0);
  if (pos_ayuda_pisada != -1){
    codigo_ayuda = (juego->ayudas[pos_ayuda_pisada]).codigo;

    switch (codigo_ayuda) {

      case CODIGO_POCION:
        if((juego->jugador).vida > 0){
          actualizar_vida(&(juego->jugador),0,VIDA_POCION);
          eliminar_ayuda(juego->ayudas, &(juego->tope_ayudas), pos_ayuda_pisada);
        }
      break;

      case CODIGO_RIDDIKULUS:
        aprender_hechizo(&(juego->jugador), juego->ayudas[pos_ayuda_pisada]);
        eliminar_ayuda(juego->ayudas, &(juego->tope_ayudas), pos_ayuda_pisada);
      break;

      case CODIGO_IMPEDIMENTA:
        aprender_hechizo(&(juego->jugador), juego->ayudas[pos_ayuda_pisada]);
        eliminar_ayuda(juego->ayudas, &(juego->tope_ayudas), pos_ayuda_pisada);
      break;

      case CODIGO_ESFINGE:
        eliminar_ayuda(juego->ayudas, &(juego->tope_ayudas), pos_ayuda_pisada);
      break;
    }
  }else if(pos_obstaculo_pisado != -1){
    codigo_obstaculo = (juego->obstaculos[pos_obstaculo_pisado]).codigo;

    switch (codigo_obstaculo){

      case CODIGO_ACROMANTULA:
        actualizar_vida(&(juego->jugador),DANIO_ACROMANTULA,0);
        eliminar_obstaculo(juego->obstaculos, &(juego->tope_obstaculos),pos_obstaculo_pisado);
      break;

      case CODIGO_BOGGART:
      if (buscar_ayuda((juego->jugador).ayudas, (juego->jugador).tope_ayudas
        , CODIGO_RIDDIKULUS) == -1){
        actualizar_vida(&(juego->jugador),DANIO_BOGGART,0);
        eliminar_obstaculo(juego->obstaculos, &(juego->tope_obstaculos),pos_obstaculo_pisado);
      }
      break;

      case CODIGO_ESCREGUTO:
      if (buscar_ayuda((juego->jugador).ayudas, (juego->jugador).tope_ayudas
        , CODIGO_IMPEDIMENTA) == -1){
        actualizar_vida(&(juego->jugador),DANIO_ESCREGUTO,0);
        eliminar_obstaculo(juego->obstaculos, &(juego->tope_obstaculos),pos_obstaculo_pisado);
      }
      break;
    }
  }
}

/*
 * Devolverá el estado del juego, 1 ganado, 0 en curso, -1 perdido.
 */

int estado_juego(juego_t juego){

  int fil_copa = (((juego.copa).posicion).fil);
  int col_copa = (((juego.copa).posicion).col);
  int fil_jugador = (((juego.jugador).posicion).fil);
  int col_jugador = (((juego.jugador).posicion).col);
  int fil_rival = (((juego.rival).posicion).fil);
  int col_rival = (((juego.rival).posicion).col);
  int vida_jugador = ((juego.jugador).vida);
  int estado = 0;

  if ((fil_copa == fil_jugador) && (col_copa == col_jugador)) {
    if (vida_jugador > 0){
            estado = 1;
    }else{
      estado = -1;
    }
  }else if ((fil_copa == fil_rival && col_copa == col_rival) || vida_jugador <= 0) {
    estado = -1;
  }
  return estado;
}

/*
 * Devolverá una coordenada aleatoria dentro del rango TAMANIOxTAMANIO.
 * No valida que dicha coordenada coincida con un pasillo ni que exista
 * otro objeto en esa posición.
 */

coordenada_t posicion_aleatoria(){

  coordenada_t coordenada;
  srand((unsigned int)clock());
  coordenada.fil = rand() % (TAMANIO + 1);
  coordenada.col = rand() % (TAMANIO + 1);

  return coordenada;
}

/*
 - PRECONDICIONES: Recibe el laberinto base, y un laberinto vacio de tamaño [15x15].
 - POSTCONDICIONES: Copia las paredes del laberinto base en laberinto vacio.
 */

void copiar_laberinto(char laberinto[TAMANIO][TAMANIO], char laberinto_original[TAMANIO][TAMANIO]){

  for (int m = 0; m < TAMANIO; m++){
    for (int n = 0; n < TAMANIO; n++){
      if (laberinto_original[m][n] == PARED){
        laberinto[m][n] = '-';
      }
      else{
        laberinto[m][n] = VACIO;
      }
    }
  }
}

/*
 * Actualizará la matriz mostrada al usuario, con los elementos presentes
 * en el juego.
 */

 void actualizar_laberinto(juego_t juego, char laberinto[TAMANIO][TAMANIO]){

   int fil_jugador = ((juego.jugador).posicion).fil;
   int col_jugador = ((juego.jugador).posicion).col;
   int fil_rival = ((juego.rival).posicion).fil;
   int col_rival = ((juego.rival).posicion).col;
   int fil_copa = ((juego.copa).posicion).fil;
   int col_copa = ((juego.copa).posicion).col;
   int fil_obstaculo;
   int col_obstaculo;
   int fil_ayuda;
   int col_ayuda;

   copiar_laberinto(laberinto, juego.laberinto_original);
   if ((buscar_ayuda(juego.ayudas, juego.tope_ayudas,CODIGO_ESFINGE) == -1)
       || ((juego.jugador).vida <= VIDA_PARA_REVELAR_COPA)){
      laberinto[fil_copa][col_copa] = CODIGO_COPA;
   }
   for (int i = 0; i < juego.tope_obstaculos; i++){
     fil_obstaculo = ((juego.obstaculos[i]).posicion).fil;
     col_obstaculo = ((juego.obstaculos[i]).posicion).col;
     laberinto[fil_obstaculo][col_obstaculo] = (juego.obstaculos[i]).codigo;
   }
   for (int j = 0; j < juego.tope_ayudas; j++){
     fil_ayuda = ((juego.ayudas[j]).posicion).fil;
     col_ayuda = ((juego.ayudas[j]).posicion).col;
     laberinto[fil_ayuda][col_ayuda] = (juego.ayudas[j]).codigo;
   }
   laberinto[fil_rival][col_rival] = CODIGO_RIVAL;
   laberinto[fil_jugador][col_jugador] = CODIGO_JUGADOR;
 }

/*
 * Mostrará el laberinto por pantalla.
 */

void mostrar_laberinto(char laberinto[TAMANIO][TAMANIO]){

  for (int m = 0; m < TAMANIO; m++){
    for (int n = 0; n < TAMANIO; n++){
      printf(" %c",laberinto[m][n]);
    }
    printf("\n");
  }
}
