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
#include "EstoqueMercadoArvore.c"

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
        "ListaFrutasArvore.txt", "ListaBebidasArvore.txt", "ListaDocesArvore.txt", "ListaSalgadosArvore.txt", "ListaEnlatadosArvore.txt"
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
