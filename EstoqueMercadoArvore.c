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

void mostrarArquivo(const char *nomeArquivo);
#include "EstoqueMercadoArvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Biblioteca responsável por gerar datas de vencimento aleatórias

void criarArvore(Arvore *raiz) {
    *raiz = NULL;
}

/// Cria a árvore inicializando a raiz como NULL
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

// Aloca memória para um novo nó da árvore e o inicializa com o item fornecido
// Libera a memória alocada para toda a árvore, percorrendo-a recursivamente
void liberarArvore(Arvore raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esq);
        liberarArvore(raiz->dir);
        free(raiz);
    }
}

void inserirItem(Arvore *raiz, Item item) {
    if (*raiz == NULL) {
        *raiz = alocarNo(item); // Aloca um novo nó e o insere na árvore se a raiz for NULL
    } else {
        if (strcmp(item.nome, (*raiz)->item.nome) < 0) // Se não for NULL, compara o nome do item
            inserirItem(&(*raiz)->esq, item); // Se o nome do item for menor, insere na subárvore esquerda
        else
            inserirItem(&(*raiz)->dir, item); // Caso contrário, insere na subárvore direita
    }
}

void mostrarArvore(Arvore raiz) {
    if (raiz != NULL) {
        mostrarArvore(raiz->esq); // Mostra a subárvore esquerda se existir
        printf("Nome: %s | Tipo: %s | Vencimento: %d | Setor: %s\n",
               raiz->item.nome, raiz->item.tipo, raiz->item.vencimento, raiz->item.setor);
        mostrarArvore(raiz->dir); // Mostra a subárvore direita se existir
    }
}

// Função que organiza os itens da árvore por tipo e os grava em arquivos correspondentes
// Os itens são categorizados em tipos predefinidos (ex.: "fruta", "bebida") e gravados
void organizarEGravarArvore(Arvore raiz) {
    const char *nomesArquivos[5] = {
        "ListaFrutasArvore.txt", "ListaBebidasArvore.txt", "ListaDocesArvore.txt", "ListaSalgadosArvore.txt", "ListaEnlatadosArvore.txt"
    };

    if (raiz == NULL)
        return;

    organizarEGravarArvore(raiz->esq); // Chamada recursiva para a subárvore esquerda

    if (raiz->item.vencimento > 0) {
        const char *nomeArquivo = NULL; // Inicializa o nome do arquivo como NULL
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
            FILE *arquivo = fopen(nomeArquivo, "a"); // Abre o arquivo para gravação em modo texto
            if (arquivo == NULL) {
                printf("Erro ao abrir o arquivo %s para gravacao.\n", nomeArquivo);
            } else {
                fprintf(arquivo, "Nome: %s | Tipo: %s | Vencimento: %d | Setor: %s\n",
                        raiz->item.nome, raiz->item.tipo, raiz->item.vencimento, raiz->item.setor);
                fclose(arquivo); // Fecha o arquivo após a gravação
                printf("Gravado: %s em %s\n", raiz->item.nome, nomeArquivo); // Exibe mensagem de sucesso
            }
        }
    }

    organizarEGravarArvore(raiz->dir); // Chamada recursiva para a subárvore direita
}

void removerItensVencidosArvore(const char *nomeArquivo) {
    FILE *arquivoOriginal = fopen(nomeArquivo, "r"); // Abre o arquivo original para leitura
    FILE *arquivoTemp = fopen("temp.txt", "w"); // Abre um arquivo temporário para gravação
    Item item;

    if (arquivoOriginal == NULL || arquivoTemp == NULL) {
        printf("Erro ao abrir arquivos para remocao.\n");
        return;
    }

    while (fscanf(arquivoOriginal, "Nome: %[^|]| Tipo: %[^|]| Vencimento: %d | Setor: %[^\n]\n",
                  item.nome, item.tipo, &item.vencimento, item.setor) == 4) {
        if (item.vencimento > 0) {
            fprintf(arquivoTemp, "Nome: %s | Tipo: %s | Vencimento: %d | Setor: %s\n",
                    item.nome, item.tipo, item.vencimento, item.setor);
        }
    }

    fclose(arquivoOriginal);
    fclose(arquivoTemp);
    remove(nomeArquivo);
    rename("temp.txt", nomeArquivo); // Remove o arquivo original e renomeia o temporário para o nome do original
}

int contarItensNoArquivo(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r"); // Abre o arquivo para leitura
    if (arquivo == NULL) return 0;

    int contador = 0;
    Item item;
    while (fscanf(arquivo, "Nome: %[^|]| Tipo: %[^|]| Vencimento: %d | Setor: %[^\n]\n",
                  item.nome, item.tipo, &item.vencimento, item.setor) == 4) {
        contador++;
    }
    fclose(arquivo);
    return contador; // Retorna o número total de itens lidos do arquivo
}

Arvore carregarItensEmArvore(int *quantidadeLida) {
    FILE *arquivo = fopen("ListaItens.txt", "r"); // Abre o arquivo "ListaItens.txt" para leitura
    if (arquivo == NULL) return NULL;

    Arvore raiz = NULL;
    Item item;
    *quantidadeLida = 0;

    while (fscanf(arquivo, "Nome: %[^|]| Tipo: %[^|]| Vencimento: %d | Setor: %[^\n]\n",
                  item.nome, item.tipo, &item.vencimento, item.setor) == 4 && *quantidadeLida < MAX_ITENS_INSERIR) {
        inserirItem(&raiz, item);
        (*quantidadeLida)++;
    }

    fclose(arquivo);
    return raiz;
}

void criarListaItensSeNaoExistir() {
    FILE *arquivo = fopen("ListaItens.txt", "r");
    if (arquivo != NULL) {
        fclose(arquivo);
        return;
    }

    arquivo = fopen("ListaItens.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar ListaItens.txt.\n");
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
        fprintf(arquivo, "Nome: %s | Tipo: %s | Vencimento: %d | Setor: %s\n",
                item.nome, item.tipo, item.vencimento, item.setor);
    }

    fclose(arquivo);
}

void mostrarArquivo(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    Item item;

    if (arquivo == NULL) {
        printf("Arquivo %s nao encontrado.\n", nomeArquivo);
        return;
    }

    printf("Conteudo do arquivo %s:\n", nomeArquivo);
    while (fscanf(arquivo, "Nome: %[^|]| Tipo: %[^|]| Vencimento: %d | Setor: %[^\n]\n",
                  item.nome, item.tipo, &item.vencimento, item.setor) == 4) {
        printf("Nome: %s | Tipo: %s | Vencimento: %d | Setor: %s\n",
               item.nome, item.tipo, item.vencimento, item.setor);
    }

    fclose(arquivo);
}