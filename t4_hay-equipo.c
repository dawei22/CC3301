#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "jsocket.h"
#include "util.h"



int main(int argc, char** argv) {
	char *nombre = argv[1];
	int s = j_socket();

	char* direcc = getenv("ORGSVR");
	char* host = strtok(direcc,":");
	int port = atoi(strtok(NULL,":"));

	if (j_connect(s,host, port) < 0) {
		perror("error");
		exit(1);
	}
	sendstr(s,nombre);
	for (int i = 0; i <5 ; i++) {

		char* resp = getstr(s);
	//	printf("respuesta : %s\n", resp);
	    printf("%s\n", resp);
	}

	/*for (int i = 0, i < 5; i++) {
		printf("%s\n", resp[i]);

	}*/
	
	return 0;

}