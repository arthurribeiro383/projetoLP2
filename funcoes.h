#ifndef FUNCOES_H
#define FUNCOES_H

//=================INICIO DO ARQUIVO==============================================
#define ESGOTADO 1
#define MAX_NOTI 3 //maximo de notificações diferentes
typedef void(*notificar)(const char*); //tipo 'notificar' é uma função void que recebe char*.

//Variaveis globais:
extern int qtdProdutos; //Contador de produtos cadastrados (variavel global)
extern int qtd_alertas; //serve para ambos os sistemas de notificação

//ESTRUTURAS:
typedef struct custom_noti{
    int option;
    char descricao[20];
    notificar alerta;
}custom_noti;

extern custom_noti noti_mod[MAX_NOTI];  //sistema custom de notificações

typedef struct
{
    int id;
    char nome[50];
    unsigned char status;
    float preco;
    int quantidade;
} Tproduto;

typedef struct Toferta{
    char nome[50];
    int qtd;
    float valor;
    struct Toferta* prox;
} Toferta;

//FUNCOES DO ESTOQUE: 
Tproduto* cadastrarProduto(Tproduto produto[]);
void listarProdutosRecursivo(Tproduto produtos[], int indice);
void atualizarEstoque(Tproduto produtos[]);
void deletarProduto(Tproduto[], int id);
int buscaProduto_ID(Tproduto[], int id); //Busca o produto por ID e retorna indice. "-1 = Produto nao encontrado"


//FUNCOES DE OFERTA:
void vendasMenu(Toferta*); //Função para executar e controlar o menu de vendas
void registrar_oferta(Toferta*);  //Parâmetro de entrada: ptr para cabeça da lista(preferencial criar no main)
void excluir_oferta(Toferta*);
void lista_ofertas(Toferta*);  //imprime todas as ofertas
void liberaLista(Toferta*);  //libera a lista inteira EXCETO A CABEÇA(liberar no main ou modificar função)Isso facilita reutilização da cabeça se necessário

//FUNCOES DE ALERTA:
void alerta_email(const char* msg);
void alerta_sistema(const char* msg);
void alerta_cel(const char* msg);
void registrar_alerta_custom(notificar, char*); //registra um alerta + uma descricao
void option_alerta_custom(void); //verifica se o usuario quer ou nao aquele alerta. Deve ser usada sempre imediatamente antes de notificar_all_custom
void notificar_all_custom(const char*); //Chama ou nao alguma funcao de alerta

//Funcoes de Interface.
#define COR_RESET  "\033[0m"
#define COR_TITULO "\033[1;36m"
#define COR_MENU   "\033[1;33m"
#define COR_OK     "\033[1;32m"
#define COR_ERRO   "\033[1;31m"
#define COR_INFO   "\033[1;34m"
void limpaTela(void);
void cabecalho(void);

//Funcoes para tirar o switch case
// Protótipos das funções de menu
void acaoListar(void *data);
void acaoAtualizar(void *data);
void acaoDeletar(void *data);
void acaoMenuVendas(void *data);

typedef void (*Callback)(void*);


#endif