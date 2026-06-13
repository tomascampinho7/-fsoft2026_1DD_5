#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <vector>
#include <string>
#include "Livro.h"
#include "Utente.h"
#include "Bibliotecario.h"
#include "Requisicao.h"

class Biblioteca {
private:
    std::vector<Livro> livros;
    std::vector<Utente> utentes;
    std::vector<Bibliotecario> bibliotecarios;
    std::vector<Requisicao> requisicoes;
    int proximoIdRequisicao;
    int proximoNumeroUtente;

    Livro* procurarLivroPorIsbn(const std::string& isbn);
    Livro* procurarLivroPorTitulo(const std::string& titulo);
    Livro* procurarLivro(const std::string& query);   // ISBN ou título automaticamente
    Utente* procurarUtentePorNumero(int numeroUtente);
    Bibliotecario* procurarBibliotecario(const std::string& username);

public:
    Biblioteca();

    void carregarDadosIniciais();

    // Catálogo
    void consultarCatalogo() const;
    bool adicionarLivro(const std::string& isbn, const std::string& titulo,
                        const std::string& autor, int ano, int quantidade);
    bool removerCopiaLivro(const std::string& isbn);
    bool editarLivro(const std::string& isbn, const std::string& novoTitulo,
                     const std::string& novoAutor, int novoAno);

    // Login
    Utente* loginUtente(int numeroUtente, const std::string& password);
    Bibliotecario* loginBibliotecario(const std::string& username, const std::string& password);

    // Gestão de utentes
    bool registarUtente(const std::string& nome, const std::string& email,
                        const std::string& contacto, const std::string& password);
    void listarUtentes() const;
    bool editarPerfilUtente(int numeroUtente, const std::string& novoNome,
                            const std::string& novoEmail, const std::string& novoContacto);
    bool alterarPasswordUtente(int numeroUtente, const std::string& passwordAtual,
                               const std::string& novaPassword);
    bool editarUtenteAdmin(int numeroUtente, const std::string& novoNome,
                           const std::string& novoEmail, const std::string& novoContacto);
    bool resetPasswordUtenteAdmin(int numeroUtente, const std::string& novaPassword);

    // Gestão de bibliotecários (só admin)
    bool adicionarBibliotecario(const std::string& username, const std::string& password,
                                const std::string& nome);
    void listarBibliotecarios() const;
    bool editarPerfilBibliotecario(const std::string& username, const std::string& novoNome);
    bool alterarPasswordBibliotecario(const std::string& username,
                                      const std::string& atual, const std::string& nova);
    bool editarBibliotecarioAdmin(const std::string& username, const std::string& novoNome);
    bool resetPasswordBibliotecarioAdmin(const std::string& username, const std::string& nova);

    // Requisições
    bool requisitarLivro(int numeroUtente, const std::string& query);
    bool registarDevolucao(const std::string& query);
    void listarRequisicoesAtivas(int numeroUtente) const;
    void listarTodasRequisicoes() const;
    void listarRequisicoesAtivasAdmin() const;
    void listarRequisicoesUtente(int numeroUtente) const;

    // Estatísticas (bibliotecário)
    void mostrarEstatisticasSemana() const;
    void mostrarEstatisticasMes() const;
    void mostrarEstatisticasAno() const;
};

#endif
