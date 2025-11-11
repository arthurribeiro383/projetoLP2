#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"funcoes.h"

//========Variáveis globais=========
int qtd_alertas=0;
notificar alertas[MAX_NOTI];
//==================================
void vendasMenu(Toferta* cabeca){
    int option=0;

    do{
    printf("======MENU DE VENDAS======\n"
        "\t-> Sempre que uma oferta e excluido ou adicionada uma notificacao e enviada para todos\n"
        "1. Registrar Oferta\n"
        "2. Excluir Oferta\n"
        "3. Mostrar Ofertas\n"
        "4. Sair do Menu de Vendas\n");
    printf("Selecione opcao desejada: ");
    scanf("%d", &option);

    switch(option){
        case 1:
            registrar_oferta(cabeca);
            break;
        case 2:
            excluir_oferta(cabeca);            
            break;
        case 3:
            lista_ofertas(cabeca);
            break;
        case 4: 
            printf("Obrigado! Volte sempre!!!\n");
            return;
            //caso de saída do menu --> ainda a implementar --> depende do jeito que a função for utilizada
        default: 
            printf("Opcao invalida! Tente Novamente\n!");
            break;
    }

    }while(option > 0 || option < 5);
}

int main(void){
    Toferta* cabeca=malloc(sizeof(Toferta)); //cabeça sentinela SEMPRE
    cabeca->prox = NULL;

    registrar_alerta(alerta_cel);
    registrar_alerta(alerta_email);
    registrar_alerta(alerta_sistema);
/*
    registrar_oferta_teste(cabeca, "Laranjeiras", 15, 85.34);
    registrar_oferta_teste(cabeca, "Limoes", 47, 94.99);
    registrar_oferta_teste(cabeca, "Acucares(kg)", 9, 52.34);
    registrar_oferta_teste(cabeca, "Cafe(pcts)", 8, 32.60);
    lista_ofertas(cabeca);
    printf("\n");

    printf("\n\nQTD de alertas: %d\n\n", qtd_alertas);

    excluir_oferta_teste(cabeca, "Acucares(kg)");
    lista_ofertas(cabeca);
    printf("\n");
*/

    vendasMenu(cabeca);

    liberaLista(cabeca);
    free(cabeca);
    system("PAUSE");
    return 0;
}