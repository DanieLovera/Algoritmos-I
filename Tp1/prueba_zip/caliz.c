#include <stdio.h>
#include <stdbool.h>

const int EDAD_MIN = 17;
const int INTELIGENCIA_MIN = 0;
const int INTELIGENCIA_MAX = 10;
const int FUERZA_MIN = 0;
const int FUERZA_MAX = 10;
const char CAPACIDAD_MAGICA_MAX ='B';
const int VALOR_CM_B = 100;
const char CAPACIDAD_MAGICA_MED ='R';
const int VALOR_CM_R = 50;
const char CAPACIDAD_MAGICA_MIN ='M';
const int VALOR_CM_M = 0;
const char CONDICION_FIN = 'N';

/*
- PRECONDICIONES: La edad recibida debe ser numero entero positivo.
- POSTCONDICIONES: Asigna la edad del participante.
*/
bool validar_edad (unsigned short edad){
  return (EDAD_MIN <= edad);
}

/*
- PRECONDICIONES: La edad leida por teclado debe ser numero entero positivo.
- POSTCONDICIONES: Asigna la edad del participante.
*/
void pedir_edad(unsigned short *edad){
  scanf("%hu",edad);
}

/*
- PRECONDICIONES: La inteligencia recibida debe ser numero entero.
- POSTCONDICIONES: Asigna la inteligencia del participante.
*/
bool validar_inteligencia(int inteligencia){
  return (inteligencia <= INTELIGENCIA_MAX && inteligencia >= INTELIGENCIA_MIN);
}

/*
- PRECONDICIONES: La inteligencia leida por teclado debe ser un numero entero.
- POSTCONDICIONES: Asigna la inteligencia del participante.
*/
void pedir_inteligencia(int *inteligencia){
  int var_aux;
  printf("\nIngrese la inteligencia del participante [%i-%i]:\n"
    ,INTELIGENCIA_MIN,INTELIGENCIA_MAX);
  scanf("%i",&var_aux);
  while (!validar_inteligencia(var_aux)){
    printf("\n[Advertencia] El valor ingresado esta fuera del rango.\n");
    printf("Ingrese nuevamente la inteligencia del participante [%i-%i]:\n"
      ,INTELIGENCIA_MIN,INTELIGENCIA_MAX);
    scanf("%i",&var_aux);
  }
  *inteligencia = var_aux;
}

/*
- PRECONDICIONES: La fuerza recibida debe ser numero entero.
- POSTCONDICIONES: Asigna la fuerza del participante.
*/
bool validar_fuerza(int fuerza){
  return (fuerza <= FUERZA_MAX && fuerza >= FUERZA_MIN);
}

/*
- PRECONDICIONES: La fuerza leida por teclado debe ser un numero entero.
- POSTCONDICIONES: Asigna la fuerza del participante.
*/
void pedir_fuerza(int *fuerza){
  int var_aux;
  printf("\nIngrese la fuerza del participante [%i-%i]:\n"
    ,FUERZA_MIN,FUERZA_MAX);
  scanf("%i",&var_aux);
  while (!validar_fuerza(var_aux)){
    printf("\n[Advertencia] El valor ingresado esta fuera del rango.\n");
    printf("Ingrese nuevamente la fuerza del participante [%i-%i]:\n"
      ,FUERZA_MIN,FUERZA_MAX);
    scanf("%i",&var_aux);
  }
  *fuerza = var_aux;
}

/*
- PRECONDICIONES: La capacidad magica recibida debe ser un caracter.
- POSTCONDICIONES: Asigna la capacidad magica del participante.
*/
bool validar_capacidad_magica(char capacidad_magica){
  if (!(capacidad_magica >= 'A' && capacidad_magica <= 'Z')){
    printf("\n[Advertencia] Ingresaste una letra minuscula.\n");
    return false;
  }
  if (!(capacidad_magica == CAPACIDAD_MAGICA_MAX
    || capacidad_magica == CAPACIDAD_MAGICA_MED || capacidad_magica == CAPACIDAD_MAGICA_MIN)){
      printf("\n[Avertencia] Ingresaste una letra invalida.\n");
      return false;
  }
  return true;
}

/*
- PRECONDICIONES: La capacidad magica leida por teclado debe ser un caracter.
- POSTCONDICIONES: Asigna la capacidad magica del participante.
*/
void pedir_capacidad_magica(char *capacidad_magica){
  char var_aux;
  printf("\nIngrese la capacidad magica del particiante [%c(buena) -%c(regular) -%c(mala)]:\n"
    ,CAPACIDAD_MAGICA_MAX,CAPACIDAD_MAGICA_MED,CAPACIDAD_MAGICA_MIN);
  scanf(" %c",&var_aux);
  while (!(validar_capacidad_magica(var_aux))){
    printf("Ingrese nuevamente la capacidad magica del particiante [%c(buena) -%c(regular) -%c(mala)]:\n"
      ,CAPACIDAD_MAGICA_MAX,CAPACIDAD_MAGICA_MED,CAPACIDAD_MAGICA_MIN);
    scanf(" %c",&var_aux);
  }
  *capacidad_magica = var_aux;
}

