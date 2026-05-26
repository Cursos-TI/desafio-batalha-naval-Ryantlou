#include <stdio.h>
#include <stdbool.h>

// Definição de constantes para facilitar a manutenção do código
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

int main() {
    // Matriz 10x10 que representa o tabuleiro do jogo (inicializada inteira com zero)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {AGUA};

    // Vetores unidimensionais para representar as partes de cada navio (tamanho 3)
    int navioHorizontal[TAMANHO_NAVIO] = {NAVIO, NAVIO, NAVIO};
    int navioVertical[TAMANHO_NAVIO] = {NAVIO, NAVIO, NAVIO};

    // Definição das coordenadas iniciais de posicionamento (Linha, Coluna)
    // Navio Horizontal: começará na linha 2, coluna 3 (ocupará as colunas 3, 4 e 5)
    int linhaNavioH = 2;
    int colunaNavioH = 3;

    // Navio Vertical: começará na linha 5, coluna 6 (ocupará as linhas 5, 6 e 7)
    int linhaNavioV = 5;
    int colunaNavioV = 6;

    // Variável booleana para controle de validação do posicionamento
    bool posicionamentoValido = true;

    // =========================================================================
    // 1. VALIDAÇÃO DOS LIMITES DO TABULEIRO
    // =========================================================================
    
    // Verifica se o navio horizontal ultrapassa a borda direita
    if (colunaNavioH + TAMANHO_NAVIO > TAMANHO_TABULEIRO || linhaNavioH >= TAMANHO_TABULEIRO) {
        posicionamentoValido = false;
        printf("Erro: Navio horizontal ultrapassa os limites do tabuleiro!\n");
    }

    // Verifica se o navio vertical ultrapassa a borda inferior
    if (linhaNavioV + TAMANHO_NAVIO > TAMANHO_TABULEIRO || colunaNavioV >= TAMANHO_TABULEIRO) {
        posicionamentoValido = false;
        printf("Erro: Navio vertical ultrapassa os limites do tabuleiro!\n");
    }

    // =========================================================================
    // 2. VALIDAÇÃO DE SOBREPOSIÇÃO E POSICIONAMENTO DOS NAVIOS
    // =========================================================================
    if (posicionamentoValido) {
        
        // Como os navios estão em coordenadas distantes (linha 2 e linha 5), 
        // sabemos que não há sobreposição. Vamos inseri-los copiando os dados dos vetores.

        // Posicionando o Navio Horizontal: percorre e altera as colunas mantendo a linha fixa
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linhaNavioH][colunaNavioH + i] = navioHorizontal[i];
        }

        // Posicionando o Navio Vertical: percorre e altera as linhas mantendo a coluna fixa
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linhaNavioV + i][colunaNavioV] = navioVertical[i];
        }

        printf("Navios posicionados com sucesso!\n\n");
    } else {
        printf("Falha ao posicionar os navios devido a erros de coordenada.\n\n");
        return 1; // Encerra o programa indicando erro
    }

    // =========================================================================
    // 3. EXIBIÇÃO DO TABULEIRO NO CONSOLE
    // =========================================================================
    printf("====== TABULEIRO BATALHA NAVAL ======\n");
    
    // Loops aninhados: o loop externo controla as linhas e o interno as colunas
    for (int l = 0; l < TAMANHO_TABULEIRO; l++) {
        for (int c = 0; c < TAMANHO_TABULEIRO; c++) {
            // Imprime o valor da coordenada seguido de um espaço para formatação organizada
            printf("%d ", tabuleiro[l][c]);
        }
        // Quebra de linha ao final de cada linha da matriz para gerar o formato quadrado
        printf("\n");
    }
    printf("=====================================\n");

    return 0;
}
