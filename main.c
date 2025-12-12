#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"


int main (void)
{
    // Registra os callbacks de alerta
    registrar_alerta_custom(alerta_cel, "Celular");
    registrar_alerta_custom(alerta_email, "E-mail");
    registrar_alerta_custom(alerta_sistema, "Sistema");

    int resposta;
    Tproduto* produtos = NULL; // Array para armazenar os produtos
    
    // Resgata produtos do arquivo
    produtos = (Tproduto*)resgata_vet("produtos.dat", sizeof(Tproduto), &qtdProdutos);
    //produtos = carregarProdutosCSV("produtos.csv");


    Toferta* cabeca = NULL;
    // Resgata vendas (ofertas) do arquivo e converte para lista
    Toferta* temp_lista_vet = (Toferta*)resgata_vet("vendas.dat", sizeof(Toferta), &qtd_ofertas);
    vetEmLista(temp_lista_vet, &cabeca);

    // Se o vetor temporario foi alocado, liberar agora que ja está na lista
    if(temp_lista_vet != NULL) {
        free(temp_lista_vet);
        temp_lista_vet = NULL;
    }

    // Configuração do array de ponteiros para funções (Callbacks do menu)
    Callback acoes[] = {
        NULL,             // idx 0
        NULL,             // idx = cadastrar (não vai para o vetor por causa do parametro diferente)
        acaoListar,       // 1
        acaoAtualizar,    // 2
        acaoDeletar,      // 3
        acaoMenuVendas    // 4
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
        acoes[resposta]( resposta == 5 ? (void*) &cabeca : (void*) produtos );

    } while (1);

    // Salva o estado atual nos arquivos binarios antes de sair
    temp_lista_vet = listaEmVet(cabeca);

    grava_vet((void*)temp_lista_vet, "vendas.dat", sizeof(Toferta), &qtd_ofertas);
    grava_vet((void*)produtos, "produtos.dat", sizeof(Tproduto), &qtdProdutos);
    //salvarProdutosCSV("produtos.csv", produtos);

    
    // Libera memoria
    if(temp_lista_vet) free(temp_lista_vet);
    liberaLista(cabeca);
    cabeca = NULL;
    if(produtos) free(produtos);
    produtos = NULL;

    return 0;
}