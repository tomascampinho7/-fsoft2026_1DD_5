#ifndef REQUISICAO_H
#define REQUISICAO_H

#include <string>

class Requisicao {
private:
    int numeroUtente;
    std::string isbnLivro;
    std::string dataRequisicao;
    std::string dataLimite;
    bool ativa;

public:
    Requisicao();
    Requisicao(int numeroUtente, const std::string& isbnLivro,
               const std::string& dataRequisicao, const std::string& dataLimite);

    int getNumeroUtente() const;
    std::string getIsbnLivro() const;
    std::string getDataRequisicao() const;
    std::string getDataLimite() const;
    bool estaAtiva() const;

    void fecharRequisicao();

    void mostrar() const;
};

#endif