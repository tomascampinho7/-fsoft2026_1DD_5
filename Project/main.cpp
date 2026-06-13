#include <iostream>
#include <string>
#include <limits>
#include "Biblioteca.h"

// ─── Utilitários ──────────────────────────────────────────────────────────────

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

// ─── Registo de novo utente (menu principal) ──────────────────────────────────

void menuRegistarUtente(Biblioteca& biblioteca) {
    std::cout << "\n--- Criar conta de Utente ---\n";
    std::string nome     = lerLinha("Nome: ");
    std::string email    = lerLinha("Email: ");
    std::string contacto = lerLinha("Contacto telefonico (opcional): ");
    std::string pass     = lerLinha("Password: ");
    biblioteca.registarUtente(nome, email, contacto, pass);
}

// ─── Menus do Utente ──────────────────────────────────────────────────────────

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
            biblioteca.editarPerfilUtente(numeroUtente, lerLinha("Novo nome: "), "", "");
        } else if (opcao == 2) {
            biblioteca.editarPerfilUtente(numeroUtente, "", lerLinha("Novo email: "), "");
        } else if (opcao == 3) {
            biblioteca.editarPerfilUtente(numeroUtente, "", "", lerLinha("Novo contacto: "));
        } else if (opcao == 4) {
            std::string atual = lerLinha("Password atual: ");
            std::string nova  = lerLinha("Nova password: ");
            if (biblioteca.alterarPasswordUtente(numeroUtente, atual, nova))
                std::cout << "Password alterada com sucesso.\n";
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
            std::string query = lerLinha("ISBN ou titulo do livro: ");
            if (biblioteca.requisitarLivro(numeroUtente, query))
                std::cout << "Livro requisitado com sucesso.\n";
        } else if (opcao == 3) {
            std::string query = lerLinha("ISBN ou titulo do livro a devolver: ");
            if (biblioteca.registarDevolucao(query))
                std::cout << "Livro devolvido com sucesso.\n";
        } else if (opcao == 4) {
            biblioteca.listarRequisicoesAtivas(numeroUtente);
        } else if (opcao == 5) {
            menuEditarPerfilUtente(biblioteca, numeroUtente);
        }
    } while (opcao != 0);
}

// ─── Menus do Bibliotecário ───────────────────────────────────────────────────

void menuEditarUtenteAdmin(Biblioteca& biblioteca) {
    int numero = lerInteiro("Numero do utente a editar: ");
    int opcao;
    do {
        std::cout << "\n--- Editar Utente ---\n";
        std::cout << "1. Alterar nome\n";
        std::cout << "2. Alterar email\n";
        std::cout << "3. Alterar contacto\n";
        std::cout << "4. Redefinir password\n";
        std::cout << "0. Voltar\n";
        opcao = lerInteiro("Opcao: ");

        if (opcao == 1) biblioteca.editarUtenteAdmin(numero, lerLinha("Novo nome: "), "", "");
        else if (opcao == 2) biblioteca.editarUtenteAdmin(numero, "", lerLinha("Novo email: "), "");
        else if (opcao == 3) biblioteca.editarUtenteAdmin(numero, "", "", lerLinha("Novo contacto: "));
        else if (opcao == 4) biblioteca.resetPasswordUtenteAdmin(numero, lerLinha("Nova password: "));
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

        if (opcao == 1) biblioteca.editarLivro(isbn, lerLinha("Novo titulo: "), "", 0);
        else if (opcao == 2) biblioteca.editarLivro(isbn, "", lerLinha("Novo autor: "), 0);
        else if (opcao == 3) biblioteca.editarLivro(isbn, "", "", lerInteiro("Novo ano: "));
    } while (opcao != 0);
}

void menuConsultarRequisicoes(Biblioteca& biblioteca) {
    int opcao;
    do {
        std::cout << "\n--- Consultar Requisicoes ---\n";
        std::cout << "1. Todas as requisicoes\n";
        std::cout << "2. Apenas requisicoes ativas\n";
        std::cout << "3. Requisicoes de um utente\n";
        std::cout << "0. Voltar\n";
        opcao = lerInteiro("Opcao: ");

        if (opcao == 1) biblioteca.listarTodasRequisicoes();
        else if (opcao == 2) biblioteca.listarRequisicoesAtivasAdmin();
        else if (opcao == 3) biblioteca.listarRequisicoesUtente(lerInteiro("Numero do utente: "));
    } while (opcao != 0);
}

void menuEstatisticas(Biblioteca& biblioteca) {
    int opcao;
    do {
        std::cout << "\n--- Estatisticas ---\n";
        std::cout << "1. Esta semana\n";
        std::cout << "2. Este mes\n";
        std::cout << "3. Este ano\n";
        std::cout << "0. Voltar\n";
        opcao = lerInteiro("Opcao: ");

        if (opcao == 1) biblioteca.mostrarEstatisticasSemana();
        else if (opcao == 2) biblioteca.mostrarEstatisticasMes();
        else if (opcao == 3) biblioteca.mostrarEstatisticasAno();
    } while (opcao != 0);
}

