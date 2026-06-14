#include "../Include/Requisicao.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <cstring>

// Converte std::tm para "DD/MM/AAAA"
std::string Requisicao::tmParaString(const std::tm& t) {
    std::ostringstream oss;
    oss << std::setfill('0')
        << std::setw(2) << t.tm_mday << "/"
        << std::setw(2) << (t.tm_mon + 1) << "/"
        << (t.tm_year + 1900);
    return oss.str();
}

Requisicao::Requisicao() {
    id = 0;
    numeroUtente = 0;
    isbnLivro = "";
    ativa = false;
    std::memset(&dataRequisicao, 0, sizeof(dataRequisicao));
    std::memset(&dataLimite, 0, sizeof(dataLimite));
}

Requisicao::Requisicao(int id, int numeroUtente, const std::string& isbnLivro) {
    this->id = id;
    this->numeroUtente = numeroUtente;
    this->isbnLivro = isbnLivro;
    this->ativa = true;

    // Data atual do sistema
    std::time_t agora = std::time(nullptr);
    std::tm* local = std::localtime(&agora);
    this->dataRequisicao = *local;

    // Data limite = hoje + 14 dias
    std::time_t limite = agora + 14 * 24 * 60 * 60;
    std::tm* localLimite = std::localtime(&limite);
    this->dataLimite = *localLimite;
}

int Requisicao::getId() const { return id; }
int Requisicao::getNumeroUtente() const { return numeroUtente; }
std::string Requisicao::getIsbnLivro() const { return isbnLivro; }
std::string Requisicao::getDataRequisicaoStr() const { return tmParaString(dataRequisicao); }
std::string Requisicao::getDataLimiteStr() const { return tmParaString(dataLimite); }
const std::tm& Requisicao::getDataRequisicaoTm() const { return dataRequisicao; }
bool Requisicao::estaAtiva() const { return ativa; }

void Requisicao::fechar() { ativa = false; }

void Requisicao::mostrar() const {
    std::cout << "ID Requisicao: " << id << "\n";
    std::cout << "Numero de utente: " << numeroUtente << "\n";
    std::cout << "ISBN do livro: " << isbnLivro << "\n";
    std::cout << "Data de requisicao: " << getDataRequisicaoStr() << "\n";
    std::cout << "Data limite: " << getDataLimiteStr() << "\n";
    std::cout << "Estado: " << (ativa ? "Ativa" : "Fechada") << "\n";
}
