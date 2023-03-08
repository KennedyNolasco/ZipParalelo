#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]) {
   if (argc != 3) {
       fprintf(stderr, "uso: %s <arqentrada> <arqsaida>\n", argv[0]);
       exit(1);
   }
   FILE *fptr;
   fptr = fopen(argv[1],"r");
   if(fptr==NULL){
       printf("Arquivo não encontrado\n");   
       exit(1);  
   }
   fseek(fptr, 0, SEEK_END); 
   int size = ftell(fptr); 
   fseek(fptr, 0, SEEK_SET); 
   char *string = malloc((size+1)*sizeof(char));
   fgets(string,size+1,fptr);
   int count = 0;
   int i;
   char atual;
   atual = string[0];
   fclose(fptr);
   fptr = fopen(argv[2],"w");
   for(i=0;i<strlen(string);i++){
       if(string[i]==atual){
           count++;
       }
       else{
           fprintf(fptr,"%d",count);
           fprintf(fptr,"%c",atual);
           atual = string[i];
           count = 1;
       }
   }
   fprintf(fptr,"%d",count);
   fprintf(fptr,"%c",atual);
   fclose(fptr);
   return 0;
}


