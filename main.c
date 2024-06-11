#include <stdio.h>
#include "cidades.h"

int main() {
    const char *nomeArquivo = "teste1.txt";

    Estrada *estrada = getEstrada(nomeArquivo);
    if (estrada == NULL) {
        printf("Erro ao ler o arquivo ou os dados estão fora dos limites permitidos.\n");
        return 1;
    }

    double menorVizinhanca = calcularMenorVizinhanca(nomeArquivo);
    if (menorVizinhanca < 0) {
        printf("Erro ao calcular a menor vizinhança.\n");
        return 1;
    }
    printf("A menor vizinhança é: %.2f\n", menorVizinhanca);

    char *cidade = cidadeMenorVizinhanca(nomeArquivo);
    if (cidade == NULL) {
        printf("Erro ao encontrar a cidade com a menor vizinhança.\n");
        return 1;
    }
    printf("A cidade com a menor vizinhança é: %s\n", cidade);

    free(cidade);
    free(estrada->C);
    free(estrada);

    return 0;
}
