#include "../Include/Livro.h"
#include <iostream>

Livro::Livro() {
    isbn = "";
    titulo = "";
    autor = "";
    anoPublicacao = 0;
    stockTotal = 0;
    stockDisponivel = 0;
}

Livro::Livro(const std::string& isbn, const std::string& titulo, const std::string& autor,
             int anoPublicacao, int stockTotal) {
    this->isbn = isbn;
    this->titulo = titulo;
    this->autor = autor;
    this->anoPublicacao = anoPublicacao;

    if (stockTotal < 0) {
        stockTotal = 0;
    }

    this->stockTotal = stockTotal;
    this->stockDisponivel = stockTotal;
}

std::string Livro::getIsbn() const { return isbn; }
std::string Livro::getTitulo() const { return titulo; }
std::string Livro::getAutor() const { return autor; }
int Livro::getAnoPublicacao() const { return anoPublicacao; }
int Livro::getStockTotal() const { return stockTotal; }
int Livro::getStockDisponivel() const { return stockDisponivel; }

bool Livro::estaDisponivel() const {
    return stockDisponivel > 0;
}

void Livro::aumentarStock(int quantidade) {
    if (quantidade > 0) {
        stockTotal += quantidade;
        stockDisponivel += quantidade;
    }
}

bool Livro::requisitarCopia() {
    if (stockDisponivel <= 0) return false;
    stockDisponivel--;
    return true;
}

bool Livro::devolverCopia() {
    if (stockDisponivel >= stockTotal) return false;
    stockDisponivel++;
    return true;
}

bool Livro::removerCopia() {
    if (stockDisponivel <= 0) return false;
    stockDisponivel--;
    stockTotal--;
    return true;
}

void Livro::setTitulo(const std::string& novoTitulo) { titulo = novoTitulo; }
void Livro::setAutor(const std::string& novoAutor) { autor = novoAutor; }
void Livro::setAnoPublicacao(int novoAno) { anoPublicacao = novoAno; }

void Livro::mostrar() const {
    std::cout << "ISBN: " << isbn << "\n";
    std::cout << "Titulo: " << titulo << "\n";
    std::cout << "Autor: " << autor << "\n";
    std::cout << "Ano: " << anoPublicacao << "\n";
    std::cout << "Stock total: " << stockTotal << "\n";
    std::cout << "Stock disponivel: " << stockDisponivel << "\n";
    std::cout << "Estado: " << (estaDisponivel() ? "Disponivel" : "Indisponivel") << "\n";
}
