#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"funcoes.h"

int main (void)
{

    int resposta, id_del;
    Tproduto* produtos = NULL; // Array para armazenar os produtos

    do 
    {
        printf("\nMENU: \n");
        printf("1. Cadastrar produtos.\n");
        printf("2. Listar produtos cadastrados.\n");
        printf("3. Atualizar estoque.\n");
        printf("4. Deletar produto.\n");
        printf("5. Sair\n");
        printf("Escolha: ");
        scanf("%d", &resposta);
        
        while (resposta < 1 || resposta > 5)
        {
            printf("Resposta invalida. Tente novamente: ");
            scanf("%d", &resposta);
        }

        switch (resposta)
        {
            case 1:
                printf("\nCadastrar produtos selecionado.\n");
                while (getchar() != '\n');
                produtos = cadastrarProduto(produtos);
                break;
            case 2:
                printf("\nListar produtos cadastrados selecionado.\n");
                if (qtdProdutos == 0)
                {
                    printf("Nenhum produto cadastrado.\n");
                    break;
                }
                else
                {
                listarProdutos(produtos);
                break;
                }

            case 3:
                printf("\nAtualizar estoque selecionado.\n");
                atualizarEstoque(produtos);
                break;

            case 4:
                printf("\nDeletar produto selecionado.\n");
                printf("Insira o ID do produto a ser excluido: ");
                scanf("%d", &id_del);
                deletarProduto(produtos, id_del);
                break;

            case 5:
                printf("Saindo do programa.\n");
                break;
        }

        if(produtos == NULL){
            printf("Alocação do vetor invalido: Encerrando produto!\n");
            break;
        }

    } while (resposta != 5);

    free(produtos);
    return  0;
}
