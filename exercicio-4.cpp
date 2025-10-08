/*
-------------------------------------------------------------------
Exercício 4 — Medindo tempo por thread
Adapte o código do exercício anterior para:
a) Medir e exibir o tempo total de execução.
b) Medir e exibir o tempo gasto por cada thread.
c) Mostrar quantas threads foram utilizadas no cálculo.
-------------------------------------------------------------------
*/



// ---------------------------------------------------------------------------------
// --- Bibliotecas Incluídas ---
// ---------------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono>

// ---------------------------------------------------------------------------------
// --- Função Principal (main) ---
// ---------------------------------------------------------------------------------

int main() {
    // -----------------------------------------------------------------------------
    // --- Configuração Inicial ---
    // -----------------------------------------------------------------------------

    /*
     * const int TAMANHO = 10000000;
     * Descrição: Aumentamos o tamanho do vetor para 10 milhões de elementos.
     * Como vimos no exercício anterior, uma carga de trabalho maior torna a
     * paralelização mais vantajosa e os tempos medidos mais significativos,
     * minimizando o impacto do overhead.
     */
    const int TAMANHO = 10000000;

    std::vector<double> a(TAMANHO);
    std::vector<double> x(TAMANHO, 1.5);
    std::vector<double> y(TAMANHO, 2.5);
    std::vector<double> z(TAMANHO, 3.5);

    // Variáveis para armazenar os resultados das medições
    int num_threads_utilizadas = 0;
    std::vector<double> tempos_por_thread;

    // -----------------------------------------------------------------------------
    // --- a) Medição do Tempo Total de Execução ---
    // -----------------------------------------------------------------------------
    std::cout << "Iniciando calculo paralelo..." << std::endl;

    // Inicia a cronometragem para o tempo total da região paralela.
    auto start_total = std::chrono::high_resolution_clock::now();

    /*
     * #pragma omp parallel
     * Descrição: Inicia a região paralela. A partir daqui, o bloco de código
     * será executado por múltiplas threads. Note que separamos a diretiva 'parallel'
     * da diretiva 'for'. Fazemos isso para poder executar código que é específico
     * de cada thread ANTES e DEPOIS do loop de trabalho.
     */
    #pragma omp parallel
    {
        // --- c) Captura do número de threads ---
        /*
         * #pragma omp master
         * Descrição: Esta diretiva especifica que o bloco de código seguinte
         * será executado APENAS pela thread mestre (thread de ID 0).
         * Usamos isso para realizar operações de inicialização de forma segura,
         * evitando que todas as threads tentem modificar as mesmas variáveis
         * ao mesmo tempo (o que seria uma condição de corrida).
         */
        #pragma omp master
        {
            /*
             * num_threads_utilizadas = omp_get_num_threads();
             * Descrição: A função 'omp_get_num_threads()' retorna o número total de
             * threads na equipe atual. A thread mestre armazena este valor.
             */
            num_threads_utilizadas = omp_get_num_threads();

            /*
             * tempos_por_thread.resize(num_threads_utilizadas);
             * Descrição: Redimensiona nosso vetor de tempos para que ele tenha
             * exatamente uma posição para cada thread. Ex: se tiver 4 threads,
             * o vetor terá 4 posições (índices 0 a 3).
             */
            tempos_por_thread.resize(num_threads_utilizadas);
        }

        /*
         * #pragma omp barrier
         * Descrição: Esta é uma barreira de sincronização. NENHUMA thread pode
         * passar deste ponto até que TODAS as threads da equipe tenham chegado aqui.
         * É crucial para garantir que a inicialização feita pela thread mestre
         * (obter o número de threads e redimensionar o vetor) termine antes que
         * as outras threads tentem usar essas variáveis.
         */
        #pragma omp barrier

        // --- b) Medição do tempo por thread ---
        
        /*
         * int tid = omp_get_thread_num();
         * Descrição: Cada thread obtém seu próprio ID (0, 1, 2, ...).
         */
        int tid = omp_get_thread_num();

        // Cada thread inicia seu próprio cronômetro.
        auto start_thread = std::chrono::high_resolution_clock::now();

        /*
         * #pragma omp for schedule(static)
         * Descrição: Agora distribuímos o trabalho do loop 'for' entre as threads
         * que já foram criadas pela diretiva '#pragma omp parallel'. Cada thread
         * executará uma porção das iterações do loop.
         */
        #pragma omp for schedule(static)
        for (int i = 0; i < TAMANHO; ++i) {
            a[i] = x[i] * x[i] + y[i] * y[i] + z[i] * z[i];
        }

        // Após a thread terminar sua parte do loop, ela para seu cronômetro.
        auto end_thread = std::chrono::high_resolution_clock::now();
        
        // A duração é calculada e armazenada na posição correspondente ao ID da thread.
        std::chrono::duration<double, std::milli> duration_thread = end_thread - start_thread;
        tempos_por_thread[tid] = duration_thread.count();

    } // Fim da região paralela

    // Para a cronometragem do tempo total.
    auto end_total = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration_total = end_total - start_total;

    // -----------------------------------------------------------------------------
    // --- Exibição dos Resultados ---
    // -----------------------------------------------------------------------------
    std::cout << "\n--- Resultados ---" << std::endl;
    
    // a) Exibe o tempo total de execução.
    std::cout << "a) Tempo total de execucao: " << duration_total.count() << " ms" << std::endl;

    // c) Exibe o número de threads utilizadas.
    std::cout << "c) Numero de threads utilizadas: " << num_threads_utilizadas << std::endl;

    // b) Itera sobre o vetor de tempos e exibe o tempo gasto por cada thread.
    std::cout << "b) Tempo gasto por thread:" << std::endl;
    for (int i = 0; i < num_threads_utilizadas; ++i) {
        std::cout << "   - Thread " << i << ": " << tempos_por_thread[i] << " ms" << std::endl;
    }

    return 0;
}