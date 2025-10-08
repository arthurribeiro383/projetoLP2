#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char nome[50];
    float preco;
    int quantidade;
} Tproduto;

// Protótipos das funções: 
void cadastrarProduto(Tproduto produto[]);
void listarProdutos(Tproduto produtos[]);
Tproduto atualizarEstoque(Tproduto produtos[]);
void deletarProduto(Tproduto[], int id);
int buscaProduto_ID(Tproduto[], int id); //Busca o produto por ID e retorna indice. "-1 = Produto nao encontrado"
//_______________________________________________________________________________________________________________________

int qtdProdutos = 0; //Contador de produtos cadastrados (variavel global)

int main (void)
{

    int resposta, id_del;
    Tproduto produtos[100]; // Array para armazenar os produtos

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
                cadastrarProduto(produtos);
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


    } while (resposta != 5);

    return  0;
}

// Implementacao da funcao para cadastrar produtos 
void cadastrarProduto(Tproduto produtos [])
{
    while (qtdProdutos < 100)
    {
        printf("Insira o nome do produto %d (Digite ""0"" para terminar o cadastro): ", qtdProdutos+1);
        fgets(produtos[qtdProdutos].nome, 50, stdin);
        produtos[qtdProdutos].nome[strcspn(produtos[qtdProdutos].nome, "\n")] = 0;
    
        if (strcmp(produtos[qtdProdutos].nome, "0") == 0)
        {
            break;
        }

        printf("Insira o preco do produto(por @): ");
        scanf("%f", &produtos[qtdProdutos].preco);
        while (getchar() != '\n');
        printf("Insira a quantidade do produto: ");
        scanf("%d", &produtos[qtdProdutos].quantidade);
        while (getchar() != '\n');
        produtos[qtdProdutos].id = qtdProdutos + 1;
        qtdProdutos++;
        printf("\n");
    }
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
                while (selecaoFuncaoAtualizar < 1 || selecaoFuncaoAtualizar > 3)
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
                        printf("Produto atualizado com sucesso!\n");
                        break;
                }

    return produtos[idEncontradoAtt];
}

int buscaProduto_ID(Tproduto vet[], int id)
{
    int i, achou=0;

    for(i=0; i<qtdProdutos; i++)
    {
        if(id == vet[i].id)
        {
            achou = 1;
            break;
        }
    }
    
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

    for(int i=i_excl; i<qtdProdutos-1; i++)
    {
        vet[i] = vet[i+1];
    }
    printf("Produto excluido com sucesso!\n");
}