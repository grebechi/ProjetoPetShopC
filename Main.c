#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Cliente.h"
#include "Pet.h"
#include "Servico.h"
#include "Prestados.h"

// Estrutura para armazenar o código do pet e o lucro total
typedef struct {
    int codPet;
    float lucroTotal;
} PetLucro;

// Estrutura para armazenar o código do cliente e o lucro total
typedef struct {
    int codCliente;
    float lucroTotal;
} ClienteLucro;

void exibirPrestacoes() {
    int quantidade;
    ServicoPrestado *listaServicosPrestados = listarPrestacoes(&quantidade);  // Obtém os serviços prestados
    float lucroTotal = 0;  // Variável para armazenar o lucro total

    if (quantidade == 0) {
        printf("Nenhum serviço prestado registrado.\n");
    } else {
        for (int i = 0; i < quantidade; i++) {
            // Buscar o pet
            Pet *pet = buscarPetPorCodigo(listaServicosPrestados[i].codPet);

            // Buscar o cliente associado ao pet, se o pet foi encontrado
            Cliente *cliente = NULL;
            if (pet != NULL) {
                cliente = buscarClientePorCodigo(pet->codCliente);
            }

            // Buscar o serviço
            Servico *servico = buscarServicoPorCodigo(listaServicosPrestados[i].codServico);

            // Exibir as informações formatadas
            printf("Serviço Prestado - Data: %s\n", listaServicosPrestados[i].data);

            // Verificar quais informações foram encontradas e exibir apenas o que foi encontrado
            if (pet != NULL) {
                printf("Pet: %s (Código: %d)\n", pet->nome, pet->cod);
            } else {
                printf("Pet: Não encontrado (Código: %d)\n", listaServicosPrestados[i].codPet);
            }

            if (cliente != NULL) {
                printf("Cliente: %s (Código: %d)\n", cliente->nome, cliente->cod);
            } else if (pet != NULL) {
                printf("Cliente: Não encontrado para o pet %s (Código: %d)\n", pet->nome, pet->cod);
            }

            if (servico != NULL) {
                printf("Serviço: %s (Código: %d)\n", servico->nome, servico->cod);
            } else {
                printf("Serviço: Não encontrado (Código: %d)\n", listaServicosPrestados[i].codServico);
            }

            // Exibir o lucro do serviço prestado
            printf("Lucro: R$: %.2f\n\n", listaServicosPrestados[i].lucro);

            // Somar o lucro ao total
            lucroTotal += listaServicosPrestados[i].lucro;

            // Liberar a memória alocada para pet, cliente e serviço, se encontrados
            if (pet != NULL) free(pet);
            if (cliente != NULL) free(cliente);
            if (servico != NULL) free(servico);
        }
    }

    // Exibir o lucro total de todos os serviços listados
    printf("\nLucro total de todos os serviços: R$: %.2f\n", lucroTotal);

    // Liberar a memória da lista de serviços prestados
    free(listaServicosPrestados);
}

void exibirLucroTotalServicos() {
    int quantidade;
    ServicoPrestado *listaServicosPrestados = listarPrestacoes(&quantidade);  // Obtém a lista de serviços prestados

    if (quantidade == 0) {
        printf("Nenhum serviço prestado registrado.\n");
        return;
    }

    // Array para armazenar os lucros por serviço (assumindo que não haverá mais de 'quantidade' serviços diferentes)
    float lucros[quantidade];  // Array para armazenar os lucros totais por serviço
    int codigosServicos[quantidade];  // Array para armazenar os códigos dos serviços
    int totalServicos = 0;

    // Inicializar os arrays
    for (int i = 0; i < quantidade; i++) {
        lucros[i] = 0;
        codigosServicos[i] = 0;
    }

    // Agrupar os lucros por código de serviço
    for (int i = 0; i < quantidade; i++) {
        int codigoAtual = listaServicosPrestados[i].codServico;

        // Verificar se o serviço já está no array de lucros
        int encontrado = 0;
        for (int j = 0; j < totalServicos; j++) {
            if (codigosServicos[j] == codigoAtual) {
                lucros[j] += listaServicosPrestados[i].lucro;  // Somar o lucro
                encontrado = 1;
                break;
            }
        }

        // Se o serviço não foi encontrado, adicioná-lo ao array
        if (!encontrado) {
            codigosServicos[totalServicos] = codigoAtual;
            lucros[totalServicos] = listaServicosPrestados[i].lucro;
            totalServicos++;
        }
    }

    // Exibir os resultados
    printf("\n--- Lucros dos Serviços Prestados ---\n");
    for (int i = 0; i < totalServicos; i++) {
        // Buscar o nome do serviço pelo código
        Servico *servico = buscarServicoPorCodigo(codigosServicos[i]);
        if (servico != NULL) {
            printf("Serviço: %s (Código: %d), Lucro total: R$: %.2f\n",
                   servico->nome, servico->cod, lucros[i]);
            free(servico);  // Liberar a memória do serviço
        }
    }

    free(listaServicosPrestados);  // Liberar a memória da lista de serviços prestados
}

