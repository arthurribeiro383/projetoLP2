#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"funcoes.h"

int qtd_alertas=0;
custom_noti noti_mod[MAX_NOTI];

int main (void)
{
    registrar_alerta_custom(alerta_cel, "Celular");
    registrar_alerta_custom(alerta_email, "E-mail");
    registrar_alerta_custom(alerta_sistema, "Sistema");

    int resposta, id_del;
    Tproduto* produtos = NULL; // Array para armazenar os produtos
    Toferta* cabeca= malloc(sizeof(Toferta));  //cabeça para lista de ofertas
    cabeca->prox=NULL;


    do 
    {
        printf("\nMENU: \n");
        printf("1. Cadastrar produtos.\n");
        printf("2. Listar produtos cadastrados.\n");
        printf("3. Atualizar estoque.\n");
        printf("4. Deletar produto.\n");
        printf("5. Menu de Vendas\n");
        printf("6. Sair\n");
        printf("Escolha: ");
        scanf("%d", &resposta);
        
        while (resposta < 1 || resposta > 6)
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
                vendasMenu(cabeca);
                break;

            case 6:
                printf("Saindo do programa.\n");
                break;
        }

    } while (resposta != 6);

    liberaLista(cabeca);
    free(cabeca);
    cabeca=NULL;
    free(produtos);
    produtos=NULL;
    return  0;
}
