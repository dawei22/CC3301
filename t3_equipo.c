#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include "equipo.h"

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond1 =  PTHREAD_COND_INITIALIZER; //espera a 5 jugadores
pthread_cond_t cond2 =  PTHREAD_COND_INITIALIZER; //si ya hay 5, espera

int j = 0; 

int contador = 0; //jugadores que han entrado
int sale = 0; //jugadores que han salido
char** team; //team 

char **hay_equipo(char *nombre){

	pthread_mutex_lock(&mtx);
	while (contador == 5) {
		pthread_cond_wait(&cond2, &mtx);
	}
	if (j == 0)
		team = malloc(sizeof(char *) * 5);
	team[j] = nombre;
	j++;	
	contador++;
	while (contador < 5) {
		pthread_cond_wait(&cond1, &mtx);
	}
	sale++;
	pthread_cond_broadcast(&cond1);
	
	char** equipo;		
	equipo = malloc(sizeof(char *) * 5);
	equipo = team;

	if (sale == 5) {
		contador = 0;
		sale = 0;
		j =0;
		pthread_cond_broadcast(&cond2);
	}
	pthread_mutex_unlock(&mtx);	
	return equipo;
}

