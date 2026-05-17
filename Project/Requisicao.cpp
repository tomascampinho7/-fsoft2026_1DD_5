
#include "Requisicao.h"
#include <iostream>

Requisicao::Requisicao() {
    this->numeroUtente = 0;
    this->isbnLivro = "";
    this->dataRequisicao = "";
    this->dataLimite = "";
    this->ativa = false;
}

Requisicao::Requisicao(int numeroUtente, const std::string& isbnLivro,
                       const std::string& dataRequisicao, const std::string& dataLimite) {
    this->numeroUtente = numeroUtente;
    this->isbnLivro = isbnLivro;
    this->dataRequisicao = dataRequisicao;
    this->dataLimite = dataLimite;
    this->ativa = true;
}

int Requisicao::getNumeroUtente() const {
    return numeroUtente;
}

std::string Requisicao::getIsbnLivro() const {
    return isbnLivro;
}

std::string Requisicao::getDataRequisicao() const {
    return dataRequisicao;
}

std::string Requisicao::getDataLimite() const {
    return dataLimite;
}

bool Requisicao::estaAtiva() const {
    return ativa;
}

void Requisicao::fecharRequisicao() {
    ativa = false;
}

void Requisicao::mostrar() const {
    std::cout << "Numero de utente: " << numeroUtente << "\n";
    std::cout << "ISBN do livro: " << isbnLivro << "\n";
    std::cout << "Data de requisicao: " << dataRequisicao << "\n";
    std::cout << "Data limite: " << dataLimite << "\n";
    std::cout << "Estado: " << (ativa ? "Ativa" : "Fechada") << "\n";
}