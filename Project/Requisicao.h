#ifndef REQUISICAO_H
#define REQUISICAO_H

#include <string>
#include <ctime>

class Requisicao {
private:
    int id;
    int numeroUtente;
    std::string isbnLivro;
    std::tm dataRequisicao;   // data real do sistema
    std::tm dataLimite;       // dataRequisicao + 14 dias
    bool ativa;

    static std::string tmParaString(const std::tm& t);

public:
    Requisicao();
    Requisicao(int id, int numeroUtente, const std::string& isbnLivro);

    int getId() const;
    int getNumeroUtente() const;
    std::string getIsbnLivro() const;
    std::string getDataRequisicaoStr() const;
    std::string getDataLimiteStr() const;
    const std::tm& getDataRequisicaoTm() const;
    bool estaAtiva() const;

    void fechar();

    void mostrar() const;
};

#endif
