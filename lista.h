#ifndef LISTA_H
#define LISTA_H

#define NUM_BUSCAS_TESTE 10000
#define MAX_VALOR_ALEATORIO 100000

typedef struct
{
    int qtd;
    int *numeros;
} Lista;

/* Criação/Destruição/IO */
Lista *criar_lista(int quantidade);
void destruir_lista(Lista *lista);
Lista *clonar_lista(Lista *original);
void gerar_arquivo_aleatorio(const char *nome_arquivo, int quantidade);
Lista *carregar_arquivo(const char *nome_arquivo, int quantidade_esperada);
void salvar_arquivo_ordenado(const char *nome_arquivo, Lista *lista, const char *alg_nome, double tempo_ms);

/* Buscas */
int busca_sequencial(Lista *lista, int chave);
int busca_binaria(Lista *lista, int chave);
void comparar_desempenho_buscas(Lista *lista_desordenada, Lista *lista_ordenada);

/* Ordenações */
void executar_selection_sort(Lista *lista);
void executar_insertion_sort(Lista *lista);
void executar_bubble_sort(Lista *lista);
void executar_radix_sort(Lista *lista);
void executar_quick_sort(Lista *lista);
void executar_merge_sort(Lista *lista);
void executar_heap_sort(Lista *lista);

/* Função que processa todos os algoritmos automaticamente */
void processar_todos_algoritmos(const char *arq_entrada[], const char *arq_saida[], const int tamanhos[], int qtd_cenarios);

#endif
