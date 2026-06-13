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

int Utente::getNumeroUtente() const { return numeroUtente; }
std::string Utente::getNome() const { return nome; }
std::string Utente::getEmail() const { return email; }
std::string Utente::getContactoTelefonico() const { return contactoTelefonico; }

bool Utente::validarPassword(const std::string& password) const {
    return this->password == password;
}

// --- Edição pelo próprio utente ---

void Utente::setNome(const std::string& novoNome) {
    if (!novoNome.empty()) nome = novoNome;
}

void Utente::setEmail(const std::string& novoEmail) {
    if (!novoEmail.empty()) email = novoEmail;
}

void Utente::setContactoTelefonico(const std::string& novoContacto) {
    if (!novoContacto.empty()) contactoTelefonico = novoContacto;
}

bool Utente::alterarPassword(const std::string& passwordAtual, const std::string& novaPassword) {
    if (!validarPassword(passwordAtual)) {
        std::cout << "Password atual incorreta.\n";
        return false;
    }
    if (novaPassword.empty()) {
        std::cout << "A nova password nao pode ser vazia.\n";
        return false;
    }
    password = novaPassword;
    return true;
}

// --- Edição pelo bibliotecário ---

void Utente::setNomeBibliotecario(const std::string& novoNome) {
    if (!novoNome.empty()) nome = novoNome;
}

void Utente::setEmailBibliotecario(const std::string& novoEmail) {
    if (!novoEmail.empty()) email = novoEmail;
}

void Utente::setContactoBibliotecario(const std::string& novoContacto) {
    if (!novoContacto.empty()) contactoTelefonico = novoContacto;
}

void Utente::resetPasswordBibliotecario(const std::string& novaPassword) {
    if (!novaPassword.empty()) password = novaPassword;
}

void Utente::mostrar() const {
    std::cout << "Numero de utente: " << numeroUtente << "\n";
    std::cout << "Nome: " << nome << "\n";
    std::cout << "Email: " << email << "\n";
    std::cout << "Contacto: " << contactoTelefonico << "\n";
}
