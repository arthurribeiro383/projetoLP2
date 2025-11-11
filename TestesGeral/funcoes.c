#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"funcoes.h"

extern int qtd_alertas;
extern notificar alertas[MAX_NOTI];

//==============FUNÇÕES RELACIONADAS ÀS OFERTAS ========================================================

void registrar_oferta_teste(Toferta* head, char* nome, int qtd, float valor){
    Toferta* nova=malloc(sizeof(Toferta));
    char notificacao[100];

    strcpy(nova->nome, nome); //copia de nome para nova
    nova->qtd = qtd;
    nova->valor = valor;

    nova->prox = head->prox; //adiciona 'nova' depois da cabeça
    head->prox = nova;  //liga 'cabeça' à 'nova'

    snprintf(notificacao, 100, "Nova oferta adicionada\n    Nome->%s\n    Quantidade->%d\n    Valor->%.2f\n", nome, qtd, valor);
    notificar_all(alertas, notificacao);

}

void registrar_oferta(Toferta* head){
    Toferta* nova=malloc(sizeof(Toferta));
    char notificacao[100];

    getchar(); //consome buffer de entrada
    printf("Insira o nome do produto: ");
    fgets(nova->nome, 50, stdin);
    nova->nome[strcspn(nova->nome, "\n")] = '\0'; //tira o '\n'

    printf("Insira a quantidade de itens da oferta: ");
    scanf("%d", &nova->qtd);

    printf("Insira o valor da oferta: ");
    scanf("%f", &nova->valor);

    nova->prox = head->prox; //adiciona 'nova' depois da cabeça
    head->prox = nova;  //liga 'cabeça' à 'nova'

    snprintf(notificacao, 100, "Nova oferta adicionada\n    Nome->%s\n    Quantidade->%d\n    Valor->%.2f\n", nova->nome, nova->qtd, nova->valor);
    notificar_all(alertas, notificacao);

}

void excluir_oferta(Toferta* p){
    Toferta* ant=p;
    p=p->prox;
    char notificacao[100];
    char nome[50];

    getchar(); //consome buffer de entrada
    printf("Insira o nome do produto a ser excluido(exatamente igual a lista): ");
    fgets(nome, 50, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    while(p!=NULL){ //avança até achar o nó a ser excluído (identificado pelo nome)
        if(strcmp(p->nome, nome) == 0) break;
        ant=p; //sempre guarda o que aponta pra p
        p=p->prox;
    }
    if(p==NULL){ //se o while finalizou pois chegou ao fim
        printf("Nome nao encontrado na lista\n");
        return;
    }

    snprintf(notificacao, 100, "Oferta esgotada\n    Nome->%s\n    Quantidade->%d\n    Valor->%.2f\n", p->nome, p->qtd, p->valor); //nesse momento p é p nó a ser excluído
    notificar_all(alertas, notificacao);

    ant->prox = p->prox; //só é executado se alista não chegou ao fim(evitar segmentation fault)
    free(p);

}

void excluir_oferta_teste(Toferta* p, const char* nome){
    Toferta* ant=p;
    p=p->prox;
    char notificacao[100];

    while(p!=NULL){ //avança até achar o nó a ser excluído (identificado pelo nome)
        if(strcmp(p->nome, nome) == 0) break;
        ant=p; //sempre guarda o que aponta pra p
        p=p->prox;
    }
    if(p==NULL){ //se o while finalizou pois chegou ao fim
        printf("Nome nao encontrado na lista\n");
        return;
    }

    snprintf(notificacao, 100, "Oferta esgotada\n    Nome->%s\n    Quantidade->%d\n    Valor->%.2f\n", p->nome, p->qtd, p->valor); //nesse momento p é p nó a ser excluído
    notificar_all(alertas, notificacao);

    ant->prox = p->prox; //só é executado se alista não chegou ao fim(evitar segmentation fault)
    free(p);

}

void lista_ofertas(Toferta* p){
    int i;
    printf("======INICIO DA LISTA=====\n");

    for(i=0, p=p->prox ; p != NULL; i++, p = p->prox){

        printf("======Lista[%d]======\n"
            "qtd: %d\n"
            "Valor: %.2f\n"
            "Nome: %s\n", i+1, p->qtd, p->valor, p->nome);
            printf("\n");
    }

    printf("=====FIM DA LISTA=====\n");
}

void liberaLista(Toferta* p){
    Toferta* liberar=NULL;
    p=p->prox;  //tirar(ou comentar, em caso de testes) ESSA linha para liberar cabeça também
    while(p!=NULL){
        liberar = p;
        p = p->prox;
        free(liberar);
    }
    printf("Lista liberada""\n");
}

//========FIM DAS FUNÇÕES DE OFERTAS=========================================================================

//========FUNÇÕES RELACIONADAS ÀS NOTIFICAÇÕES/ALERTAS=======================================================

void alerta_email(const char* msg){
    printf("Email enviado automaticamente para todos\n%s\n", msg);
}

void alerta_sistema(const char* msg){
    printf("ATENCAO: Notificacao de sistema\n%s\n", msg);
}

void alerta_cel(const char* msg){
    printf("Mensagem automatica enviada para todos os cadastrados\n%s\n", msg);
}

void registrar_alerta(notificar reg){;
    alertas[qtd_alertas++] = reg;
}

void notificar_all(notificar* vet, const char* msg){
    for(int i=0; i<qtd_alertas; i++){
        vet[i](msg);
    }
}