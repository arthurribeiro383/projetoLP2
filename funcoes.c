#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

//FUNCOES DE INTERFACE
void limpaTela(void){
    if (_WIN32)
        system("cls");
    else
        system("clear");
}

void cabecalho(void){
    printf(COR_TITULO "========================================\n" COR_RESET);
    printf(COR_TITULO "         SISTEMA DE ESTOQUE\n" COR_RESET);
    printf(COR_TITULO "========================================\n\n" COR_RESET);
}

//Inicializacao de Var Globais
int qtdProdutos = 0;
int qtd_alertas = 0;
custom_noti noti_mod[MAX_NOTI];

//LOGICA PRINCIPAL DO PROGRAMA
    //PARTE DE PRODUTOS

Tproduto* cadastrarProduto(Tproduto* produtos)
{   char nome_temp[50];
    while (1)
    {

        printf("Insira o nome do produto %d (Digite ""0"" para terminar o cadastro): ", qtdProdutos+1);
        fgets(nome_temp, 50, stdin);
        nome_temp[strcspn(nome_temp, "\n")] = 0;

        if (strcmp(nome_temp, "0") == 0) //se o digitador for 0, sai
        {
            limpaTela();
            break;
        }
        
        Tproduto* temp = realloc(produtos, (qtdProdutos+1)*sizeof(Tproduto));
        if(temp == NULL){
            fprintf(stderr, COR_ERRO"Alocação de vetor inválida: Encerrando Programa\n" COR_RESET);
            free(produtos);
            return NULL;
        }
        produtos = temp;
        
        strcpy(produtos[qtdProdutos].nome, nome_temp);
        

        printf("Insira o preco do produto(por @): ");
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
        qtdProdutos++; //incrementa qtd de produtos

        printf(COR_OK "Produto cadastrado!\n" COR_RESET);
        printf("\n");
    }
    return produtos;
}


void listarProdutosRecursivo(Tproduto *produtos, int i) {

    if (qtdProdutos == 0) {
        printf(COR_ERRO "Nenhum produto cadastrado.\n" COR_RESET);
        return;
    }

    if (i == 0) {
        printf(COR_TITULO "Lista de produtos:\n\n" COR_RESET);

        printf("%-4s | %-30s | %-6s | %-8s | %-10s\n",
               "ID", "Nome", "Qtd", "Preco", "Status");

        printf("-----+--------------------------------+-------+----------+------------\n");
    }

    if (i >= qtdProdutos) {
        return;
    }

    printf("%-4d | %-30s | %-6d | R$%6.2f | ",
           produtos[i].id,
           produtos[i].nome,
           produtos[i].quantidade,
           produtos[i].preco);

    if (produtos[i].status & ESGOTADO)
        printf(COR_ERRO "ESGOTADO" COR_RESET "\n");
    else
        printf(COR_OK "DISPONIVEL" COR_RESET "\n");

    // Chamada recursiva
    listarProdutosRecursivo(produtos, i + 1);
}



// Implementacao da funcao para atualizar estoque
void atualizarEstoque(Tproduto produtos[])
{
    int respostaParaListagemAtt, idParaAtualizar, idEncontradoAtt, selecaoFuncaoAtualizar;
    printf("Deseja listar os produtos cadastrados para adiquirir o id do produto a ser atualizado? (1-Sim / 0-Nao): ");
                scanf("%d", &respostaParaListagemAtt);
                while (respostaParaListagemAtt < 0 || respostaParaListagemAtt > 1)
                {
                    printf("Resposta invalida. Tente novamente: ");
                    scanf("%d", &respostaParaListagemAtt);
                }

                switch (respostaParaListagemAtt)
                {
                    case 1:
                        printf("\nListagem de produtos:\n");
                        listarProdutosRecursivo(produtos, 0);
                        break;
                    case 0:
                        break;
                }

                printf("Insira o ID do produto a ser atualizado: ");
                scanf("%d", &idParaAtualizar);
                idEncontradoAtt = buscaProduto_ID(produtos, idParaAtualizar);
                if (idEncontradoAtt == -1) 
                    return;

                printf("O que deseja atualizar no produto selecionado?\n");
                printf("1. Nome\n");
                printf("2. Preco\n");
                printf("3. Quantidade\n");
                printf("4. Tudo\n");
                printf("Escolha: ");
                scanf("%d", &selecaoFuncaoAtualizar);
                while (selecaoFuncaoAtualizar < 1 || selecaoFuncaoAtualizar > 4)
                {
                    printf("Resposta invalida. Tente novamente: ");
                    scanf("%d", &selecaoFuncaoAtualizar);
                }

                switch (selecaoFuncaoAtualizar)
                {
                    case 1:
                        while (getchar() != '\n');
                        printf("Insira o novo nome do produto: ");
                        fgets(produtos[idEncontradoAtt].nome, 50, stdin);
                        produtos[idEncontradoAtt].nome[strcspn(produtos[idEncontradoAtt].nome, "\n")] = 0;
                        printf("Nome atualizado com sucesso!\n");
                        break;
                    
                    case 2:
                        printf("Insira o novo preco do produto(por @): ");
                        scanf("%f", &produtos[idEncontradoAtt].preco);
                        printf("Preco atualizado com sucesso!\n");
                        break;
                    
                    case 3:
                        printf("Insira a nova quantidade do produto: ");
                        scanf("%d", &produtos[idEncontradoAtt].quantidade);
                         if (produtos[idEncontradoAtt].quantidade == 0)
                            produtos[idEncontradoAtt].status |= ESGOTADO; //marca como esgotado
                        else{
                            produtos[idEncontradoAtt].status &= ~ESGOTADO;//desmarca como esgotado
                            }
                        printf("Quantidade atualizada com sucesso!\n");
                        break;
                    
                    case 4:
                        while (getchar() != '\n');
                        printf("Insira o novo nome do produto: ");
                        fgets(produtos[idEncontradoAtt].nome, 50, stdin);
                        produtos[idEncontradoAtt].nome[strcspn(produtos[idEncontradoAtt].nome, "\n")] = 0;
                        
                        printf("Insira o novo preco do produto(por @): ");
                        scanf("%f", &produtos[idEncontradoAtt].preco);
                        
                        printf("Insira a nova quantidade do produto: ");
                        scanf("%d", &produtos[idEncontradoAtt].quantidade);
                        if (produtos[idEncontradoAtt].quantidade == 0)
                            produtos[idEncontradoAtt].status |= ESGOTADO; //marca como esgotado
                        else{
                            produtos[idEncontradoAtt].status &= ~ESGOTADO;//desmarca como esgotado
                        }
                        printf("Produto atualizado com sucesso!\n");
                        break;
                }
}

