#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"

// Função para inicializar as cidades a partir do arquivo
Estrada *getEstrada(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        return NULL;
    }

    Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
    if (!estrada) {
        fclose(arquivo);
        return NULL;
    }

    if (fscanf(arquivo, "%d", &estrada->T) != 1) {
        free(estrada);
        fclose(arquivo);
        return NULL;
    }

    if (estrada->T < 3 || estrada->T > 1000000) {
        free(estrada);
        fclose(arquivo);
        return NULL;
    }

    if (fscanf(arquivo, "%d", &estrada->N) != 1) {
        free(estrada);
        fclose(arquivo);
        return NULL;
    }

    if (estrada->N < 2 || estrada->N > 10000) {
        free(estrada);
        fclose(arquivo);
        return NULL;
    }

    estrada->C = (Cidade *)malloc(estrada->N * sizeof(Cidade));
    if (!estrada->C) {
        free(estrada);
        fclose(arquivo);
        return NULL;
    }

    for (int i = 0; i < estrada->N; i++) {
        if (fscanf(arquivo, "%d %255s", &estrada->C[i].Posicao, estrada->C[i].Nome) != 2) {
            free(estrada->C);
            free(estrada);
            fclose(arquivo);
            return NULL;
        }
        if (estrada->C[i].Posicao <= 0 || estrada->C[i].Posicao >= estrada->T) {
            free(estrada->C);
            free(estrada);
            fclose(arquivo);
            return NULL;
        }
    }

    fclose(arquivo);
    return estrada;
}

// Função para calcular a menor vizinhança
double calcularMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada) {
        return -1.0; // Indicador de erro
    }

    double menorVizinhanca = estrada->T; // Inicializa com o valor máximo possível

    for (int i = 0; i < estrada->N - 1; i++) {
        double vizinhanca = (estrada->C[i + 1].Posicao - estrada->C[i].Posicao) / 2.0;
        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
        }
    }

    free(estrada->C);
    free(estrada);
    return menorVizinhanca;
}

// Função para encontrar a cidade com a menor vizinhança
char *cidadeMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada) {
        return NULL; // Indicador de erro
    }

    double menorVizinhanca = estrada->T; // Inicializa com o valor máximo possível
    int cidadeIndex = -1;

    for (int i = 0; i < estrada->N - 1; i++) {
        double vizinhanca = (estrada->C[i + 1].Posicao - estrada->C[i].Posicao) / 2.0;
        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
            cidadeIndex = i;
        }
    }

    char *cidadeNome = (char *)malloc(256 * sizeof(char));
    if (cidadeIndex != -1) {
        strcpy(cidadeNome, estrada->C[cidadeIndex].Nome);
    } else {
        free(cidadeNome);
        cidadeNome = NULL;
    }

    free(estrada->C);
    free(estrada);
    return cidadeNome;
}
