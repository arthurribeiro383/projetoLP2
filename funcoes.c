#define _GNU_SOURCE
#include "funcoes.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// Inicializacao de Var Globais
int qtdProdutos = 0;
int qtd_alertas = 0;
int qtd_ofertas = 0;
custom_noti noti_mod[MAX_NOTI];

// Funcoes de Interface
void limpaTela(void){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void cabecalho(void) {
    printf(COR_TITULO"┌─────────────────────────────────────────────────────┐\n"COR_RESET);
    printf(COR_TITULO"│        SISTEMA DE ESTOQUE - Fazenda Cacaueira       │\n"COR_RESET);
    printf(COR_TITULO"└─────────────────────────────────────────────────────┘\n\n"COR_RESET);
}

void Pause(void) {
    printf("\nPressione ENTER para continuar...");
    while (getchar() != '\n');
}

// Funcoes de Menu (Callbacks)

void acaoListar(void *produtos) {
    limpaTela();
    listarProdutos((Tproduto*)produtos);
}

void acaoAtualizar(void *data) {
    Tproduto *produtos = (Tproduto*) data;
    atualizarEstoque(produtos);
}

void acaoDeletar(void *data) {
    Tproduto *produtos = (Tproduto*) data;
    int id_del;
    printf("Insira o ID do produto a ser excluido: ");
    scanf("%d", &id_del);
    deletarProduto(produtos, id_del);
}

void acaoMenuVendas(void *data) {
    Toferta **cabeca = (Toferta**) data;
    vendasMenu(cabeca);
}

//================= PARTE DE PRODUTOS =================

Tproduto* cadastrarProduto(Tproduto* produtos)
{   
    char nome_temp[TAM_NOME];
    while (1)
    {
        printf("Insira o nome do produto %d (Digite ""0"" para terminar o cadastro): ", qtdProdutos+1);
        fgets(nome_temp, TAM_NOME, stdin);
        nome_temp[strcspn(nome_temp, "\n")] = 0;

        if (strcmp(nome_temp, "0") == 0) //se o digitador for 0, sai
        {
            limpaTela();
            break;
        }
        
        Tproduto* temp = realloc(produtos, (qtdProdutos + 1) * sizeof(Tproduto));
        if(!temp){
            fprintf(stderr, COR_ERRO"Erro de alocacao\n"COR_RESET);
            free(produtos);
            return NULL;
        }
        produtos = temp;
        
        strcpy(produtos[qtdProdutos].nome, nome_temp);
        
        printf("Insira o preco do produto (por arroba): ");
        scanf("%f", &produtos[qtdProdutos].preco);
        while (getchar() != '\n');

        printf("Insira a quantidade do produto: ");
        scanf("%d", &produtos[qtdProdutos].quantidade);
        if (produtos[qtdProdutos].quantidade == 0)
            produtos[qtdProdutos].status |= ESGOTADO; //marca como esgotado
        else
            produtos[qtdProdutos].status &= ~ESGOTADO; //desmarca como esgotado
        while (getchar() != '\n');

        produtos[qtdProdutos].id = qtdProdutos + 1;
        qtdProdutos++;

        printf(COR_OK "Produto cadastrado!\n" COR_RESET);
        printf("\n");
    }
    return produtos;

}

void listarProdutos(Tproduto *produtos) {
    if (qtdProdutos == 0) {
        printf(COR_ERRO "Nenhum produto cadastrado.\n" COR_RESET);
        return;
    }

    printf("Deseja ordenar a listagem? (0-Nao 1-Nome 2-Preco 3-Quantidade): ");
    int op;
    scanf("%d", &op);
    while (getchar() != '\n');

    // copia temporária
    Tproduto *temp = malloc(qtdProdutos * sizeof(Tproduto));
    if (!temp) {
        perror("malloc");
        return;
    }
    memcpy(temp, produtos, qtdProdutos * sizeof(Tproduto));
    
    switch (op)
    {
        case 1:
            qsort(temp, qtdProdutos, sizeof(Tproduto), cmpNome);
            break;
        case 2:
            qsort(temp, qtdProdutos, sizeof(Tproduto), cmpPreco);
            break;
        case 3:
            qsort(temp, qtdProdutos, sizeof(Tproduto), cmpQtd);
            break;
    }

    cabecalho();
    printf("ID  | Nome%-28s | Qtd  | Preco    | Status\n", "");
    printf("----+-------------------------------+------+----------+----------\n");

    // CHAMADA DA FUNÇÃO RECURSIVA 
    listarRecursivo(temp, 0, qtdProdutos);

    free(temp);
}

void listarRecursivo(Tproduto *produtos, int i, int total){
    if (i == total)
        return;

    printf("%-3d | %-29s | %4d | R$%7.2f | ",
           produtos[i].id,
           produtos[i].nome,
           produtos[i].quantidade,
           produtos[i].preco);

    if (produtos[i].status & ESGOTADO)
        printf(COR_ERRO "ESGOTADO" COR_RESET);
    else
        printf(COR_OK "DISPONIVEL" COR_RESET);

    printf("\n");

    listarRecursivo(produtos, i + 1, total);  // chamada recursiva
}


void atualizarEstoque(Tproduto *produtos)
{
    if (qtdProdutos == 0) {
        printf(COR_ERRO"Nenhum produto cadastrado.\n"COR_RESET);
        return;
    }

    int listar, idAtualizar, idEncontradoAtt, opc;
    printf("Deseja ver os produtos para obter o ID? (1-Sim / 0-Nao): ");
    scanf("%d", &listar);
    while (getchar() != '\n');

    while (listar < 0 || listar > 1)
    {
        printf("Resposta invalida. Tente novamente: ");
        scanf("%d", &listar);
    }

    if (listar == 1)
        listarProdutos(produtos);

    printf("Insira o ID do produto a ser atualizado: ");
    scanf("%d", &idAtualizar);
    while (getchar() != '\n');

    idEncontradoAtt = buscaProduto_ID(produtos, idAtualizar);
    if (idEncontradoAtt == -1){
        printf(COR_ERRO"Produto nao cadastrado!\n"COR_RESET);
        return;
    }

    printf("O que deseja atualizar no produto selecionado?\n");
    printf("1. Nome\n");
    printf("2. Preco\n");
    printf("3. Quantidade\n");
    printf("4. Tudo\n");
    printf("Escolha: ");
    scanf("%d", &opc);
    while (getchar() != '\n');

    while (opc < 1 || opc > 4)
    {
        printf(COR_ERRO"Resposta invalida. Tente novamente: "COR_RESET);
        scanf("%d", &opc);
        while (getchar() != '\n');
    }

    switch (opc)
    {
        case 1:
            printf("Insira o novo nome do produto: ");
            fgets(produtos[idEncontradoAtt].nome, TAM_NOME, stdin);
            produtos[idEncontradoAtt].nome[strcspn(produtos[idEncontradoAtt].nome, "\n")] = 0;
            break;
        
        case 2:
            printf("Insira o novo preco do produto(por @): ");
            scanf("%f", &produtos[idEncontradoAtt].preco);
            while (getchar() != '\n');
            break;
        
        case 3:
            printf("Insira a nova quantidade do produto: ");
            scanf("%d", &produtos[idEncontradoAtt].quantidade);
            while (getchar() != '\n');

            if (produtos[idEncontradoAtt].quantidade == 0)
                produtos[idEncontradoAtt].status |= ESGOTADO; //marca como esgotado
            else{
                produtos[idEncontradoAtt].status &= ~ESGOTADO;//desmarca como esgotado
                }
            break;
        
        case 4:
            while (getchar() != '\n');
            printf("Insira o novo nome do produto: ");
            fgets(produtos[idEncontradoAtt].nome, TAM_NOME, stdin);
            produtos[idEncontradoAtt].nome[strcspn(produtos[idEncontradoAtt].nome, "\n")] = 0;
            
            printf("Insira o novo preco do produto(por @): ");
            scanf("%f", &produtos[idEncontradoAtt].preco);
            while (getchar() != '\n');

            printf("Insira a nova quantidade do produto: ");
            scanf("%d", &produtos[idEncontradoAtt].quantidade);
            while (getchar() != '\n');
            if (produtos[idEncontradoAtt].quantidade == 0)
                produtos[idEncontradoAtt].status |= ESGOTADO; //marca como esgotado
            else{
                produtos[idEncontradoAtt].status &= ~ESGOTADO;//desmarca como esgotado
            }
            break;
    }
    printf(COR_OK"Atualizacao concluida. \n"COR_RESET);
}

void deletarProduto(Tproduto *vet, int id){
    if (qtdProdutos == 0){
        printf(COR_INFO "Nenhum produto para deletar. \n" COR_RESET);
        return;
    }
    //Faz a busca do indice do item a ser excluído
    int i_excl = buscaProduto_ID(vet, id);

    //código de erro = Produto nao cadastrado
    if(i_excl == -1)
        return;

    //Sobrescreve o produto a ser excluido pelos seguintes
    for(int i = i_excl; i < qtdProdutos-1; i++){
        vet[i] = vet[i+1];
        vet[i].id--;
    }

    
    qtdProdutos--; //Diminui 1 da quantidade total

    printf(COR_OK "Produto excluido com sucesso!\n" COR_RESET);
}

int buscaProduto_ID(Tproduto *vet, int id)
{
    int i;
    //Faz a busca pelo ID fornecido em todo o vetor
    for(i=0; i<qtdProdutos; i++){
        if(id == vet[i].id)
        {
            return i;
        }
    }
        printf(COR_ERRO "ID fornecido Nao Cadastrado\n" COR_RESET);
        return -1;
}

// Comparadores qsort
int cmpNome(const void *a, const void *b) {
    const Tproduto *p1 = a;
    const Tproduto *p2 = b;
    return strcmp(p1->nome, p2->nome);
}
int cmpPreco(const void *a, const void *b) {
    const Tproduto *p1 = a;
    const Tproduto *p2 = b;
    if (p1->preco < p2->preco)
        return -1;
    if (p1->preco > p2->preco)
        return 1;
    return 0;
}
int cmpQtd(const void *a, const void *b) {
    const Tproduto *p1 = a;
    const Tproduto *p2 = b;
    return (p1->quantidade - p2->quantidade);
}

//Funcoes de Oferta
void vendasMenu(Toferta** cabeca){
    int option=0;

    do{
        cabecalho();
        printf(COR_TITULO "======MENU DE VENDAS======\n" COR_RESET);
        printf("1. Registrar Oferta\n");
        printf("2. Excluir Oferta\n");
        printf("3. Mostrar Ofertas\n");
        printf("4. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &option);
        while (getchar() != '\n');

        switch(option){
            case 1:
                registrar_oferta(cabeca);
                break;
            case 2:
                excluir_oferta(cabeca);            
                break;
            case 3:
                lista_ofertas(*cabeca);
                break;
            case 4: 
                printf("Obrigado! Volte sempre!!!\n");
                return;
            default: 
                printf(COR_ERRO"Opcao invalida! Tente Novamente\n!"COR_RESET);
                break;
        }
        Pause();
    } while(option >= 1 && option <= 3);
}

void registrar_oferta(Toferta** head){
    Toferta* nova=malloc(sizeof(Toferta));
    if(!nova){
        perror("malloc");
        return;
    }

    char notificacao[256];

    printf("Insira o nome do produto: ");
    fgets(nova->nome, TAM_NOME, stdin);
    nova->nome[strcspn(nova->nome, "\n")] = '\0'; //tira o '\n'

    printf("Insira a quantidade de itens da oferta: ");
    scanf("%d", &nova->qtd);

    printf("Insira o valor da oferta: ");
    scanf("%f", &nova->valor);
    while (getchar() != '\n');

    nova->prox = *head; //adiciona 'nova' depois da cabeça
    *head = nova;  //liga 'cabeça' à 'nova'

    snprintf(notificacao, sizeof(notificacao), "Nova oferta adicionada\n    Nome->%49s\n    Quantidade->%d\n    Valor->%.2f\n", nova->nome, nova->qtd, nova->valor);
    option_alerta_custom();
    notificar_all_custom(notificacao);

    printf(COR_OK "Oferta registrada!\n" COR_RESET);
    qtd_ofertas++;
}

void excluir_oferta(Toferta** head){
    Toferta* ant=NULL;
    Toferta* p=*head;
    char notificacao[170];
    char nome[TAM_NOME];

    if(p == NULL){
        printf("Lista vazia!\n");
        return;
    }

    printf("Insira o nome do produto a ser excluido(exatamente igual a lista): ");
    fgets(nome, TAM_NOME, stdin);
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

    snprintf(notificacao, sizeof(notificacao), "Oferta esgotada\n    Nome->%49s\n    Quantidade->%d\n    Valor->%.2f\n", p->nome, p->qtd, p->valor); //nesse momento p é p nó a ser excluído
    option_alerta_custom();
    notificar_all_custom(notificacao);

    if(ant == NULL){//primeiro no
        *head = p->prox; //proximo depois da cabeça
    }
    else{
        ant->prox = p->prox; //só é executado se alista não chegou ao fim(evitar segmentation fault)
    }
    free(p);
    qtd_ofertas--;

    printf(COR_OK "Oferta excluída!\n" COR_RESET);
}

void lista_ofertas(Toferta* p){
    int i;
    printf(COR_TITULO "\n======LISTA DE OFERTAS=====\n" COR_RESET);

    for(i=0; p != NULL; i++, p = p->prox){
        printf("[%d] Nome: %s | Qtd: %d | Valor: %.2f\n",i+1, p->nome, p->qtd, p->valor);
    }

    printf(COR_TITULO "=====FIM DAS OFERTAS=====\n\n" COR_RESET);
}

void liberaLista(Toferta* p){
    Toferta* liberar=NULL;
    while(p!=NULL){
        liberar = p;
        p = p->prox;
        free(liberar);
    }
}

Toferta* listaEmVet(Toferta* p){
    if(qtd_ofertas == 0){
        // Removido o print para não poluir a saída ao sair do programa
        return NULL;
    }
    Toferta* vetor = malloc(qtd_ofertas*sizeof(Toferta));
    for(int i=0; i<qtd_ofertas; i++){
        vetor[i] = *p;
        p=p->prox;
    }
    return vetor;
}

void vetEmLista(Toferta* vet, Toferta** head){
    // Correção: Loop reverso para manter a ordem da lista ligada original
    for(int i = qtd_ofertas - 1; i >= 0; i--){
        Toferta* novo = malloc(sizeof(Toferta));
        *novo = vet[i];
        novo->prox = *head;
        *head = novo;
    }
}

// Funcoes de Alerta

void alerta_email(const char* msg){
    // Texto padronizado
    printf("\nEmail enviado automaticamente para confirmacao (Todos)\n%s\n", msg);
}

void alerta_sistema(const char* msg){
    printf("\nATENCAO: Notificacao de sistema\n%s\n", msg);
}

void alerta_cel(const char* msg){
    printf("\nMensagem automatica enviada para todos os celulares cadastrados\n%s\n", msg);
}

void registrar_alerta_custom(notificar reg, char* descri){
    if(qtd_alertas >= MAX_NOTI){
        printf("Quantidade maxima de alertas excedida!\n");
        return;
    }
    noti_mod[qtd_alertas].alerta = reg;
    strcpy(noti_mod[qtd_alertas].descricao, descri);
    qtd_alertas++;
}

void option_alerta_custom(void){
    for(int i=0; i<qtd_alertas; i++){
        printf("-->Deseja enviar notificacao para %s (1 para sim, 0 para nao)? ", noti_mod[i].descricao);
        scanf("%d", &noti_mod[i].option);
    }
}

void notificar_all_custom(const char* msg){
    for(int i=0; i<qtd_alertas; i++){
        if(noti_mod[i].option) noti_mod[i].alerta(msg);
    }
}

//Funcoes de Arquivo
void grava_vet(void* vet, const char* arq, int size_elem, int* tam){
    FILE* file=fopen(arq, "wb");
    if(file==NULL){
        printf("ERRO ao gravar arquivo binário!\n");
        return;
    }

    fwrite(vet, size_elem, (*tam), file);
    fclose(file);
}

void* resgata_vet(const char* arq, int size_elem, int* tam){
    void* vet = NULL;
    
    FILE* file=fopen(arq, "ab");  //abre e fecha arquivo com append para garantir existência
    if(file==NULL){
        printf("ERRO ao abrir/criar arquivo binário!\n");
        return NULL;
    }
    fclose(file); 

    file=fopen(arq, "rb");
    if(file==NULL){
        printf("ERRO ao ler arquivo binário!\n"); // Correção: Era "gravar" no original
        return NULL;
    }

    while(1){
        char aux[size_elem]; // Buffer temporário do tamanho do elemento

        //casting para algo que tem 1 byte para usar aritmética
        if(fread(aux, size_elem, 1, file) != 1) break;

        void* temp = realloc(vet, ((*tam)+1)*size_elem);
        if(temp == NULL){
            printf("Erro ao alocar memoria\n");
            free(vet);
            fclose(file);
            return NULL;
        }
        vet = temp;

        for(int i=0; i<size_elem; i++){
            ((char*)vet)[*tam * size_elem + i] = aux[i];
        }

        (*tam)++;
    }
    
    fclose(file);
    return vet;
}
void salvarProdutosCSV(const char *nomeArq, Tproduto *produtos) {
    FILE *f = fopen(nomeArq, "w");
    if (!f) {
        perror("fopen");
        return;
    }

    for (int i = 0; i < qtdProdutos; i++) {
        fprintf(f, "%d;%s;%d;%.2f;%u\n",produtos[i].id,produtos[i].nome,produtos[i].quantidade,produtos[i].preco,(unsigned int)produtos[i].status);
    }

    fclose(f);
    printf(COR_OK "Dados salvos em %s\n" COR_RESET, nomeArq);
}

Tproduto* carregarProdutosCSV(const char *nomeArq) {
    FILE *f = fopen(nomeArq, "r");
    if (!f) 
        return NULL;
    
    Tproduto *produtos = NULL;
    char linha[256];
    while (fgets(linha, sizeof(linha), f)) {
        produtos = realloc(produtos, (qtdProdutos + 1) * sizeof(Tproduto));
        if (!produtos){
            perror("realloc");
            exit(1);
        }

        unsigned int status;
        sscanf(linha, "%d;%49[^;];%d;%f;%u",&produtos[qtdProdutos].id,produtos[qtdProdutos].nome,&produtos[qtdProdutos].quantidade,&produtos[qtdProdutos].preco,&status);
        produtos[qtdProdutos].status = (unsigned char)status;
        qtdProdutos++;
    }
    fclose(f);
    return produtos;
}