// Função para comparar os lucros (para qsort)
int compararLucros(const void *a, const void *b) {
    PetLucro *lucroA = (PetLucro *)a;
    PetLucro *lucroB = (PetLucro *)b;
    return (lucroB->lucroTotal - lucroA->lucroTotal);  // Ordenar em ordem decrescente
}

void exibirLucroPorPet() {
    int quantidade;
    ServicoPrestado *listaServicosPrestados = listarPrestacoes(&quantidade);  // Obtém a lista de serviços prestados

    if (quantidade == 0) {
        printf("Nenhum serviço prestado registrado.\n");
        return;
    }

    // Array para armazenar o lucro total por pet
    PetLucro petLucros[quantidade];
    int totalPets = 0;

    // Inicializar os arrays de lucros
    for (int i = 0; i < quantidade; i++) {
        petLucros[i].codPet = 0;
        petLucros[i].lucroTotal = 0;
    }

    // Agrupar os lucros por pet
    for (int i = 0; i < quantidade; i++) {
        int codigoPetAtual = listaServicosPrestados[i].codPet;

        // Verificar se o pet já está no array de lucros
        int encontrado = 0;
        for (int j = 0; j < totalPets; j++) {
            if (petLucros[j].codPet == codigoPetAtual) {
                petLucros[j].lucroTotal += listaServicosPrestados[i].lucro;  // Somar o lucro
                encontrado = 1;
                break;
            }
        }

        // Se o pet não foi encontrado, adicioná-lo ao array
        if (!encontrado) {
            petLucros[totalPets].codPet = codigoPetAtual;
            petLucros[totalPets].lucroTotal = listaServicosPrestados[i].lucro;
            totalPets++;
        }
    }

    // Ordenar os pets pelo lucro total em ordem decrescente
    qsort(petLucros, totalPets, sizeof(PetLucro), compararLucros);

    float lucroTotalGeral = 0;  // Variável para calcular o lucro total exibido

    // Exibir os resultados
    printf("\n--- Ranking de Pets que Mais Trouxeram Lucro ---\n");
    for (int i = 0; i < totalPets; i++) {
        // Buscar o pet e o cliente pelo código do pet
        Pet *pet = buscarPetPorCodigo(petLucros[i].codPet);
        if (pet != NULL) {
            Cliente *cliente = buscarClientePorCodigo(pet->codCliente);
            if (cliente != NULL) {
                printf("Pet: %s (Código: %d), Cliente: %s (Código: %d), Lucro total: R$: %.2f\n",
                       pet->nome, pet->cod,
                       cliente->nome, cliente->cod,
                       petLucros[i].lucroTotal);
                free(cliente);  // Liberar a memória do cliente
            }
            free(pet);  // Liberar a memória do pet
            // Somar apenas os lucros dos pets que estão sendo exibidos
            lucroTotalGeral += petLucros[i].lucroTotal;
        }
    }

    // Exibir o lucro total geral apenas dos pets listados
    printf("\nLucro total de todos os pets listados: R$: %.2f\n", lucroTotalGeral);

    free(listaServicosPrestados);  // Liberar a memória da lista de serviços prestados
}

