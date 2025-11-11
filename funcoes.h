#ifndef FUNCOES_H
#define FUNCOES_H

typedef struct
{
    int id;
    char nome[50];
    float preco;
    int quantidade;
} Tproduto;

extern int qtdProdutos; //Contador de produtos cadastrados (variavel global)


//______________________________________________________________________________________________________________________ 
//Protótipos das funções:
Tproduto* cadastrarProduto(Tproduto produto[]);
void listarProdutos(Tproduto produtos[]);
Tproduto atualizarEstoque(Tproduto produtos[]);
void deletarProduto(Tproduto[], int id);
int buscaProduto_ID(Tproduto[], int id); //Busca o produto por ID e retorna indice. "-1 = Produto nao encontrado"
//_______________________________________________________________________________________________________________________

#endif