#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "lista.h"

/* --- Auxiliares --- */
static double obter_tempo_ms(clock_t inicio, clock_t fim)
{
    return ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000.0;
}

/* --- Criação / Destruição / IO --- */
Lista *criar_lista(int quantidade)
{
    Lista *nova_lista = (Lista *)malloc(sizeof(Lista));
    if (!nova_lista)
        return NULL;
    nova_lista->qtd = quantidade;
    nova_lista->numeros = (int *)malloc(quantidade * sizeof(int));
    if (!nova_lista->numeros)
    {
        free(nova_lista);
        return NULL;
    }
    return nova_lista;
}

void destruir_lista(Lista *lista)
{
    if (lista != NULL)
    {
        free(lista->numeros);
        free(lista);
    }
}

Lista *clonar_lista(Lista *original)
{
    Lista *copia = criar_lista(original->qtd);
    if (!copia)
        return NULL;
    for (int i = 0; i < original->qtd; i++)
        copia->numeros[i] = original->numeros[i];
    return copia;
}

void gerar_arquivo_aleatorio(const char *nome_arquivo, int quantidade)
{
    FILE *f = fopen(nome_arquivo, "w");
    if (!f)
    {
        printf("  Erro ao criar %s\n", nome_arquivo);
        return;
    }
    for (int i = 0; i < quantidade; i++)
    {
        fprintf(f, "%d\n", rand() % MAX_VALOR_ALEATORIO);
    }
    fclose(f);
    printf("  -> Arquivo gerado: %s\n", nome_arquivo);
}

Lista *carregar_arquivo(const char *nome_arquivo, int quantidade_esperada)
{
    FILE *f = fopen(nome_arquivo, "r");
    if (!f)
        return NULL;
    Lista *lista = criar_lista(quantidade_esperada);
    if (!lista)
    {
        fclose(f);
        return NULL;
    }
    for (int i = 0; i < quantidade_esperada; i++)
    {
        if (fscanf(f, "%d", &lista->numeros[i]) != 1)
        {
            // Caso o arquivo tenha menos números do que o esperado
            lista->qtd = i;
            break;
        }
    }
    fclose(f);
    return lista;
}

void salvar_arquivo_ordenado(const char *nome_arquivo, Lista *lista, const char *alg_nome, double tempo_ms)
{
    FILE *f = fopen(nome_arquivo, "w");
    if (!f)
    {
        printf("  Erro ao salvar %s\n", nome_arquivo);
        return;
    }
    for (int i = 0; i < lista->qtd; i++)
        fprintf(f, "%d\n", lista->numeros[i]);

    fprintf(f, "\n--- ESTATISTICAS ---\n");
    fprintf(f, "Algoritmo: %s\n", alg_nome);
    fprintf(f, "Tempo de Processamento: %.4f ms\n", tempo_ms);
    fclose(f);
}

/* --- Buscas --- */
int busca_sequencial(Lista *lista, int chave)
{
    for (int i = 0; i < lista->qtd; i++)
        if (lista->numeros[i] == chave)
            return i;
    return -1;
}