void exibirLucroPorCliente() {
    int quantidade;
    ServicoPrestado *listaServicosPrestados = listarPrestacoes(&quantidade);  // Obtém a lista de serviços prestados

    if (quantidade == 0) {
        printf("Nenhum serviço prestado registrado.\n");
        return;
    }

    // Array para armazenar o lucro total por cliente
    ClienteLucro clienteLucros[quantidade];
    int totalClientes = 0;
    float lucroTotalGeral = 0;

    // Inicializar os arrays de lucros
    for (int i = 0; i < quantidade; i++) {
        clienteLucros[i].codCliente = 0;
        clienteLucros[i].lucroTotal = 0;
    }

    // Agrupar os lucros por cliente
    for (int i = 0; i < quantidade; i++) {
        // Buscar o pet para obter o código do cliente
        Pet *pet = buscarPetPorCodigo(listaServicosPrestados[i].codPet);
        if (pet == NULL) {
            continue;  // Ignora se o pet não for encontrado
        }

        int codigoClienteAtual = pet->codCliente;

        // Verificar se o cliente já está no array de lucros
        int encontrado = 0;
        for (int j = 0; j < totalClientes; j++) {
            if (clienteLucros[j].codCliente == codigoClienteAtual) {
                clienteLucros[j].lucroTotal += listaServicosPrestados[i].lucro;  // Somar o lucro
                encontrado = 1;
                break;
            }
        }

        // Se o cliente não foi encontrado, adicioná-lo ao array
        if (!encontrado) {
            clienteLucros[totalClientes].codCliente = codigoClienteAtual;
            clienteLucros[totalClientes].lucroTotal = listaServicosPrestados[i].lucro;
            totalClientes++;
        }

        free(pet);  // Liberar a memória do pet
    }

    // Ordenar os clientes pelo lucro total em ordem decrescente
    qsort(clienteLucros, totalClientes, sizeof(ClienteLucro), compararLucros);

    // Exibir os resultados
    printf("\n--- Ranking de Clientes que Mais Trouxeram Lucro ---\n");
    for (int i = 0; i < totalClientes; i++) {
        // Buscar o cliente pelo código
        Cliente *cliente = buscarClientePorCodigo(clienteLucros[i].codCliente);
        if (cliente != NULL) {
            printf("Cliente: %s (Código: %d), Lucro total: R$: %.2f\n",
                   cliente->nome, cliente->cod, clienteLucros[i].lucroTotal);
            free(cliente);  // Liberar a memória do cliente
        }

        // Somar o lucro total de todos os clientes
        lucroTotalGeral += clienteLucros[i].lucroTotal;
    }

    // Exibir o lucro total geral
    printf("\nLucro total de todos os clientes: R$: %.2f\n", lucroTotalGeral);

    free(listaServicosPrestados);  // Liberar a memória da lista de serviços prestados
}

// Função para o menu de Serviços Prestados
void menuPrestados() {
    int opcao;
    do {
        system("clear");  // Limpa o terminal a cada ciclo do menu
        printf("\n--- Menu de Serviços Prestados ---\n");
        printf("0. Voltar\n");
        printf("1. Listar serviços prestados\n");
        printf("2. Registrar serviço prestado\n");
        printf("3. Ver lucro por serviço\n");
        printf("4. Ver pet que mais trouxe lucro\n"); 
        printf("5. Ver cliente que mais trouxe lucro\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            case 1:
                exibirPrestacoes();
                break;
            case 2: {
                int codPet, codServico;
                char data[11];
                printf("Digite o código do pet: ");
                scanf("%d", &codPet);
                printf("Digite o código do serviço: ");
                scanf("%d", &codServico);
                printf("Digite a data (DD/MM/AAAA): ");
                scanf(" %[^\n]", data);

                // Tentar registrar o serviço prestado
                int resultado = registrarPrestacao(codPet, codServico, data);

                if (resultado == 1) {
                    printf("Erro: Pet com o código %d não encontrado.\n", codPet);
                } else if (resultado == 2) {
                    printf("Erro: Serviço com o código %d não encontrado.\n", codServico);
                } else {
                    printf("Serviço registrado com sucesso!\n");
                }
                break;
            }
            case 3:{
                exibirLucroTotalServicos();  // Exibir os lucros agrupados por serviço
                break;
            }
            case 4:{
                exibirLucroPorPet();  // Exibir o ranking de pets que mais trouxeram lucro
                break;
            }
            case 5:{
                exibirLucroPorCliente();  // Exibir o ranking de clientes que mais trouxeram lucro
                break;
            }
            default:
                printf("Opção inválida!\n");
                break;
        }
        printf("\nPressione qualquer tecla para continuar...\n");
        getchar(); // Aguarda o usuário pressionar uma tecla
        getchar(); // Para capturar corretamente o Enter após a escolha de menu
    } while (opcao != 0);
}



