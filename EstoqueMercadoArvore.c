/**************************************************************************************************
 * Nome: TAD - Árvore Binária de Busca (ABB) para Estoque de Supermercado
 * Descrição: Essa TAD foi criada com o objetivo de gerenciar o estoque de um supermercado,
 *          utilizando uma árvore binária de busca para armazenar os itens e suas informações.
 * Autor: Isadora Gesaro Rezende,
          Jeovanni Conservani Da Silva,
          Khevyn Henrique G. T. Alves,
          Leonardo de Arruda Macedo
 * Data da última modificação: 08/05/2025
 *************************************************************************************************/


void mostrarArquivo(const char *nomeArquivo);
#include "EstoqueMercadoArvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Biblioteca responsável por geral datas de vencimento aleatórias



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

// Funcao que organiza os itens da árvore por tipo e os grava em arquivos correspondentes
// Os itens são categorizados em tipos predefinidos (ex.: "fruta", "bebida") e gravados
void organizarEGravarArvore(Arvore raiz) {
    const char *nomesArquivos[5] = {
        "ListaFrutasArvore", "ListaBebidasArvore", "ListaDocesArvore", "ListaSalgadosArvore", "ListaEnlatadosArvore"
    };

    if (raiz == NULL)
        return;

    organizarEGravarArvore(raiz->esq); // Chamada recursiva para a subárvore esquerda

    if (raiz->item.vencimento > 0) {
        const char *nomeArquivo = NULL; // Inicializa o nome do arquivo como NULL
        // Verifica o tipo do item e define o nome do arquivo correspondente
        printf("Item: %s | Tipo detectado: [%s]\n", raiz->item.nome, raiz->item.tipo);

        // "Conjunto de ifs" para verificar o tipo do item e definir o nome do arquivo correspondente
        // Se o tipo do item for "fruta", grava no arquivo "ListaFrutasArvore" e por aí vai...
        if (strcmp(raiz->item.tipo, "fruta") == 0) nomeArquivo = nomesArquivos[0];
        else if (strcmp(raiz->item.tipo, "bebida") == 0) nomeArquivo = nomesArquivos[1];
        else if (strcmp(raiz->item.tipo, "doce") == 0) nomeArquivo = nomesArquivos[2];
        else if (strcmp(raiz->item.tipo, "salgado") == 0) nomeArquivo = nomesArquivos[3];
        else if (strcmp(raiz->item.tipo, "enlatado") == 0) nomeArquivo = nomesArquivos[4];
        else {
            printf("Tipo desconhecido: %s - Item %s nao sera gravado.\n", raiz->item.tipo, raiz->item.nome);
        }

        if (nomeArquivo != NULL) {
            FILE *arquivo = fopen(nomeArquivo, "ab"); // Se o nomeArquivo for diferente de NULL, abre o arquivo para gravação
            if (arquivo == NULL) {
                printf("Erro ao abrir o arquivo %s para gravacao.\n", nomeArquivo);
            } else {
                fwrite(&(raiz->item), sizeof(Item), 1, arquivo); // Se não for NULL, grava o item no arquivo (fwrite é responsável por gravar o item no arquivo)
                fclose(arquivo); // Fecha o arquivo após a gravação
                printf("Gravado: %s em %s\n", raiz->item.nome, nomeArquivo); // Exibe mensagem de sucesso
            }
        }
    }

    organizarEGravarArvore(raiz->dir); // Chamada recursiva para a subárvore direita
}
void removerItensVencidosArvore(const char *nomeArquivo) {
    FILE *arquivoOriginal = fopen(nomeArquivo, "rb"); // Abre o arquivo original para leitura
    FILE *arquivoTemp = fopen("temp.bin", "wb"); // Abre um arquivo temporário para gravação
    Item item; // Declaração de um item para leitura e gravação

    if (arquivoOriginal == NULL || arquivoTemp == NULL) {
        printf("Erro ao abrir arquivos para remocao.\n"); // Verifica se os arquivos foram abertos corretamente
        return;
    }

    while (fread(&item, sizeof(Item), 1, arquivoOriginal) == 1) { // Enquanto houver itens no arquivo original, lê um item e grava no arquivo temporário
        // Verifica se o item não está vencido (vencimento > 0) e grava no arquivo temporário
        if (item.vencimento > 0) {
            fwrite(&item, sizeof(Item), 1, arquivoTemp); // Grava o item no arquivo temporário se não estiver vencido
        }
    }

    fclose(arquivoOriginal);
    fclose(arquivoTemp);
    remove(nomeArquivo);
    rename("temp.bin", nomeArquivo); // Remove o arquivo original e renomeia o temporário para o nome do original
}

