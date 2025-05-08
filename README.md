# 🚀 Gerenciador de Tarefas

## 📝 Descrição do Projeto
Projeto acadêmico que compara o desempenho entre Lista Encadeada e Árvore AVL para operações básicas de um gerenciador de tarefas, incluindo inserção, busca e remoção. Desenvolvido em C como trabalho da disciplina de Estrutura de Dados.

O projeto implementa uma estrutura de Tarefa com os seguintes atributos:
- ID único
- Nome
- Descrição
- Prioridade
- Categoria

## ✨ Funcionalidades
- 📊 Comparação de desempenho entre estruturas de dados
- ⏱️ Medição precisa de tempo de execução
- 📈 Geração de dados para análise

## ✅ Operações implementadas
- Inserção de tarefas
- Busca por ID, prioridade, categoria e nome
- Remoção no início, fim e por valor específico
- Ordenação automática (AVL) e manual (Lista)
- Verificação de ordenação
- Duplicação de listas para testes comparativos

## 🛠️ Como Compilar e Executar

### Pré-requisitos:
- Compilador GCC
- Arquivos de dados de teste (inclusos no repositório)

### Estrutura do Projeto
```
├── script_dados/         # Pasta com arquivos de teste
│   ├── 30_porcento_comeco.py
│   ├── 30_porcento_fim.py
│   ├── 30_porcento_importante.py
│   └── crescente.py
│   └── decrescente.py
│   └── desordenado.py
├── aplicacao.c           # Programa principal com função main e testes comparativos
├── lista_dinamica.c      # Implementação da lista encadeada
├── lista_dinamica.h      # Cabeçalho da lista encadeada
├── arvore_avl.c          # Implementação da árvore AVL
├── arvore_avl.h          # Cabeçalho da árvore AVL
```

### Compilação
```bash
gcc lista_dinamica.c arvore_avl.c aplicacao.c -o gerenciador_tarefas.exe
```

### Execução
```bash
# Executa todos os testes com diferentes conjutos de dados (de acordo com aplicacao.c)
./gerenciador_tarefas.exe
```
 
## 📋 Saída do Programa
O programa gera uma tabela comparativa para diferentes tamanhos de conjunto de dados:

```
******** COMPARADOR DE DESEMPENHO: LISTA ENCADEADA vs ARVORE AVL ********

***** TESTE COM 100 ELEMENTOS *****

Tipo    Insercao    Ordenacao   Verificacao    Buscas      Remocao_Inicio    Remocao_Fim    Remocao_Valor    TOTAL
LISTA   0.000123s   0.000056s   0.000003s      0.000018s   0.000007s         0.000015s      0.000022s        0.000244s
AVL     0.000089s   ---------   ---------      0.000005s   ---------         ---------      0.000012s        0.000106s

***** TESTE COM 10000 ELEMENTOS *****

Tipo    Insercao    Ordenacao   Verificacao    Buscas      Remocao_Inicio    Remocao_Fim    Remocao_Valor    TOTAL
LISTA   0.120000s   1.450000s   0.000250s      0.250000s   0.002000s         0.148000s      0.150000s        2.120250s
AVL     0.080000s   ---------   ---------      0.020000s   ---------         ---------      0.040000s        0.140000s
```

O programa testa com diferentes tamanhos de conjunto: 100, 1.000, 10.000, 20.000, 30.000, 40.000 e 50.000 elementos.

## 📊 Resultados e Conclusões
- **Para conjuntos pequenos (100-1.000 tarefas)**:
  - A Lista Encadeada pode apresentar vantagem em inserções simples
  - A AVL já demonstra superioridade considerável em operações de busca
  - A diferença total de desempenho é perceptível, mas não crítica

- **Para conjuntos grandes (10.000+ tarefas)**:
  - A AVL torna-se significativamente mais eficiente em buscas e remoções
  - O tempo combinado de inserção e ordenação na Lista torna-se expressivamente elevado
  - A diferença de performance pode chegar a mais de 10x em favor da AVL
  
## 🧪 Detalhes das Implementações

### Lista Encadeada
- Implementa uma lista simplesmente encadeada
- Ordenação por algoritmo de ordenação por seleção (O(n²))
- Inserção no fim (O(n))
- Remoção no início (O(1)), fim (O(n)) e por valor (O(n))
- Busca linear (O(n))

### Árvore AVL
- Implementa uma árvore binária de busca balanceada
- Auto-balanceamento por rotações (direita, esquerda, dupla)
- Inserção mantendo o balanceamento (O(log n))
- Remoção mantendo o balanceamento (O(log n))
- Busca binária por ID (O(log n))
- Busca completa para outros atributos (O(n))

## 👥 Equipe
Desenvolvido por:

- **Bruno da Silveira Escanhoela**
- **Gabriel Ferreira do Nascimento**
- **Guilherme Soares Leite Coelho**
- **João Guilherme Volta Kinol**
- **Yuri Peruzzo**

---

*Projeto desenvolvido para a disciplina de Estrutura de Dados - Centro Universitário Facens 2025S1*