// Variável para controlar se os serviços pré-definidos já foram adicionados
bool servicosPredefinidosAdicionados = false;

// Função para adicionar valores pré-definidos de serviços
void adicionarServicosPredefinidos() {
    const char *nomes[20] = {
        "Banho", "Tosa", "Vacina", "Consulta", "Exame", 
        "Banho Medicinal", "Escovação de Dentes", "Limpeza de Ouvido", "Corte de Unhas", "Aplicação de Antipulgas",
        "Hidratação", "Tosa Higiênica", "Banho com Hidratação", "Banho Aromático", "Vermifugação",
        "Tosa Completa", "Checkup Completo", "Banho a Seco", "Desembaraçamento", "Clareamento Dental"
    };

    float valoresCobrados[20] = {
        50.00, 70.00, 90.00, 100.00, 150.00, 
        60.00, 40.00, 35.00, 20.00, 55.00,
        80.00, 45.00, 65.00, 75.00, 110.00,
        95.00, 120.00, 85.00, 105.00, 130.00
    };

    float valoresCustos[20] = {
        20.00, 30.00, 45.00, 50.00, 80.00, 
        25.00, 15.00, 12.00, 8.00, 25.00,
        35.00, 18.00, 28.00, 30.00, 50.00,
        40.00, 55.00, 38.00, 48.00, 60.00
    };

    for (int i = 0; i < 20; i++) {
        cadastrarServico(nomes[i], valoresCobrados[i], valoresCustos[i]);
    }

    servicosPredefinidosAdicionados = true;
    printf("Serviços pré-definidos adicionados com sucesso!\n");
}

void exibirServicos() {
    int quantidade;
    Servico *servicos = listarServicos(&quantidade);  // Obtém a lista de serviços

    if (servicos == NULL) {
        printf("Erro ao alocar memória para serviços.\n");
        return;
    }

    if (quantidade == 0) {
        printf("Nenhum serviço cadastrado.\n");
    } else {
        for (int i = 0; i < quantidade; i++) {
            printf("Código: %d, Nome: %s, Valor Cobrado: %.2f, Valor de Custo: %.2f\n", 
                   servicos[i].cod, servicos[i].nome, servicos[i].valorCobrado, servicos[i].valorCusto);
        }
    }

    free(servicos);  // Libera a memória do array de serviços temporário após o uso

}

