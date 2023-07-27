#include <stdio.h>
#include <string.h>
#include "funcoes.h"
#include <stdlib.h>

void incluir(Raiz* raiz)
{
    Evento* novo = (Evento*)malloc(sizeof(Evento));
    novo->left = NULL;
    novo->right = NULL;
    novo->data = setdata(2);
    if (confData(novo->data) == -1) {
        printf("Data invalida.\n");
        free(novo);
        return;
    }
    printf("Duracao: (hh:mm)");
    scanf("%d:%d", &novo->duracaoh, &novo->duracaom);
    if((novo->duracaoh < 0 || novo->duracaoh >= 24) || (novo->duracaom < 0) || novo->duracaom > 60){
        printf("Duração invalida. \n");
        free(novo);
        return;
    }
    printf("Descricao: \n");
    scanf(" %[^\n]", novo->descricao);
    transformador(novo);
    if(busca(raiz->no, novo) != NULL) {
        printf("\nHorario ocupado!\n");
        free(novo);
        return;
        }
    else{
        if (raiz->no == NULL)
                raiz->no = novo;
        else
            raiz->no = adubo(raiz->no, novo);
        }
    
}   

void listar(Evento* raiz)
{
    if(raiz != NULL){
        listar(raiz->left);
        imprimir(raiz);
        listar(raiz->right);
    }
}

void sair(Evento* raiz){
    if (raiz != NULL){
        sair(raiz->left);
        sair(raiz->right);
        free(raiz);
        printf("-");
    }
}

void consultar(Raiz* raiz)
{
    int tipobusca;
    printf("Digite 1 para busca com data e 2 para data/hora\n");
    scanf("%d", &tipobusca);
    Evento* procurador = (Evento*)malloc(sizeof(Evento));
    procurador->left = NULL;
    procurador->right = NULL;
    procurador->data = setdata(tipobusca);
    if(procurador->data.ano == -1) return;
    if(tipobusca == 1){
        procurador->duracaoh = 23;
        procurador->duracaom = 59;
        }
    else {
        procurador->duracaoh = 0;
        procurador->duracaom = 0;
        }
    transformador(procurador);
    Evento* encontrado = busca(raiz->no, procurador);
    if(tipobusca == 2){
        if (encontrado == NULL) printf("Agenda Vazia\n\n");
        else imprimir(encontrado);
    } 
    if(tipobusca == 1){
        if (encontrado == NULL){
            printf("Agenda Vazia\n\n");
        } else {
            buscaAll(encontrado, procurador);
    }} 
    free(procurador);
}

void alterar(Evento* raiz)
{
    Evento* procurador = (Evento*)malloc(sizeof(Evento));
    procurador->left = NULL;
    procurador->right = NULL;
    procurador->data = setdata(2);
    if(procurador->data.ano == -1) return;
    procurador->duracaoh = 0;
    procurador->duracaom = 0;
    transformador(procurador);
    Evento* encontrado = busca(raiz, procurador);
    if (encontrado == NULL)
        printf("\nCompromisso nao encontrado\n\n");
    else {
        int backupDuracaoh = encontrado->duracaoh;
        int backupDuracaom = encontrado->duracaom;
        char backupDescricao[100];
        long long int backupFim = encontrado->fim;
        strcpy(backupDescricao, encontrado->descricao); 
        printf("Duracao: (hh:mm)");
        scanf("%d:%d", &encontrado->duracaoh, &encontrado->duracaom);
        printf("Descricao: ");
        scanf(" %[^\n]", encontrado->descricao);
        transformador(encontrado);
        if(busca(raiz, encontrado) != NULL){
            printf("\nHorario ocupado!\n");
            encontrado->duracaoh = backupDuracaoh;
            encontrado->duracaom = backupDuracaom;
            strcpy(encontrado->descricao, backupDescricao);
            encontrado->fim = backupFim;
        }}
    free(procurador);
}

void excluir(Raiz* raiz)
{
    Evento* procurador = (Evento*)malloc(sizeof(Evento));
    procurador->left = NULL;
    procurador->right = NULL;
    procurador->data = setdata(2);
    if(procurador->data.ano == -1) return;
    procurador->duracaoh = 0;
    procurador->duracaom = 0;
    transformador(procurador);
    if (busca(raiz->no, procurador) == NULL)
        printf("\nCompromisso nao encontrado\n\n");
    else raiz->no = removido(raiz->no, procurador);
}

