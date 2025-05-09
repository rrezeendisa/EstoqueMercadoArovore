/*****************************************************************************
 * Nome: Aplicação estoque de supermercado feito em C com árvore binária de busca
 * Descrição: Essa aplicação tem como objetivo gerenciar o estoque de um supermercado,
 *          utilizando uma árvore binária de busca para armazenar os itens e suas informações.
 * Autor: Isadora Gesaro Rezende,
          Jeovanni Conservani Da Silva,
          Khevyn Henrique G. T. Alves,
          Leonardo de Arruda Macedo
 * Data da última modificação: 09/05/2025
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "EstoqueMercadoArvore.h"

int main() {
    // Inicializa a árvore e a variável de quantidade lida
    Arvore estoque;
    int quantidadeLida;

    criarListaItensSeNaoExistir(); // Cria o arquivo "ListaItens.txt" se ele não existir
    estoque = carregarItensEmArvore(&quantidadeLida); // Carrega os itens da lista em uma árvore

    if (quantidadeLida == 0) {
        printf("Nenhum item foi carregado da ListaItens.\n");
    } else {
        printf("Itens carregados: %d\n", quantidadeLida);
        organizarEGravarArvore(estoque); // Organiza os itens por tipo e grava em arquivos .txt
    }

    // Nomes dos arquivos de saída para cada tipo de item
    const char *arquivos[5] = {
        "ListaFrutasArvore.txt", "ListaBebidasArvore.txt", "ListaDocesArvore.txt", "ListaSalgadosArvore.txt", "ListaEnlatadosArvore.txt"
    };

    // Mostra o conteúdo dos arquivos antes da remoção dos itens vencidos
    printf("\nConteúdo dos arquivos antes da remoção dos itens vencidos:\n");
    for (int i = 0; i < 5; i++) {
        printf("\nArquivo: %s\n", arquivos[i]);
        mostrarArquivo(arquivos[i]); // Exibe o conteúdo do arquivo
        removerItensVencidosArvore(arquivos[i]); // Remove itens vencidos do arquivo
    }

    // Mostra o conteúdo dos arquivos após a remoção dos itens vencidos
    printf("\nConteúdo dos arquivos após a remoção dos itens vencidos:\n");
    for (int i = 0; i < 5; i++) {
        printf("\nArquivo: %s\n", arquivos[i]);
        mostrarArquivo(arquivos[i]); // Exibe o conteúdo do arquivo após a remoção
    }

    liberarArvore(estoque); // Libera a memória alocada para a árvore
    return 0;
}