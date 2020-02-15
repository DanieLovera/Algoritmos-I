#include <stdio.h>

int main(){
	char nombre[50];
	printf("Ingresa el nombre que quieras: \n");
	scanf("%[^\n]", nombre);
	printf("\n%s",nombre);
	printf("\nFin del programa\n");
	return 0;
}