int buscaProduto_ID(Tproduto vet[], int id)
{
    int i, achou=0;

    //Faz a busca pelo ID fornecido em todo o vetor
    for(i=0; i<qtdProdutos; i++)
    {
        if(id == vet[i].id)
        {
            achou = 1;
            break;
        }
    }
    //Retorna o indice do ID fornecido ou codigo de erro(-1)
    if(achou)
    {
        return i;
    }
    else
    {
        printf(COR_ERRO "ID fornecido Nao Cadastrado\n" COR_RESET);
        return -1;
    }
}

void deletarProduto(Tproduto vet[], int id)
{
    //Faz a busca do indice do item a ser excluído
    int i_excl=buscaProduto_ID(vet, id);

    //código de erro = Produto nao cadastrado
    if(i_excl == -1)
    {
        return;
    }

    //Sobrescreve o produto a ser excluido pelos seguintes
    for(int i=i_excl; i<qtdProdutos-1; i++)
    {
        vet[i] = vet[i+1];
        vet[i].id--;
    }
    //Diminui 1 da quantidade total
    qtdProdutos--;
    printf(COR_OK "Produto excluido com sucesso!\n" COR_RESET);
}

void vendasMenu(Toferta* cabeca){
    int option=0;

    do{
    cabecalho();
    printf(COR_TITULO "======MENU DE VENDAS======\n" COR_RESET);
        printf("1. Registrar Oferta\n");
        printf("2. Excluir Oferta\n");
        printf("3. Mostrar Ofertas\n");
        printf("4. Sair\n");
        printf("Selecione opcao desejada: ");
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
            lista_ofertas(cabeca);
            break;
        case 4: 
            printf("Obrigado! Volte sempre!!!\n");
            return;
        default: 
            printf("Opcao invalida! Tente Novamente\n!");
            break;
    }

    }while(option >= 1 && option <= 3);
}

void registrar_oferta(Toferta* head){
    Toferta* nova=malloc(sizeof(Toferta));
    if(!nova){
        perror("malloc");
        return;
    }

    char notificacao[120];

    printf("Insira o nome do produto: ");
    fgets(nova->nome, 50, stdin);
    nova->nome[strcspn(nova->nome, "\n")] = '\0'; //tira o '\n'

    printf("Insira a quantidade de itens da oferta: ");
    scanf("%d", &nova->qtd);

    printf("Insira o valor da oferta: ");
    scanf("%f", &nova->valor);
    while (getchar() != '\n');

    nova->prox = head->prox; //adiciona 'nova' depois da cabeça
    head->prox = nova;  //liga 'cabeça' à 'nova'

    snprintf(notificacao, 120, "Nova oferta adicionada\n    Nome->%s\n    Quantidade->%d\n    Valor->%.2f\n", nova->nome, nova->qtd, nova->valor);
    option_alerta_custom();
    notificar_all_custom(notificacao);

    printf(COR_OK "Oferta registrada!\n" COR_RESET);
}

void excluir_oferta(Toferta* p){
    Toferta* ant=p;
    p=p->prox;
    char notificacao[170];
    char nome[50];

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
    option_alerta_custom();
    notificar_all_custom(notificacao);

    ant->prox = p->prox; //só é executado se alista não chegou ao fim(evitar segmentation fault)
    free(p);

    printf(COR_OK "Oferta excluída!\n" COR_RESET);

}

void lista_ofertas(Toferta* p){
    int i;
    printf(COR_TITULO "\n======INICIO DA LISTA=====\n" COR_RESET);

    for(i=0, p=p->prox ; p != NULL; i++, p = p->prox){

        printf("======Lista[%d]======\n"
            "\tqtd: %d\n"
            "\tValor: %.2f\n"
            "\tNome: %s\n" , i+1, p->qtd, p->valor, p->nome);
            printf("\n");
    }

    printf(COR_TITULO "=====FIM DA LISTA=====\n\n" COR_RESET);
}

void liberaLista(Toferta* p){
    Toferta* liberar=NULL;
    p=p->prox;  //tirar(ou comentar, em caso de testes) ESSA linha para liberar cabeça também
    while(p!=NULL){
        liberar = p;
        p = p->prox;
        free(liberar);
    }
}

void alerta_email(const char* msg){
    printf("\nEmail enviado automaticamente para todos\n%s\n", msg);
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

void acaoListar(void *data) {
    limpaTela();
    listarProdutosRecursivo((Tproduto*)data, 0);
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
    Toferta *cabeca = (Toferta*) data;
    vendasMenu(cabeca);
}
