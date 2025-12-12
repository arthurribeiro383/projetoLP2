#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>

// Definições e macros
#define ESGOTADO 1 // 0000 0001
#define MAX_NOTI 3 //maximo de notificações diferentes
#define TAM_NOME 50

// Cores para interface
#define COR_RESET  "\x1b[0m"
#define COR_TITULO "\x1B[36m"
#define COR_MENU   "\x1b[34m"
#define COR_OK     "\x1b[32m"
#define COR_INFO   "\x1b[33m"
#define COR_ERRO   "\x1b[31m"

// Menu Callback
typedef void(*notificar)(const char*); //tipo 'notificar' é uma função void que recebe char*.
typedef void (*Callback)(void*);

// Tipos e Estruturas

typedef struct custom_noti{
    int option;
    char descricao[20];
    notificar alerta;
} custom_noti;

typedef struct {
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

// VARIAVEIS GLOBAIS (EXTERN)
extern int qtdProdutos;
extern int qtd_alertas;
extern int qtd_ofertas;
extern custom_noti noti_mod[MAX_NOTI];

// Funcoes de Interface
void limpaTela(void);
void cabecalho(void);
void Pause (void);

// Funcoes de Menu (Callbacks)
void acaoListar(void *produtos);
void acaoAtualizar(void *data);
void acaoDeletar(void *data);
void acaoMenuVendas(void *data);

// Funcoes de Estoque
Tproduto* cadastrarProduto(Tproduto* produtos);
void listarProdutos(Tproduto *produtos);
void listarRecursivo(Tproduto *produtos, int i, int total);
void atualizarEstoque(Tproduto *produtos);
void deletarProduto(Tproduto vet[], int id);
int buscaProduto_ID(Tproduto vet[], int id);

// Funcoes Comparadoras para o Qsort
int cmpNome(const void *a, const void *b);
int cmpPreco(const void *a, const void *b);
int cmpQtd(const void *a, const void *b);

// Funcoes de Oferta
void vendasMenu(Toferta** cabeca);
void registrar_oferta(Toferta** head);
void excluir_oferta(Toferta** head);
void lista_ofertas(Toferta* p);
void liberaLista(Toferta* p);
Toferta* listaEmVet(Toferta* p);
void vetEmLista(Toferta* vet, Toferta** head);

// Funcoes de Alerta
void alerta_email(const char* msg);
void alerta_sistema(const char* msg);
void alerta_cel(const char* msg);
void registrar_alerta_custom(notificar reg, char* descri);
void option_alerta_custom(void);
void notificar_all_custom(const char* msg);

// Funcoes de Arquivo
void grava_vet(void* vet, const char* arq, int size_elem, int* tam);
void* resgata_vet(const char* arq, int size_elem, int* tam);
void salvarProdutosCSV(const char *nomeArq, Tproduto *produtos);
Tproduto* carregarProdutosCSV(const char *nomeArq);

#endif