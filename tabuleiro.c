#include <stdio.h>
#include <stdlib.h>
#include "tabuleiro.h"

void resultado(tabuleiro** tab, int linha, int coluna){
  int bomba = -1;
  for(int g=0; g<linha; g++){
    for(int a=0; a<coluna; a++){
      if(tab[g][a].revelada == bomba && tab[g][a].valor == -1){
        printf("Uma mina foi encontrada na jogada %d!\n", tab[g][a].joguei); break;
      }
    }
  }
  for(int g=0; g<linha; g++){
    for(int a=0; a<coluna; a++){
      if(tab[g][a].revelada == 0){
        printf("%c\t", '-');
      }if(tab[g][a].revelada == 1 || tab[g][a].revelada == bomba){
        printf("%d\t", tab[g][a].valor);
      }
    }
    printf("\n");
  }
  
}
  

void recursiva(tabuleiro ** tab, int linha, int coluna, int lin, int col){
   int bomba = -1;
   if(lin >= linha || col >= coluna || lin<0 || col<0){
      return;
   }if(tab[lin][col].revelada == 1){
      return;
   }if(tab[lin][col].valor == 0){
      tab[lin][col].revelada = 1;
      recursiva(tab, linha, coluna, lin+1, col);
      recursiva(tab, linha, coluna, lin, col+1);
      recursiva(tab, linha, coluna, lin-1, col);
      recursiva(tab, linha, coluna, lin, col-1); 
   }if(tab[lin][col].valor == -1){
      tab[lin][col].revelada = bomba;
      return;
   }if(tab[lin][col].valor > 0){
      tab[lin][col].revelada = 1;
      return;
   }
  
}

void bombastica(tabuleiro ** tab, int linha, int coluna){
  for(int g=0; g<linha; g++){
    for(int a=0; a<coluna; a++){
    int aux=0;
      if(tab[g][a].valor != -1){
        if(g<linha-1 && tab[g+1][a].valor == -1){
          aux+=1;
        }if(g<linha-1 && a>0 && tab[g+1][a-1].valor == -1){
          aux+=1;
        }if(g<linha-1 && a<coluna-1 && tab[g+1][a+1].valor == -1){
          aux+=1;
        }if(g>0 && tab[g-1][a].valor == -1){
          aux+=1;
        }if(g>0 && a>0 && tab[g-1][a-1].valor == -1){
          aux+=1;
        }if(g>0 && a<coluna-1 && tab[g-1][a+1].valor == -1){
          aux+=1;
        }if(a<coluna-1 && tab[g][a+1].valor == -1){
          aux+=1;
        }if(a>0 && tab[g][a-1].valor == -1){
          aux+=1;
        }
      tab[g][a].valor = aux;
  
      }
    }
  }
  
}


void LerArquivo(const char* nomearquivo){

  //variaveis usadas durante o codigo
  char string[1] = {"-"};
  int linha = 0;
  int coluna = 0;
  int bomba = 0;
  int jogadas = 0;
  int i = 0;
  int j = 0;
  int cont = 1;

  //selecionando o arquivo para leitura
  FILE *arq = fopen(nomearquivo, "r");
  if(arq == NULL){
    printf("Erro ao abrir o arquivo!");
      return;
  }
  
  //lendo a quantidade de linhas e colunas da matriz correspondente no arquivo
  fscanf(arq, "%d%d", &linha, &coluna);
  
  //criando a matriz de struct
  tabuleiro ** tab = malloc(linha * sizeof(tabuleiro *));
  for(i=0; i<linha; i++){
    tab[i]=malloc((coluna) *sizeof(tabuleiro));
   }
  
  //inicializando os valores do struct com zero
  for(i=0; i<linha; i++){
    for(j=0; j<coluna; j++){
      tab[i][j].valor = 0;
      tab[i][j].revelada = 0;
      tab[i][j].joguei = 0;
    }
   }
 
   //lendo a segunda linha do arquivo e salvando a quantidade de bombas
   fscanf(arq, "%d", &bomba);
   
   //salvando a posiçao das bombas e adicionando o valor de -1 a elas
   int linhaboom;
   int colunaboom;
   for(i=0; i<bomba; i++){
     fscanf(arq, "%d%d", &linhaboom, &colunaboom);
     tab[linhaboom][colunaboom].valor = -1;
   }    
  
   //lendo a quantidade de jogadas
   fscanf(arq, "%d", &jogadas);
   
   //chamando a funcao bombastica que salva o valor de cada casa do tabuleiro 
   bombastica(tab, linha, coluna);
   
   //lendo a posiçao de todas as jogadas e salvando a ordem de cada jogada
   int linhajogada;
   int colunajogada; 
   for(i=0; i<jogadas; i++){
     fscanf(arq, "%d%d", &linhajogada, &colunajogada); 
     tab[linhajogada][colunajogada].joguei = i+1;
     //chamada da funçao recursiva
     recursiva(tab, linha, coluna, linhajogada, colunajogada);
    }
    
   //chamada da funçai resultado responsavel por imprimir o tabuleiro
   resultado(tab, linha, coluna);
  
   //desalocando a memoria da matriz tabuleiro
   for (int i = 0; i < linha; i++) {
     free(tab[i]);
   }
   free(tab);
   
 }


 
