/*
-------------------------------------------------------------------
Exercício 1 — “Hello World” Paralelo
a) Crie uma região paralela com #pragma omp parallel.
b) Cada thread deve imprimir uma mensagem indicando seu número (omp_get_thread_num()) 
   e o total de threads (omp_get_num_threads()).
c) Configure o programa para rodar com 4 threads.
-------------------------------------------------------------------
*/


// ---------------------------------------------------------------------------------
// --- Bibliotecas Incluídas ---
// ---------------------------------------------------------------------------------

/*
 * #include <iostream>
 * Descrição: Esta é uma biblioteca padrão do C++ para operações de entrada e saída
 * (Input/Output Stream). Ela é essencial para que possamos exibir informações
 * no console do usuário. Neste código, a utilizamos para ter acesso ao objeto 'std::cout',
 * que nos permite imprimir texto na tela.
 */
#include <iostream>

/*
 * #include <omp.h>
 * Descrição: Esta é a biblioteca principal do OpenMP (Open Multi-Processing).
 * Incluir este cabeçalho é fundamental para utilizar as funcionalidades de
 * paralelismo que o OpenMP oferece. Ele nos dá acesso a:
 * - Diretivas de compilador (como #pragma omp parallel).
 * - Funções da biblioteca de runtime (como omp_get_thread_num() e omp_get_num_threads()).
 */
#include <omp.h>


// ---------------------------------------------------------------------------------
// --- Função Principal (main) ---
// ---------------------------------------------------------------------------------

/*
 * int main()
 * Descrição: Esta é a função principal, o ponto de entrada de qualquer programa C++.
 * A execução do código começa aqui.
 *
 * Parâmetros:
 * - Nenhum.
 *
 * Retorno:
 * - Retorna um valor inteiro (int). Por convenção, o valor 0 indica que o
 * programa foi executado com sucesso.
 */
int main() {

    // -----------------------------------------------------------------------------
    // --- Início da Região Paralela ---
    // -----------------------------------------------------------------------------

    /*
     * #pragma omp parallel num_threads(4)
     * Descrição: Esta é uma diretiva do OpenMP que instrui o compilador a criar
     * uma região paralela. O bloco de código que vem logo a seguir (delimitado
     * por chaves {}) será executado por múltiplas threads simultaneamente.
     *
     * Cláusulas e Parâmetros:
     * - 'parallel': É o comando que define a criação da região paralela.
     * - 'num_threads(4)': É uma cláusula que especifica o número exato de threads
     * que devem ser criadas para executar esta região. Neste caso, estamos
     * fixando o número de threads em 4, conforme solicitado no enunciado.
     * Se esta cláusula fosse omitida, o sistema OpenMP decidiria o número
     * de threads (geralmente com base no número de núcleos do processador).
     */
    #pragma omp parallel num_threads(4)
    {
        // O código dentro deste bloco será executado por cada uma das 4 threads.

        // --- Variáveis locais de cada thread ---

        /*
         * int thread_id = omp_get_thread_num();
         * Descrição: Declaração de uma variável inteira chamada 'thread_id'.
         * Cada thread que executa este código terá sua própria cópia desta variável.
         * A função 'omp_get_thread_num()' é chamada para obter o identificador
         * (ID) único da thread atual dentro da equipe de threads. Os IDs são
         * numerados a partir de 0. Portanto, para 4 threads, teremos IDs 0, 1, 2 e 3.
         */
        int thread_id = omp_get_thread_num();

        /*
         * int total_threads = omp_get_num_threads();
         * Descrição: Declaração de uma variável inteira chamada 'total_threads'.
         * Assim como 'thread_id', cada thread terá sua própria cópia.
         * A função 'omp_get_num_threads()' retorna o número total de threads
         * que estão atualmente ativas na região paralela. Neste caso, o valor
         * retornado será sempre 4, pois foi o que definimos na diretiva omp parallel.
         */
        int total_threads = omp_get_num_threads();

        // --- Saída de Dados ---

        /*
         * std::cout << "Olá! Sou a thread " << thread_id << " de um total de " << total_threads << " threads." << std::endl;
         * Descrição: Esta linha de código imprime a mensagem solicitada no console.
         * - 'std::cout': Objeto de fluxo de saída padrão.
         * - '<<': Operador de inserção, usado para enviar dados para o fluxo de saída.
         * - A mensagem é construída concatenando texto fixo com os valores das
         * variáveis 'thread_id' e 'total_threads'.
         * - 'std::endl': Insere um caractere de nova linha no final da mensagem e
         * força a descarga do buffer de saída (garantindo que o texto apareça
         * imediatamente no console).
         *
         * Como cada thread executa esta linha de forma independente, teremos 4 mensagens
         * impressas na tela. A ordem em que as mensagens aparecem não é garantida,
         * pois o escalonador do sistema operacional decide qual thread executa em que momento.
         */
        std::cout << "Ola! Sou a thread " << thread_id << " de um total de " << total_threads << " threads." << std::endl;

    } // --- Fim da Região Paralela ---

    // Após este ponto, o programa volta a ser sequencial, executado apenas pela thread mestre (thread 0).

    /*
     * return 0;
     * Descrição: Indica ao sistema operacional que o programa terminou sua
     * execução sem encontrar erros.
     */
    return 0;
}