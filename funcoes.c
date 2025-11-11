#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"funcoes.h"


extern int qtdProdutos; //Contador de produtos cadastrados (variavel global)
extern int qtd_alertas; //serve para ambos os sistemas de notificação
extern custom_noti noti_mod[MAX_NOTI];  //sistema custom de notificações


// Implementacao da funcao para cadastrar produtos 
Tproduto* cadastrarProduto(Tproduto* produtos)
{   char nome_temp[50];
    while (1)
    {

        printf("Insira o nome do produto %d (Digite ""0"" para terminar o cadastro): ", qtdProdutos+1);

        fgets(nome_temp, 50, stdin);
        nome_temp[strcspn(nome_temp, "\n")] = 0;

        if (strcmp(nome_temp, "0") == 0) //se o digitador for 0, sai
        {
            break;
        }
        
        Tproduto* temp = realloc(produtos, (qtdProdutos+1)*sizeof(Tproduto));
        if(temp == NULL){
            printf("Alocação de vetor inválida: Encerrando Programa\n");
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

        printf("\n");
    }
    return produtos;
}

// Implementacao da funcao para listar produtos
void listarProdutos(Tproduto produtos[])
{
    printf("Listagem de produtos.\n");
    printf("_______________________\n");
    for (int i = 0; i < qtdProdutos; i++)
    {
        printf("ID: %d\n", produtos[i].id);
        printf("Nome: %s\n", produtos[i].nome);
        printf("Preco: %.2f\n", produtos[i].preco);
        printf("Quantidade: %d\n", produtos[i].quantidade);
        printf("_______________________\n");
    }
}

// Implementacao da funcao para atualizar estoque
Tproduto atualizarEstoque(Tproduto produtos[])
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
                        listarProdutos(produtos);
                        break;
                    case 0:
                        break;
                }

                printf("Insira o ID do produto a ser atualizado: ");
                scanf("%d", &idParaAtualizar);
                idEncontradoAtt = buscaProduto_ID(produtos, idParaAtualizar);

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

    return produtos[idEncontradoAtt];
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
        printf("ID fornecido Nao Cadastrado\n");
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
    printf("Produto excluido com sucesso!\n");
}

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
        default: 
            printf("Opcao invalida! Tente Novamente\n!");
            break;
    }

    }while(option > 0 || option < 5);
}

void registrar_oferta(Toferta* head){
    Toferta* nova=malloc(sizeof(Toferta));
    char notificacao[120];

    getchar(); //consome buffer de entrada
    printf("Insira o nome do produto: ");
    fgets(nova->nome, 50, stdin);
    nova->nome[strcspn(nova->nome, "\n")] = '\0'; //tira o '\n'

    printf("Insira o nome do vendedor: ");
    fgets(nova->vendedor, 50, stdin);
    nova->vendedor[strcspn(nova->vendedor, "\n")] = '\0'; //tira o '\n'


    printf("Insira a quantidade de itens da oferta: ");
    scanf("%d", &nova->qtd);

    printf("Insira o valor da oferta: ");
    scanf("%f", &nova->valor);

    nova->prox = head->prox; //adiciona 'nova' depois da cabeça
    head->prox = nova;  //liga 'cabeça' à 'nova'

    snprintf(notificacao, 120, "Nova oferta adicionada\n    Nome->%s\n    Quantidade->%d\n    Valor->%.2f\n", nova->nome, nova->qtd, nova->valor);
    option_alerta_custom();
    notificar_all_custom(notificacao);

}

void excluir_oferta(Toferta* p){
    Toferta* ant=p;
    p=p->prox;
    char notificacao[170];
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
    option_alerta_custom();
    notificar_all_custom(notificacao);

    ant->prox = p->prox; //só é executado se alista não chegou ao fim(evitar segmentation fault)
    free(p);

}

void lista_ofertas(Toferta* p){
    int i;
    printf("\n======INICIO DA LISTA=====\n");

    for(i=0, p=p->prox ; p != NULL; i++, p = p->prox){

        printf("======Lista[%d]======\n"
            "\tqtd: %d\n"
            "\tValor: %.2f\n"
            "\tNome: %s\n" 
            "\tVendedor: %s\n", i+1, p->qtd, p->valor, p->nome, p->vendedor);
            printf("\n");
    }

    printf("=====FIM DA LISTA=====\n\n");
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
    printf("Email enviado automaticamente para todos\n%s\n", msg);
}

void alerta_sistema(const char* msg){
    printf("ATENCAO: Notificacao de sistema\n%s\n", msg);
}

void alerta_cel(const char* msg){
    printf("Mensagem automatica enviada para todos os celulares cadastrados\n%s\n", msg);
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
        printf("Deseja enviar notificacao para %s (1 para sim, 0 para nao)? ", noti_mod[i].descricao);
        scanf("%d", &noti_mod[i].option);
    }
}

void notificar_all_custom(const char* msg){
    for(int i=0; i<qtd_alertas; i++){
        if(noti_mod[i].option) noti_mod[i].alerta(msg);
    }
}
