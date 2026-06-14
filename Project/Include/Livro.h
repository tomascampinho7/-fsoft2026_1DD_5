#ifndef LIVRO_H
#define LIVRO_H

#include <string>

class Livro {
private:
    std::string isbn;
    std::string titulo;
    std::string autor;
    int anoPublicacao;
    int stockTotal;
    int stockDisponivel;

public:
    Livro();
    Livro(const std::string& isbn, const std::string& titulo, const std::string& autor,
          int anoPublicacao, int stockTotal);

    std::string getIsbn() const;
    std::string getTitulo() const;
    std::string getAutor() const;
    int getAnoPublicacao() const;
    int getStockTotal() const;
    int getStockDisponivel() const;

    bool estaDisponivel() const;

    void aumentarStock(int quantidade);
    bool requisitarCopia();
    bool devolverCopia();
    bool removerCopia();

    // Edição (bibliotecário)
    void setTitulo(const std::string& novoTitulo);
    void setAutor(const std::string& novoAutor);
    void setAnoPublicacao(int novoAno);

    void mostrar() const;
};

#endif
