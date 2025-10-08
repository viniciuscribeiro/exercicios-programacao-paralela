# Lista de Exercícios: Programação Paralela com OpenMP

Este repositório contém a resolução da lista de exercícios da disciplina de Programação Paralela, focada na utilização de diretivas OpenMP para paralelizar algoritmos em C++. O objetivo é explorar e demonstrar a aplicação de conceitos fundamentais de concorrência e medição de desempenho.

> **Disciplina:** Programação Paralela  
> **Professor:** Prof. Rodrigo Gonçalves Pinto  
> **Aluno:** Vinicius Cordeiro Ribeiro  
> **Instituição:** IESB  
> **Data:** 08 de Outubro de 2025

---

## 🚀 Sobre o Projeto

O projeto consiste em cinco exercícios práticos que abordam desde a criação de regiões paralelas simples até o uso de cláusulas de redução, estratégias de escalonamento (`schedule`) e mecanismos de sincronização para medição de performance por thread.

Cada arquivo `.cpp` corresponde a um exercício, está autocontido e é exaustivamente comentado para explicar a lógica, as funções e as diretivas OpenMP utilizadas, conforme as instruções da atividade.

### 🗂️ Estrutura do Repositório

* `/exercicio-1.cpp`: Criação de uma região paralela "Hello World" com um número fixo de threads.
* `/exercicio-2.cpp`: Demonstração do uso da cláusula `reduction` para evitar condições de corrida em somatórios.
* `/exercicio-3.cpp`: Medição de performance (tempo de execução) de um loop com carga de trabalho uniforme usando `schedule(static)`.
* `/exercicio-4.cpp`: Medição de tempo por thread individual, utilizando diretivas de sincronização como `master` e `barrier`.
* `/exercicio-5.cpp`: Comparativo de desempenho entre os escalonadores `schedule(static)` e `schedule(dynamic)` com diferentes contagens de threads.

### 🛠️ Tecnologias Utilizadas

* **Linguagem:** C++
* **Paralelismo:** OpenMP
* **Compilador:** GCC (g++)

---

## ⚙️ Como Compilar e Executar

É necessário ter o compilador `g++` e as bibliotecas do OpenMP (`libgomp`) instaladas.

### Comando de Compilação

Para compilar qualquer um dos exercícios, utilize o seguinte comando no terminal. A flag `-fopenmp` é essencial para habilitar o OpenMP, e a flag `-O2` é recomendada para otimização de performance.

```bash
g++ -o [nome_do_executavel] [arquivo_fonte.cpp] -fopenmp -O2
````

### Exemplos Práticos

```bash
# Compilando e executando o Exercício 1
g++ -o ex1 exercicio-1.cpp -fopenmp -O2
./ex1

# Compilando e executando o Exercício 2
g++ -o ex2 exercicio-2.cpp -fopenmp -O2
./ex2

# Compilando e executando o Exercício 3
g++ -o ex3 exercicio-3.cpp -fopenmp -O2
./ex3

# Compilando e executando o Exercício 4
g++ -o ex4 exercicio-4.cpp -fopenmp -O2
./ex4

# Compilando e executando o Exercício 5
g++ -o ex5 exercicio-5.cpp -fopenmp -O2
./ex5
```

-----

## 💡 Resumo dos Conceitos Abordados

  * **Exercício 1:** Criação de regiões paralelas (`#pragma omp parallel`) e identificação de threads (`omp_get_thread_num`, `omp_get_num_threads`).
  * **Exercício 2:** Solução de condições de corrida em operações de somatório com a cláusula `reduction(+:variavel)`.
  * **Exercício 3:** Medição de tempo com a biblioteca `<chrono>` e aplicação do escalonador `schedule(static)` para cargas de trabalho uniformes.
  * **Exercício 4:** Sincronização e medição granular com as diretivas `#pragma omp master` e `#pragma omp barrier` para realizar a medição de tempo por thread.
  * **Exercício 5:** Análise comparativa de estratégias de escalonamento (`static` vs. `dynamic`) e o impacto da contagem de threads na performance, relacionando com as características do hardware (núcleos físicos vs. lógicos).

-----

**Vinicius Cordeiro Ribeiro**

[GitHub](https://github.com/viniciuscribeiro) | [LinkedIn](https://www.linkedin.com/in/viniciuscordeiroribeiro/)
