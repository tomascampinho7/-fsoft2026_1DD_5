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

    // Catálogo
    void consultarCatalogo() const;
    bool adicionarLivro(const std::string& isbn, const std::string& titulo,
                        const std::string& autor, int ano, int quantidade);
    bool removerCopiaLivro(const std::string& isbn);

    // Login
    Utente* loginUtente(int numeroUtente, const std::string& password);
    bool loginBibliotecario(const std::string& username, const std::string& password) const;

    // Requisições
    bool requisitarLivro(int numeroUtente, const std::string& isbn);
    bool registarDevolucao(const std::string& isbn);
    void listarRequisicoesAtivas(int numeroUtente) const;

    // Gestão de utentes
    void listarUtentes() const;

    // Edição de perfil pelo utente (requer password atual para alterar password)
    bool editarPerfilUtente(int numeroUtente, const std::string& novoNome,
                            const std::string& novoEmail, const std::string& novoContacto);
    bool alterarPasswordUtente(int numeroUtente, const std::string& passwordAtual,
                               const std::string& novaPassword);

    // Edição pelo bibliotecário
    bool editarUtenteAdmin(int numeroUtente, const std::string& novoNome,
                           const std::string& novoEmail, const std::string& novoContacto);
    bool resetPasswordUtenteAdmin(int numeroUtente, const std::string& novaPassword);
    bool editarLivro(const std::string& isbn, const std::string& novoTitulo,
                     const std::string& novoAutor, int novoAno);
};

#endif
