#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "jsocket.h"
#include "util.h"


typedef void *(*Thread_fun)(void*);

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond1 =  PTHREAD_COND_INITIALIZER; //espera a 5 jugadores
pthread_cond_t cond2 =  PTHREAD_COND_INITIALIZER; //si ya hay 5, espera

int j = 0; 
int i = 0;

int contador = 0; //jugadores que han entrado
int sale = 0; //jugadores que han salido
char** team; //team 

void *hay_equipo(char* nombre, int cliente){

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
		printf("waiting\n");
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
		printf("Equipo!\n");
	}
	
	for (int i = 0 ; i <5 ; i++) {
		sendstr(cliente, equipo[i]);
	}
	pthread_mutex_unlock(&mtx);
	return 0;
}

void* serv(int s) {
	char * nombre = getstr(s);
	hay_equipo(nombre,s);
	return 0;
}


int main(int argc, char ** argv) {
	int p = j_socket();
	long client;
	if (j_bind(p,atoi(argv[1])) < 0) {
		perror("j_bind");
		exit(1);
	}
	for (;;) {
		client = j_accept(p);
		i++;
		printf("cliente %i conectado\n", i);
		pthread_t pid;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) != 0) {
        	printf("error");
      	}
      	if ( pthread_create(&pid, &attr, (Thread_fun) serv, (void *) client) != 0) {
        	printf("error");
      	}
      	pthread_attr_destroy(&attr);
		//hay_equipo(client);

	}
}