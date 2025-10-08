/*
-------------------------------------------------------------------
Exercício 5 — Escalonamento
Use novamente o cálculo de a[i] = x[i]^2 + y[i]^2 + z[i]^2, mas:
a) Execute com schedule(static) e schedule(dynamic, 1000).
b) Compare os tempos em diferentes quantidades de threads (2, 4, 8).
c) Explique em quais situações static e dynamic são mais adequados.
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
// --- Função Auxiliar para Executar e Medir o Teste ---
// ---------------------------------------------------------------------------------
/*
 * void executar_teste(int num_threads, const std::string& tipo_schedule)
 * Descrição: Esta função encapsula a lógica de execução e medição de tempo
 * para uma configuração específica (um número de threads e um tipo de schedule).
 * Isso evita a repetição de código na função 'main'.
 *
 * Parâmetros:
 * - int num_threads: O número de threads que o OpenMP deve usar para o teste.
 * - const std::string& tipo_schedule: Uma string ("static" ou "dynamic") para
 * identificar qual schedule será usado e para imprimir o resultado corretamente.
 */
void executar_teste(int num_threads, const std::string& tipo_schedule) {
    const int TAMANHO = 20000000; // Aumentado para 20 milhões para ter tempos mais robustos
    std::vector<double> a(TAMANHO);
    std::vector<double> x(TAMANHO, 1.5);
    std::vector<double> y(TAMANHO, 2.5);
    std::vector<double> z(TAMANHO, 3.5);

    /*
     * omp_set_num_threads(num_threads);
     * Descrição: Função do OpenMP que define o número de threads a serem usadas
     * nas próximas regiões paralelas. É a forma programática de controlar o
     * número de threads, conforme solicitado no item (b).
     */
    omp_set_num_threads(num_threads);

    // Início da medição de tempo
    auto start_time = std::chrono::high_resolution_clock::now();

    // A região paralela começa aqui
    #pragma omp parallel
    {
        // Usamos um 'if/else' para aplicar a diretiva correta com base no parâmetro
        if (tipo_schedule == "static") {
            /*
             * #pragma omp for schedule(static)
             * Descrição: Divide as iterações em blocos de tamanho igual e as atribui
             * às threads de forma fixa antes do loop começar. É eficiente para
             * cargas de trabalho uniformes.
             */
            #pragma omp for schedule(static)
            for (int i = 0; i < TAMANHO; ++i) {
                a[i] = x[i] * x[i] + y[i] * y[i] + z[i] * z[i];
            }
        } else if (tipo_schedule == "dynamic") {
            /*
             * #pragma omp for schedule(dynamic, 1000)
             * Descrição: As iterações são divididas em blocos (chunks) de tamanho 1000.
             * Esses blocos são colocados em uma "fila de tarefas". Cada thread, ao
             * ficar livre, pega o próximo bloco da fila para processar.
             * Isso introduz mais overhead, mas é ótimo para cargas de trabalho
             * desiguais, pois evita que uma thread fique ociosa.
             */
            #pragma omp for schedule(dynamic, 1000)
            for (int i = 0; i < TAMANHO; ++i) {
                a[i] = x[i] * x[i] + y[i] * y[i] + z[i] * z[i];
            }
        }
    } // Fim da região paralela

    // Fim da medição de tempo
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end_time - start_time;

    // Imprime o resultado formatado
    std::cout << "Threads: " << num_threads << ", Schedule: " << tipo_schedule
              << ", Tempo: " << duration.count() << " ms" << std::endl;
}

// ---------------------------------------------------------------------------------
// --- Função Principal (main) ---
// ---------------------------------------------------------------------------------

int main() {
    std::cout << "--- Comparando Desempenho de Schedules OpenMP ---" << std::endl;

    // Vetor com as quantidades de threads a serem testadas
    std::vector<int> threads_para_testar = {2, 4, 8};

    for (int n_threads : threads_para_testar) {
        std::cout << "\n--- Testando com " << n_threads << " threads ---" << std::endl;
        
        // a) Executa com schedule(static)
        executar_teste(n_threads, "static");
        
        // a) Executa com schedule(dynamic, 1000)
        executar_teste(n_threads, "dynamic");
    }

    return 0;
}