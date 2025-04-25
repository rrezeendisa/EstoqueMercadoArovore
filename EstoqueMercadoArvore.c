/**
 * @file EstoqueMercadoArvore.c
 * @brief Implementação de uma estrutura de árvore binária para gerenciar itens de estoque em um mercado.
 * 
 * Este arquivo contém funções para criar, manipular e persistir uma estrutura de árvore binária
 * para gerenciar itens de estoque. Os itens são categorizados por tipo e armazenados em arquivos separados.
 * A árvore suporta operações como inserção, travessia e remoção de itens vencidos.
 * 
 * 
 */

 /**
    * @brief Inicializa a árvore binária, definindo a raiz como NULL.
    * 
    * @param raiz Ponteiro para a raiz da árvore.
    */
void criarArvore(Arvore *raiz);

/**
 * @brief Aloca memória para um novo nó da árvore e o inicializa com o item fornecido.
 * 
 * @param item O item a ser armazenado no novo nó.
 * @return Ponteiro para o nó recém-alocado.
 */
No* alocarNo(Item item);

/**
 * @brief Libera a memória alocada para toda a árvore.
 * 
 * @param raiz A raiz da árvore a ser liberada.
 */
void liberarArvore(Arvore raiz);

/**
 * @brief Insere um novo item na árvore binária.
 * 
 * @param raiz Ponteiro para a raiz da árvore.
 * @param item O item a ser inserido.
 */
void inserirItem(Arvore *raiz, Item item);

/**
 * @brief Exibe o conteúdo da árvore binária em uma travessia em ordem.
 * 
 * @param raiz A raiz da árvore a ser exibida.
 */
void mostrarArvore(Arvore raiz);

/**
 * @brief Organiza os itens da árvore por tipo e os grava em arquivos correspondentes.
 * 
 * Os itens são categorizados em tipos predefinidos (ex.: "fruta", "bebida") e gravados
 * em arquivos separados. Itens com tipos desconhecidos não são gravados.
 * 
 * @param raiz A raiz da árvore a ser organizada e gravada em arquivos.
 */
void organizarEGravarArvore(Arvore raiz);

/**
 * @brief Remove itens vencidos de um arquivo e atualiza o arquivo.
 * 
 * Lê itens do arquivo especificado, remove itens vencidos e grava os itens restantes
 * em um arquivo temporário, que substitui o arquivo original.
 * 
 * @param nomeArquivo O nome do arquivo a ser processado.
 */
void removerItensVencidosArvore(const char *nomeArquivo);

/**
 * @brief Conta o número de itens em um arquivo.
 * 
 * @param nomeArquivo O nome do arquivo a ser contado.
 * @return O número de itens no arquivo.
 */
int contarItensNoArquivo(const char *nomeArquivo);

/**
 * @brief Carrega itens de um arquivo em uma árvore binária.
 * 
 * Lê itens do arquivo "ListaItens" e os insere em uma árvore binária.
 * O número de itens lidos é limitado por MAX_ITENS_INSERIR.
 * 
 * @param quantidadeLida Ponteiro para um inteiro para armazenar o número de itens lidos.
 * @return A raiz da árvore binária contendo os itens carregados.
 */
Arvore carregarItensEmArvore(int *quantidadeLida);

/**
 * @brief Cria o arquivo "ListaItens" com dados de exemplo, caso ele não exista.
 * 
 * Gera uma lista de itens com datas de vencimento aleatórias e tipos predefinidos,
 * e os grava no arquivo "ListaItens".
 */
void criarListaItensSeNaoExistir();

/**
 * @brief Exibe o conteúdo de um arquivo.
 * 
 * Lê e imprime os itens armazenados no arquivo especificado.
 * 
 * @param nomeArquivo O nome do arquivo a ser exibido.
 */
void mostrarArquivo(const char *nomeArquivo);
#include "EstoqueMercadoArvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



void criarArvore(Arvore *raiz) {
    *raiz = NULL;
}

No* alocarNo(Item item) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro ao alocar memoria para no.\n");
        exit(1);
    }
    novo->item = item;
    novo->esq = novo->dir = NULL;
    return novo;
}

void liberarArvore(Arvore raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esq);
        liberarArvore(raiz->dir);
        free(raiz);
    }
}

void inserirItem(Arvore *raiz, Item item) {
    if (*raiz == NULL) {
        *raiz = alocarNo(item);
    } else {
        if (strcmp(item.nome, (*raiz)->item.nome) < 0)
            inserirItem(&(*raiz)->esq, item);
        else
            inserirItem(&(*raiz)->dir, item);
    }
}

void mostrarArvore(Arvore raiz) {
    if (raiz != NULL) {
        mostrarArvore(raiz->esq);
        printf("Nome: %s | Tipo: %s | Vencimento: %d | Setor: %s\n",
               raiz->item.nome, raiz->item.tipo, raiz->item.vencimento, raiz->item.setor);
        mostrarArvore(raiz->dir);
    }
}

