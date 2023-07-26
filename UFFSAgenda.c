#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcoes.h"

int main()
{
    Raiz* raiz = (Raiz*)malloc(sizeof(Raiz));
    raiz->no = NULL;
    int comando;

    do {
        printf("\n-----------------------------------------------\n");
        printf("Bem vindo a AgendaUFFS!\n");
        printf("1. Incluir\n2. Consultar\n3. Alterar\n4. Excluir\n5. Listar Todos\n6. Sair\n");
        scanf("%d", &comando);
        if (comando == 1) incluir(raiz);
        else if (comando == 2) consultar(raiz);
        else if (comando == 3) alterar(raiz->no);
        else if (comando == 4) excluir(raiz);
        else if (comando == 5) listar(raiz->no);
        else if(comando == 6) sair(raiz->no);
        else 
            printf("Comando invalido\n");
    } while (comando != 6);
    printf("\nSaindo da AgendaUFFS.\n");
    raiz = NULL;
    free(raiz);
    return 0;
}
