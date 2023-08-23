#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <locale.h>

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

// Função para cadastrar uma pessoa e armazená-la internamente
void cadastrarPessoa(std::vector<Pessoa>& pessoas) {
    Pessoa pessoa;

    std::cout << "Digite o nome: ";
    std::cin.ignore(); // Limpar o buffer do teclado
    std::getline(std::cin, pessoa.nome);

    std::cout << "Digite a idade: ";
    std::cin >> pessoa.idade;

    std::cout << "Digite o peso (em kg): ";
    std::cin >> pessoa.peso;

    std::cout << "Digite a altura (em metros): ";
    std::cin >> pessoa.altura;

    pessoas.push_back(pessoa);
    std::cout << "Pessoa cadastrada com sucesso!\n";
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
int sair() {
    std::cout << "\n \n \n";
    system("PAUSE");
    system("cls");
    return 0;
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