// Função para o menu de Serviços
void menuServicos() {
    int opcao;
    do {
        system("clear");  // Limpa o terminal a cada ciclo do menu
        printf("\n--- Menu de Serviços ---\n");
        printf("0. Voltar\n");
        printf("1. Listar serviços\n");
        printf("2. Cadastrar serviço\n");
        printf("3. Pesquisar serviço por nome\n");
        printf("4. Pesquisar serviço por codigo\n");
        printf("5. Atualizar dados do serviço\n");
        printf("6. Excluir serviço por código\n");

        // Verifica se os serviços pré-definidos já foram adicionados
        if (!servicosPredefinidosAdicionados) {
            printf("7. Adicionar serviços pré-definidos (apenas uma vez)\n");
        }

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            case 1:
                exibirServicos();
                break;
            case 2: {
                char nome[100];
                float valorCobrado, valorCusto;
                printf("Digite o nome do serviço: ");
                scanf(" %[^\n]", nome);
                printf("Digite o valor cobrado: ");
                scanf("%f", &valorCobrado);
                printf("Digite o valor de custo: ");
                scanf("%f", &valorCusto);
                cadastrarServico(nome, valorCobrado, valorCusto);
                break;
            }
            case 3: {
                char nome[100];
                printf("Digite o nome do serviço: ");
                scanf(" %[^\n]", nome);

                Servico *servico = buscarServicoPorNome(nome);
                if (servico) {
                    printf("Serviço encontrado: Nome: %s, Valor Cobrado: %.2f, Valor de Custo: %.2f\n", 
                        servico->nome, servico->valorCobrado, servico->valorCusto);
                    free(servico);  // Libera a memória do serviço temporário após o uso
                } else {
                    printf("Serviço não encontrado.\n");
                }
                break;
            }
            case 4: {
                int codServico;
                printf("Digite o código do serviço: ");
                scanf("%d", &codServico);

                Servico *servico = buscarServicoPorCodigo(codServico);
                if (servico) {
                    printf("Serviço encontrado: Nome: %s, Valor Cobrado: %.2f, Valor de Custo: %.2f\n", 
                        servico->nome, servico->valorCobrado, servico->valorCusto);
                    free(servico);  // Libera a memória do serviço temporário após o uso
                } else {
                    printf("Serviço não encontrado.\n");
                }
                break;
            }
            case 5: {
                int codServico;
                char nome[100];
                float valorCobrado, valorCusto;

                printf("Digite o código do serviço a ser atualizado: ");
                scanf("%d", &codServico);

                // Buscar o serviço para exibir os detalhes
                Servico *servico = buscarServicoPorCodigo(codServico);

                if (servico == NULL) {
                    printf("Erro: Serviço com o código %d não encontrado.\n", codServico);
                    return;
                }

                // Exibir os detalhes atuais do serviço
                printf("\nServiço encontrado:\n");
                printf("Código: %d, Nome: %s, Valor Cobrado: %.2f, Valor de Custo: %.2f\n", 
                    servico->cod, servico->nome, servico->valorCobrado, servico->valorCusto);

                // Armazenar os valores antigos para exibição posterior
                char nomeAntigo[100];
                float valorCobradoAntigo = servico->valorCobrado;
                float valorCustoAntigo = servico->valorCusto;
                strcpy(nomeAntigo, servico->nome);

                // Solicitar novos valores
                printf("\nDigite o novo nome do serviço: ");
                scanf(" %[^\n]", nome);
                printf("Digite o novo valor cobrado: ");
                scanf("%f", &valorCobrado);
                printf("Digite o novo valor de custo: ");
                scanf("%f", &valorCusto);

                // Atualizar o serviço com os novos valores
                if (atualizarServico(codServico, nome, valorCobrado, valorCusto)) {
                    printf("\nServiço atualizado com sucesso.\n");

                    // Exibir os valores antigos e os novos
                    printf("\nValores antigos:\n");
                    printf("Nome: %s, Valor Cobrado: %.2f, Valor de Custo: %.2f\n",
                        nomeAntigo, valorCobradoAntigo, valorCustoAntigo);

                    printf("\nNovos valores:\n");
                    printf("Nome: %s, Valor Cobrado: %.2f, Valor de Custo: %.2f\n",
                        nome, valorCobrado, valorCusto);
                } else {
                    printf("Erro ao atualizar o serviço.\n");
                }
                break;
            }
            case 6: {
                int cod;
                printf("Digite o código do serviço: ");
                scanf("%d", &cod);
                if (excluirServicoPorCodigo(cod)) {
                    printf("Serviço excluído com sucesso.\n");
                } else {
                    printf("Serviço não encontrado.\n");
                }
                break;
            }
            case 7:
                if (!servicosPredefinidosAdicionados) {
                    adicionarServicosPredefinidos();
                } else {
                    printf("Opção inválida!\n");
                }
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
        printf("\nPressione qualquer tecla para continuar...\n");
        getchar(); // Aguarda o usuário pressionar uma tecla
        getchar(); // Para capturar corretamente o Enter após a escolha de menu
    } while (opcao != 0);
}


// Variável para controlar se os valores pré-definidos já foram adicionados
bool clientesPredefinidosAdicionados = false;

