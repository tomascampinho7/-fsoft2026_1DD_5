#include "Requisicao.h"
#include <iostream>

Requisicao::Requisicao() {
    this->id = 0;
    this->numeroUtente = 0;
    this->isbnLivro = "";
    this->dataRequisicao = "";
    this->dataLimite = "";
    this->ativa = false;
}

Requisicao::Requisicao(int id, int numeroUtente, const std::string& isbnLivro,
                       const std::string& dataRequisicao, const std::string& dataLimite) {
    this->id = id;
    this->numeroUtente = numeroUtente;
    this->isbnLivro = isbnLivro;
    this->dataRequisicao = dataRequisicao;
    this->dataLimite = dataLimite;
    this->ativa = true;
}

int Requisicao::getId() const { return id; }
int Requisicao::getNumeroUtente() const { return numeroUtente; }
std::string Requisicao::getIsbnLivro() const { return isbnLivro; }
std::string Requisicao::getDataRequisicao() const { return dataRequisicao; }
std::string Requisicao::getDataLimite() const { return dataLimite; }
bool Requisicao::estaAtiva() const { return ativa; }

void Requisicao::fechar() {
    ativa = false;
}

void Requisicao::mostrar() const {
    std::cout << "ID Requisicao: " << id << "\n";
    std::cout << "Numero de utente: " << numeroUtente << "\n";
    std::cout << "ISBN do livro: " << isbnLivro << "\n";
    std::cout << "Data de requisicao: " << dataRequisicao << "\n";
    std::cout << "Data limite: " << dataLimite << "\n";
    std::cout << "Estado: " << (ativa ? "Ativa" : "Fechada") << "\n";
}
