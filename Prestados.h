#include <stdbool.h>
#ifndef PRESTADOS_H
#define PRESTADOS_H

typedef struct {
    int codPet;
    int codServico;
    char data[11]; // Formato: "DD/MM/AAAA"
} ServicoPrestado;

// Funções para gerenciamento dos serviços prestados
bool inicializarPrestados();
void encerrarPrestados();
int registrarPrestacao(int codPet, int codServico, const char *data);
ServicoPrestado* buscarPrestacaoPorPet(int codPet);
ServicoPrestado* listarPrestacoes(int *quantidade); // Retorna um array de serviços prestados e a quantidade deles
int quantidadePrestacoes();

#endif