// Função para adicionar valores pré-definidos de clientes
void adicionarClientesPredefinidos() {
    const char *nomes[10] = {"Alice", "Bruno", "Carlos", "Daniela", "Eduardo", "Fernanda", "Gabriel", "Helena", "Isabel", "Joaquim"};
    const char *tels[10] = {"1111-1111", "2222-2222", "3333-3333", "4444-4444", "5555-5555", "6666-6666", "7777-7777", "8888-8888", "9999-9999", "1010-1010"};
    const char *cpfs[10] = {"111.111.111-11", "222.222.222-22", "333.333.333-33", "444.444.444-44", "555.555.555-55", "666.666.666-66", "777.777.777-77", "888.888.888-88", "999.999.999-99", "101.101.101-10"};

    for (int i = 0; i < 10; i++) {
        cadastrarCliente(nomes[i], tels[i], cpfs[i]);
    }
    clientesPredefinidosAdicionados = true;
    printf("Clientes pré-definidos adicionados com sucesso!\n");
}

// Função para exibir a lista de clientes
void exibirClientes() {
    int quantidade;
    Cliente *clientes = listarClientes(&quantidade); // Obtém a lista de clientes

    if (clientes == NULL) {
        printf("Erro ao alocar memória para clientes.\n");
        return;
    }

    if (quantidade == 0) {
        printf("Nenhum cliente cadastrado.\n");
    } else {
        for (int i = 0; i < quantidade; i++) {
            printf("Código: %d, Nome: %s, Telefone: %s, CPF: %s\n", clientes[i].cod, clientes[i].nome, clientes[i].tel, clientes[i].cpf);
        }
    }

    free(clientes);  // Libera a memória do array de clientes temporário após o uso

}

// Função para exibir clientes e seus pets
void exibirClientesComPets() {
    Cliente *clientes;
    Pet *pets;
    int quantidadeClientes, quantidadePets;

    // Obtém todos os clientes e pets
    listarClientesComPets(&clientes, &pets, &quantidadeClientes, &quantidadePets);

    if (quantidadeClientes == 0) {
        printf("Nenhum cliente cadastrado.\n");
    } else {
        // Exibe cada cliente e os pets associados
        for (int i = 0; i < quantidadeClientes; i++) {
            printf("Cliente: %s (Código: %d, Telefone: %s, CPF: %s)\n", clientes[i].nome, clientes[i].cod, clientes[i].tel, clientes[i].cpf);
            bool temPets = false;

            // Verifica se há pets vinculados ao cliente
            for (int j = 0; j < quantidadePets; j++) {
                if (pets[j].codCliente == clientes[i].cod) {
                    if (!temPets) {
                        printf("  Pets:\n");
                        temPets = true;
                    }
                    printf("    - Pet: %s (Espécie: %s, Código Pet: %d)\n", pets[j].nome, pets[j].especie, pets[j].cod);
                }
            }

            if (!temPets) {
                printf("  Nenhum pet vinculado a este cliente.\n");
            }
        }
    }
}

// Função para verificar pets vinculados ao cliente e, se o usuário confirmar, excluir o cliente e os pets
void excluirClienteComVerificacao(int codCliente) {
    int quantidadePetsVinculados;
    Pet *petsVinculados = NULL;

    if (verificarPetsVinculados(codCliente, &petsVinculados, &quantidadePetsVinculados)) {
        printf("O cliente possui %d pet(s) vinculado(s):\n", quantidadePetsVinculados);
        for (int i = 0; i < quantidadePetsVinculados; i++) {
            printf("Pet %d - Nome: %s, Espécie: %s\n", petsVinculados[i].cod, petsVinculados[i].nome, petsVinculados[i].especie);
        }

        char confirmacao;
        printf("Deseja continuar e excluir o cliente e seus pets vinculados? (s/n): ");
        scanf(" %c", &confirmacao);

        if (confirmacao == 's' || confirmacao == 'S') {
            excluirClientePorCodigo(codCliente); // Exclui o cliente
            excluirPetsPorCliente(codCliente); // Exclui os pets vinculados
            printf("Cliente e pets excluídos com sucesso.\n");
        } else {
            printf("Operação de exclusão cancelada.\n");
        }

        free(petsVinculados); // Libera a memória alocada para os pets vinculados
    } else {
        // Se não houver pets vinculados, exclui o cliente diretamente
        if (excluirClientePorCodigo(codCliente)) {
            printf("Cliente excluído com sucesso.\n");
        } else {
            printf("Cliente não encontrado.\n");
        }
    }
}

