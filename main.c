#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nome[50];
    float preco;
    int quantidade;
} Tproduto;

// O prototipo da funcao cadastrarProduto foi alterado para um ponteiro pois é um array
// e arrays sao passados por referencia
void cadastrarProduto(Tproduto* produto);

void listarProdutos();

Tproduto atualizarEstoque(Tproduto produto);

void deletarProduto(int id);

// Tproduto* buscarProdutoPorID(int id); Tentar implementar nos próximos checkpoints

int main (void){

    int resposta;
    Tproduto produtos[100]; // Array para armazenar os produtos

    do {
        printf("\nMENU: \n");
        printf("1. Cadastrar produtos.\n");
        printf("2. Listar produtos cadastrados.\n");
        printf("3. Atualizar estoque.\n");
        printf("4. Deletar produto.\n");
        printf("5. Sair\n");
        printf("Choose an option: ");
        scanf("%d", &resposta);
        while (resposta < 1 || resposta > 5) {
            printf("Resposta invalida. Tente novamente: ");
            scanf("%d", &resposta);
        }

        switch (resposta) {
            case 1:
                printf("Cadastrar produtos selecionado.\n");
                cadastrarProduto(produtos);
                break;
            case 2:
                printf("Listar produtos cadastrados selecionado.\n");
                void listarProdutos();
                break;
            case 3:
                printf("Atualizar estoque selecionado.\n");
                // Chamar funcao para atualizar estoque
                break;
            case 4:
                printf("Deletar produto selecionado.\n");
                // Chamar funcao para deletar produto
                break;
            case 5:
                printf("Saindo do programa.\n");
                break;
        }


    } while (resposta != 5);

    return  0;
}

// Implementacao da funcao para cadastrar produtos 
void cadastrarProduto(Tproduto produtos []){
    int i = 0;
    do {
    printf("Insira o nome do produto %d (Digite ""0"" para terminar o cadastro): ", i+1);
    fgets(produtos[i].nome, 100, stdin);
    while (getchar() != '\n');
    if (!(strcmp(produtos[i].nome, "0\n"))) {
        return;
    }
    else {
        printf("Insira o preco do produto: ");
        scanf("%f", &produtos[i].preco);
        while (getchar() != '\n');
        printf("Insira a quantidade do produto: ");
        scanf("%d", &produtos[i].quantidade);
        while (getchar() != '\n');
        produtos[i].id = i + 1;
        i++;
        getchar();
    }
    } while (i < 100);
}



Tproduto atualizarEstoque(Tproduto produtos){
    return produtos;
}