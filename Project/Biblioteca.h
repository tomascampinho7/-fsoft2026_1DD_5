#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <vector>
#include <string>
#include "Livro.h"
#include "Utente.h"
#include "Requisicao.h"

class Biblioteca {
private:
    std::vector<Livro> livros;
    std::vector<Utente> utentes;
    std::vector<Requisicao> requisicoes;
    int proximoIdRequisicao;

    Livro* procurarLivroPorIsbn(const std::string& isbn);
    Utente* procurarUtentePorNumero(int numeroUtente);

public:
    Biblioteca();

    void carregarDadosIniciais();

    void consultarCatalogo() const;
    bool adicionarLivro(const std::string& isbn, const std::string& titulo,
                        const std::string& autor, int ano, int quantidade);

    bool removerCopiaLivro(const std::string& isbn);

    Utente* loginUtente(int numeroUtente, const std::string& password);
    bool loginBibliotecario(const std::string& username, const std::string& password) const;

    bool requisitarLivro(int numeroUtente, const std::string& isbn);
    bool registarDevolucao(const std::string& isbn);

    void listarRequisicoesAtivas(int numeroUtente) const;
    void listarUtentes() const;
};

#endif