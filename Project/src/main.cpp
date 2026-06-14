#include <iostream>
#include "Biblioteca.h"
#include "Interface.h"

int main() {
    Biblioteca biblioteca;

    std::cout << "A iniciar o Sistema de Gestao de Biblioteca...\n";


    iniciarMenuPrincipal(biblioteca);

    std::cout << "Ate logo!\n";
    return 0;
}