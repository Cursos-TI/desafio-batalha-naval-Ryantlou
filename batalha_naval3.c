#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definição de constantes de tamanho e identificadores visuais
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define TAMANHO_HABILIDADE 5 // Matrizes de habilidade 5x5

#define AGUA 0
#define NAVIO 3
#define EFEITO 5

// Protótipos das funções auxiliares de inicialização e exibição
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int origemL, int origemC);

int main() {
    // Matriz principal do tabuleiro inicializada com água (0)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {AGUA};

    // Declaração das 3 matrizes de habilidades especiais (5x5)
    int habilidadeCone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE] = {0};
    int habilidadeCruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE] = {0};
    int habilidadeOctaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE] = {0};

    // Centro das matrizes de habilidade (para matriz 5x5, o centro é o índice 2)
    int centro = TAMANHO_HABILIDADE / 2;

    // =========================================================================
    // 1. REPRODUÇÃO DOS 4 NAVIOS (Níveis Novato e Aventureiro)
    // =========================================================================
    // Horizontal (linha 1), Vertical (coluna 1), Diagonais (iniciando em 0,6 e 7,5)
    for (int i = 0; i < TAMANHO_NAVIO; i++) tabuleiro[1][2 + i] = NAVIO;
    for (int i = 0; i < TAMANHO_NAVIO; i++) tabuleiro[4 + i][1] = NAVIO;
    for (int i = 0; i < TAMANHO_NAVIO; i++) tabuleiro[0 + i][6 + i] = NAVIO;
    for (int i = 0; i < TAMANHO_NAVIO; i++) tabuleiro[7 + i][5 - i] = NAVIO;


    // =========================================================================
    // 2. CONSTRUÇÃO DINÂMICA DAS MATRIZES DE HABILIDADE (Uso de Condicionais)
    // =========================================================================
    for (int l = 0; l < TAMANHO_HABILIDADE; l++) {
        for (int c = 0; c < TAMANHO_HABILIDADE; c++) {
            
            // A. Lógica do CONE (Origem no topo/centro e expande para baixo)
            // A largura expande simetricamente conforme as linhas aumentam
            if (l >= centro && c >= (centro - (l - centro)) && c <= (centro + (l - centro))) {
                habilidadeCone[l][c] = 1;
            }

            // B. Lógica da CRUZ (Linha central ou Coluna central)
            if (l == centro || c == centro) {
                habilidadeCruz[l][c] = 1;
            }

            // C. Lógica do OCTAEDRO / LOSANGO (Distância de Manhattan até o centro)
            // A soma da distância absoluta da linha e coluna ao centro deve ser <= raio do centro
            if ((abs(l - centro) + abs(c - centro)) <= centro) {
                habilidadeOctaedro[l][c] = 1;
            }
        }
    }


    // =========================================================================
    // 3. INTEGRAÇÃO E SOBREPOSIÇÃO NO TABULEIRO PRINCIPAL
    // Definição dos pontos de origem (coordenadas centrais da habilidade no tabuleiro)
    // =========================================================================
    
    // Define a origem do Cone na linha 4, coluna 4
    int origemConeL = 4, origemConeC = 4;
    // Define a origem da Cruz na linha 2, coluna 8
    int origemCruzL = 2, origemCruzC = 8;
    // Define a origem do Octaedro na linha 7, coluna 7
    int origemOctaedoL = 7, origemOctaedoC = 7;

    // Aplicação das habilidades sobrepondo ao tabuleiro original com validação de bordas
    aplicarHabilidade(tabuleiro, habilidadeCone, origemConeL, origemConeC);
    aplicarHabilidade(tabuleiro, habilidadeCruz, origemCruzL, origemCruzC);
    aplicarHabilidade(tabuleiro, habilidadeOctaedro, origemOctaedoL, origemOctaedoC);


    // =========================================================================
    // 4. EXIBIÇÃO DO RESULTADO COMPLETO NO CONSOLE
    // =========================================================================
    printf("========== TABULEIRO BATALHA NAVAL - NIVEL MESTRE ==========\n");
    printf("Legenda: 0 = Agua | 3 = Navio | 5 = Area de Efeito de Habilidade\n\n");
    exibirTabuleiro(tabuleiro);
    printf("============================================================\n");

    return 0;
}

// =========================================================================
// FUNÇÕES AUXILIARES E DE CONTROLE
// =========================================================================

// Função para aplicar e centrar a matriz de efeito 5x5 em uma coordenada do tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int origemL, int origemC) {
    int centro = TAMANHO_HABILIDADE / 2;

    for (int l = 0; l < TAMANHO_HABILIDADE; l++) {
        for (int c = 0; c < TAMANHO_HABILIDADE; c++) {
            
            // Se a posição da matriz de habilidade está ativa (1)
            if (habilidade[l][c] == 1) {
                // Calcula a posição correspondente no tabuleiro transladando o centro
                int tabL = origemL + (l - centro);
                int tabC = origemC + (c - centro);

                // Condicional crítica: Garante que a área de efeito permaneça dentro dos limites 10x10
                if (tabL >= 0 && tabL < TAMANHO_TABULEIRO && tabC >= 0 && tabC < TAMANHO_TABULEIRO) {
                    // Sobrepõe marcando visualmente com o valor 5 (Área afetada)
                    tabuleiro[tabL][tabC] = EFEITO;
                }
            }
        }
    }
}

// Função para renderizar e formatar o tabuleiro na tela
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int l = 0; l < TAMANHO_TABULEIRO; l++) {
        for (int c = 0; c < TAMANHO_TABULEIRO; c++) {
            printf("%d ", tabuleiro[l][c]);
        }
        printf("\n");
    }
}