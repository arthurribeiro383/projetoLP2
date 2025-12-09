#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"funcoes.h"


int main (void)
{

    registrar_alerta_custom(alerta_cel, "Celular");
    registrar_alerta_custom(alerta_email, "E-mail");
    registrar_alerta_custom(alerta_sistema, "Sistema");

    int resposta, id_del;
    Tproduto* produtos = NULL; // Array para armazenar os produtos

    Toferta* cabeca= malloc(sizeof(Toferta));  //cabeça para lista de ofertas
    if(!cabeca){
        perror("malloc");
        return 1;
    }
    cabeca->prox=NULL;

    Callback acoes[] = {
    NULL,             // índice 0 não usado
    NULL,             // 1 = cadastrar (não vai para o vetor por causa do parametro diferente)
    acaoListar,       // 2
    acaoAtualizar,    // 3
    acaoDeletar,      // 4
    acaoMenuVendas    // 5
};

    limpaTela();
    do 
    {
        cabecalho();
        printf(COR_MENU "1. Cadastrar produtos.\n" COR_RESET);
        printf(COR_MENU "2. Listar produtos cadastrados.\n" COR_RESET);
        printf(COR_MENU "3. Atualizar estoque.\n" COR_RESET);
        printf(COR_MENU "4. Deletar produto.\n" COR_RESET);
        printf(COR_MENU "5. Menu de Vendas\n" COR_RESET);
        printf(COR_MENU "6. Sair\n" COR_RESET);
        printf("Escolha: ");
        scanf("%d", &resposta);
        while (getchar() != '\n');
        
        while (resposta < 1 || resposta > 6)
        {
            printf("Resposta invalida. Tente novamente: ");
            scanf("%d", &resposta);
            while (getchar() != '\n');
        }

         if (resposta == 6)
        break;

        if (resposta == 1) {
            produtos = cadastrarProduto(produtos);
            continue;
        }

        // Chama via callback
        acoes[resposta]( resposta == 5 ? (void*) cabeca : (void*) produtos );

    } while (1);

    
    liberaLista(cabeca);
    free(cabeca);
    cabeca=NULL;
    free(produtos);
    produtos = NULL;
    return  0;
}
