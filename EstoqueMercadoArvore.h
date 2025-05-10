/**************************************************************************************************
 * Nome: Cabecalho do TAD - Árvore Binária de Busca (ABB) para Estoque de Supermercado
 * Descrição: Cabecalho do TAD que define a estrutura de dados e as funções para manipulação da árvore
 *            binária.
 * Autor: Isadora Gesaro Rezende,
          Jeovanni Conservani Da Silva,
          Khevyn Henrique G. T. Alves,
          Leonardo de Arruda Macedo
 * Data da última modificação: 08/05/2025
 *************************************************************************************************/




#ifndef MERCADO_ARVORE_H
#define MERCADO_ARVORE_H

#define MAX_ITENS_INSERIR 10000
#define MAX_ESTOQUE 10000

typedef struct Item {
    char nome[50];
    char tipo[20];
    int vencimento;
    char setor[10];
} Item;

typedef struct No {
    Item item;
    struct No *esq, *dir;
} No;

typedef No* Arvore;

// TAD da ABB para estoque
void criarArvore(Arvore *raiz);
No* alocarNo(Item item);
void liberarArvore(Arvore raiz);
void inserirItem(Arvore *raiz, Item item);
void mostrarArvore(Arvore raiz);
void organizarEGravarArvore(Arvore raiz);
void removerItensVencidosArvore(const char *nomeArquivo);
int contarItensNoArquivo(const char *nomeArquivo);
Arvore carregarItensEmArvore(int *quantidadeLida);
void criarListaItensSeNaoExistir();
void mostrarArquivo(const char *nomeArquivo);

#endif
