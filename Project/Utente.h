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

    void mostrar() const;
};

#endif