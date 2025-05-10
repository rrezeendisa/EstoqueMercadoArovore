/**************************************************************************************************
 * Nome: TAD - Árvore Binária de Busca (ABB) para Estoque de Supermercado
 * Descrição: Essa TAD foi criada com o objetivo de gerenciar o estoque de um supermercado,
 *          utilizando uma árvore binária de busca para armazenar os itens e suas informações.
 * Autor: Isadora Gesaro Rezende,
          Jeovanni Conservani Da Silva,
          Khevyn Henrique G. T. Alves,
          Leonardo de Arruda Macedo
 * Data da última modificação: 09/05/2025
 *************************************************************************************************/

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
        "ListaFrutasArvore.txt", "ListaBebidasArvore.txt", "ListaDocesArvore.txt", "ListaSalgadosArvore.txt", "ListaEnlatadosArvore.txt"
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
            FILE *arquivo = fopen(nomeArquivo, "at");  // Modo de texto para anexar
            if (arquivo == NULL) {
                printf("Erro ao abrir o arquivo %s para gravacao.\n", nomeArquivo);
            } else {
                fprintf(arquivo, "Nome: %s | Tipo: %s | Vencimento: %d | Setor: %s\n",
                        raiz->item.nome, raiz->item.tipo, raiz->item.vencimento, raiz->item.setor);
                fclose(arquivo);
                printf("Gravado: %s em %s\n", raiz->item.nome, nomeArquivo);
            }
        }
    }

    organizarEGravarArvore(raiz->dir);
}

void removerItensVencidosArvore(const char *nomeArquivo) {
    FILE *arquivoOriginal = fopen(nomeArquivo, "rt");
    FILE *arquivoTemp = fopen("temp.txt", "wt");
    Item item;

    if (arquivoOriginal == NULL || arquivoTemp == NULL) {
        printf("Erro ao abrir arquivos para remocao.\n");
        return;
    }

    while (fscanf(arquivoOriginal, "Nome: %49s | Tipo: %19s | Vencimento: %d | Setor: %9s\n",
                  item.nome, item.tipo, &item.vencimento, item.setor) == 4) {
        if (item.vencimento > 0) {
            fprintf(arquivoTemp, "Nome: %s | Tipo: %s | Vencimento: %d | Setor: %s\n",
                    item.nome, item.tipo, item.vencimento, item.setor);
        }
    }

    fclose(arquivoOriginal);
    fclose(arquivoTemp);
    remove(nomeArquivo);
    rename("temp.txt", nomeArquivo);
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
    FILE *arquivo = fopen("ListaItens.txt", "rt");
    if (arquivo == NULL) return NULL;

    Arvore raiz = NULL;
    Item item;
    *quantidadeLida = 0;

while (fscanf(arquivo, "Nome: %[^|]|Tipo: %[^|]|Vencimento: %d|Setor: %[^\n]\n",
              item.nome, item.tipo, &item.vencimento, item.setor) == 4 && *quantidadeLida < MAX_ITENS_INSERIR)
{
    inserirItem(&raiz, item);
    (*quantidadeLida)++;
}

    fclose(arquivo);
    return raiz;
}

void criarListaItensSeNaoExistir() {
    FILE *arquivo = fopen("ListaItens.txt", "wt"); 
    if (arquivo != NULL) {
        fclose(arquivo);
        return;
    }

    arquivo = fopen("ListaItens.txt", "w");
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
    FILE *arquivo = fopen(nomeArquivo, "rt");
    Item item;

    if (arquivo == NULL) {
        printf("Arquivo %s nao encontrado.\n", nomeArquivo);
        return;
    }

    printf("Conteudo do arquivo %s:\n", nomeArquivo);
    while (fscanf(arquivo, "Nome: %49s | Tipo: %19s | Vencimento: %d | Setor: %9s\n",
                  item.nome, item.tipo, &item.vencimento, item.setor) == 4) {
        printf("Nome: %s | Tipo: %s | Vencimento: %d | Setor: %s\n",
               item.nome, item.tipo, item.vencimento, item.setor);
    }

    fclose(arquivo);
}