// Função para o menu de Clientes
void menuClientes() {
    int opcao;
    do {
        system("clear");
        printf("\n--- Menu de Clientes ---\n");
        printf("0. Voltar\n");
        printf("1. Listar clientes\n");
        printf("2. Listar clientes e pets\n");  // Nova opção
        printf("3. Cadastrar cliente\n");
        printf("4. Pesquisar cliente por nome\n");
        printf("5. Pesquisar cliente por código\n");
        printf("6. Excluir cliente por código\n");

        if (!clientesPredefinidosAdicionados) {
            printf("7. Adicionar clientes pré-definidos (apenas uma vez)\n");
        }

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            case 1:
                exibirClientes(); // Usar a nova função para exibir clientes
                break;
            case 2:
                exibirClientesComPets();  // Chama a nova função
                break;
            case 3: {
                char nome[100], tel[15], cpf[14];
                printf("Digite o nome: ");
                scanf(" %[^\n]", nome);
                printf("Digite o telefone: ");
                scanf(" %[^\n]", tel);
                printf("Digite o CPF: ");
                scanf(" %[^\n]", cpf);
                cadastrarCliente(nome, tel, cpf);
                break;
            }
            case 4: {
                 char nome[100];
                printf("Digite o nome do cliente: ");
                scanf(" %[^\n]", nome);
                Cliente *cliente = buscarClientePorNome(nome);
                if (cliente) {
                    printf("Cliente encontrado: Nome: %s, Telefone: %s, CPF: %s\n", cliente->nome, cliente->tel, cliente->cpf);
                    free(cliente);  // Libera a memória do cliente temporário após o uso
                } else {
                    printf("Cliente não encontrado.\n");
                }
                break;
            }

             case 5: {
                int codCliente;
                printf("Digite o código do cliente: ");
                scanf("%d", &codCliente);
                Cliente *cliente = buscarClientePorCodigo(codCliente);
                
                if (cliente) {
                    printf("Cliente encontrado: Nome: %s, Telefone: %s, CPF: %s\n", cliente->nome, cliente->tel, cliente->cpf);
                    free(cliente);  // Libera a memória do cliente temporário após o uso
                } else {
                    printf("Cliente não encontrado.\n");
                }
                break;
            }
            case 6: {
                int codCliente;
                printf("Digite o código do cliente: ");
                scanf("%d", &codCliente);
                excluirClienteComVerificacao(codCliente);
                break;
            }
            case 7:
                if (!clientesPredefinidosAdicionados) {
                    adicionarClientesPredefinidos();
                } else {
                    printf("Opção inválida!\n");
                }
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }

        printf("\nPressione qualquer tecla para continuar...\n");
        getchar(); // Aguarda o usuário pressionar uma tecla
        getchar(); // Para capturar corretamente o Enter após a escolha de menu
    } while (opcao != 0);
}

