#include <stdbool.h>
#ifndef PRESTADOS_H
#define PRESTADOS_H

typedef struct {
    int codPet;
    int codServico;
    char data[11]; // Formato: "DD/MM/AAAA"
} ServicoPrestado;

// Estrutura para armazenar os lucros por serviço
typedef struct {
    int codServico;
    float lucroTotal;
    char nomeServico[100];
} LucroServico;

// Funções para gerenciamento dos serviços prestados
bool inicializarPrestados();
void encerrarPrestados();
int registrarPrestacao(int codPet, int codServico, const char *data);
ServicoPrestado* buscarPrestacaoPorPet(int codPet);
ServicoPrestado* listarPrestacoes(int *quantidade); // Retorna um array de serviços prestados e a quantidade deles
LucroServico* calcularLucroServicosPrestados(int *totalLucros);
int quantidadePrestacoes();

#endif
