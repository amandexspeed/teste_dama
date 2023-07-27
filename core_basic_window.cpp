#include "raylib.h"
#include <stdio.h>

struct Posicao
{
    int linha;
    int coluna;
};

void inicializarTabuleiro(float celulaTamanho, float raio, Texture2D pecaDama, Texture2D pecaDama2);
bool validarPosicao(int linha, int coluna);
bool validarMovimento(Posicao posicaoAtual, Posicao novaPosicao, char jogadorAtual);
void moverPeca(Posicao posicaoAtual, Posicao novaPosicao);

int tabuleiro[8][8];

int main(void)
{
    const int telaLargura = 700;
    const int telaAltura = 700;
    const float celulaTamanho = telaLargura / 8;
    const float raio = celulaTamanho / 3;
    InitWindow(telaLargura, telaAltura, "Dama");

    Texture2D pecaDama = LoadTexture("resources/peca11.png");
    Texture2D pecaDama2 = LoadTexture("resources/peca22.png");

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        Vector2 mousePosition = GetMousePosition();

        BeginDrawing();

        ClearBackground(RAYWHITE);

        inicializarTabuleiro(celulaTamanho,raio, pecaDama,pecaDama2);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

// Função para inicializar o tabuleiro com as peças nas posições iniciais
void inicializarTabuleiro(float celulaTamanho, float raio, Texture2D pecaDama, Texture2D pecaDama2)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {

            float posX = i * celulaTamanho;
            float posY = j * celulaTamanho;

            Color celulaCor = (i + j) % 2 == 0 ? WHITE : LIGHTGRAY;

            DrawRectangle(posX, posY, celulaTamanho, celulaTamanho, celulaCor);
            DrawRectangleLines(posX, posY, celulaTamanho, celulaTamanho, BLACK);

                if ((j < 3) && ((i + j) % 2 != 0))
                {
                    tabuleiro[i][j] = 'O';
                    float centroX = posX + celulaTamanho / 2;
                    float centroY = posY + celulaTamanho / 2;

                    DrawTexture(pecaDama, centroX - raio, centroY - raio, WHITE);
                }
                else if ((j > 4) && ((i + j) % 2 != 0))
                {
                    tabuleiro[i][j] = 'X'; // Peças do jogador 2 (X)
                    float centroX = posX + celulaTamanho / 2;
                    float centroY = posY + celulaTamanho / 2;

                    DrawTexture(pecaDama2, centroX - raio, centroY - raio, WHITE);
                }
                else
                {
                    tabuleiro[i][j] = ' '; // Espaços vazios
                }
        }
    }
}

// Função para verificar se uma posição é válida no tabuleiro
bool validarPosicao(int linha, int coluna)
{
    return (linha >= 0 && linha < 8 && coluna >= 0 && coluna < 8);
}

// Função para verificar se o movimento é válido para o jogador atual
bool validarMovimento(Posicao posicaoAtual, Posicao novaPosicao, char jogadorAtual)
{
    int linhaDiff = novaPosicao.linha - posicaoAtual.linha;
    int colunaDiff = novaPosicao.coluna - posicaoAtual.coluna;

    // Verifica se as posições são válidas
    if (!validarPosicao(novaPosicao.linha, novaPosicao.coluna) || !validarPosicao(posicaoAtual.linha, posicaoAtual.coluna))
        return false;

    // Verifica se a posição de destino está vazia
    if (tabuleiro[novaPosicao.linha][novaPosicao.coluna] != ' ')
        return false;

    // Verifica se o movimento é válido para o jogador atual
    if (jogadorAtual == 'O')
    {
        if (linhaDiff == 1 && (colunaDiff == 1 || colunaDiff == -1))
            return true;
    }
    else if (jogadorAtual == 'X')
    {
        if (linhaDiff == -1 && (colunaDiff == 1 || colunaDiff == -1))
            return true;
    }

    return false;
}

// Função para mover a peça para uma nova posição
void moverPeca(Posicao posicaoAtual, Posicao novaPosicao)
{
    tabuleiro[novaPosicao.linha][novaPosicao.coluna] = tabuleiro[posicaoAtual.linha][posicaoAtual.coluna];
    tabuleiro[posicaoAtual.linha][posicaoAtual.coluna] = ' ';
}
