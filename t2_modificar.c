  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>


char aux[2]; 
char *points = ":";
char space = ' ';
long offset;

FILE *fp;

int main (int argc, char *argv[]) {
   
   fp = fopen(argv[1],"r+");
   char *word = argv[2];
   char *def = argv[3];

   // Busco palabra en diccionario
   int len = strlen(word);
   char buffer[len+1];

   offset = 0;

   while (fread(buffer, len, 1, fp) != 0) { //Mientras lea algo en file
   	buffer[len] = '\0'; //Agrego \0 para leerlo como string
   	fread(aux,1,1,fp); //Despues de palabra deben venir ":"
   	aux[1] = '\0';
      

   	//Podria pasar que me entreguen parte de una palabra, por ej : aliment . Este se detecta como positivo
   	//para que eso no pase, se sabra que se busco una palabra "completa" si a continuacion hay un ":"
   	if (strcmp(word,buffer) == 0 && strcmp(aux,points)==0) { 
   		fwrite(def,strlen(def),1,fp);
         fwrite(points,1,1,fp);
         int actualPos = ftell(fp);
         for (int i = actualPos; i<=78 + offset; i++) {
            putc(space,fp); 
         }
         putc('\n',fp);
   		break;

   	}
      else {
         offset += 80;
         fseek(fp,80-len-1,SEEK_CUR); //Me desplazo a la linea siguiente
      }
   	
   }

   //Agregar nueva palabra
   if (fread(buffer, len, 1, fp) == 0){
   	fwrite(word,len,1,fp);
   	fwrite(points,1,1,fp);
   	fwrite(def,strlen(def),1,fp);
   	fwrite(points,1,1,fp);
      for (int i = ftell(fp); i<=78 + offset; i++) {
         putc(space,fp); 
      }
      putc('\n',fp);
   }


   fclose(fp);
   
   return(0);
}