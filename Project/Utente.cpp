#include "Utente.h"
#include <iostream>

Utente::Utente() {
    this->numeroUtente = 0;
    this->nome = "";
    this->email = "";
    this->contactoTelefonico = "";
    this->password = "";
}

Utente::Utente(int numeroUtente, const std::string& nome, const std::string& email,
               const std::string& contactoTelefonico, const std::string& password) {
    this->numeroUtente = numeroUtente;
    this->nome = nome;
    this->email = email;
    this->contactoTelefonico = contactoTelefonico;
    this->password = password;
}

int Utente::getNumeroUtente() const {
    return numeroUtente;
}

std::string Utente::getNome() const {
    return nome;
}

std::string Utente::getEmail() const {
    return email;
}

std::string Utente::getContactoTelefonico() const {
    return contactoTelefonico;
}

bool Utente::validarPassword(const std::string& password) const {
    return this->password == password;
}

void Utente::mostrar() const {
    std::cout << "Numero de utente: " << numeroUtente << "\n";
    std::cout << "Nome: " << nome << "\n";
    std::cout << "Email: " << email << "\n";
    std::cout << "Contacto: " << contactoTelefonico << "\n";
}