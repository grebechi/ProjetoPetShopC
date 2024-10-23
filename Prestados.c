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

// Função para comparar lucros (para qsort)
int compararLucro(const void *a, const void *b) {
    LucroServico *servicoA = (LucroServico *)a;
    LucroServico *servicoB = (LucroServico *)b;
    return (servicoB->lucroTotal - servicoA->lucroTotal);  // Ordem decrescente
}

// Função para calcular os lucros dos serviços prestados e retornar o array de lucros
LucroServico* calcularLucroServicosPrestados(int *totalLucros) {
    int quantidade;
    ServicoPrestado *listaServicosPrestados = listarPrestacoes(&quantidade);  // Obtém a lista de serviços prestados

    if (quantidade == 0) {
        *totalLucros = 0;
        free(listaServicosPrestados);  // Liberar a memória da lista de serviços prestados
        return NULL;
    }

    // Criar um array para armazenar os lucros por serviço (máximo igual ao total de serviços prestados)
    LucroServico *lucros = (LucroServico *)malloc(quantidade * sizeof(LucroServico));
    *totalLucros = 0;

    // Agrupar os lucros por serviço
    for (int i = 0; i < quantidade; i++) {
        Servico *servico = buscarServicoPorCodigo(listaServicosPrestados[i].codServico);
        if (servico == NULL) {
            continue;
        }

        float lucro = servico->valorCobrado - servico->valorCusto;  // Calcular o lucro

        // Verificar se o serviço já está no array de lucros
        int encontrado = 0;
        for (int j = 0; j < *totalLucros; j++) {
            if (lucros[j].codServico == servico->cod) {
                lucros[j].lucroTotal += lucro;  // Somar o lucro
                encontrado = 1;
                break;
            }
        }

        // Se o serviço não foi encontrado, adicioná-lo ao array
        if (!encontrado) {
            lucros[*totalLucros].codServico = servico->cod;
            lucros[*totalLucros].lucroTotal = lucro;
            strncpy(lucros[*totalLucros].nomeServico, servico->nome, sizeof(lucros[*totalLucros].nomeServico) - 1);
            lucros[*totalLucros].nomeServico[sizeof(lucros[*totalLucros].nomeServico) - 1] = '\0';  // Garantir terminação nula
            (*totalLucros)++;
        }

        free(servico);  // Liberar a memória do serviço
    }

    free(listaServicosPrestados);  // Liberar a memória da lista de serviços prestados

    // Ordenar os serviços pelo lucro total (do maior para o menor)
    qsort(lucros, *totalLucros, sizeof(LucroServico), compararLucro);

    return lucros;
}

// Função para buscar serviços prestados por pet
ServicoPrestado* buscarPrestacaoPorPet(int codPet) {
      for (int i = 0; i < totalPrestados; i++) {
        if (prestados[i].codPet == codPet) {
            // Alocar memória para o serviço prestado temporário
            ServicoPrestado *prestacaoTemp = (ServicoPrestado *)malloc(sizeof(ServicoPrestado));
            if (prestacaoTemp == NULL) {
                return NULL; // Falha na alocação de memória
            }

            // Copiar os dados da prestação encontrada para o temporário
            *prestacaoTemp = prestados[i];
            return prestacaoTemp;
        }
    }
    return NULL; // Serviço prestado não encontrado
}

// Função para listar serviços prestados e retornar o array de serviços prestados
ServicoPrestado* listarPrestacoes(int *quantidade) {
     *quantidade = totalPrestados;

    // Alocar memória para o array temporário de serviços prestados
    ServicoPrestado *prestacoesTemp = (ServicoPrestado *)malloc(totalPrestados * sizeof(ServicoPrestado));
    if (prestacoesTemp == NULL) {
        return NULL; // Falha na alocação de memória
    }

    // Copiar os dados dos serviços prestados para o array temporário
    for (int i = 0; i < totalPrestados; i++) {
        prestacoesTemp[i] = prestados[i];
    }

    return prestacoesTemp;

}

// Função para obter a quantidade de serviços prestados
int quantidadePrestacoes() {
    return totalPrestados;
}
