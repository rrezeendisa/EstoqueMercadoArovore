/**
 * @file EstoqueMercadoArvoreMain.c
 * @brief Programa principal para gerenciar o estoque de um mercado utilizando uma estrutura de árvore.
 *
 * Este programa realiza as seguintes operações:
 * - Cria uma lista de itens, caso ela não exista.
 * - Carrega os itens da lista em uma estrutura de árvore.
 * - Organiza e grava a árvore em um arquivo.
 * - Mostra o conteúdo de arquivos específicos relacionados ao estoque.
 * - Remove itens vencidos da árvore e atualiza os arquivos correspondentes.
 * - Exibe os arquivos após a remoção dos itens vencidos.
 * - Libera a memória alocada para a árvore ao final da execução.
 *
 * @note O programa utiliza os seguintes arquivos de estoque: 
 *       "ListaFrutas", "ListaBebidas", "ListaDoces", "ListaSalgados", "ListaEnlatados".
 *
 * @dependencies EstoqueMercadoArvore.h
 *
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "EstoqueMercadoArvore.h"

int main() {
    Arvore estoque;
    int quantidadeLida;

    criarListaItensSeNaoExistir();
    estoque = carregarItensEmArvore(&quantidadeLida);

    if (quantidadeLida == 0) {
        printf("Nenhum item foi carregado da ListaItens.\n");
    } else {
        printf("Itens carregados: %d\n", quantidadeLida);
        organizarEGravarArvore(estoque);
    }

    const char *arquivos[5] = {
        "ListaFrutas", "ListaBebidas", "ListaDoces", "ListaSalgados", "ListaEnlatados"
    };

    for (int i = 0; i < 5; i++) {
        printf("\nArquivo: %s\n", arquivos[i]);
        mostrarArquivo(arquivos[i]);
        removerItensVencidosArvore(arquivos[i]);
    }

    printf("\nApos remocao dos itens vencidos:\n");

    for (int i = 0; i < 5; i++) {
        printf("\nArquivo: %s\n", arquivos[i]);
        mostrarArquivo(arquivos[i]);
    }

    liberarArvore(estoque);
    return 0;
}
