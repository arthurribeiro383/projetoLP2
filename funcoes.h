#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//================= DEFINICOES E MACROS =================
#define ESGOTADO 1
#define MAX_NOTI 3 //maximo de notificações diferentes

// Cores para interface
#define COR_RESET  "\033[0m"
#define COR_TITULO "\033[1;36m"
#define COR_MENU   "\033[1;33m"
#define COR_OK     "\033[1;32m"
#define COR_ERRO   "\033[1;31m"
#define COR_INFO   "\033[1;34m"

//================= TIPOS E ESTRUTURAS =================
typedef void(*notificar)(const char*); //tipo 'notificar' é uma função void que recebe char*.

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

typedef void (*Callback)(void*);

//================= VARIAVEIS GLOBAIS (EXTERN) =================
extern int qtdProdutos;
extern int qtd_alertas;
extern int qtd_ofertas;
extern custom_noti noti_mod[MAX_NOTI];

//================= PROTOTIPOS DE FUNCOES =================

// Funcoes de Interface
void limpaTela(void);
void cabecalho(void);

// Funcoes de Menu (Callbacks)
void acaoListar(void *data);
void acaoAtualizar(void *data);
void acaoDeletar(void *data);
void acaoMenuVendas(void *data);

// Funcoes de Estoque
Tproduto* cadastrarProduto(Tproduto* produtos);
void listarProdutosRecursivo(Tproduto produtos[], int indice);
void atualizarEstoque(Tproduto produtos[]);
void deletarProduto(Tproduto vet[], int id);
int buscaProduto_ID(Tproduto vet[], int id);

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

// Utilitarios
void substituirVirgulaPorPonto(char *str);

#endif