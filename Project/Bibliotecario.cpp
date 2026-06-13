#include "Bibliotecario.h"
#include <iostream>

Bibliotecario::Bibliotecario() : username(""), password(""), nome(""), isAdmin(false) {}

Bibliotecario::Bibliotecario(const std::string& username, const std::string& password,
                             const std::string& nome, bool isAdmin)
    : username(username), password(password), nome(nome), isAdmin(isAdmin) {}

std::string Bibliotecario::getUsername() const { return username; }
std::string Bibliotecario::getNome() const { return nome; }
bool Bibliotecario::getIsAdmin() const { return isAdmin; }

bool Bibliotecario::validarPassword(const std::string& pw) const {
    return this->password == pw;
}

void Bibliotecario::setNome(const std::string& novoNome) {
    if (!novoNome.empty()) nome = novoNome;
}

bool Bibliotecario::alterarPassword(const std::string& atual, const std::string& nova) {
    if (!validarPassword(atual)) {
        std::cout << "Password atual incorreta.\n";
        return false;
    }
    if (nova.empty()) {
        std::cout << "A nova password nao pode ser vazia.\n";
        return false;
    }
    password = nova;
    return true;
}

void Bibliotecario::setNomeAdmin(const std::string& novoNome) {
    if (!novoNome.empty()) nome = novoNome;
}

void Bibliotecario::resetPasswordAdmin(const std::string& nova) {
    if (!nova.empty()) password = nova;
}

void Bibliotecario::mostrar() const {
    std::cout << "Username: " << username << "\n";
    std::cout << "Nome: " << nome << "\n";
    std::cout << "Perfil: " << (isAdmin ? "Administrador" : "Bibliotecario") << "\n";
}
