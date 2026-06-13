#ifndef REQUISICAO_H
#define REQUISICAO_H

#include <string>

class Requisicao {
private:
    int id;
    int numeroUtente;
    std::string isbnLivro;
    std::string dataRequisicao;
    std::string dataLimite;
    bool ativa;

public:
    Requisicao();
    Requisicao(int id, int numeroUtente, const std::string& isbnLivro,
               const std::string& dataRequisicao, const std::string& dataLimite);

    int getId() const;
    int getNumeroUtente() const;
    std::string getIsbnLivro() const;
    std::string getDataRequisicao() const;
    std::string getDataLimite() const;
    bool estaAtiva() const;

    void fechar();

    void mostrar() const;
};

#endif
