#ifndef UTENTE_H
#define UTENTE_H

#include <string>

class Utente {
private:
    int numeroUtente;
    std::string nome;
    std::string email;
    std::string contactoTelefonico;
    std::string password;

public:
    Utente();
    Utente(int numeroUtente, const std::string& nome, const std::string& email,
           const std::string& contactoTelefonico, const std::string& password);

    int getNumeroUtente() const;
    std::string getNome() const;
    std::string getEmail() const;
    std::string getContactoTelefonico() const;

    bool validarPassword(const std::string& password) const;

    // Edição pelo próprio utente
    void setNome(const std::string& novoNome);
    void setEmail(const std::string& novoEmail);
    void setContactoTelefonico(const std::string& novoContacto);
    bool alterarPassword(const std::string& passwordAtual, const std::string& novaPassword);

    // Edição pelo bibliotecário (sem verificação de password)
    void setNomeBibliotecario(const std::string& novoNome);
    void setEmailBibliotecario(const std::string& novoEmail);
    void setContactoBibliotecario(const std::string& novoContacto);
    void resetPasswordBibliotecario(const std::string& novaPassword);

    void mostrar() const;
};

#endif
