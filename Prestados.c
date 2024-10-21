#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Prestados.h"

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

// Função para registrar um serviço prestado
bool registrarPrestacao(int codPet, int codServico, const char *data) {
    if (totalPrestados == tamanhoPrestados) {
        ajustarTamanhoPrestados();
    }

    ServicoPrestado novoPrestado;
    novoPrestado.codPet = codPet;
    novoPrestado.codServico = codServico;
    strncpy(novoPrestado.data, data, sizeof(novoPrestado.data));

    prestados[totalPrestados] = novoPrestado;
    totalPrestados++;

    return true;
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
