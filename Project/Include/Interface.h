#ifndef INTERFACE_H
#define INTERFACE_H

#include "Biblioteca.h"
#include <string>

// ─── Utilitários ───
void limparBuffer();
std::string lerLinha(const std::string& prompt);
int lerInteiro(const std::string& prompt);

// ─── Menus Secundários ───
void menuVisitante(Biblioteca& biblioteca);
void menuRegistarUtente(Biblioteca& biblioteca);
void menuEditarPerfilUtente(Biblioteca& biblioteca, int numeroUtente);
void menuUtente(Biblioteca& biblioteca, int numeroUtente);

void menuEditarUtenteAdmin(Biblioteca& biblioteca);
void menuEditarLivro(Biblioteca& biblioteca);
void menuConsultarRequisicoes(Biblioteca& biblioteca);
void menuEstatisticas(Biblioteca& biblioteca);
void menuGerirBibliotecarios(Biblioteca& biblioteca);
void menuEditarPerfilBibliotecario(Biblioteca& biblioteca, const std::string& username);
void menuBibliotecario(Biblioteca& biblioteca, Bibliotecario* bib);

// ─── Função de Arranque ───
void iniciarMenuPrincipal(Biblioteca& biblioteca);

#endif