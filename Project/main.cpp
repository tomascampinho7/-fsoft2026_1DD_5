#include <iostream>
#include <string>
#include <limits>
#include "Biblioteca.h"

// ─── Utilitários ─────────────────────────────────────────────────────────────

void limparBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string lerLinha(const std::string& prompt) {
    std::string valor;
    std::cout << prompt;
    std::getline(std::cin, valor);
    return valor;
}

int lerInteiro(const std::string& prompt) {
    int valor;
    std::cout << prompt;
    while (!(std::cin >> valor)) {
        std::cin.clear();
        limparBuffer();
        std::cout << "Entrada invalida. " << prompt;
    }
    limparBuffer();
    return valor;
}

// ─── Menus do Utente ─────────────────────────────────────────────────────────

void menuEditarPerfilUtente(Biblioteca& biblioteca, int numeroUtente) {
    int opcao;
    do {
        std::cout << "\n--- Editar Perfil ---\n";
        std::cout << "1. Alterar nome\n";
        std::cout << "2. Alterar email\n";
        std::cout << "3. Alterar contacto telefonico\n";
        std::cout << "4. Alterar password\n";
        std::cout << "0. Voltar\n";
        opcao = lerInteiro("Opcao: ");

        if (opcao == 1) {
            std::string nome = lerLinha("Novo nome: ");
            biblioteca.editarPerfilUtente(numeroUtente, nome, "", "");
        } else if (opcao == 2) {
            std::string email = lerLinha("Novo email: ");
            biblioteca.editarPerfilUtente(numeroUtente, "", email, "");
        } else if (opcao == 3) {
            std::string contacto = lerLinha("Novo contacto: ");
            biblioteca.editarPerfilUtente(numeroUtente, "", "", contacto);
        } else if (opcao == 4) {
            std::string atual  = lerLinha("Password atual: ");
            std::string nova   = lerLinha("Nova password: ");
            if (biblioteca.alterarPasswordUtente(numeroUtente, atual, nova)) {
                std::cout << "Password alterada com sucesso.\n";
            }
        }
    } while (opcao != 0);
}

void menuUtente(Biblioteca& biblioteca, int numeroUtente) {
    int opcao;
    do {
        std::cout << "\n=== Menu Utente ===\n";
        std::cout << "1. Consultar catalogo\n";
        std::cout << "2. Requisitar livro\n";
        std::cout << "3. Devolver livro\n";
        std::cout << "4. Ver as minhas requisicoes ativas\n";
        std::cout << "5. Editar perfil\n";
        std::cout << "0. Sair\n";
        opcao = lerInteiro("Opcao: ");

        if (opcao == 1) {
            biblioteca.consultarCatalogo();
        } else if (opcao == 2) {
            std::string isbn = lerLinha("ISBN do livro: ");
            if (biblioteca.requisitarLivro(numeroUtente, isbn)) {
                std::cout << "Livro requisitado com sucesso.\n";
            }
        } else if (opcao == 3) {
            std::string isbn = lerLinha("ISBN do livro a devolver: ");
            if (biblioteca.registarDevolucao(isbn)) {
                std::cout << "Livro devolvido com sucesso.\n";
            }
        } else if (opcao == 4) {
            biblioteca.listarRequisicoesAtivas(numeroUtente);
        } else if (opcao == 5) {
            menuEditarPerfilUtente(biblioteca, numeroUtente);
        }
    } while (opcao != 0);
}

// ─── Menus do Bibliotecário ──────────────────────────────────────────────────

void menuEditarUtenteAdmin(Biblioteca& biblioteca) {
    int numeroUtente = lerInteiro("Numero do utente a editar: ");

    int opcao;
    do {
        std::cout << "\n--- Editar Utente (Admin) ---\n";
        std::cout << "1. Alterar nome\n";
        std::cout << "2. Alterar email\n";
        std::cout << "3. Alterar contacto telefonico\n";
        std::cout << "4. Redefinir password\n";
        std::cout << "0. Voltar\n";
        opcao = lerInteiro("Opcao: ");

        if (opcao == 1) {
            std::string nome = lerLinha("Novo nome: ");
            biblioteca.editarUtenteAdmin(numeroUtente, nome, "", "");
        } else if (opcao == 2) {
            std::string email = lerLinha("Novo email: ");
            biblioteca.editarUtenteAdmin(numeroUtente, "", email, "");
        } else if (opcao == 3) {
            std::string contacto = lerLinha("Novo contacto: ");
            biblioteca.editarUtenteAdmin(numeroUtente, "", "", contacto);
        } else if (opcao == 4) {
            std::string nova = lerLinha("Nova password: ");
            biblioteca.resetPasswordUtenteAdmin(numeroUtente, nova);
        }
    } while (opcao != 0);
}

