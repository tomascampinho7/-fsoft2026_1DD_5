#include <iostream>
#include <limits>
#include "Biblioteca.h"

void limparErroInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void menuVisitante(Biblioteca& biblioteca) {
    int opcao;

    do {
        std::cout << "\n=== Menu Visitante ===\n";
        std::cout << "1. Consultar catalogo\n";
        std::cout << "0. Voltar\n";
        std::cout << "Opcao: ";
        std::cin >> opcao;

        if (std::cin.fail()) {
            limparErroInput();
            opcao = -1;
        }

        switch (opcao) {
            case 1:
                biblioteca.consultarCatalogo();
                break;
            case 0:
                std::cout << "A voltar ao menu principal...\n";
                break;
            default:
                std::cout << "Opcao invalida.\n";
        }

    } while (opcao != 0);
}

void menuUtente(Biblioteca& biblioteca, Utente* utente) {
    int opcao;

    do {
        std::cout << "\n=== Menu Utente ===\n";
        std::cout << "Utente: " << utente->getNome() << "\n";
        std::cout << "1. Consultar catalogo\n";
        std::cout << "2. Requisitar livro\n";
        std::cout << "3. Consultar requisicoes ativas\n";
        std::cout << "0. Encerrar sessao\n";
        std::cout << "Opcao: ";
        std::cin >> opcao;

        if (std::cin.fail()) {
            limparErroInput();
            opcao = -1;
        }

        switch (opcao) {
            case 1:
                biblioteca.consultarCatalogo();
                break;

            case 2: {
                std::string isbn;
                std::cout << "Introduza o ISBN do livro: ";
                std::cin >> isbn;

                if (biblioteca.requisitarLivro(utente->getNumeroUtente(), isbn)) {
                    std::cout << "Livro requisitado com sucesso.\n";
                    std::cout << "Data limite de devolucao: 31/05/2026\n";
                } else {
                    std::cout << "Nao foi possivel requisitar o livro.\n";
                }

                break;
            }

            case 3:
                biblioteca.listarRequisicoesAtivas(utente->getNumeroUtente());
                break;

            case 0:
                std::cout << "Sessao encerrada com sucesso.\n";
                break;

            default:
                std::cout << "Opcao invalida.\n";
        }

    } while (opcao != 0);
}

void menuBibliotecario(Biblioteca& biblioteca) {
    int opcao;

    do {
        std::cout << "\n=== Menu Bibliotecario ===\n";
        std::cout << "1. Consultar catalogo\n";
        std::cout << "2. Adicionar livro\n";
        std::cout << "3. Remover livro\n";
        std::cout << "4. Registar devolucao\n";
        std::cout << "5. Listar utentes registados\n";
        std::cout << "0. Encerrar sessao\n";
        std::cout << "Opcao: ";
        std::cin >> opcao;

        if (std::cin.fail()) {
            limparErroInput();
            opcao = -1;
        }

        switch (opcao) {
            case 1:
                biblioteca.consultarCatalogo();
                break;

            case 2: {
                std::string isbn;
                std::string titulo;
                std::string autor;
                int ano;

                std::cout << "ISBN: ";
                std::cin >> isbn;

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "Titulo: ";
                std::getline(std::cin, titulo);

                std::cout << "Autor: ";
                std::getline(std::cin, autor);

                std::cout << "Ano de publicacao: ";
                std::cin >> ano;

                if (std::cin.fail()) {
                    limparErroInput();
                    std::cout << "Ano invalido.\n";
                    break;
                }

                Livro livro(isbn, titulo, autor, ano);

                if (biblioteca.adicionarLivro(livro)) {
                    std::cout << "Livro adicionado com sucesso.\n";
                } else {
                    std::cout << "Erro: ja existe um livro com esse ISBN.\n";
                }

                break;
            }

            case 3: {
                std::string isbn;
                std::cout << "ISBN do livro a remover: ";
                std::cin >> isbn;

                if (biblioteca.removerLivro(isbn)) {
                    std::cout << "Livro removido com sucesso.\n";
                } else {
                    std::cout << "Nao foi possivel remover o livro.\n";
                }

                break;
            }

            case 4: {
                std::string isbn;
                std::cout << "ISBN do livro devolvido: ";
                std::cin >> isbn;

                if (biblioteca.registarDevolucao(isbn)) {
                    std::cout << "Devolucao registada com sucesso.\n";
                } else {
                    std::cout << "Nao foi possivel registar a devolucao.\n";
                }

                break;
            }

            case 5:
                biblioteca.listarUtentes();
                break;

            case 0:
                std::cout << "Sessao encerrada com sucesso.\n";
                break;

            default:
                std::cout << "Opcao invalida.\n";
        }

    } while (opcao != 0);
}

void loginUtente(Biblioteca& biblioteca) {
    int numeroUtente;
    std::string password;

    std::cout << "\n=== Login Utente ===\n";
    std::cout << "Numero de utente: ";
    std::cin >> numeroUtente;

    if (std::cin.fail()) {
        limparErroInput();
        std::cout << "Numero de utente invalido.\n";
        return;
    }

    std::cout << "Password: ";
    std::cin >> password;

    Utente* utente = biblioteca.loginUtente(numeroUtente, password);

    if (utente != nullptr) {
        std::cout << "Login efetuado com sucesso.\n";
        menuUtente(biblioteca, utente);
    } else {
        std::cout << "Credenciais invalidas.\n";
    }
}

void loginBibliotecario(Biblioteca& biblioteca) {
    std::string username;
    std::string password;

    std::cout << "\n=== Login Bibliotecario ===\n";
    std::cout << "Username: ";
    std::cin >> username;

    std::cout << "Password: ";
    std::cin >> password;

    if (biblioteca.loginBibliotecario(username, password)) {
        std::cout << "Login efetuado com sucesso.\n";
        menuBibliotecario(biblioteca);
    } else {
        std::cout << "Credenciais invalidas.\n";
    }
}

int main() {
    Biblioteca biblioteca;
    int opcao;

    do {
        std::cout << "\n=== Sistema de Biblioteca ===\n";
        std::cout << "1. Entrar como visitante\n";
        std::cout << "2. Login utente\n";
        std::cout << "3. Login bibliotecario\n";
        std::cout << "0. Sair\n";
        std::cout << "Opcao: ";
        std::cin >> opcao;

        if (std::cin.fail()) {
            limparErroInput();
            opcao = -1;
        }

        switch (opcao) {
            case 1:
                menuVisitante(biblioteca);
                break;

            case 2:
                loginUtente(biblioteca);
                break;

            case 3:
                loginBibliotecario(biblioteca);
                break;

            case 0:
                std::cout << "A sair da aplicacao...\n";
                break;

            default:
                std::cout << "Opcao invalida.\n";
        }

    } while (opcao != 0);

    return 0;
}