int contarItensNoArquivo(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "rb"); // Abre o arquivo para leitura
    if (arquivo == NULL) return 0; // Se o arquivo não existir, retorna 0

    int contador = 0;
    Item item;
    while (fread(&item, sizeof(Item), 1, arquivo) == 1) { // Enquanto houver itens no arquivo, lê um item e incrementa o contador
        contador++;
    }
    fclose(arquivo);
    return contador; // Retorna o número total de itens lidos do arquivo
}

Arvore carregarItensEmArvore(int *quantidadeLida) {
    FILE *arquivo = fopen("ListaItens", "rb"); // Abre o arquivo "ListaItens" para leitura, onde estão os itens
    if (arquivo == NULL) return NULL;

    Arvore raiz = NULL; // Inicializa a raiz da árvore como NULL
    Item item;
    *quantidadeLida = 0; // Inicializa a quantidade lida como 0

    // Enquanto houver itens no arquivo, lê um item e insere na árvore
    while (fread(&item, sizeof(Item), 1, arquivo) == 1 && *quantidadeLida < MAX_ITENS_INSERIR) {
        inserirItem(&raiz, item); // Insere o item na árvore e incrementa a quantidade lida
        (*quantidadeLida)++;
    }

    fclose(arquivo);
    return raiz; // Retorna a raiz da árvore com os itens carregados
}

void criarListaItensSeNaoExistir() {
    FILE *arquivo = fopen("ListaItens", "rb"); // Tenta abrir o arquivo "ListaItens" para leitura
    if (arquivo != NULL) {
        fclose(arquivo);
        return;
    }

    arquivo = fopen("ListaItens", "wb"); // Se o arquivo não existir, cria um novo arquivo para gravação
    // Se o arquivo não puder ser criado, exibe mensagem de erro e retorna
    if (arquivo == NULL) {
        printf("Erro ao criar ListaItens.\n");
        return;
    }

    Item item;
    const char *tipos[5] = {"fruta", "bebida", "doce", "salgado", "enlatado"}; // Tipos de itens predefinidos
    // Inicializa o gerador de números aleatórios com a hora atual
    srand(time(NULL));

    for (int i = 0; i < MAX_ITENS_INSERIR; i++) { // Gera itens aleatórios para o arquivo "ListaItens" quantidade definida em EstoqueMercadoArvore.h
        int tipoIndex = i % 5; // Gera um índice aleatório para selecionar o tipo do item
        strcpy(item.tipo, tipos[tipoIndex]); // Copia o tipo selecionado para o item
        sprintf(item.nome, "Item_%d", i + 1); // Gera um nome para o item
        item.vencimento = (i % 10 == 0) ? 0 : (1 + rand() % 30); // Gera uma data de vencimento aleatória entre 1 e 30 dias, ou 0 para itens vencidos
        sprintf(item.setor, "Setor %c", 'A' + tipoIndex); // Gera um setor para o item baseado no índice do tipo
        fwrite(&item, sizeof(Item), 1, arquivo); // Grava o item no arquivo
    }

    fclose(arquivo);
}

void mostrarArquivo(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "rb"); // Abre o arquivo para leitura
    Item item;

    if (arquivo == NULL) {
        printf("Arquivo %s nao encontrado.\n", nomeArquivo);
        return;
    }

    printf("Conteudo do arquivo %s:\n", nomeArquivo);
    // Enquanto houver itens no arquivo, lê um item e exibe suas informações
    while (fread(&item, sizeof(Item), 1, arquivo) == 1) {
        printf("Nome: %s | Tipo: %s | Vencimento: %d | Setor: %s\n",
               item.nome, item.tipo, item.vencimento, item.setor);
    }

    fclose(arquivo);
}
