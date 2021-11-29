/******************************************************************************
 Trabalho 2 - EDA INF 1010

*** AUTORES ***
** BERNARDO RUIZ FERNANDES - 1711180 **
** JOÃO GABRIEL NIELSEN - 1820419 **

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "trie.h"

#define TAM 26
 

Trie *criaNo(char v)
{
    Trie *no = (Trie *) malloc(sizeof(Trie));

    if(no == NULL)
    {
        printf("!! Erro na alocacao de memoria !!\n");
        return NULL;
    }

    no->letra = v;
    no->ocupacao = 1;           
    
    // Inicia os filhos como NULL
    for (int i = 0; i < TAM; i++)
        no->filhos[i] = NULL;

    return no;
}

Trie *criaTrie()
{

    Trie *t = criaNo(' ');
    t->termino = 1;
    
    return t;
}


void inserePalavra(Trie *t, char *palavra) 
{
    int idx;
    Trie * atual =  t;
    
    // Percorre cada letra da palavra para adicionar
    while(*palavra)
    {
        // Selecionamos a letra da vez
        // Usamos o *palavra - 'a' para pegar o inidice. Ex: 'd' - 'a' = 3 ('d' e a posicao 3 do filho)
        idx = tolower(*palavra) - 'a';
        
        // Caso nao tenha um no com a letra que estamos querendo adicionar criamos um novo e o adicionamos na Trie
        if(atual->filhos[idx] == NULL) {
            
            Trie* novo = criaNo(tolower(*palavra));
            atual->filhos[idx] = novo;
            atual = novo;
        }
        
        // Caso ja exista so seguir em frente
        else {
            
            atual = atual->filhos[idx];
            atual->ocupacao++;
        }
        
        // Seguir para a proxima letra
        palavra++;
    }
    
    atual->termino = 1;
    
}



int buscarPalavra(Trie *t, char *palavra)
{
    int idx;
    
    while (*palavra)
    {
        idx = tolower(*palavra) - 'a';
        
        // Analisamos se a Trie possue um filho que corresponda ao character da palavra
        if (t->filhos[idx] != NULL)
            // Se possui entao seguimos para a proxima letra
            t = t->filhos[idx];
        
        
        else
            // Se nao possui entao nao achamos
            return 0;
    
        
        // Segue para a proxima letra
        palavra++;
    }
 
    // retorna 1 caso tenha encontrado o No final da palavra e 0 se nao e final de uma palavra
    return t->termino;
}


Trie* buscarPrefixo(Trie *t, char *palavra) //basicamente uma busca que retorna um ponteiro para o ultimo character do prefixo
{
    
    int idx;
    
    while (*palavra)
    {
        idx = tolower(*palavra) - 'a';
        
        if (t->filhos[idx] != NULL)
            t = t->filhos[idx];
        
        else
            return 0;
        
        // Segue para a proxima letra
        palavra++;
    }

    return t;
}



void removerPalavra(Trie *t, char *palavra) {
    
    int idx;
    
    if (buscarPalavra(t, palavra) == 0) {
        
        return;
    }
    
    while (*palavra)
    {
        idx = tolower(*palavra) - 'a';
        
        if (t->filhos[idx] != NULL ) { 
            t = t->filhos[idx];
            t->ocupacao--;
        }
        
        else {
            
            liberar(t->filhos[idx]);
            return;
        }
        
        palavra++;
    }
    
    t->termino = 0;
    
}


void alphabetize2(Trie * t, char prefixo[])
{
    int i;

    if (t->termino == 1){
        printf("%s\n", prefixo); 
    }

    for (i = 0; i < TAM; ++i)
    {
        if (t->filhos[i] != NULL)
        {
            char ch = t->filhos[i]->letra;
            
            int l = strlen(prefixo);
            if(l > 0){
                char novo_prefixo[l];
                strcpy(novo_prefixo, prefixo);
                strncat(novo_prefixo, &ch, 1); 
                alphabetize2(t->filhos[i], novo_prefixo);
            }
            else{
                char novo_prefixo[] = {ch, '\0'};
                alphabetize2(t->filhos[i], novo_prefixo);
            }
        }
    }
}

void alphabetize(Trie * t){
    char prefixo[] = "";
    alphabetize2(t, prefixo);
}

void liberar(Trie *t){
    
    int i;
    for (i = 0; i < TAM; ++i)
        if (t->filhos[i] != NULL)
            liberar(t->filhos[i]);
    
    free(t);
}