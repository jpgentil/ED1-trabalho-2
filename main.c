#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lista.h"

#define QTD_CENARIOS 4
const int TAMANHOS[QTD_CENARIOS] = {100, 1000, 10000, 100000};
const char *ARQ_ENTRADA[QTD_CENARIOS] = {"seq_100.txt", "seq_1000.txt", "seq_10000.txt", "seq_100000.txt"};
/* ARQ_SAIDA não é necessário pois geramos ord_<alg>_<tam>.txt automaticamente */

void menu_gerar()
{
    printf("\n--- 1. GERACAO DE DADOS ---\n");
    for (int i = 0; i < QTD_CENARIOS; i++)
    {
        gerar_arquivo_aleatorio(ARQ_ENTRADA[i], TAMANHOS[i]);
    }
}

void menu_processar()
{
    printf("\n--- 2. ORDENACAO E TESTES (TODOS OS ALGORITMOS) ---\n");
    processar_todos_algoritmos(ARQ_ENTRADA, NULL, TAMANHOS, QTD_CENARIOS);
}

int main()
{
    srand((unsigned int)time(NULL));
    int opcao = -1;

    while (opcao != 0)
    {
        printf("\n=== TRABALHO DE ESTRUTURA DE DADOS ===\n");
        printf("1 - Gerar Arquivos\n");
        printf("2 - Ordenar e Comparar Buscas\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        if (scanf("%d", &opcao) != 1)
        {
            // limpar stdin em caso de entrada inválida
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            opcao = -1;
            continue;
        }

        switch (opcao)
        {
        case 1:
            menu_gerar();
            break;
        case 2:
            menu_processar();
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida.\n");
        }
    }
    return 0;
}
