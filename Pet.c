#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pet.h"

#define TAMANHO_INICIAL 5

static Pet *pets = NULL;
static int totalPets = 0;
static int tamanhoPets = TAMANHO_INICIAL;

// Função para inicializar o array de pets
bool inicializarPets() {
    pets = (Pet *)malloc(tamanhoPets * sizeof(Pet));
    if (pets == NULL) {
        return false; // Falha ao alocar memória
    }
    return true;
}

// Função para encerrar e liberar a memória
void encerrarPets() {
    free(pets);
    pets = NULL;
    totalPets = 0;
    tamanhoPets = TAMANHO_INICIAL;
}

// Função para redimensionar o array de pets (aumentar/diminuir)
void ajustarTamanhoPets() {
    if (totalPets == tamanhoPets) {
        tamanhoPets *= 2;
        pets = (Pet *)realloc(pets, tamanhoPets * sizeof(Pet));
    } else if (totalPets < tamanhoPets / 2 && tamanhoPets > TAMANHO_INICIAL) {
        tamanhoPets /= 2;
        pets = (Pet *)realloc(pets, tamanhoPets * sizeof(Pet));
    }
}

// Função para cadastrar um pet
bool cadastrarPet(const char *nome, const char *especie, int codCliente) {
    if (totalPets == tamanhoPets) {
        ajustarTamanhoPets();
    }

    Pet novoPet;
    novoPet.cod = totalPets + 1;
    strncpy(novoPet.nome, nome, sizeof(novoPet.nome));
    strncpy(novoPet.especie, especie, sizeof(novoPet.especie));
    novoPet.codCliente = codCliente;

    pets[totalPets] = novoPet;
    totalPets++;

    return true;
}

// Função para buscar um pet pelo nome
Pet* buscarPetPorNome(const char *nome) {
     for (int i = 0; i < totalPets; i++) {
        if (strcasecmp(pets[i].nome, nome) == 0) {
            // Alocar memória para o pet temporário
            Pet *petTemp = (Pet *)malloc(sizeof(Pet));
            if (petTemp == NULL) {
                return NULL; // Falha na alocação de memória
            }

            // Copiar os dados do pet encontrado para o pet temporário
            *petTemp = pets[i];
            return petTemp;
        }
    }
    return NULL; // Pet não encontrado
}

// Função para buscar um pet pelo código
Pet* buscarPetPorCodigo(int cod) {
    for (int i = 0; i < totalPets; i++) {
        if (pets[i].cod == cod) {
            // Alocar memória para o pet temporário
            Pet *petTemp = (Pet *)malloc(sizeof(Pet));
            if (petTemp == NULL) {
                return NULL; // Falha na alocação de memória
            }

            // Copiar os dados do pet encontrado para o pet temporário
            *petTemp = pets[i];
            return petTemp;
        }
    }
    return NULL; // Pet não encontrado
}


// Exclui todos os pets vinculados a um cliente
void excluirPetsPorCliente(int codCliente) {
    int quantidade;
    Pet *listaPets = listarPets(&quantidade);

    for (int i = 0; i < quantidade; i++) {
        if (listaPets[i].codCliente == codCliente) {
            excluirPetPorCodigo(listaPets[i].cod); // Exclui o pet
        }
    }
}

// Função para excluir um pet pelo código
bool excluirPetPorCodigo(int cod) {
    for (int i = 0; i < totalPets; i++) {
        if (pets[i].cod == cod) {
            for (int j = i; j < totalPets - 1; j++) {
                pets[j] = pets[j + 1]; // Mover os pets restantes
            }
            totalPets--;
            ajustarTamanhoPets(); // Ajustar o tamanho do array se necessário
            return true;
        }
    }
    return false; // Pet não encontrado
}

// Função para listar pets e retornar o array de pets
Pet* listarPets(int *quantidade) {
    *quantidade = totalPets;

    // Alocar memória para o array de pets temporário
    Pet *petsTemp = (Pet *)malloc(totalPets * sizeof(Pet));
    if (petsTemp == NULL) {
        return NULL; // Falha na alocação de memória
    }

    // Copiar os dados dos pets para o array temporário
    for (int i = 0; i < totalPets; i++) {
        petsTemp[i] = pets[i];
    }

    return petsTemp;
}

// Função para obter a quantidade de pets
int quantidadePets() {
    return totalPets;
}
