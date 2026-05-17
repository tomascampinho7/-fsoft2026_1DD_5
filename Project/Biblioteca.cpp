#include "Biblioteca.h"
#include <iostream>

Biblioteca::Biblioteca() {
    proximoIdRequisicao = 1;
    carregarDadosIniciais();
}

void Biblioteca::carregarDadosIniciais() {
    livros.push_back(Livro("9780001", "Os Maias", "Eca de Queiros", 1888, 3));
    livros.push_back(Livro("9780002", "Memorial do Convento", "Jose Saramago", 1982, 2));
    livros.push_back(Livro("9780003", "Harry Potter e a Pedra Filosofal", "J. K. Rowling", 1997, 4));

    utentes.push_back(Utente(1, "Diogo Silva", "diogo@email.com", "1234"));
    utentes.push_back(Utente(2, "Nuno Teixeira", "nuno@email.com", "1234"));
    utentes.push_back(Utente(3, "Gustavo Pereira", "gustavo@email.com", "1234"));
}

Livro* Biblioteca::procurarLivroPorIsbn(const std::string& isbn) {
    for (Livro& livro : livros) {
        if (livro.getIsbn() == isbn) {
            return &livro;
        }
    }

    return nullptr;
}

Utente* Biblioteca::procurarUtentePorNumero(int numeroUtente) {
    for (Utente& utente : utentes) {
        if (utente.getNumeroUtente() == numeroUtente) {
            return &utente;
        }
    }

    return nullptr;
}

void Biblioteca::consultarCatalogo() const {
    if (livros.empty()) {
        std::cout << "O catalogo encontra-se vazio de momento.\n";
        return;
    }

    std::cout << "\n=== Catalogo de Livros ===\n";

    for (const Livro& livro : livros) {
        livro.mostrar();
        std::cout << "--------------------------\n";
    }
}

bool Biblioteca::adicionarLivro(const std::string& isbn, const std::string& titulo,
                                const std::string& autor, int ano, int quantidade) {
    if (quantidade <= 0) {
        std::cout << "A quantidade deve ser superior a zero.\n";
        return false;
    }

    Livro* livroExistente = procurarLivroPorIsbn(isbn);

    if (livroExistente != nullptr) {
        livroExistente->aumentarStock(quantidade);
        std::cout << "Livro ja existente. O stock foi aumentado.\n";
        return true;
    }

    livros.push_back(Livro(isbn, titulo, autor, ano, quantidade));
    return true;
}

bool Biblioteca::removerCopiaLivro(const std::string& isbn) {
    for (auto it = livros.begin(); it != livros.end(); ++it) {
        if (it->getIsbn() == isbn) {
            if (!it->removerCopia()) {
                std::cout << "Nao e possivel remover uma copia. Todas as copias estao requisitadas.\n";
                return false;
            }

            if (it->getStockTotal() == 0) {
                livros.erase(it);
            }

            return true;
        }
    }

    std::cout << "Livro nao encontrado.\n";
    return false;
}

Utente* Biblioteca::loginUtente(int numeroUtente, const std::string& password) {
    Utente* utente = procurarUtentePorNumero(numeroUtente);

    if (utente != nullptr && utente->validarPassword(password)) {
        return utente;
    }

    return nullptr;
}

bool Biblioteca::loginBibliotecario(const std::string& username, const std::string& password) const {
    return username == "admin" && password == "admin";
}

bool Biblioteca::requisitarLivro(int numeroUtente, const std::string& isbn) {
    Utente* utente = procurarUtentePorNumero(numeroUtente);
    Livro* livro = procurarLivroPorIsbn(isbn);

    if (utente == nullptr) {
        std::cout << "Utente nao encontrado.\n";
        return false;
    }

    if (livro == nullptr) {
        std::cout << "Livro nao encontrado.\n";
        return false;
    }

    if (!livro->requisitarCopia()) {
        std::cout << "Livro indisponivel. Nao existe stock disponivel.\n";
        return false;
    }

    requisicoes.push_back(Requisicao(
        proximoIdRequisicao,
        numeroUtente,
        isbn,
        "17/05/2026",
        "31/05/2026"
    ));

    proximoIdRequisicao++;

    return true;
}

bool Biblioteca::registarDevolucao(const std::string& isbn) {
    Livro* livro = procurarLivroPorIsbn(isbn);

    if (livro == nullptr) {
        std::cout << "Livro nao encontrado.\n";
        return false;
    }

    for (Requisicao& requisicao : requisicoes) {
        if (requisicao.getIsbnLivro() == isbn && requisicao.estaAtiva()) {
            requisicao.fechar();

            if (!livro->devolverCopia()) {
                std::cout << "Erro ao atualizar stock do livro.\n";
                return false;
            }

            return true;
        }
    }

    std::cout << "Nao existe requisicao ativa para esse livro.\n";
    return false;
}

void Biblioteca::listarRequisicoesAtivas(int numeroUtente) const {
    bool encontrou = false;

    std::cout << "\n=== Requisicoes Ativas ===\n";

    for (const Requisicao& requisicao : requisicoes) {
        if (requisicao.getNumeroUtente() == numeroUtente && requisicao.estaAtiva()) {
            requisicao.mostrar();
            std::cout << "--------------------------\n";
            encontrou = true;
        }
    }

    if (!encontrou) {
        std::cout << "Nao tem requisicoes ativas de momento.\n";
    }
}

void Biblioteca::listarUtentes() const {
    if (utentes.empty()) {
        std::cout << "Nao existem utentes registados.\n";
        return;
    }

    std::cout << "\n=== Utentes Registados ===\n";

    for (const Utente& utente : utentes) {
        utente.mostrar();
        std::cout << "--------------------------\n";
    }
}