int busca_binaria(Lista *lista, int chave)
{
    int inicio = 0, fim = lista->qtd - 1;
    while (inicio <= fim)
    {
        int meio = inicio + (fim - inicio) / 2;
        if (lista->numeros[meio] == chave)
            return meio;
        if (lista->numeros[meio] < chave)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

void comparar_desempenho_buscas(Lista *lista_desordenada, Lista *lista_ordenada)
{
    printf("   [Testando %d buscas aleatorias...]\n", NUM_BUSCAS_TESTE);
    clock_t inicio, fim;

    inicio = clock();
    for (int i = 0; i < NUM_BUSCAS_TESTE; i++)
    {
        int chave = rand() % MAX_VALOR_ALEATORIO;
        (void)busca_sequencial(lista_desordenada, chave);
    }
    fim = clock();
    printf("   -> Busca Sequencial (Lista Aleatoria): %.4f ms\n", obter_tempo_ms(inicio, fim));

    inicio = clock();
    for (int i = 0; i < NUM_BUSCAS_TESTE; i++)
    {
        int chave = rand() % MAX_VALOR_ALEATORIO;
        (void)busca_binaria(lista_ordenada, chave);
    }
    fim = clock();
    printf("   -> Busca Binaria    (Lista Ordenada):  %.4f ms\n", obter_tempo_ms(inicio, fim));
}

/* --- Selection Sort --- */
void executar_selection_sort(Lista *lista)
{
    int n = lista->qtd;
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
            if (lista->numeros[j] < lista->numeros[min])
                min = j;
        int tmp = lista->numeros[i];
        lista->numeros[i] = lista->numeros[min];
        lista->numeros[min] = tmp;
    }
}

/* --- Insertion Sort --- */
void executar_insertion_sort(Lista *lista)
{
    int n = lista->qtd;
    for (int i = 1; i < n; i++)
    {
        int chave = lista->numeros[i];
        int j = i - 1;
        while (j >= 0 && lista->numeros[j] > chave)
        {
            lista->numeros[j + 1] = lista->numeros[j];
            j--;
        }
        lista->numeros[j + 1] = chave;
    }
}

/* --- Bubble Sort --- */
void executar_bubble_sort(Lista *lista)
{
    int n = lista->qtd;
    for (int i = 0; i < n - 1; i++)
    {
        int trocou = 0;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (lista->numeros[j] > lista->numeros[j + 1])
            {
                int tmp = lista->numeros[j];
                lista->numeros[j] = lista->numeros[j + 1];
                lista->numeros[j + 1] = tmp;
                trocou = 1;
            }
        }
        if (!trocou)
            break;
    }
}

/* --- Radix Sort (igual ao modelo do colega) --- */
static int pegar_maximo(Lista *lista)
{
    int max = lista->numeros[0];
    for (int i = 1; i < lista->qtd; i++)
        if (lista->numeros[i] > max)
            max = lista->numeros[i];
    return max;
}

