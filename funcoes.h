#ifndef FUNCOES_H
#define FUNCOES_H

//=================INICIO DO ARQUIVO==============================================
#define MAX_NOTI 3 //maximo de notificações diferentes
typedef void(*notificar)(const char*); //tipo 'notificar' é uma função void que recebe char*.

//ESTRUTURAS:
typedef struct custom_noti{
    int option;
    char descricao[20];
    notificar alerta;
}custom_noti;

typedef struct
{
    int id;
    char nome[50];
    unsigned char status;
    float preco;
    int quantidade;
} Tproduto;

typedef struct Toferta{
    char vendedor[50];
    char nome[50];
    int qtd;
    float valor;
    struct Toferta* prox;
} Toferta;

//FUNCOES DO ESTOQUE: 
Tproduto* cadastrarProduto(Tproduto produto[]);
void listarProdutos(Tproduto produtos[]);
Tproduto atualizarEstoque(Tproduto produtos[]);
void deletarProduto(Tproduto[], int id);
int buscaProduto_ID(Tproduto[], int id); //Busca o produto por ID e retorna indice. "-1 = Produto nao encontrado"


//FUNCOES DE OFERTA:
void vendasMenu(Toferta*); //Função para executar e controlar o menu de vendas
void registrar_oferta(Toferta*);  //Parâmetro de entrada: ptr para cabeça da lista(preferencial criar no main)
void excluir_oferta(Toferta*);
void lista_ofertas(Toferta*);  //imprime todas as ofertas
void liberaLista(Toferta*);  //libera a lista inteira EXCETO A CABEÇA(liberar no main ou modificar função)Isso facilita reutilização da cabeça se necessário

//FUNCOES DE ALERTA.
void alerta_email(const char* msg);
void alerta_sistema(const char* msg);
void alerta_cel(const char* msg);
void registrar_alerta_custom(notificar, char*); //registra um alerta + uma descricao
void option_alerta_custom(void); //verifica se o usuario quer ou nao aquele alerta. Deve ser usada sempre imediatamente antes de notificar_all_custom
void notificar_all_custom(const char*); //Chama ou nao alguma funcao de alerta

extern int qtdProdutos; //Contador de produtos cadastrados (variavel global)

#endif