#include <stdbool.h>
#ifndef CLIENTE_H
#define CLIENTE_H

typedef struct {
    int cod;
    char nome[100];
    char tel[15];
    char cpf[14];
} Cliente;

// Funções para gerenciamento de clientes
bool inicializarClientes();
void encerrarClientes();
bool cadastrarCliente(const char *nome, const char *tel, const char *cpf);
Cliente* buscarClientePorNome(const char *nome);
Cliente* buscarClientePorCodigo(int cod);
bool excluirClientePorCodigo(int cod);
Cliente* listarClientes(int *quantidade); // Retorna um array de clientes e a quantidade deles

#endif
