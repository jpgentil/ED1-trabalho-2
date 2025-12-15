# Análise de Algoritmos de Ordenação e Busca

Este projeto acadêmico de Estrutura de Dados implementa e compara o desempenho de sete algoritmos clássicos de ordenação: Selection Sort, Insertion Sort, Bubble Sort, Quick Sort, Merge Sort, Heap Sort e Radix Sort. O programa também analisa a eficiência de algoritmos de busca, comparando a busca sequencial em listas desordenadas com a busca binária em listas ordenadas. Através de testes empíricos com conjuntos de dados de diferentes tamanhos (100, 1.000, 10.000 e 100.000 elementos), o sistema permite observar na prática as diferenças de desempenho entre algoritmos com complexidades O(n²), O(n log n) e O(nk), demonstrando como a escolha do algoritmo adequado impacta significativamente o tempo de processamento conforme o volume de dados aumenta.

### Estrutura do Projeto

```
.
├── main.c          # Programa principal com menu interativo
├── lista.c         # Implementação dos algoritmos
├── lista.h         # Definições e protótipos
└── README.md       # Este arquivo
```

### Como Compilar e Executar

### Compilação
```bash
gcc main.c lista.c -o programa -O2
```

### Execução
```bash
./programa
```

### Funcionalidades

### Menu Principal
1. **Gerar Arquivos** - Cria arquivos com números aleatórios
2. **Ordenar e Comparar Buscas** - Executa todos os algoritmos e compara resultados
3. **Sair** - Encerra o programa

### Cenários de Teste

O programa testa automaticamente 4 cenários com diferentes tamanhos:
- 100 elementos
- 1.000 elementos
- 10.000 elementos
- 100.000 elementos

### Arquivos Gerados

### Arquivos de Entrada
- `seq_100.txt` - 100 números aleatórios
- `seq_1000.txt` - 1.000 números aleatórios
- `seq_10000.txt` - 10.000 números aleatórios
- `seq_100000.txt` - 100.000 números aleatórios

### Arquivos de Saída
Para cada algoritmo e tamanho, são gerados arquivos no formato:
- `ord_<algoritmo>_<tamanho>.txt`

Exemplo: `ord_quick_1000.txt`

Cada arquivo contém:
- Lista ordenada
- Estatísticas do processamento
- Tempo de execução em milissegundos

### Análise de Desempenho

O programa mede automaticamente:
- **Tempo de ordenação** para cada algoritmo
- **Tempo de busca sequencial** em lista desordenada
- **Tempo de busca binária** em lista ordenada
- Comparação com 10.000 buscas aleatórias

### Configurações

Constantes definidas em `lista.h`:
```c
#define NUM_BUSCAS_TESTE 10000      // Quantidade de buscas para teste
#define MAX_VALOR_ALEATORIO 100000  // Valor máximo dos números gerados
```

### Exemplo de Uso

```
=== TRABALHO DE ESTRUTURA DE DADOS ===
1 - Gerar Arquivos
2 - Ordenar e Comparar Buscas
0 - Sair
Opcao: 1

--- 1. GERACAO DE DADOS ---
  -> Arquivo gerado: seq_100.txt
  -> Arquivo gerado: seq_1000.txt
  -> Arquivo gerado: seq_10000.txt
  -> Arquivo gerado: seq_100000.txt

Opcao: 2

>>> Processando Cenario: 1000 numeros
   -> selection: 2.3456 ms
   -> insertion: 1.8234 ms
   -> bubble: 3.1234 ms
   -> quick: 0.2345 ms
   -> merge: 0.3456 ms
   -> heap: 0.4123 ms
   -> radix: 0.1890 ms
   [Testando 10000 buscas aleatorias...]
   -> Busca Sequencial (Lista Aleatoria): 45.2341 ms
   -> Busca Binaria    (Lista Ordenada):  0.8234 ms
```

### Observações

- Os números são gerados aleatoriamente entre 0 e 99.999
- Cada execução produz resultados diferentes devido à aleatoriedade
- O tempo de execução varia conforme o hardware utilizado
- Algoritmos O(n²) tornam-se significativamente mais lentos em listas grandes

### Objetivo Acadêmico

Este projeto demonstra:
- Implementação prática de algoritmos clássicos
- Análise empírica de complexidade computacional
- Diferenças de desempenho entre algoritmos O(n²) e O(n log n)
- Importância da ordenação para otimização de buscas

## 📄 Licença

Projeto acadêmico para fins educacionais.