/*
- PRECONDICIONES: La capacidad magica recibida debe ser un caracter.
- POSTCONDICIONES: Devuelve el valor de la capacidad magica ingresada.
*/
int asignar_valores_cm(char capacidad_magica){
  if (capacidad_magica == CAPACIDAD_MAGICA_MAX){
    return VALOR_CM_B;
  }else if(capacidad_magica == CAPACIDAD_MAGICA_MED){
    return VALOR_CM_R;
  }
  return VALOR_CM_M;
}

/*
- PRECONDICIONES: Los valores de inteligencia y fuerza deben ser numeros enteros,
la capacidad magica recibida debe ser un caracter.
- POSTCONDICIONES: Define un campeon
*/
bool definir_campeon(int inteligencia, int inteligencia_campeon, int fuerza
  , int fuerza_campeon, char capacidad_magica, char capacidad_magica_campeon){
    bool es_campeon = true;
    int valor_cm = asignar_valores_cm (capacidad_magica);
    int valor_cm_aux = asignar_valores_cm(capacidad_magica_campeon);

    if(inteligencia < inteligencia_campeon){
      es_campeon = false;
    }else if (inteligencia == inteligencia_campeon){
      if (fuerza < fuerza_campeon){
        es_campeon = false;
      }else if (fuerza == fuerza_campeon){
        if (valor_cm <= valor_cm_aux){
          es_campeon = false;
        }
      }
    }
    return es_campeon;
  }

  /*
  - PRECONDICIONES: Los valores de inteligencia y fuerza deben ser numeros enteros,
  la capacidad magica recibida debe ser un caracter.
  - POSTCONDICIONES: Cambia los atributos por los del campeon.
  */
void volcar_atributos(int inteligencia, int fuerza, char capacidad_magica
  , int *inteligencia_campeon, int *fuerza_campeon, char *capacidad_magica_campeon){
  *inteligencia_campeon = inteligencia;
  *fuerza_campeon = fuerza;
  *capacidad_magica_campeon = capacidad_magica;
}

void mensaje_nuevo_ingreso(){
  printf("\nDesea ingresar un alumno? (%c para NO, cualquier otra tecla para si):\n",CONDICION_FIN);
}

/*
PRECONDICIONES:
- Para añadir un nuevo alumno se deben ingresar unicamente caracteres.
POSTCONDICIONES:
- El numero del campeon del torneo.
*/
int main() {
  unsigned short edad;
  int inteligencia;
  int inteligencia_campeon;
  int fuerza;
  int fuerza_campeon;
  char capacidad_magica;
  char capacidad_magica_campeon;

  bool es_candidato;
  bool es_campeon;
  unsigned int campeon = 0;
  unsigned int numero_participantes_validos = 0;
  unsigned int numero_participantes = 0;
  char nuevo_participante;

  mensaje_nuevo_ingreso();
  scanf(" %c",&nuevo_participante);
  while(nuevo_participante != CONDICION_FIN){
      printf("\nIngrese la edad del participante:\n");
      pedir_edad(&edad);
      es_candidato = validar_edad(edad);
      numero_participantes++;
      if (es_candidato){
        numero_participantes_validos++;
        pedir_inteligencia(&inteligencia);
        pedir_fuerza(&fuerza);
        pedir_capacidad_magica(&capacidad_magica);

        if (numero_participantes_validos == 1){
          campeon = numero_participantes;
          volcar_atributos(inteligencia,fuerza,capacidad_magica
            , &inteligencia_campeon, &fuerza_campeon, &capacidad_magica_campeon);
          mensaje_nuevo_ingreso();
          scanf(" %c",&nuevo_participante);

        }else{
          es_campeon = definir_campeon(inteligencia, inteligencia_campeon
            , fuerza, fuerza_campeon, capacidad_magica, capacidad_magica_campeon);

            if (es_campeon){
              campeon = numero_participantes;
              volcar_atributos(inteligencia,fuerza,capacidad_magica
                , &inteligencia_campeon, &fuerza_campeon, &capacidad_magica_campeon);
              mensaje_nuevo_ingreso();
              scanf(" %c",&nuevo_participante);

            }else{
              mensaje_nuevo_ingreso();
              scanf(" %c",&nuevo_participante);

            }
          }
      }else{
          printf("\n[Advertencia] No calificas para entrar al torneo, tienes menos de %i años.\n",EDAD_MIN);
          mensaje_nuevo_ingreso();
          scanf(" %c",&nuevo_participante);
      }
  }

  if (campeon == 0){
      printf("\nNo hay campeón :(\n");

  }else{
    printf("\nEl campeón es el número %i :) \n",campeon);
  }
  return 0;
}
