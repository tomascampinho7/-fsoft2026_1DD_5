#include <cassert>
#include <iostream>

#include "Livro.h"
#include "Utente.h"
#include "Biblioteca.h"

void testarStockLivro() {
    Livro livro("TESTE001", "Livro Teste", "Autor Teste", 2026, 2);

    assert(livro.getStockTotal() == 2);
    assert(livro.getStockDisponivel() == 2);
    assert(livro.estaDisponivel());

    assert(livro.requisitarCopia());
    assert(livro.getStockDisponivel() == 1);

    assert(livro.devolverCopia());
    assert(livro.getStockDisponivel() == 2);
}

void testarLoginUtente() {
    Biblioteca biblioteca;

    Utente* utente = biblioteca.loginUtente(1, "1234");
    assert(utente != nullptr);

    Utente* invalido = biblioteca.loginUtente(1, "password_errada");
    assert(invalido == nullptr);
}

void testarRequisicaoEDevolucao() {
    Biblioteca biblioteca;

    bool requisicao = biblioteca.requisitarLivro(1, "9780001");
    assert(requisicao);

    bool devolucao = biblioteca.registarDevolucao("9780001");
    assert(devolucao);
}

int main() {
    testarStockLivro();
    testarLoginUtente();
    testarRequisicaoEDevolucao();

    std::cout << "Todos os testes passaram com sucesso.\n";
    return 0;
}