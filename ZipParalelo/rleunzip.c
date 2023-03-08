#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
int main(int argc, char *argv[]) {
   if (argc != 2) {
       fprintf(stderr, "uso: %s <arqzipado>\n", argv[0]);
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
   char num[10];
   int count = 0;
   char atual;
   for(int i=0;i<10;i++){
       num[i] = '\0';
   }
   for(int i=0;i<strlen(string);i++){
       if(isalpha(string[i])==0){
           num[count] = string[i];
           count++;
       }
       else{
           atual = string[i];
           for(int i=0;i<atoi(num);i++){
               printf("%c",atual); 
           }
           count=0;
           for(int i=0;i<10;i++){
               num[i] = '\0';
           }
       }
   }
   printf("\n"); 
   fclose(fptr);
   return 0;
}


