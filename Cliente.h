#include <stdbool.h>
#ifndef CLIENTE_H
#define CLIENTE_H

#include "Pet.h"

typedef struct {
    int cod;
    char nome[100];
    char tel[15];
    char cpf[14];
} Cliente;

bool inicializarClientes();
void encerrarClientes();
bool cadastrarCliente(const char *nome, const char *tel, const char *cpf);
Cliente* buscarClientePorNome(const char *nome);
Cliente* buscarClientePorCodigo(int cod);
bool excluirClientePorCodigo(int cod);
Cliente* listarClientes(int *quantidade);
bool verificarPetsVinculados(int codCliente, Pet **petsVinculados, int *quantidade); // Verifica e retorna pets vinculados

#endif
