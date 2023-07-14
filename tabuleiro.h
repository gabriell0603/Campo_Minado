#ifndef TABULEIRO_H
#define TABULEIRO_H

typedef struct tabuleiro{

    //inteiro que representa a quantidade bombas adjacentes
    int valor; 

    //inteiro que retorna se uma casa foi revelada
    int revelada;

    //inteiro que armazena as jogada
    int joguei;    

}tabuleiro;



//funçao void que recebe a matriz de stcruct e o tamanho da matriz e imprimi na tela o tabuleiro
void resultado(tabuleiro **tab, int linha, int coluna);

//funçao recursiva que recebe a matriz de struct, o tamanho da matriz, e as linhas e colunas jogadas e armazena se uma casa foi revelada ou nao
void recursiva(tabuleiro **tab, int linha, int coluna, int lin, int col);

//funçao void que recebe a matriz de struct e o tamanho da matriz, responsavel por marmazenar o valor de uma determinada casa, considerando se há bombas nela ou nas adjacencias 
void bombastica(tabuleiro ** tab, int linha, int coluna);

//funçao void que recebe uma string e le os arquivos, chamando as outras funçoes
void LerArquivo(const char* nomearquivo);

#endif
