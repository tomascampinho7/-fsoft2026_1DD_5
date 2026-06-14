#ifndef BIBLIOTECARIO_H
#define BIBLIOTECARIO_H

#include <string>

class Bibliotecario {
private:
    std::string username;
    std::string password;
    std::string nome;
    bool isAdmin;

public:
    Bibliotecario();
    Bibliotecario(const std::string& username, const std::string& password,
                  const std::string& nome, bool isAdmin = false);

    std::string getUsername() const;
    std::string getNome() const;
    bool getIsAdmin() const;

    bool validarPassword(const std::string& password) const;

    // Edição pelo próprio
    void setNome(const std::string& novoNome);
    bool alterarPassword(const std::string& atual, const std::string& nova);

    // Edição pelo admin
    void setNomeAdmin(const std::string& novoNome);
    void resetPasswordAdmin(const std::string& nova);

    void mostrar() const;
};

#endif
