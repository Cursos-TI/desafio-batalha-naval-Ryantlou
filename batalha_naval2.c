#include <stdio.h>
#include <stdbool.h>

// Definição de constantes do jogo
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

int main() {
    // Matriz 10x10 que representa o tabuleiro, inicializada inteiramente com zero (água)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {AGUA};

    // Variável booleana para monitorar se todas as validações de posição passaram
    bool posicionamentoValido = true;

    // =========================================================================
    // DEFINIÇÃO DAS COORDENADAS INICIAIS DOS 4 NAVIOS (Tamanho fixo = 3)
    // =========================================================================
    
    // 1. Navio Horizontal (Linha constante, Coluna avança)
    int linhaH = 1, colunaH = 2;

    // 2. Navio Vertical (Linha avança, Coluna constante)
    int linhaV = 4, colunaV = 1;

    // 3. Navio Diagonal Crescente (Linha aumenta, Coluna aumenta)
    int linhaDiag1 = 0, colunaDiag1 = 6;

    // 4. Navio Diagonal Decrescente (Linha aumenta, Coluna diminui)
    int linhaDiag2 = 7, colunaDiag2 = 5;


    // =========================================================================
    // VALIDAÇÃO DE LIMITES (Garantir que nenhum navio saia da matriz 10x10)
    // =========================================================================
    
    // Valida Navio Horizontal
    if (linhaH >= TAMANHO_TABULEIRO || (colunaH + TAMANHO_NAVIO) > TAMANHO_TABULEIRO) {
        posicionamentoValido = false;
        printf("Erro: Navio Horizontal fora dos limites!\n");
    }

    // Valida Navio Vertical
    if ((linhaV + TAMANHO_NAVIO) > TAMANHO_TABULEIRO || colunaV >= TAMANHO_TABULEIRO) {
        posicionamentoValido = false;
        printf("Erro: Navio Vertical fora dos limites!\n");
    }

    // Valida Navio Diagonal Crescente (ambos os eixos aumentam 3 posições)
    if ((linhaDiag1 + TAMANHO_NAVIO) > TAMANHO_TABULEIRO || (colunaDiag1 + TAMANHO_NAVIO) > TAMANHO_TABULEIRO) {
        posicionamentoValido = false;
        printf("Erro: Navio Diagonal 1 fora dos limites!\n");
    }

    // Valida Navio Diagonal Decrescente (linha aumenta, mas coluna diminui 3 posições)
    if ((linhaDiag2 + TAMANHO_NAVIO) > TAMANHO_TABULEIRO || (colunaDiag2 - TAMANHO_NAVIO + 1) < 0) {
        posicionamentoValido = false;
        printf("Erro: Navio Diagonal 2 fora dos limites!\n");
    }


    // =========================================================================
    // VALIDAÇÃO DE SOBREPOSIÇÃO E POSICIONAMENTO REAL DOS NAVIOS
    // =========================================================================
    if (posicionamentoValido) {
        
        // 1. Posicionando o Navio Horizontal
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linhaH][colunaH + i] = NAVIO;
        }

        // 2. Posicionando o Navio Vertical
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linhaV + i][colunaV] = NAVIO;
        }

        // 3. Posicionando o Navio Diagonal Crescente (Linha++, Coluna++)
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linhaDiag1 + i][colunaDiag1 + i] = NAVIO;
        }

        // 4. Posicionando o Navio Diagonal Decrescente (Linha++, Coluna--)
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linhaDiag2 + i][colunaDiag2 - i] = NAVIO;
        }

        printf("Os 4 navios foram posicionados com sucesso!\n\n");

    } else {
        printf("Falha no posicionamento. Verifique as coordenadas inseridas.\n\n");
        return 1; // Encerra o programa em caso de erro de limites
    }


    // =========================================================================
    // EXIBIÇÃO DO TABULEIRO COMPLETO NO CONSOLE
    // =========================================================================
    printf("========== TABULEIRO COMPLETO (10x10) ==========\n");
    
    // Loops aninhados para renderizar a matriz bidimensional
    for (int l = 0; l < TAMANHO_TABULEIRO; l++) {
        for (int c = 0; c < TAMANHO_TABULEIRO; c++) {
            // Imprime o número seguido de espaço para manter o alinhamento visual
            printf("%d ", tabuleiro[l][c]);
        }
        // Quebra de linha necessária após imprimir todas as colunas da linha atual
        printf("\n");
    }
    printf("=================================================\n");

    return 0;
}