void organizarEGravarArvore(Arvore raiz) {
    const char *nomesArquivos[5] = {
        "ListaFrutas", "ListaBebidas", "ListaDoces", "ListaSalgados", "ListaEnlatados"
    };

    if (raiz == NULL)
        return;

    organizarEGravarArvore(raiz->esq);

    if (raiz->item.vencimento > 0) {
        const char *nomeArquivo = NULL;

        printf("Item: %s | Tipo detectado: [%s]\n", raiz->item.nome, raiz->item.tipo);

        if (strcmp(raiz->item.tipo, "fruta") == 0) nomeArquivo = nomesArquivos[0];
        else if (strcmp(raiz->item.tipo, "bebida") == 0) nomeArquivo = nomesArquivos[1];
        else if (strcmp(raiz->item.tipo, "doce") == 0) nomeArquivo = nomesArquivos[2];
        else if (strcmp(raiz->item.tipo, "salgado") == 0) nomeArquivo = nomesArquivos[3];
        else if (strcmp(raiz->item.tipo, "enlatado") == 0) nomeArquivo = nomesArquivos[4];
        else {
            printf("Tipo desconhecido: %s - Item %s nao sera gravado.\n", raiz->item.tipo, raiz->item.nome);
        }

        if (nomeArquivo != NULL) {
            FILE *arquivo = fopen(nomeArquivo, "ab");
            if (arquivo == NULL) {
                printf("Erro ao abrir o arquivo %s para gravacao.\n", nomeArquivo);
            } else {
                fwrite(&(raiz->item), sizeof(Item), 1, arquivo);
                fclose(arquivo);
                printf("Gravado: %s em %s\n", raiz->item.nome, nomeArquivo);
            }
        }
    }

    organizarEGravarArvore(raiz->dir);
}

void removerItensVencidosArvore(const char *nomeArquivo) {
    FILE *arquivoOriginal = fopen(nomeArquivo, "rb");
    FILE *arquivoTemp = fopen("temp.bin", "wb");
    Item item;

    if (arquivoOriginal == NULL || arquivoTemp == NULL) {
        printf("Erro ao abrir arquivos para remocao.\n");
        return;
    }

    while (fread(&item, sizeof(Item), 1, arquivoOriginal) == 1) {
        if (item.vencimento > 0) {
            fwrite(&item, sizeof(Item), 1, arquivoTemp);
        }
    }

    fclose(arquivoOriginal);
    fclose(arquivoTemp);
    remove(nomeArquivo);
    rename("temp.bin", nomeArquivo);
}

int contarItensNoArquivo(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) return 0;

    int contador = 0;
    Item item;
    while (fread(&item, sizeof(Item), 1, arquivo) == 1) {
        contador++;
    }
    fclose(arquivo);
    return contador;
}

Arvore carregarItensEmArvore(int *quantidadeLida) {
    FILE *arquivo = fopen("ListaItens", "rb");
    if (arquivo == NULL) return NULL;

    Arvore raiz = NULL;
    Item item;
    *quantidadeLida = 0;

    while (fread(&item, sizeof(Item), 1, arquivo) == 1 && *quantidadeLida < MAX_ITENS_INSERIR) {
        inserirItem(&raiz, item);
        (*quantidadeLida)++;
    }

    fclose(arquivo);
    return raiz;
}

void criarListaItensSeNaoExistir() {
    FILE *arquivo = fopen("ListaItens", "rb");
    if (arquivo != NULL) {
        fclose(arquivo);
        return;
    }

    arquivo = fopen("ListaItens", "wb");
    if (arquivo == NULL) {
        printf("Erro ao criar ListaItens.\n");
        return;
    }

    Item item;
    const char *tipos[5] = {"fruta", "bebida", "doce", "salgado", "enlatado"};
    srand(time(NULL));

    for (int i = 0; i < MAX_ITENS_INSERIR; i++) {
        int tipoIndex = i % 5;
        strcpy(item.tipo, tipos[tipoIndex]);
        sprintf(item.nome, "Item_%d", i + 1);
        item.vencimento = (i % 10 == 0) ? 0 : (1 + rand() % 30);
        sprintf(item.setor, "Setor %c", 'A' + tipoIndex);
        fwrite(&item, sizeof(Item), 1, arquivo);
    }

    fclose(arquivo);
}

void mostrarArquivo(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "rb");
    Item item;

    if (arquivo == NULL) {
        printf("Arquivo %s nao encontrado.\n", nomeArquivo);
        return;
    }

    printf("Conteudo do arquivo %s:\n", nomeArquivo);
    while (fread(&item, sizeof(Item), 1, arquivo) == 1) {
        printf("Nome: %s | Tipo: %s | Vencimento: %d | Setor: %s\n",
               item.nome, item.tipo, item.vencimento, item.setor);
    }

    fclose(arquivo);
}
