#ifndef FUNCOES_H
#define FUNCOES_H

#define MAX_NOTI 3 //maximo de notificações diferentes
typedef void(*notificar)(const char*); //tipo 'notificar' é uma função void que recebe char*.

/*
Por enquanto os alertas estão sendo enviados para todos
Ainda estou pensando numa maneira de especificar(ex: "Olá 'fulano de tal'. Temos uma novidade...")
para emails personalizados
Podemos fazer algo como: "Deseja receber emails?"
*/

//FUNCOES DE ALERTA___________________________
void alerta_email(const char* msg);
void alerta_sistema(const char* msg);
void alerta_cel(const char* msg);
void registrar_alerta(notificar reg);
void notificar_all(notificar*, const char*);
//____________________________________________

typedef struct Toferta{
    char nome[50];
    int qtd;
    float valor;
    struct Toferta* prox;
} Toferta;


void registrar_oferta(Toferta*);  //parametros:  ptr para cabeca
void registrar_oferta_teste(Toferta* head, char* nome, int qtd, float valor);
void excluir_oferta_teste(Toferta*, const char*);   //parametros:  ptr para cabeca / nome do prod a ser excluido
void excluir_oferta(Toferta*);
void lista_ofertas(Toferta*);  //imprime todas as ofertas
void liberaLista(Toferta*);  //libera a lista inteira EXCETO A CABEÇA(liberar no main ou modificar função)Isso facilita reutilização da cabeça se necessário

#endif