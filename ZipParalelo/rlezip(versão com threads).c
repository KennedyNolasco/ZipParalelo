#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
//Aluno:Kennedy Coelho Nolasco
//Matrícula: 21751912
char *string;
void *zippa(void *arg){ //função que as threads irão executar, a função simplesmente conta o número de vezes que a letra da posicao passada no arg se repete e retorna esse valor
    int posicao = *(int*)arg;
    char atual = string[posicao];
    int i = 0;
    int *count = malloc(sizeof(int));
    *count = 0; 
    while(string[posicao+i]==atual){
        i++;
        *count = *count+1;
    }
    return (void*)count;
}
int main(int argc, char *argv[]) {
   if (argc != 4) {
       fprintf(stderr, "uso: %s <arqentrada> <arqsaida> <nthreads>\n", argv[0]);
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
   string = malloc((size+1)*sizeof(char));  //nessa variavel vai ficar o vetor de char que tá no arquivo
   fgets(string,size+1,fptr);
   int nthreads = atoi(argv[3]);
   pthread_t pid[nthreads];
   int rodada = 1; 
   char charrodada[nthreads]; //esse vetor vai guardar o char atual que as threads tão trabalhando, a thread 0 vai trabalhar com o char 0, a thread 1 com o char 1, etc
   int posicaorodada[nthreads];// esse vetor vai guardar a posicao que as threads vao trabalhar, pra ser usado na função zippa
   char atual = string[0]; 
   atual = string[0];
   charrodada[0] = atual;
   posicaorodada[0] = 0;
   void* retorno[nthreads];
   fclose(fptr);
   fptr = fopen(argv[2],"w");
   for(int i=0;i<strlen(string);i++){ //passo pela string inteira no loop
       if(string[i]!=atual){ //se o char for diferente do atual então achei uma nova letra pra ser processada
           charrodada[rodada] = string[i]; //boto esse char no charrodada
           posicaorodada[rodada] = i; //e boto essa posicao no posicaorodada
           rodada++; //incremento a rodada pois agora tenho mais uma thread que vai trabalhar nessa rodada
           atual = string[i]; // e atualizo o atual
       }
       if(rodada>=nthreads){ //caso eu tiver letras o suficiente pra todas as threads trabalharem então eu rodo esse bloco de código
           for (int i = 0; i < rodada; i++) { //crio as threads e faço executar o zippa
               pthread_create(&pid[i], NULL, zippa, &posicaorodada[i]);
           }
           for (int i = 0; i < rodada; i++) { //espero as threads terminarem e jogo o retorno no vetor retorno
               pthread_join(pid[i], &retorno[i]); 
           }
           for (int i = 0; i < rodada; i++) { //escrevo os valores no arquivo
               fprintf(fptr,"%d",*(int*)retorno[i]);
               fprintf(fptr,"%c",charrodada[i]); 
           }
           rodada = 0;
       }   
   }
   for (int i = 0; i < rodada; i++) {
       pthread_create(&pid[i], NULL, zippa, &posicaorodada[i]);
   }
   for (int i = 0; i < rodada; i++) {
       pthread_join(pid[i], &retorno[i]); 
   }
   for (int i = 0; i < rodada; i++) {
       fprintf(fptr,"%d",*(int*)retorno[i]);
       fprintf(fptr,"%c",charrodada[i]); 
   }
   fclose(fptr);
   return 0;
}


