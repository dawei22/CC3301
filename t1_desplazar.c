#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "desplazar.h"

void desplazar(char *str, int from, int nbytes, int by) {
	int len = strlen(str);
	int i = nbytes;
	if (by > 0) {
		char *inicio = str + from + nbytes -1 ;
		char *fin = inicio + by;
		while (i > 0) {
			if ((fin - str) < len) { 
				*fin = *inicio;
			}
			fin--;
			inicio--;
			i--;
		}
	}
	else {
		char *inicio = str + from;
		char *fin = inicio + by;
		while (i > 0) {
			if ((fin - str) >= 0) {
				*fin = *inicio;
			}
			inicio++;
			fin++;
			--i;
		}
	}
}

char *desplazamiento(char *str, int from, int nbytes, int by) {
	char *new =  malloc(sizeof(char)*strlen(str) + 1); //Se suma 1 para guardar fin del string
	strcpy(new,str);
	desplazar(new,from,nbytes,by);
	return new;
}
