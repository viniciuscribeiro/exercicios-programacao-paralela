/*
-------------------------------------------------------------------
Exercício 2 — Paralelizando um for simples
a) Crie um vetor v de tamanho 100 e inicialize todos os elementos com o valor 1.
b) Escreva um loop sequencial que soma todos os elementos.
c) Refaça o loop com #pragma omp parallel for reduction(+:soma).
d) Compare os resultados e explique por que a diretiva reduction é necessária.
-------------------------------------------------------------------
*/


// ---------------------------------------------------------------------------------
// --- Bibliotecas Incluídas ---
// ---------------------------------------------------------------------------------

/*
 * #include <iostream>
 * Descrição: Biblioteca padrão do C++ para operações de entrada e saída.
 * Utilizada para imprimir os resultados no console com 'std::cout'.
 */
#include <iostream>

/*
 * #include <vector>
 * Descrição: Biblioteca padrão do C++ que fornece o container 'std::vector'.
 * Um vector é um array dinâmico que pode gerenciar seu próprio armazenamento,
 * sendo uma forma mais segura e flexível de trabalhar com listas de elementos
 * do que os arrays C-style.
 */
#include <vector>

/*
 * #include <omp.h>
 * Descrição: Biblioteca principal do OpenMP (Open Multi-Processing).
 * Essencial para utilizar as diretivas de paralelismo, como '#pragma omp parallel for',
 * e as cláusulas associadas, como 'reduction'.
 */
#include <omp.h>


// ---------------------------------------------------------------------------------
// --- Função Principal (main) ---
// ---------------------------------------------------------------------------------

int main() {
    // -----------------------------------------------------------------------------
    // --- a) Criação e inicialização do vetor ---
    // -----------------------------------------------------------------------------

    /*
     * const int TAMANHO = 100;
     * Descrição: Declaração de uma constante inteira para o tamanho do vetor.
     * Usar uma constante torna o código mais legível e fácil de manter, pois se
     * precisarmos alterar o tamanho, mudamos em apenas um lugar.
     */
    const int TAMANHO = 100;

    /*
     * std::vector<int> v(TAMANHO, 1);
     * Descrição: Criação do vetor 'v' solicitado.
     * - 'std::vector<int>': Declara que 'v' será um vetor de números inteiros.
     * - '(TAMANHO, 1)': Este é um construtor do std::vector que recebe dois argumentos:
     * 1. O tamanho do vetor (nossa constante TAMANHO, que é 100).
     * 2. O valor inicial para todos os elementos (neste caso, o número 1).
     * Com esta única linha, criamos o vetor 'v' com 100 elementos, todos inicializados com 1.
     */
    std::vector<int> v(TAMANHO, 1);

    // -----------------------------------------------------------------------------
    // --- b) Loop sequencial para somar os elementos ---
    // -----------------------------------------------------------------------------
    std::cout << "--- Calculo Sequencial ---" << std::endl;

    /*
     * long long soma_sequencial = 0;
     * Descrição: Declaração da variável que irá armazenar a soma dos elementos.
     * Foi escolhido o tipo 'long long' por ser uma boa prática em somatórios,
     * pois ele suporta números muito maiores que 'int', prevenindo 'overflow'
     * (quando o resultado da soma excede a capacidade da variável).
     */
    long long soma_sequencial = 0;

    /*
     * for (int i = 0; i < TAMANHO; ++i) { ... }
     * Descrição: Este é um loop 'for' padrão e sequencial.
     * Ele itera sobre cada índice do vetor, de 0 até 99 (TAMANHO - 1).
     * Em cada iteração, o valor do elemento v[i] é adicionado à variável 'soma_sequencial'.
     * Este loop é executado por uma única thread (a thread principal).
     */
    for (int i = 0; i < TAMANHO; ++i) {
        soma_sequencial += v[i];
    }

    // Impressão do resultado sequencial. O valor esperado é 100 * 1 = 100.
    std::cout << "Soma sequencial: " << soma_sequencial << std::endl << std::endl;


    // -----------------------------------------------------------------------------
    // --- c) Loop paralelo com reduction ---
    // -----------------------------------------------------------------------------
    std::cout << "--- Calculo Paralelo (Correto) ---" << std::endl;

    /*
     * long long soma_paralela = 0;
     * Descrição: Variável para armazenar o resultado da soma paralela.
     */
    long long soma_paralela = 0;

    /*
     * #pragma omp parallel for reduction(+:soma_paralela)
     * Descrição: Diretiva OpenMP que paraleliza o loop 'for' seguinte.
     * - 'parallel for': Indica que as iterações do loop podem ser divididas e
     * distribuídas entre as várias threads disponíveis.
     * - 'reduction(+:soma_paralela)': Esta é a cláusula crucial. Ela informa ao OpenMP
     * que a variável 'soma_paralela' será usada para uma operação de "redução"
     * (neste caso, uma soma, indicada pelo '+'). O OpenMP fará o seguinte:
     * 1. Criará uma cópia local e privada de 'soma_paralela' para cada thread, inicializada com 0.
     * 2. Cada thread somará sua parte dos elementos do vetor em sua cópia privada.
     * 3. Ao final do loop, o OpenMP irá somar os resultados de todas as cópias privadas
     * e armazenar o total final na variável original 'soma_paralela'.
     */
    #pragma omp parallel for reduction(+:soma_paralela)
    for (int i = 0; i < TAMANHO; ++i) {
        soma_paralela += v[i];
    }

    // Impressão do resultado paralelo. O valor esperado também é 100.
    std::cout << "Soma paralela (com reduction): " << soma_paralela << std::endl << std::endl;


    // -----------------------------------------------------------------------------
    // --- Demonstração: O que acontece sem o reduction (RESULTADO ERRADO) ---
    // -----------------------------------------------------------------------------
    std::cout << "--- Calculo Paralelo (Incorreto) ---" << std::endl;
    long long soma_paralela_errada = 0;

    // Este loop está deliberadamente errado para fins de demonstração
    #pragma omp parallel for
    for (int i = 0; i < TAMANHO; ++i) {
        // Acesso concorrente e não protegido à variável compartilhada!
        soma_paralela_errada += v[i];
    }

    std::cout << "Soma paralela (sem reduction - RESULTADO INCORRETO): " << soma_paralela_errada << std::endl;

    return 0;
}