// Menu de gestão de bibliotecários — só visível ao admin
void menuGerirBibliotecarios(Biblioteca& biblioteca) {
    int opcao;
    do {
        std::cout << "\n--- Gerir Bibliotecarios ---\n";
        std::cout << "1. Listar bibliotecarios\n";
        std::cout << "2. Adicionar bibliotecario\n";
        std::cout << "3. Editar nome de bibliotecario\n";
        std::cout << "4. Redefinir password de bibliotecario\n";
        std::cout << "0. Voltar\n";
        opcao = lerInteiro("Opcao: ");

        if (opcao == 1) {
            biblioteca.listarBibliotecarios();
        } else if (opcao == 2) {
            std::string user = lerLinha("Username: ");
            std::string pass = lerLinha("Password: ");
            std::string nome = lerLinha("Nome: ");
            biblioteca.adicionarBibliotecario(user, pass, nome);
        } else if (opcao == 3) {
            std::string user = lerLinha("Username do bibliotecario: ");
            std::string nome = lerLinha("Novo nome: ");
            biblioteca.editarBibliotecarioAdmin(user, nome);
        } else if (opcao == 4) {
            std::string user = lerLinha("Username do bibliotecario: ");
            std::string nova = lerLinha("Nova password: ");
            biblioteca.resetPasswordBibliotecarioAdmin(user, nova);
        }
    } while (opcao != 0);
}

void menuEditarPerfilBibliotecario(Biblioteca& biblioteca, const std::string& username) {
    int opcao;
    do {
        std::cout << "\n--- Editar Perfil ---\n";
        std::cout << "1. Alterar nome\n";
        std::cout << "2. Alterar password\n";
        std::cout << "0. Voltar\n";
        opcao = lerInteiro("Opcao: ");

        if (opcao == 1) {
            biblioteca.editarPerfilBibliotecario(username, lerLinha("Novo nome: "));
        } else if (opcao == 2) {
            std::string atual = lerLinha("Password atual: ");
            std::string nova  = lerLinha("Nova password: ");
            if (biblioteca.alterarPasswordBibliotecario(username, atual, nova))
                std::cout << "Password alterada com sucesso.\n";
        }
    } while (opcao != 0);
}

void menuBibliotecario(Biblioteca& biblioteca, Bibliotecario* bib) {
    int opcao;
    do {
        std::cout << "\n=== Menu Bibliotecario ===\n";
        std::cout << "1. Consultar catalogo\n";
        std::cout << "2. Adicionar livro\n";
        std::cout << "3. Remover copia de livro\n";
        std::cout << "4. Editar livro\n";
        std::cout << "5. Listar utentes\n";
        std::cout << "6. Editar dados de utente\n";
        std::cout << "7. Consultar requisicoes\n";
        std::cout << "8. Estatisticas\n";
        if (!bib->getIsAdmin())
            std::cout << "9. Editar meu perfil\n";
        if (bib->getIsAdmin())
            std::cout << "9. Gerir bibliotecarios (admin)\n";
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
            biblioteca.removerCopiaLivro(lerLinha("ISBN do livro: "));
        } else if (opcao == 4) {
            menuEditarLivro(biblioteca);
        } else if (opcao == 5) {
            biblioteca.listarUtentes();
        } else if (opcao == 6) {
            menuEditarUtenteAdmin(biblioteca);
        } else if (opcao == 7) {
            menuConsultarRequisicoes(biblioteca);
        } else if (opcao == 8) {
            menuEstatisticas(biblioteca);
        } else if (opcao == 9 && !bib->getIsAdmin()) {
            menuEditarPerfilBibliotecario(biblioteca, bib->getUsername());
        } else if (opcao == 9 && bib->getIsAdmin()) {
            menuGerirBibliotecarios(biblioteca);
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
        std::cout << "3. Registar novo utente\n";
        std::cout << "0. Sair\n";
        opcao = lerInteiro("Opcao: ");

        if (opcao == 1) {
            int numero       = lerInteiro("Numero de utente: ");
            std::string pass = lerLinha("Password: ");
            Utente* utente   = biblioteca.loginUtente(numero, pass);

            if (!utente) std::cout << "Credenciais invalidas.\n";
            else {
                std::cout << "Bem-vindo, " << utente->getNome() << "!\n";
                menuUtente(biblioteca, numero);
            }
        } else if (opcao == 2) {
            std::string user = lerLinha("Username: ");
            std::string pass = lerLinha("Password: ");
            Bibliotecario* bib = biblioteca.loginBibliotecario(user, pass);

            if (!bib) std::cout << "Credenciais invalidas.\n";
            else {
                std::cout << "Bem-vindo, " << bib->getNome() << "!\n";
                menuBibliotecario(biblioteca, bib);
            }
        } else if (opcao == 3) {
            menuRegistarUtente(biblioteca);
        }
    } while (opcao != 0);

    std::cout << "Ate logo!\n";
    return 0;
}
