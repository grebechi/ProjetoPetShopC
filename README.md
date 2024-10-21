# Projeto de Pet Shop - Algoritmos e Programação II

Este projeto foi desenvolvido como parte da disciplina de **Algoritmos e Programação II** do **IFRS - Campus Osório**, ministrada pelo professor **Marcelo Paravisi**.

## Proposta do Projeto

O tema do projeto foi definido pelo professor e trata-se da implementação de um sistema de Pet Shop especializado em felinos. O objetivo principal do sistema é gerenciar clientes, pets, serviços e os serviços prestados aos pets. Além disso, o projeto tem como foco auxiliar no entendimento de conceitos importantes de **Programação Orientada a Objetos (POO)**, mesmo que a linguagem utilizada seja **C**, que não é uma linguagem orientada a objetos.

### Estrutura do Projeto

Embora o C não seja orientado a objetos, o projeto foi desenvolvido utilizando uma estrutura que simula alguns conceitos de POO, como:

- **Structs**: Cada entidade no sistema (Clientes, Pets, Serviços, e Serviços Prestados) é representada por uma struct que armazena os dados.
- **Encapsulamento**: As variáveis internas de cada entidade são encapsuladas dentro de seus respectivos arquivos `.c` e são acessíveis apenas através de funções.
- **Separação em Arquivos**: O código foi organizado em arquivos de cabeçalho (`.h`) e arquivos de implementação (`.c`) para cada entidade, permitindo um código mais modular e organizado.

### Funcionalidades

O sistema permite:

- Cadastrar, listar, buscar e excluir **clientes**, **pets**, e **serviços**.
- Registrar e listar **serviços prestados** aos pets.
- Adicionar valores pré-definidos para clientes e serviços, facilitando a realização de testes.
- Trabalhar com **alocação dinâmica de memória**, redimensionando os arrays conforme necessário.

### Alocação Dinâmica e Memória

Um dos pontos mais interessantes deste projeto foi o trabalho com **alocação dinâmica** de memória, que nos permite gerenciar manualmente a memória usada para armazenar dados em **arrays** de structs. Isso nos leva a um maior entendimento sobre o funcionamento da **memória HEAP** e **STACK**, algo que muitas vezes passa despercebido em linguagens de alto nível, como **JavaScript** e **Python**.

Neste projeto, os arrays de structs são dinamicamente alocados e redimensionados utilizando as funções `malloc()` e `realloc()`. O sistema aumenta ou diminui o tamanho dos arrays de acordo com a necessidade, garantindo que a memória seja usada de maneira eficiente.

### Testando o VSCode como IDE

Outro aspecto interessante deste projeto foi a oportunidade de testar o **Visual Studio Code (VSCode)** como **IDE** para desenvolvimento em C. Minha máquina principal possui **MacOS**, que não oferece suporte nativo à IDE utilizada pelo professor (DEV-C++). Como alternativa, experimentei o **Xcode** e o **VSCode**, mas achei muito mais simples e versátil criar as **tasks** no VSCode para compilar automaticamente os códigos e gerar o arquivo executável da aplicação.

O **VSCode** foi uma excelente escolha para este projeto, principalmente pela sua flexibilidade e a facilidade de configuração das tasks.

### Atualizações Futuras

Este projeto foi uma excelente oportunidade para aplicar conceitos fundamentais da linguagem C e aprender mais sobre gestão de memória e estruturação de código. No futuro, pretendo expandir o sistema para incluir a **manipulação de arquivos**, permitindo que os dados dos clientes, pets e serviços sejam salvos e recuperados de um **banco de dados local**, simulando um ambiente mais próximo de sistemas reais.

### Conclusão

Desenvolver este projeto foi uma experiência extremamente enriquecedora. A prática com alocação dinâmica de memória, o entendimento sobre o uso de **structs** e a organização do código em arquivos separados proporcionaram um aprendizado profundo sobre como estruturar sistemas de maneira eficiente, mesmo em linguagens de baixo nível como C. Mal posso esperar para expandir o projeto e aplicar ainda mais conceitos que aprendi ao longo do curso.

---

### Como Executar

Para compilar e executar o sistema, utilize o seguinte comando no terminal:

```bash
gcc main.c Cliente.c Pet.c Servico.c Prestados.c -o petshop_app
./petshop_app
