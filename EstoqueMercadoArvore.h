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




#ifndef MERCADO_ARVORE_H // Verifica se o cabeçalho já foi incluído
#define MERCADO_ARVORE_H // Se não, define o cabeçalho

#define MAX_ITENS_INSERIR 100000 // Definindo o número máximo de itens a serem inseridos na árvore
#define MAX_ESTOQUE 10000 // Definindo o número máximo de itens no estoque

// Definindo a estrutura do item que será armazenado na árvore
// Cada item contém informações como nome, tipo, data de vencimento e setor
typedef struct Item {
    char nome[50];
    char tipo[20];
    int vencimento;
    char setor[10];
} Item;

// Definindo a estrutura do nó da árvore binária de busca (ABB)
// Cada nó contém um item e ponteiros para os nós esquerdo e direito
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
