#include <stdbool.h>
#ifndef SERVICO_H
#define SERVICO_H

typedef struct {
    int cod;
    char nome[100];
    float valorCobrado;
    float valorCusto;
} Servico;

// Funções para gerenciamento de serviços
bool inicializarServicos();
void encerrarServicos();
bool cadastrarServico(const char *nome, float valorCobrado, float valorCusto);
Servico* buscarServicoPorNome(const char *nome);
Servico* buscarServicoPorCodigo(int cod);
bool excluirServicoPorCodigo(int cod);
Servico* listarServicos(int *quantidade); // Retorna um array de serviços e a quantidade deles
int quantidadeServicos();

#endif
