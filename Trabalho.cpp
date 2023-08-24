#include <iostream>
#include <string>
#include <vector>
#include <locale.h>
#include <stdexcept>
#include <locale>
#include <cctype>
#include <set>

// Definição da estrutura Pessoa
struct Pessoa {
    std::string nome;
    int idade;
    float peso;
    float altura;
    float imc;
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

// Função para exibir observações sobre o IMC
void exibirObservacoesIMC(float imc) {
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

// Função para converter entrada do usuário com vírgula ou ponto para float
float converterParaFloat(const std::string& str) {
    std::string cleanedStr = str;
    for (char& c : cleanedStr) {
        if (c == ',') {
            c = '.'; // Substitui vírgulas por pontos
        }
    }
    return std::stof(cleanedStr);
}

// Função para cadastrar uma pessoa e armazená-la internamente
void cadastrarPessoa(std::vector<Pessoa>& pessoas, std::set<std::string>& nomesUtilizados) {
    Pessoa pessoa;

    try {
        std::cout << "Digite o nome: ";
        std::cin.ignore();
        std::getline(std::cin, pessoa.nome);

        if (nomesUtilizados.find(pessoa.nome) != nomesUtilizados.end()) {
            throw std::invalid_argument("Nome já cadastrado. Insira um nome único ou o nome completo.");
        }

        if (!contemApenasLetras(pessoa.nome)) {
            throw std::invalid_argument("Nome inválido. O nome deve conter apenas letras.");
        }

        if (pessoa.nome.length() < 3 || pessoa.nome.length() > 50) {
            throw std::invalid_argument("Nome inválido. O nome deve ter entre 3 e 50 letras.");
        }

        if (!std::isupper(pessoa.nome[0])) {
            throw std::invalid_argument("Nome inválido. A primeira letra deve ser maiúscula.");
        }

        nomesUtilizados.insert(pessoa.nome);


        //IDADE
        std::cout << "Digite a idade: ";
        std::cin >> pessoa.idade;
        if (pessoa.idade <= 0 || pessoa.idade > 150) {
            throw std::invalid_argument("Idade inválida. A idade deve ser positiva e razoável.");
        }

        //PESO
        std::cout << "Digite o peso (em kg): ";
        std::string pesoStr;
        std::cin >> pesoStr;

        if (pesoStr.find_first_of(",.") != std::string::npos) {
            std::cout << "Peso inválido. Use apenas números inteiros, sem vírgula ou ponto.";
            return; // Retorna sem cadastrar a pessoa
        }

        try {
            pessoa.peso = converterParaFloat(pesoStr);
            if (pessoa.peso <= 0 || pessoa.peso > 500) {
                throw std::invalid_argument("Peso inválido. O peso deve ser positivo e razoável.");
            }
        }
        catch (const std::exception& e) {
            throw std::invalid_argument("Peso inválido. Insira um valor numérico.");
        }

        //ALTURA
        std::cout << "Digite a altura (em centímetros): ";
        std::string alturaStr;
        std::cin >> alturaStr;

        if (alturaStr.find_first_of(",.") != std::string::npos) {
            std::cout << "Altura inválida. Use apenas números inteiros, sem vírgula ou ponto.";
            return; // Retorna sem cadastrar a pessoa
        }

        try {
            pessoa.altura = converterParaFloat(alturaStr) / 100.0; // Convertendo para metros
            if (pessoa.altura <= 0 || pessoa.altura > 3) {
                throw std::invalid_argument("Altura inválida. A altura deve ser positiva e razoável.");
            }
        }
        catch (const std::exception& e) {
            throw std::invalid_argument("Altura inválida. Insira um valor numérico.");
        }

        pessoa.imc = calcularIMC(pessoa.peso, pessoa.altura);

        pessoas.push_back(pessoa);

        float imc = calcularIMC(pessoa.peso, pessoa.altura);
        std::cout << "IMC calculado: " << imc << std::endl;
        exibirObservacoesIMC(imc); // Chama a função para exibir observações do IMC
        std::cout << "Pessoa cadastrada com sucesso!\n";
    }
    catch (const std::exception& e) {
        std::cout << "Erro ao cadastrar pessoa: " << e.what() << std::endl;
    }
}

// Função para listar pessoas cadastradas com nomes, idades e IMCs
void listarPessoas(const std::vector<Pessoa>& pessoas) {
    if (pessoas.empty()) {
        std::cout << "Nenhuma pessoa cadastrada." << std::endl;
        return;
    }

    std::cout << "Lista de pessoas cadastradas:" << std::endl;
    for (const Pessoa& pessoa : pessoas) {
        std::cout << "Nome: " << pessoa.nome << std::endl;
        std::cout << "Idade: " << pessoa.idade << std::endl;
        std::cout << "Peso: " << pessoa.peso << " kg" << std::endl;
        std::cout << "Altura: " << pessoa.altura << " m" << std::endl;
        std::cout << "IMC: " << pessoa.imc << std::endl;
        std::cout << "-------------------" << std::endl;
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
            std::cout << "Nome: " << pessoa.nome << std::endl;
            std::cout << "Idade: " << pessoa.idade << std::endl;
            std::cout << "Peso: " << pessoa.peso << " kg" << std::endl;
            std::cout << "Altura: " << pessoa.altura << " m" << std::endl;
            std::cout << "IMC: " << pessoa.imc << std::endl;
            exibirObservacoesIMC(imc); // Chama a função para exibir observações do IMC
            std::cout << "-------------------" << std::endl;

            break; // Não é necessário continuar procurando após encontrar
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

int main() {
    setlocale(LC_ALL, "Portuguese");
    std::vector<Pessoa> pessoas;
    int opcao = 0;

    std::set<std::string> nomesUtilizados;

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
            cadastrarPessoa(pessoas, nomesUtilizados);
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