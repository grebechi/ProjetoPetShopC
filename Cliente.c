#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Cliente.h"
#include "Pet.h"

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
        if (strcasecmp(clientes[i].nome, nome) == 0) {
            // Alocar memória para o cliente temporário
            Cliente *clienteTemp = (Cliente *)malloc(sizeof(Cliente));
            if (clienteTemp == NULL) {
                return NULL; // Falha na alocação de memória
            }

            // Copiar os dados do cliente encontrado para o cliente temporário
            *clienteTemp = clientes[i];
            return clienteTemp;
        }
    }
    return NULL; // Cliente não encontrado
}

// Função para buscar um cliente pelo código
Cliente* buscarClientePorCodigo(int cod) {
    for (int i = 0; i < totalClientes; i++) {
        if (clientes[i].cod == cod) {
            // Alocar memória para o cliente temporário
            Cliente *clienteTemp = (Cliente *)malloc(sizeof(Cliente));
            if (clienteTemp == NULL) {
                return NULL; // Falha na alocação de memória
            }

            // Copiar os dados do cliente encontrado para o cliente temporário
            *clienteTemp = clientes[i];
            return clienteTemp;
        }
    }
    return NULL; // Cliente não encontrado
}

// Verifica se o cliente tem pets vinculados e retorna o array de pets vinculados
bool verificarPetsVinculados(int codCliente, Pet **petsVinculados, int *quantidade) {
    int totalPets;
    Pet *listaPets = listarPets(&totalPets); // Obtém a lista de todos os pets
    *quantidade = 0;

    for (int i = 0; i < totalPets; i++) {
        if (listaPets[i].codCliente == codCliente) {
            (*quantidade)++;
        }
    }

    // Aloca espaço para armazenar os pets vinculados, caso haja pets
    if (*quantidade > 0) {
        *petsVinculados = (Pet *)malloc((*quantidade) * sizeof(Pet));
        int index = 0;
        for (int i = 0; i < totalPets; i++) {
            if (listaPets[i].codCliente == codCliente) {
                (*petsVinculados)[index++] = listaPets[i];
            }
        }
        return true;
    }

    return false; // Nenhum pet vinculado encontrado
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

    // Alocar memória para o array de clientes temporário
    Cliente *clientesTemp = (Cliente *)malloc(totalClientes * sizeof(Cliente));
    if (clientesTemp == NULL) {
        return NULL; // Falha na alocação de memória
    }

    // Copiar os dados dos clientes para o array temporário
    for (int i = 0; i < totalClientes; i++) {
        clientesTemp[i] = clientes[i];
    }

    return clientesTemp;
}

// Função que retorna um array de clientes e seus respectivos pets
void listarClientesComPets(Cliente **clientes, Pet **pets, int *quantidadeClientes, int *quantidadePets) {
    *clientes = listarClientes(quantidadeClientes);  // Obtém todos os clientes
    *pets = listarPets(quantidadePets);  // Obtém todos os pets
}

// Função para obter a quantidade de clientes
int quantidadeClientes() {
    return totalClientes;
}
