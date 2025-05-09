/*****************************************************************************
 * Nome: Aplicação estoque de supermercado feito em C com árvore binária de busca
 * Descrição: Essa aplicação tem como objetivo gerenciar o estoque de um supermercado,
 *          utilizando uma árvore binária de busca para armazenar os itens e suas informações.
 * Autor: Isadora Gesaro Rezende,
          Jeovanni Conservani Da Silva,
          Khevyn Henrique G. T. Alves,
          Leonardo de Arruda Macedo
 * Data da última modificação: 08/05/2025
 *****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include "EstoqueMercadoArvore.h"

int main() {
    // Inicializa a árvore e a variável de quantidade lida
    Arvore estoque;
    int quantidadeLida;

    criarListaItensSeNaoExistir();
    estoque = carregarItensEmArvore(&quantidadeLida); // Carrega os itens da lista em uma árvore

    if (quantidadeLida == 0) {
        printf("Nenhum item foi carregado da ListaItens.\n");
    } else {
        printf("Itens carregados: %d\n", quantidadeLida);
        organizarEGravarArvore(estoque);
    }
    // Variável para armazenar os nomes dos arquivos
    const char *arquivos[5] = {
        "ListaFrutasArvore", "ListaBebidasArvore", "ListaDocesArvore", "ListaSalgadosArvore", "ListaEnlatadosArvore"
    };
    // Mostra o conteúdo dos arquivos antes da remoção dos itens vencidos
    for (int i = 0; i < 5; i++) {
        printf("\nArquivo: %s\n", arquivos[i]);
        mostrarArquivo(arquivos[i]);
        removerItensVencidosArvore(arquivos[i]);
    }

    printf("\nApos remocao dos itens vencidos:\n");
    // Mostra o conteúdo dos arquivos após a remoção dos itens vencidos
    for (int i = 0; i < 5; i++) {
        printf("\nArquivo: %s\n", arquivos[i]);
        mostrarArquivo(arquivos[i]); // Exibe o conteúdo do arquivo após a remoção dos itens vencidos
    }

    liberarArvore(estoque);
    return 0;
}
