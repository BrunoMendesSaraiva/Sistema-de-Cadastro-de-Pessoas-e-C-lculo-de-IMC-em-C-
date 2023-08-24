#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <locale.h>
#include <stdexcept>

// Definição da estrutura Pessoa
struct Pessoa {
    std::string nome;
    int idade;
    float peso;
    float altura;
};

// Função para calcular o IMC
float calcularIMC(float peso, float altura) {
    return peso / (altura * altura);
}

// Função para verificar se a string contém apenas letras
bool contemApenasLetras(const std::string& str) {
    for (char c : str) {
        if (!std::isalpha(c) && !std::isspace(c)) {
            return false;
        }
    }
    return true;
}

// Função para cadastrar uma pessoa e armazená-la internamente
void cadastrarPessoa(std::vector<Pessoa>& pessoas) {
    Pessoa pessoa;

    try{
        std::cout << "Digite o nome: ";
        std::cin.ignore();
        std::getline(std::cin, pessoa.nome);

        if (!contemApenasLetras(pessoa.nome)) {
            throw std::invalid_argument("Nome inválido. O nome deve conter apenas letras.");
        }

        if (pessoa.nome.length() < 3 || pessoa.nome.length() > 50) {
            throw std::invalid_argument("Nome inválido. O nome deve ter entre 3 e 50 letras.");
        }

        if (!std::isupper(pessoa.nome[0])) {
            throw std::invalid_argument("Nome inválido. A primeira letra deve ser maiúscula.");
        }

        std::cout << "Digite a idade: ";
        std::cin >> pessoa.idade;
        if (pessoa.idade <= 0 || pessoa.idade > 150) {
            throw std::invalid_argument("Idade inválida. A idade deve ser positiva e razoável.");
        }

        std::cout << "Digite o peso (em kg): ";
        std::string pesoStr;
        std::cin >> pesoStr;
        try {
            pessoa.peso = std::stof(pesoStr);
            if (pessoa.peso <= 0 || pessoa.peso > 500) {
                throw std::invalid_argument("Peso inválido. O peso deve ser positivo e razoável.");
            }
            if (pessoa.peso <= 0) {
                throw std::invalid_argument("Peso inválido. O peso deve ser positivo.");
            }
        }
        catch (const std::exception& e) {
            throw std::invalid_argument("Peso inválido. Use '.' como separador decimal.");
        }

        std::cout << "Digite a altura (em metros): ";
        std::string alturaStr;
        std::cin >> alturaStr;
        try {
            pessoa.altura = std::stof(alturaStr);
            if (pessoa.altura <= 0 || pessoa.altura > 3) {
                throw std::invalid_argument("Altura inválida. A altura deve ser positiva e razoável.");
            }
        } catch (const std::exception& e) {
            throw std::invalid_argument("Altura inválida. Use '.' como separador decimal.");
        }

        pessoas.push_back(pessoa);
        std::cout << "Pessoa cadastrada com sucesso!\n";
    }
    catch (const std::exception& e) {
        std::cout << "Erro ao cadastrar pessoa: " << e.what() << std::endl;
    }
}

// Função para listar pessoas cadastradas com nomes, idades e IMCs
void listarPessoas(const std::vector<Pessoa>& pessoas) {
    std::cout << "\nLista de pessoas cadastradas:\n";
    for (const Pessoa& pessoa : pessoas) {
        float imc = calcularIMC(pessoa.peso, pessoa.altura);
        std::cout << "Nome: " << pessoa.nome << "\tIdade: " << pessoa.idade << "\tIMC: " << imc << "\n";
    }
    
}

// Função para pesquisar pessoa por nome e mostrar seus dados
void pesquisarPorNome(const std::vector<Pessoa>& pessoas, const std::string& nome) {
    bool encontrada = false;
    for (const Pessoa& pessoa : pessoas) {
        if (pessoa.nome == nome) {
            encontrada = true;
            float imc = calcularIMC(pessoa.peso, pessoa.altura);
            std::cout << "\nPessoa encontrada:\n";
            std::cout << "Nome: " << pessoa.nome << "\tIdade: " << pessoa.idade << "\tIMC: " << imc << "\n";
            break; 
        }
    }
    if (!encontrada) {
        std::cout << "\nPessoa não encontrada.\n";  
    }
}
// Função para limpar o console
int sair() {
    std::cout << "\n \n \n";
    system("PAUSE");
    system("cls");
    return 0;
}

// Função para imprimir observação baseada no IMC
void imprimirObservacaoIMC(float imc) {
    if (imc < 18.5) {
        std::cout << "Obs: Você está abaixo do peso\n";
    }
    else if (imc < 24) {
        std::cout << "Obs: Você está com peso normal\n";
    }
    else if (imc < 29) {
        std::cout << "Obs: Você está acima do peso\n";
    }
    else {
        std::cout << "Obs: Infelizmente, você está obeso\n";
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    std::vector<Pessoa> pessoas; // Armazenar as pessoas cadastradas
    int opcao = 0;

    
    do {
        switch(opcao) {
        case 0:
            std::cout << "\nMenu:\n";
            std::cout << "1. Cadastrar pessoa\n";
            std::cout << "2. Listar pessoas cadastradas\n";
            std::cout << "3. Pesquisar pessoa por nome\n";
            std::cout << "4. Sair\n";
            std::cout << "Escolha uma opção: ";
            std::cin >> opcao;
            break;
        case 1:
            cadastrarPessoa(pessoas);
            opcao = sair();
            system("cls");
            break;
            
        case 2:
            system("cls");
            listarPessoas(pessoas);
            opcao = sair();
            break;
         
        case 3: {
            system("cls");
            std::cin.ignore();
            std::string nome;
            std::cout << "Digite o nome da pessoa a pesquisar: ";
            std::getline(std::cin, nome);
            pesquisarPorNome(pessoas, nome);
            opcao = sair();
            break;
        }
        case 4:
            std::cout << "Encerrando o programa.\n";
            break;

        default:
            std::cout << "Opção inválida.\n";
            opcao = sair();
        }
    } while (opcao != 4);
    system("cls");
    std::cout << "O programa foi encerrado!";

    return 0;
}