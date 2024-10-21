#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Prestados.h"
#include "Pet.h"
#include "Servico.h"

#define TAMANHO_INICIAL 5

static ServicoPrestado *prestados = NULL;
static int totalPrestados = 0;
static int tamanhoPrestados = TAMANHO_INICIAL;

// Função para inicializar o array de serviços prestados
bool inicializarPrestados() {
    prestados = (ServicoPrestado *)malloc(tamanhoPrestados * sizeof(ServicoPrestado));
    if (prestados == NULL) {
        return false; // Falha ao alocar memória
    }
    return true;
}

// Função para encerrar e liberar a memória
void encerrarPrestados() {
    free(prestados);
    prestados = NULL;
    totalPrestados = 0;
    tamanhoPrestados = TAMANHO_INICIAL;
}

// Função para redimensionar o array de serviços prestados (aumentar/diminuir)
void ajustarTamanhoPrestados() {
    if (totalPrestados == tamanhoPrestados) {
        tamanhoPrestados *= 2;
        prestados = (ServicoPrestado *)realloc(prestados, tamanhoPrestados * sizeof(ServicoPrestado));
    } else if (totalPrestados < tamanhoPrestados / 2 && tamanhoPrestados > TAMANHO_INICIAL) {
        tamanhoPrestados /= 2;
        prestados = (ServicoPrestado *)realloc(prestados, tamanhoPrestados * sizeof(ServicoPrestado));
    }
}

// Retorna 0 se tudo estiver certo, 1 se o pet não existir, 2 se o serviço não existir
int registrarPrestacao(int codPet, int codServico, const char *data) {
    // Verificar se o pet existe
    Pet *pet = buscarPetPorCodigo(codPet);
    if (pet == NULL) {
        return 1;  // Código do pet inválido
    }

    // Verificar se o serviço existe
    Servico *servico = buscarServicoPorCodigo(codServico);
    if (servico == NULL) {
        return 2;  // Código do serviço inválido
    }

    // Registrar a prestação do serviço
    if (totalPrestados == tamanhoPrestados) {
        ajustarTamanhoPrestados();  // Realoca a memória se necessário
    }

    ServicoPrestado novaPrestacao;
    novaPrestacao.codPet = codPet;
    novaPrestacao.codServico = codServico;
    strncpy(novaPrestacao.data, data, sizeof(novaPrestacao.data));

    prestados[totalPrestados] = novaPrestacao;
    totalPrestados++;

    return 0;  // Sucesso
}

// Função para buscar serviços prestados por pet
ServicoPrestado* buscarPrestacaoPorPet(int codPet) {
    for (int i = 0; i < totalPrestados; i++) {
        if (prestados[i].codPet == codPet) {
            return &prestados[i];
        }
    }
    return NULL; // Serviço prestado não encontrado
}

// Função para listar serviços prestados e retornar o array de serviços prestados
ServicoPrestado* listarPrestacoes(int *quantidade) {
    *quantidade = totalPrestados;
    return prestados;
}

// Função para obter a quantidade de serviços prestados
int quantidadePrestacoes() {
    return totalPrestados;
}