void exibirPets() {
    int quantidade;
    Pet *listaPets = listarPets(&quantidade); // Obtém o array e a quantidade

     if (listaPets == NULL) {
        printf("Erro ao alocar memória para pets.\n");
        return;
    }

    if (quantidade == 0) {
        printf("Nenhum pet cadastrado.\n");
    } else {
        for (int i = 0; i < quantidade; i++) {
            Cliente *cliente = buscarClientePorCodigo(listaPets[i].codCliente); // Busca o cliente pelo código

            if (cliente != NULL) {
                printf("Código: %d, Nome: %s, Espécie: %s, Cliente: %s (Código: %d)\n",
                       listaPets[i].cod, listaPets[i].nome, listaPets[i].especie,
                       cliente->nome, cliente->cod);
            } else {
                printf("Código: %d, Nome: %s, Espécie: %s, Cliente não encontrado (Código Cliente: %d)\n",
                       listaPets[i].cod, listaPets[i].nome, listaPets[i].especie,
                       listaPets[i].codCliente);
            }
        }
    }

    free(listaPets);  // Libera a memória do array de listaPets temporário após o uso
}
// Função para o menu de Pets
void menuPets() {
    int opcao;
    do {
        system("clear");  // Limpa o terminal a cada ciclo do menu
        printf("\n--- Menu de Pets ---\n");
        printf("0. Voltar\n");
        printf("1. Listar pets\n");
        printf("2. Cadastrar pet\n");
        printf("3. Pesquisar pet por nome\n");
        printf("4. Pesquisar pet por nome\n");
        printf("5. Excluir pet por código\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            case 1:
                exibirPets();
                break;
            case 2: {
                char nome[100], especie[30];
                int codCliente;
                printf("Digite o nome do pet: ");
                scanf(" %[^\n]", nome);
                printf("Digite a espécie: ");
                scanf(" %[^\n]", especie);
                printf("Digite o código do cliente: ");
                scanf("%d", &codCliente);
                cadastrarPet(nome, especie, codCliente);
                break;
            }
            case 3: {
                char nome[100];
                printf("Digite o nome do pet: ");
                scanf(" %[^\n]", nome);
                Pet* pet = buscarPetPorNome(nome);
                if (pet) {
                    printf("Pet encontrado: Nome: %s, Espécie: %s, Código Cliente: %d\n", pet->nome, pet->especie, pet->codCliente);
                    free(pet);  // Libera a memória do pet temporário após o uso
                } else {
                    printf("Pet não encontrado.\n");
                }
                break;
            }
            case 4: {
                int codPet;
                printf("Digite o código do pet: ");
                scanf("%d", &codPet);

                Pet *pet = buscarPetPorCodigo(codPet);
                if (pet) {
                    printf("Pet encontrado: Nome: %s, Espécie: %s, Código Cliente: %d\n", pet->nome, pet->especie, pet->codCliente);
                    free(pet);  // Libera a memória do pet temporário após o uso
                } else {
                    printf("Pet não encontrado.\n");
                }
            }
            case 5: {
                int cod;
                printf("Digite o código do pet: ");
                scanf("%d", &cod);
                if (excluirPetPorCodigo(cod)) {
                    printf("Pet excluído com sucesso.\n");
                } else {
                    printf("Pet não encontrado.\n");
                }
                break;
            }
            default:
                printf("Opção inválida!\n");
                break;
        }
        printf("\nPressione qualquer tecla para continuar...\n");
        getchar(); // Aguarda o usuário pressionar uma tecla
        getchar(); // Para capturar corretamente o Enter após a escolha de menu
    } while (opcao != 0);
}

// Menu principal
void menuPrincipal() {
    int opcao;
    do {
        system("clear");  // Limpa o terminal a cada ciclo do menu
        printf("\n--- Menu Principal ---\n");
        printf("0. Sair\n");
        printf("1. Gerenciar Clientes\n");
        printf("2. Gerenciar Pets\n");
        printf("3. Gerenciar Serviços\n");
        printf("4. Gerenciar Serviços Prestados\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 0:
                printf("Saindo do sistema...\n");
                break;
            case 1:
                menuClientes();  // Vai para o menu de Clientes
                break;
            case 2:
                menuPets();  // Vai para o menu de Pets
                break;
            case 3:
                menuServicos();  // Vai para o menu de Serviços
                break;
            case 4:
                menuPrestados();  // Vai para o menu de Serviços Prestados
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (opcao != 0);
}

int main() {
    // Inicializando clientes, pets, serviços e serviços prestados
    if (!inicializarClientes() || !inicializarPets() || !inicializarServicos() || !inicializarPrestados()) {
        printf("Erro ao inicializar o sistema.\n");
        return 1;
    }

    menuPrincipal(); // Chama o menu principal

    // Encerrando e liberando a memória
    encerrarClientes();
    encerrarPets();
    encerrarServicos();
    encerrarPrestados();

    return 0;
}