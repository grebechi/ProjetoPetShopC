#include <stdbool.h>
#ifndef PET_H
#define PET_H

typedef struct {
    int cod;
    char nome[100];
    char especie[30];
    int codCliente; // Código do cliente ao qual o pet está vinculado
} Pet;

// Funções para gerenciamento de pets
bool inicializarPets();
void encerrarPets();
bool cadastrarPet(const char *nome, const char *especie, int codCliente);
Pet* buscarPetPorNome(const char *nome);
Pet* buscarPetPorCodigo(int cod);
bool excluirPetPorCodigo(int cod);
Pet* listarPets(int *quantidade); // Retorna um array de pets e a quantidade deles

#endif
