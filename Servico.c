#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Servico.h"

#define TAMANHO_INICIAL 5

static Servico *servicos = NULL;
static int totalServicos = 0;
static int tamanhoServicos = TAMANHO_INICIAL;

// Função para inicializar o array de serviços
bool inicializarServicos() {
    servicos = (Servico *)malloc(tamanhoServicos * sizeof(Servico));
    if (servicos == NULL) {
        return false; // Falha ao alocar memória
    }
    return true;
}

// Função para encerrar e liberar a memória
void encerrarServicos() {
    free(servicos);
    servicos = NULL;
    totalServicos = 0;
    tamanhoServicos = TAMANHO_INICIAL;
}

// Função para redimensionar o array de serviços (aumentar/diminuir)
void ajustarTamanhoServicos() {
    if (totalServicos == tamanhoServicos) {
        tamanhoServicos *= 2;
        servicos = (Servico *)realloc(servicos, tamanhoServicos * sizeof(Servico));
    } else if (totalServicos < tamanhoServicos / 2 && tamanhoServicos > TAMANHO_INICIAL) {
        tamanhoServicos /= 2;
        servicos = (Servico *)realloc(servicos, tamanhoServicos * sizeof(Servico));
    }
}

// Função para cadastrar um serviço
bool cadastrarServico(const char *nome, float valorCobrado, float valorCusto) {
    if (totalServicos == tamanhoServicos) {
        ajustarTamanhoServicos();
    }

    Servico novoServico;
    novoServico.cod = totalServicos + 1;
    strncpy(novoServico.nome, nome, sizeof(novoServico.nome));
    novoServico.valorCobrado = valorCobrado;
    novoServico.valorCusto = valorCusto;

    servicos[totalServicos] = novoServico;
    totalServicos++;

    return true;
}

// Função para buscar um serviço pelo nome
Servico* buscarServicoPorNome(const char *nome) {
   for (int i = 0; i < totalServicos; i++) {
        if (strcasecmp(servicos[i].nome, nome) == 0) {
            // Alocar memória para o serviço temporário
            Servico *servicoTemp = (Servico *)malloc(sizeof(Servico));
            if (servicoTemp == NULL) {
                return NULL; // Falha na alocação de memória
            }

            // Copiar os dados do serviço encontrado para o serviço temporário
            *servicoTemp = servicos[i];
            return servicoTemp;
        }
    }
    return NULL; // Serviço não encontrado
}

// Função para buscar um serviço pelo código
Servico* buscarServicoPorCodigo(int cod) {
     for (int i = 0; i < totalServicos; i++) {
        if (servicos[i].cod == cod) {
            // Alocar memória para o serviço temporário
            Servico *servicoTemp = (Servico *)malloc(sizeof(Servico));
            if (servicoTemp == NULL) {
                return NULL; // Falha na alocação de memória
            }

            // Copiar os dados do serviço encontrado para o serviço temporário
            *servicoTemp = servicos[i];
            return servicoTemp;
        }
    }
    return NULL; // Serviço não encontrado
}

// Função para excluir um serviço pelo código
bool excluirServicoPorCodigo(int cod) {
    for (int i = 0; i < totalServicos; i++) {
        if (servicos[i].cod == cod) {
            for (int j = i; j < totalServicos - 1; j++) {
                servicos[j] = servicos[j + 1]; // Mover os serviços restantes
            }
            totalServicos--;
            ajustarTamanhoServicos(); // Ajustar o tamanho do array se necessário
            return true;
        }
    }
    return false; // Serviço não encontrado
}

// Função para listar serviços e retornar o array de serviços
Servico* listarServicos(int *quantidade) {
    *quantidade = totalServicos;

    // Alocar memória para o array de serviços temporário
    Servico *servicosTemp = (Servico *)malloc(totalServicos * sizeof(Servico));
    if (servicosTemp == NULL) {
        return NULL; // Falha na alocação de memória
    }

    // Copiar os dados dos serviços para o array temporário
    for (int i = 0; i < totalServicos; i++) {
        servicosTemp[i] = servicos[i];
    }

    return servicosTemp;
}

// Função para atualizar os dados de um serviço
bool atualizarServico(int cod, const char *nome, float valorCobrado, float valorCusto) {
    for (int i = 0; i < totalServicos; i++) {
        if (servicos[i].cod == cod) {
            // Atualizar os valores do serviço
            strncpy(servicos[i].nome, nome, sizeof(servicos[i].nome));
            servicos[i].valorCobrado = valorCobrado;
            servicos[i].valorCusto = valorCusto;
            return true; // Serviço atualizado com sucesso
        }
    }
    return false; // Serviço não encontrado
}

// Função para obter a quantidade de serviços
int quantidadeServicos() {
    return totalServicos;
}