Evento* removido(Evento* raiz, Evento* alvo)
{
    if (raiz == NULL) return NULL;
    else if (alvo->inicio <= raiz->fim && alvo->fim >= raiz->inicio) {
        if (raiz->left == NULL && raiz->right == NULL) {
            free(raiz);
            return NULL;
        }
        else if (raiz->left != NULL && raiz->right != NULL) {
            Evento* maiorEsquerda = raiz->left;
            while(maiorEsquerda->right != NULL) maiorEsquerda = maiorEsquerda->right;
            raiz->data = maiorEsquerda->data;
            raiz->duracaoh = maiorEsquerda->duracaoh;
            raiz->duracaom = maiorEsquerda->duracaom;
            raiz->inicio = maiorEsquerda->inicio;
            raiz->fim = maiorEsquerda->fim;
            strcpy(raiz->descricao, maiorEsquerda->descricao);
            raiz->left = removido(raiz->left, maiorEsquerda);
            return raiz;
        }
        else if (raiz->left != NULL) {
            Evento* left = raiz->left;
            free(raiz);
            return left;
        }
        else {
            Evento* right = raiz->right;
            free(raiz);
            return right;
        }
    }
    else {
        if (alvo->inicio < raiz->inicio)
            raiz->left = removido(raiz->left, alvo);
        else
            raiz->right = removido(raiz->right, alvo);
        return raiz;
    }
}


void transformador(Evento* raiz)
{
    Data data = raiz->data;
    int diasNoMes = diasnoMes(data.mes, data.ano);
    raiz->inicio = raiz->data.ano * 100000000 + raiz->data.mes * 1000000 + raiz->data.dia * 10000
        + raiz->data.horas * 100 + raiz->data.minutos;
    if(raiz->duracaom + data.minutos >= 60){
        data.minutos = raiz->duracaom + data.minutos -60;
        data.horas++;
    }  else data.minutos += raiz->duracaom;
    if (raiz->duracaoh + data.horas >= 24) {
        data.horas = raiz->duracaoh + data.horas -24;
        data.dia++;
    }  else data.horas += raiz->duracaoh;
    
    if (data.dia > diasNoMes) {
        data.dia = 1;
        data.mes++;
    }
    if (data.mes > 12) {
        data.mes = 1;
        data.ano++;
    }
    raiz->fim = data.ano * 100000000+ data.mes * 1000000 + data.dia * 10000
        + data.horas * 100 + data.minutos;
}

int confData(Data data)
{
    if(data.minutos >= 60 || data.minutos < 0) return -1;
    else if(data.horas >= 24 || data.horas < 0) return -1;
    else if(data.dia > diasnoMes(data.mes, data.ano) || data.dia < 1) return -1;
    else if(data.ano < 0) return -1;
    else
        return 0;
}

Evento *busca(Evento* raiz, Evento* alvo)
{
    if(raiz == NULL) return NULL;
    else if (alvo->inicio <= raiz->fim && alvo->fim >= raiz->inicio && raiz != alvo)
        return raiz;
    else{
        if(alvo->inicio < raiz->inicio)
            return busca(raiz->left, alvo);
        else return busca(raiz->right, alvo);
    }
    
}

void buscaAll(Evento* raiz, Evento* alvo)
{
    if(raiz != NULL) {
        buscaAll(raiz->left, alvo);
        if(alvo->inicio <= raiz->fim && alvo->fim >= raiz->inicio)
            imprimir(raiz);
        buscaAll(raiz->right, alvo);     
    }
}

Evento* adubo(Evento* raiz, Evento* broto)
{
    if(raiz == NULL) return broto;
    else{
            if(broto->inicio <= raiz->inicio)
                raiz->left = adubo(raiz->left, broto);
            else
                raiz->right = adubo(raiz->right, broto);
        }
    return raiz;
}

Data setdata(int tipo)
{
    Data d;
    if (tipo == 2) {
        printf("Data: (dd/mm/aaaa)");
        scanf("%d/%d/%lld", &d.dia, &d.mes, &d.ano);
        printf("Hora: (hh:mm)");
        scanf("%d:%d", &d.horas, &d.minutos); }
    else if (tipo == 1) { 
        printf("Data: (dd/mm/aaaa)");
        scanf("%d/%d/%lld", &d.dia, &d.mes, &d.ano);
        d.horas = 0;
        d.minutos = 0; 
        }
    else  {
        printf("Tipo invalido, digite 1 ou 2\n");
        d.ano = -1;
    }
    if (confData(d) == -1) {
        printf("Data invalida.\n");
        d.ano = -1;
    }
    return d;
}

void imprimir(Evento* raiz)
{
    printf("\nData: %02d/%02d/%lld\n", raiz->data.dia, raiz->data.mes, raiz->data.ano);
    printf("Hora: %02dh%02d\n", raiz->data.horas, raiz->data.minutos);
    printf("Duracao: %02d:%02d\n", raiz->duracaoh, raiz->duracaom);
    printf("Descricao: %s\n", raiz->descricao);
}

int diasnoMes(int mes, int ano){
    if(mes == 4 || mes == 6 || mes == 9 || mes == 11)  return 30;
    else if (ano % 4 == 0 && mes == 2) return 29;
    else if(mes == 2) return 28;
    else return 31;
}