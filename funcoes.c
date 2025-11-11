#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"funcoes.h"


int qtdProdutos = 0; //Contador de produtos cadastrados (variavel global)


// Implementacao da funcao para cadastrar produtos 
Tproduto* cadastrarProduto(Tproduto* produtos)
{   char nome_temp[50];
    while (1)
    {

        printf("Insira o nome do produto %d (Digite ""0"" para terminar o cadastro): ", qtdProdutos+1);

        fgets(nome_temp, 50, stdin);
        nome_temp[strcspn(nome_temp, "\n")] = 0;

        if (strcmp(nome_temp, "0") == 0) //se o digitador for 0, sai
        {
            break;
        }
        
        Tproduto* temp = realloc(produtos, (qtdProdutos+1)*sizeof(Tproduto));
        if(temp == NULL){
            printf("Alocação de vetor inválida: Encerrando Programa\n");
            return NULL;
        }
        produtos = temp;
        
        strcpy(produtos[qtdProdutos].nome, nome_temp);
        

        printf("Insira o preco do produto(por @): ");
        scanf("%f", &produtos[qtdProdutos].preco);
        while (getchar() != '\n');
        printf("Insira a quantidade do produto: ");
        scanf("%d", &produtos[qtdProdutos].quantidade);
        if (produtos[qtdProdutos].quantidade == 0)
            produtos[qtdProdutos].status |= ESGOTADO; //marca como esgotado
        else
            produtos[qtdProdutos].status &= ~ESGOTADO; //desmarca como esgotado

        while (getchar() != '\n');
        produtos[qtdProdutos].id = qtdProdutos + 1;
        qtdProdutos++; //incrementa qtd de produtos

        printf("\n");
    }
    return produtos;
}

// Implementacao da funcao para listar produtos
void listarProdutos(Tproduto produtos[])
{
    printf("Listagem de produtos.\n");
    printf("_______________________\n");
    for (int i = 0; i < qtdProdutos; i++)
    {
        printf("ID: %d\n", produtos[i].id);
        printf("Nome: %s\n", produtos[i].nome);
        printf("Preco: %.2f\n", produtos[i].preco);
        
        if (produtos[i].quantidade == 0)
            printf("ESGOTADO.\n");
        else
        printf("Quantidade: %d\n", produtos[i].quantidade);
        
        printf("_______________________\n");
    }
}

// Implementacao da funcao para atualizar estoque
Tproduto atualizarEstoque(Tproduto produtos[])
{
    int respostaParaListagemAtt, idParaAtualizar, idEncontradoAtt, selecaoFuncaoAtualizar;
    printf("Deseja listar os produtos cadastrados para adiquirir o id do produto a ser atualizado? (1-Sim / 0-Nao): ");
                scanf("%d", &respostaParaListagemAtt);
                while (respostaParaListagemAtt < 0 || respostaParaListagemAtt > 1)
                {
                    printf("Resposta invalida. Tente novamente: ");
                    scanf("%d", &respostaParaListagemAtt);
                }

                switch (respostaParaListagemAtt)
                {
                    case 1:
                        listarProdutos(produtos);
                        break;
                    case 0:
                        break;
                }

                printf("Insira o ID do produto a ser atualizado: ");
                scanf("%d", &idParaAtualizar);
                idEncontradoAtt = buscaProduto_ID(produtos, idParaAtualizar);

                printf("O que deseja atualizar no produto selecionado?\n");
                printf("1. Nome\n");
                printf("2. Preco\n");
                printf("3. Quantidade\n");
                printf("4. Tudo\n");
                printf("Escolha: ");
                scanf("%d", &selecaoFuncaoAtualizar);
                while (selecaoFuncaoAtualizar < 1 || selecaoFuncaoAtualizar > 4)
                {
                    printf("Resposta invalida. Tente novamente: ");
                    scanf("%d", &selecaoFuncaoAtualizar);
                }

                switch (selecaoFuncaoAtualizar)
                {
                    case 1:
                        while (getchar() != '\n');
                        printf("Insira o novo nome do produto: ");
                        fgets(produtos[idEncontradoAtt].nome, 50, stdin);
                        produtos[idEncontradoAtt].nome[strcspn(produtos[idEncontradoAtt].nome, "\n")] = 0;
                        printf("Nome atualizado com sucesso!\n");
                        break;
                    
                    case 2:
                        printf("Insira o novo preco do produto(por @): ");
                        scanf("%f", &produtos[idEncontradoAtt].preco);
                        printf("Preco atualizado com sucesso!\n");
                        break;
                    
                    case 3:
                        printf("Insira a nova quantidade do produto: ");
                        scanf("%d", &produtos[idEncontradoAtt].quantidade);
                         if (produtos[idEncontradoAtt].quantidade == 0)
                            produtos[idEncontradoAtt].status |= ESGOTADO; //marca como esgotado
                        else
                            produtos[idEncontradoAtt].status &= ~ESGOTADO;//desmarca como esgotado
                        
                            printf("Quantidade atualizada com sucesso!\n");
                        break;
                    
                    case 4:
                        while (getchar() != '\n');
                        printf("Insira o novo nome do produto: ");
                        fgets(produtos[idEncontradoAtt].nome, 50, stdin);
                        produtos[idEncontradoAtt].nome[strcspn(produtos[idEncontradoAtt].nome, "\n")] = 0;
                        
                        printf("Insira o novo preco do produto(por @): ");
                        scanf("%f", &produtos[idEncontradoAtt].preco);
                        
                        printf("Insira a nova quantidade do produto: ");
                        scanf("%d", &produtos[idEncontradoAtt].quantidade);
                        if (produtos[idEncontradoAtt].quantidade == 0)
                            produtos[idEncontradoAtt].status |= ESGOTADO; //marca como esgotado
                        else
                            produtos[idEncontradoAtt].status &= ~ESGOTADO;//desmarca como esgotado
                        
                            printf("Produto atualizado com sucesso!\n");
                        break;
                }

    return produtos[idEncontradoAtt];
}

int buscaProduto_ID(Tproduto vet[], int id)
{
    int i, achou=0;

    //Faz a busca pelo ID fornecido em todo o vetor
    for(i=0; i<qtdProdutos; i++)
    {
        if(id == vet[i].id)
        {
            achou = 1;
            break;
        }
    }
    //Retorna o indice do ID fornecido ou codigo de erro(-1)
    if(achou)
    {
        return i;
    }
    else
    {
        printf("ID fornecido Nao Cadastrado\n");
        return -1;
    }
}

void deletarProduto(Tproduto vet[], int id)
{
    //Faz a busca do indice do item a ser excluído
    int i_excl=buscaProduto_ID(vet, id);

    //código de erro = Produto nao cadastrado
    if(i_excl == -1)
    {
        return;
    }

    //Sobrescreve o produto a ser excluido pelos seguintes
    for(int i=i_excl; i<qtdProdutos-1; i++)
    {
        vet[i] = vet[i+1];
        vet[i].id--;
    }
    //Diminui 1 da quantidade total
    qtdProdutos--;
    printf("Produto excluido com sucesso!\n");
}