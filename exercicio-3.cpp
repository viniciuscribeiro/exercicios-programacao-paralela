/*
-------------------------------------------------------------------
Exercício 3 — Expressão Vetorial
Implemente a expressão: a[i] = x[i]^2 + y[i]^2 + z[i]^2 para vetores de tamanho 1.000.000.
a) Faça a versão sequencial.
b) Paralelize com #pragma omp parallel for schedule(static).
c) Mostre o tempo total de execução em cada versão.
-------------------------------------------------------------------
*/


// ---------------------------------------------------------------------------------
// --- Bibliotecas Incluídas ---
// ---------------------------------------------------------------------------------

/*
 * #include <iostream>
 * Descrição: Padrão para entrada e saída de dados. Usado para 'std::cout'.
 */
#include <iostream>

/*
 * #include <vector>
 * Descrição: Fornece o container std::vector, um array dinâmico.
 */
#include <vector>

/*
 * #include <omp.h>
 * Descrição: Biblioteca principal do OpenMP para funcionalidades de paralelismo.
 */
#include <omp.h>

/*
 * #include <chrono>
 * Descrição: Biblioteca do C++ moderno para medição de tempo com alta precisão.
 * É a forma recomendada para cronometrar a duração de operações, sendo mais
 * precisa e portável que métodos antigos como time().
 */
#include <chrono>


// ---------------------------------------------------------------------------------
// --- Função Principal (main) ---
// ---------------------------------------------------------------------------------

int main() {
    // -----------------------------------------------------------------------------
    // --- Configuração Inicial ---
    // -----------------------------------------------------------------------------

    /*
     * const int TAMANHO = 1000000;
     * Descrição: Define o tamanho dos vetores como 1 milhão de elementos,
     * conforme solicitado no enunciado.
     */
    const int TAMANHO = 1000000;

    /*
     * std::vector<double> a(TAMANHO), x(TAMANHO), y(TAMANHO), z(TAMANHO);
     * Descrição: Declaração dos quatro vetores necessários.
     * O tipo 'double' foi escolhido para acomodar valores de ponto flutuante
     * e evitar overflow com os quadrados de números grandes.
     * - a: vetor de saída para armazenar o resultado.
     * - x, y, z: vetores de entrada.
     */
    std::vector<double> a(TAMANHO);
    std::vector<double> x(TAMANHO);
    std::vector<double> y(TAMANHO);
    std::vector<double> z(TAMANHO);

    // Inicialização dos vetores de entrada com valores de exemplo.
    // O valor exato não importa, o objetivo é ter dados para processar.
    for (int i = 0; i < TAMANHO; ++i) {
        x[i] = 1.5;
        y[i] = 2.5;
        z[i] = 3.5;
    }

    // -----------------------------------------------------------------------------
    // --- a) Versão Sequencial e Medição de Tempo ---
    // -----------------------------------------------------------------------------
    std::cout << "--- Versao Sequencial ---" << std::endl;

    /*
     * auto start_seq = std::chrono::high_resolution_clock::now();
     * Descrição: Captura o ponto no tempo exato em que a execução começa.
     * - 'std::chrono::high_resolution_clock': É o relógio com a maior precisão
     * disponível no sistema para medir intervalos de tempo.
     * - 'now()': Retorna o tempo atual ("timestamp").
     * - 'auto': O tipo do timestamp é complexo, então 'auto' deduz automaticamente
     * o tipo correto para a variável 'start_seq'.
     */
    auto start_seq = std::chrono::high_resolution_clock::now();

    // Loop sequencial que executa a expressão matemática.
    for (int i = 0; i < TAMANHO; ++i) {
        // a[i] recebe o resultado da soma dos quadrados de x[i], y[i] e z[i].
        // Usar v[i] * v[i] é geralmente mais rápido que a função pow(v[i], 2).
        a[i] = x[i] * x[i] + y[i] * y[i] + z[i] * z[i];
    }

    /*
     * auto end_seq = std::chrono::high_resolution_clock::now();
     * Descrição: Captura o ponto no tempo exato em que o loop terminou.
     */
    auto end_seq = std::chrono::high_resolution_clock::now();

    /*
     * std::chrono::duration<double, std::milli> duration_seq = end_seq - start_seq;
     * Descrição: Calcula a duração total da operação.
     * - 'end_seq - start_seq': A subtração de dois timestamps resulta em um objeto 'duration'.
     * - 'std::chrono::duration<double, std::milli>': Especificamos que queremos
     * ler essa duração como um número 'double' em unidades de milissegundos ('std::milli').
     */
    std::chrono::duration<double, std::milli> duration_seq = end_seq - start_seq;

    // Imprime o tempo de execução. 'duration_seq.count()' retorna o valor numérico da duração.
    std::cout << "Tempo de execucao: " << duration_seq.count() << " ms" << std::endl;
    // std::cout << "Resultado de a[0]: " << a[0] << std::endl << std::endl; // Opcional: para verificar o resultado


    // -----------------------------------------------------------------------------
    // --- b) Versão Paralela e Medição de Tempo ---
    // -----------------------------------------------------------------------------
    std::cout << "\n--- Versao Paralela ---" << std::endl;

    // Início da medição de tempo para a versão paralela.
    auto start_par = std::chrono::high_resolution_clock::now();

    /*
     * #pragma omp parallel for schedule(static)
     * Descrição: Diretiva que paraleliza o loop 'for' seguinte.
     * - 'parallel for': Divide as iterações do loop entre as threads.
     * - 'schedule(static)': Esta cláusula define a estratégia de "agendamento", ou
     * seja, como as iterações são distribuídas.
     * - 'static': As iterações são divididas em blocos (chunks) de tamanho
     * aproximadamente igual e distribuídas para as threads de forma fixa
     * *antes* do loop começar. Por exemplo, com 4 threads e 1.000.000 de iterações,
     * a thread 0 ficaria com 0-249999, a thread 1 com 250000-499999, e assim por diante.
     * - Por que usar 'static' aqui? Porque cada iteração do loop leva exatamente
     * o mesmo tempo para ser executada (uma soma de três quadrados). Com essa carga
     * de trabalho perfeitamente balanceada, o 'static' é ideal, pois tem a menor
     * sobrecarga (overhead) de gerenciamento.
     */
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < TAMANHO; ++i) {
        a[i] = x[i] * x[i] + y[i] * y[i] + z[i] * z[i];
    }

    // Fim da medição de tempo para a versão paralela.
    auto end_par = std::chrono::high_resolution_clock::now();

    // Cálculo da duração para a versão paralela.
    std::chrono::duration<double, std::milli> duration_par = end_par - start_par;

    std::cout << "Tempo de execucao: " << duration_par.count() << " ms" << std::endl;
    // std::cout << "Resultado de a[0]: " << a[0] << std::endl; // Opcional: para verificar o resultado

    return 0;
}