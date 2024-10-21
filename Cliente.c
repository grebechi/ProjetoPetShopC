#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Cliente.h"

#define TAMANHO_INICIAL 5

static Cliente *clientes = NULL;
static int totalClientes = 0;
static int tamanhoClientes = TAMANHO_INICIAL;

// Função para inicializar o array de clientes
bool inicializarClientes() {
    clientes = (Cliente *)malloc(tamanhoClientes * sizeof(Cliente));
    if (clientes == NULL) {
        return false; // Falha ao alocar memória
    }
    return true;
}

// Função para encerrar e liberar a memória
void encerrarClientes() {
    free(clientes);
    clientes = NULL;
    totalClientes = 0;
    tamanhoClientes = TAMANHO_INICIAL;
}

// Função para redimensionar o array de clientes (aumentar/diminuir)
void ajustarTamanhoClientes() {
    if (totalClientes == tamanhoClientes) {
        // Aumentar o tamanho do array
        tamanhoClientes *= 2;
        clientes = (Cliente *)realloc(clientes, tamanhoClientes * sizeof(Cliente));
    } else if (totalClientes < tamanhoClientes / 2 && tamanhoClientes > TAMANHO_INICIAL) {
        // Reduzir o tamanho do array
        tamanhoClientes /= 2;
        clientes = (Cliente *)realloc(clientes, tamanhoClientes * sizeof(Cliente));
    }
}

// Função para cadastrar um cliente
bool cadastrarCliente(const char *nome, const char *tel, const char *cpf) {
    if (totalClientes == tamanhoClientes) {
        ajustarTamanhoClientes();
    }

    Cliente novoCliente;
    novoCliente.cod = totalClientes + 1;
    strncpy(novoCliente.nome, nome, sizeof(novoCliente.nome));
    strncpy(novoCliente.tel, tel, sizeof(novoCliente.tel));
    strncpy(novoCliente.cpf, cpf, sizeof(novoCliente.cpf));

    clientes[totalClientes] = novoCliente;
    totalClientes++;

    return true;
}

// Função para buscar um cliente pelo nome
Cliente* buscarClientePorNome(const char *nome) {
    for (int i = 0; i < totalClientes; i++) {
        if (strcmp(clientes[i].nome, nome) == 0) {
            return &clientes[i];
        }
    }
    return NULL; // Cliente não encontrado
}

// Função para buscar um cliente pelo código
Cliente* buscarClientePorCodigo(int cod) {
    for (int i = 0; i < totalClientes; i++) {
        if (clientes[i].cod == cod) {
            return &clientes[i];
        }
    }
    return NULL; // Cliente não encontrado
}

// Função para excluir um cliente pelo código
bool excluirClientePorCodigo(int cod) {
    for (int i = 0; i < totalClientes; i++) {
        if (clientes[i].cod == cod) {
            for (int j = i; j < totalClientes - 1; j++) {
                clientes[j] = clientes[j + 1]; // Mover os clientes restantes
            }
            totalClientes--;
            ajustarTamanhoClientes(); // Ajustar o tamanho do array se necessário
            return true;
        }
    }
    return false; // Cliente não encontrado
}

// Função para listar clientes e retornar o array de clientes
Cliente* listarClientes(int *quantidade) {
    *quantidade = totalClientes;
    return clientes;
}

// Função para obter a quantidade de clientes
int quantidadeClientes() {
    return totalClientes;
}