static void counting_sort_digito(Lista *lista, int exp)
{
    int n = lista->qtd;
    int *saida = (int *)malloc(n * sizeof(int));
    int count[10] = {0};
    for (int i = 0; i < n; i++)
        count[(lista->numeros[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--)
    {
        saida[count[(lista->numeros[i] / exp) % 10] - 1] = lista->numeros[i];
        count[(lista->numeros[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; i++)
        lista->numeros[i] = saida[i];
    free(saida);
}

void executar_radix_sort(Lista *lista)
{
    if (lista->qtd == 0)
        return;
    int max = pegar_maximo(lista);
    for (int exp = 1; max / exp > 0; exp *= 10)
        counting_sort_digito(lista, exp);
}

/* --- Quick Sort --- */
static int partition(Lista *lista, int low, int high)
{
    int pivot = lista->numeros[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (lista->numeros[j] < pivot)
        {
            i++;
            int tmp = lista->numeros[i];
            lista->numeros[i] = lista->numeros[j];
            lista->numeros[j] = tmp;
        }
    }
    int tmp = lista->numeros[i + 1];
    lista->numeros[i + 1] = lista->numeros[high];
    lista->numeros[high] = tmp;
    return i + 1;
}

static void quick_sort_rec(Lista *lista, int low, int high)
{
    if (low < high)
    {
        int pi = partition(lista, low, high);
        quick_sort_rec(lista, low, pi - 1);
        quick_sort_rec(lista, pi + 1, high);
    }
}

void executar_quick_sort(Lista *lista)
{
    if (lista->qtd <= 1)
        return;
    quick_sort_rec(lista, 0, lista->qtd - 1);
}

/* --- Merge Sort --- */
static void merge(Lista *lista, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));
    for (int i = 0; i < n1; i++)
        L[i] = lista->numeros[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = lista->numeros[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            lista->numeros[k++] = L[i++];
        else
            lista->numeros[k++] = R[j++];
    }
    while (i < n1)
        lista->numeros[k++] = L[i++];
    while (j < n2)
        lista->numeros[k++] = R[j++];
    free(L);
    free(R);
}

static void merge_sort_rec(Lista *lista, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        merge_sort_rec(lista, left, mid);
        merge_sort_rec(lista, mid + 1, right);
        merge(lista, left, mid, right);
    }
}

void executar_merge_sort(Lista *lista)
{
    if (lista->qtd <= 1)
        return;
    merge_sort_rec(lista, 0, lista->qtd - 1);
}

/* --- Heap Sort --- */
static void heapify(Lista *lista, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && lista->numeros[left] > lista->numeros[largest])
        largest = left;
    if (right < n && lista->numeros[right] > lista->numeros[largest])
        largest = right;
    if (largest != i)
    {
        int tmp = lista->numeros[i];
        lista->numeros[i] = lista->numeros[largest];
        lista->numeros[largest] = tmp;
        heapify(lista, n, largest);
    }
}

void executar_heap_sort(Lista *lista)
{
    int n = lista->qtd;
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(lista, n, i);
    for (int i = n - 1; i > 0; i--)
    {
        int tmp = lista->numeros[0];
        lista->numeros[0] = lista->numeros[i];
        lista->numeros[i] = tmp;
        heapify(lista, i, 0);
    }
}

/* --- Processamento automático de todos os algoritmos --- */
void processar_todos_algoritmos(const char *arq_entrada[], const char *arq_saida[], const int tamanhos[], int qtd_cenarios)
{
    const char *nomes_alg[] = {"selection", "insertion", "bubble", "quick", "merge", "heap", "radix"};
    int num_alg = 7;

    for (int c = 0; c < qtd_cenarios; c++)
    {
        printf("\n>>> Processando Cenario: %d numeros\n", tamanhos[c]);

        Lista *lista_orig = carregar_arquivo(arq_entrada[c], tamanhos[c]);
        if (!lista_orig)
        {
            printf("Erro: Arquivo nao encontrado. Gere os dados antes.\n");
            printf("Procurando por: %s\n", arq_entrada[c]);
            continue;
        }
        printf("Arquivo carregado com sucesso!\n");

        for (int a = 0; a < num_alg; a++)
        {
            Lista *lista_ord = clonar_lista(lista_orig);
            if (!lista_ord)
            {
                printf("Erro ao clonar lista.\n");
                continue;
            }

            clock_t inicio = clock();
            if (strcmp(nomes_alg[a], "selection") == 0)
                executar_selection_sort(lista_ord);
            else if (strcmp(nomes_alg[a], "insertion") == 0)
                executar_insertion_sort(lista_ord);
            else if (strcmp(nomes_alg[a], "bubble") == 0)
                executar_bubble_sort(lista_ord);
            else if (strcmp(nomes_alg[a], "quick") == 0)
                executar_quick_sort(lista_ord);
            else if (strcmp(nomes_alg[a], "merge") == 0)
                executar_merge_sort(lista_ord);
            else if (strcmp(nomes_alg[a], "heap") == 0)
                executar_heap_sort(lista_ord);
            else if (strcmp(nomes_alg[a], "radix") == 0)
                executar_radix_sort(lista_ord);
            clock_t fim = clock();

            double tempo = obter_tempo_ms(inicio, fim);
            char nome_saida[256];
            snprintf(nome_saida, sizeof(nome_saida), "ord_%s_%d.txt", nomes_alg[a], tamanhos[c]);
            salvar_arquivo_ordenado(nome_saida, lista_ord, nomes_alg[a], tempo);
            printf("   -> %s: %.4f ms\n", nomes_alg[a][0] ? nomes_alg[a] : "algoritmo", tempo);

            destruir_lista(lista_ord);
        }

        // Comparar desempenho de buscas entre a lista original (aleatoria) e uma ordenada (usar a última ordenação: radix)
        Lista *lista_para_busca = carregar_arquivo(arq_entrada[c], tamanhos[c]);
        Lista *lista_radix = clonar_lista(lista_para_busca);
        executar_radix_sort(lista_radix);
        comparar_desempenho_buscas(lista_para_busca, lista_radix);
        destruir_lista(lista_para_busca);
        destruir_lista(lista_radix);

        destruir_lista(lista_orig);
    }
}