void menuEditarLivro(Biblioteca& biblioteca) {
    std::string isbn = lerLinha("ISBN do livro a editar: ");

    int opcao;
    do {
        std::cout << "\n--- Editar Livro ---\n";
        std::cout << "1. Alterar titulo\n";
        std::cout << "2. Alterar autor\n";
        std::cout << "3. Alterar ano de publicacao\n";
        std::cout << "0. Voltar\n";
        opcao = lerInteiro("Opcao: ");

        if (opcao == 1) {
            std::string titulo = lerLinha("Novo titulo: ");
            biblioteca.editarLivro(isbn, titulo, "", 0);
        } else if (opcao == 2) {
            std::string autor = lerLinha("Novo autor: ");
            biblioteca.editarLivro(isbn, "", autor, 0);
        } else if (opcao == 3) {
            int ano = lerInteiro("Novo ano: ");
            biblioteca.editarLivro(isbn, "", "", ano);
        }
    } while (opcao != 0);
}

void menuBibliotecario(Biblioteca& biblioteca) {
    int opcao;
    do {
        std::cout << "\n=== Menu Bibliotecario ===\n";
        std::cout << "1. Consultar catalogo\n";
        std::cout << "2. Adicionar livro\n";
        std::cout << "3. Remover copia de livro\n";
        std::cout << "4. Editar livro\n";
        std::cout << "5. Listar utentes\n";
        std::cout << "6. Editar dados de utente\n";
        std::cout << "0. Sair\n";
        opcao = lerInteiro("Opcao: ");

        if (opcao == 1) {
            biblioteca.consultarCatalogo();
        } else if (opcao == 2) {
            std::string isbn   = lerLinha("ISBN: ");
            std::string titulo = lerLinha("Titulo: ");
            std::string autor  = lerLinha("Autor: ");
            int ano            = lerInteiro("Ano de publicacao: ");
            int quantidade     = lerInteiro("Quantidade: ");
            biblioteca.adicionarLivro(isbn, titulo, autor, ano, quantidade);
        } else if (opcao == 3) {
            std::string isbn = lerLinha("ISBN do livro: ");
            biblioteca.removerCopiaLivro(isbn);
        } else if (opcao == 4) {
            menuEditarLivro(biblioteca);
        } else if (opcao == 5) {
            biblioteca.listarUtentes();
        } else if (opcao == 6) {
            menuEditarUtenteAdmin(biblioteca);
        }
    } while (opcao != 0);
}

// ─── Menu Principal ───────────────────────────────────────────────────────────

int main() {
    Biblioteca biblioteca;
    int opcao;

    do {
        std::cout << "\n=== Sistema de Gestao de Biblioteca ===\n";
        std::cout << "1. Login como Utente\n";
        std::cout << "2. Login como Bibliotecario\n";
        std::cout << "0. Sair\n";
        opcao = lerInteiro("Opcao: ");

        if (opcao == 1) {
            int numero         = lerInteiro("Numero de utente: ");
            std::string pass   = lerLinha("Password: ");
            Utente* utente     = biblioteca.loginUtente(numero, pass);

            if (utente == nullptr) {
                std::cout << "Credenciais invalidas.\n";
            } else {
                std::cout << "Bem-vindo, " << utente->getNome() << "!\n";
                menuUtente(biblioteca, numero);
            }
        } else if (opcao == 2) {
            std::string user = lerLinha("Username: ");
            std::string pass = lerLinha("Password: ");

            if (!biblioteca.loginBibliotecario(user, pass)) {
                std::cout << "Credenciais invalidas.\n";
            } else {
                std::cout << "Bem-vindo, Bibliotecario!\n";
                menuBibliotecario(biblioteca);
            }
        }
    } while (opcao != 0);

    std::cout << "Ate logo!\n";
    return 0;
}
