#include "../include/Biblioteca.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <ctime>

static std::string toLower(const std::string& s) {
    std::string r = s;
    std::transform(r.begin(), r.end(), r.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return r;
}

static bool pareceIsbn(const std::string& s) {
    if (s.empty()) return false;
    if (!std::isdigit((unsigned char)s[0])) return false;
    for (char c : s) {
        if (!std::isdigit((unsigned char)c) && c != '-') return false;
    }
    return true;
}

Biblioteca::Biblioteca() {
    proximoIdRequisicao  = 1;
    proximoNumeroUtente  = 4;
    carregarDadosIniciais();
}

void Biblioteca::carregarDadosIniciais() {
    livros.push_back(std::make_unique<Livro>("9780001", "Os Maias", "Eca de Queiros", 1888, 3));
    livros.push_back(std::make_unique<Livro>("9780002", "Memorial do Convento", "Jose Saramago", 1982, 2));
    livros.push_back(std::make_unique<Livro>("9780003", "Harry Potter e a Pedra Filosofal", "J. K. Rowling", 1997, 4));

    utentes.push_back(std::make_unique<Utente>(1, "Diogo Silva",     "diogo@email.com",    "910000001", "1234"));
    utentes.push_back(std::make_unique<Utente>(2, "Nuno Teixeira",   "nuno@email.com",     "910000002", "1234"));
    utentes.push_back(std::make_unique<Utente>(3, "Gustavo Pereira", "gustavo@email.com",  "910000003", "1234"));

    // Bibliotecário admin inicial
    bibliotecarios.push_back(std::make_unique<Bibliotecario>("admin", "admin", "Administrador", true));
}

// ─── Pesquisa interna ─────────────────────────────────────────────────────────

Livro* Biblioteca::procurarLivroPorIsbn(const std::string& isbn) {
    for (auto& l : livros)
        if (l->getIsbn() == isbn) return l.get();
    return nullptr;
}

Livro* Biblioteca::procurarLivroPorTitulo(const std::string& titulo) {
    std::string query = toLower(titulo);
    for (auto& l : livros)
        if (toLower(l->getTitulo()).find(query) != std::string::npos) return l.get();
    return nullptr;
}

Livro* Biblioteca::procurarLivro(const std::string& query) {
    if (pareceIsbn(query)) return procurarLivroPorIsbn(query);
    return procurarLivroPorTitulo(query);
}

Utente* Biblioteca::procurarUtentePorNumero(int numeroUtente) {
    for (auto& u : utentes)
        if (u->getNumeroUtente() == numeroUtente) return u.get();
    return nullptr;
}

Bibliotecario* Biblioteca::procurarBibliotecario(const std::string& username) {
    for (auto& b : bibliotecarios)
        if (b->getUsername() == username) return b.get();
    return nullptr;
}

// ─── Catálogo ─────────────────────────────────────────────────────────────────

void Biblioteca::consultarCatalogo() const {
    if (livros.empty()) { std::cout << "O catalogo encontra-se vazio de momento.\n"; return; }
    std::cout << "\n=== Catalogo de Livros ===\n";
    for (const auto& l : livros) { l->mostrar(); std::cout << "--------------------------\n"; }
}

bool Biblioteca::adicionarLivro(const std::string& isbn, const std::string& titulo,
                                const std::string& autor, int ano, int quantidade) {
    if (quantidade <= 0) { std::cout << "A quantidade deve ser superior a zero.\n"; return false; }
    Livro* existente = procurarLivroPorIsbn(isbn);
    if (existente) { existente->aumentarStock(quantidade); std::cout << "Stock aumentado.\n"; return true; }

    livros.push_back(std::make_unique<Livro>(isbn, titulo, autor, ano, quantidade));
    return true;
}

bool Biblioteca::removerCopiaLivro(const std::string& isbn) {
    for (auto it = livros.begin(); it != livros.end(); ++it) {
        if ((*it)->getIsbn() == isbn) {
            if (!(*it)->removerCopia()) {
                std::cout << "Nao e possivel remover: todas as copias estao requisitadas.\n";
                return false;
            }
            if ((*it)->getStockTotal() == 0) livros.erase(it);
            return true;
        }
    }
    std::cout << "Livro nao encontrado.\n";
    return false;
}

bool Biblioteca::editarLivro(const std::string& isbn, const std::string& novoTitulo,
                             const std::string& novoAutor, int novoAno) {
    Livro* l = procurarLivroPorIsbn(isbn);
    if (!l) { std::cout << "Livro nao encontrado.\n"; return false; }
    if (!novoTitulo.empty()) l->setTitulo(novoTitulo);
    if (!novoAutor.empty())  l->setAutor(novoAutor);
    if (novoAno > 0)         l->setAnoPublicacao(novoAno);
    std::cout << "Livro atualizado com sucesso.\n";
    return true;
}

// ─── Login ────────────────────────────────────────────────────────────────────

Utente* Biblioteca::loginUtente(int numeroUtente, const std::string& password) {
    Utente* u = procurarUtentePorNumero(numeroUtente);
    if (u && u->validarPassword(password)) return u;
    return nullptr;
}

Bibliotecario* Biblioteca::loginBibliotecario(const std::string& username,
                                              const std::string& password) {
    Bibliotecario* b = procurarBibliotecario(username);
    if (b && b->validarPassword(password)) return b;
    return nullptr;
}

// ─── Gestao de utentes ────────────────────────────────────────────────────────

bool Biblioteca::registarUtente(const std::string& nome, const std::string& email,
                                const std::string& contacto, const std::string& password) {
    if (nome.empty() || email.empty() || password.empty()) {
        std::cout << "Nome, email e password sao obrigatorios.\n";
        return false;
    }
    utentes.push_back(std::make_unique<Utente>(proximoNumeroUtente, nome, email, contacto, password));
    std::cout << "Utente registado com sucesso! Numero de utente: " << proximoNumeroUtente << "\n";
    proximoNumeroUtente++;
    return true;
}

void Biblioteca::listarUtentes() const {
    if (utentes.empty()) { std::cout << "Nao existem utentes registados.\n"; return; }
    std::cout << "\n=== Utentes Registados ===\n";
    for (const auto& u : utentes) { u->mostrar(); std::cout << "--------------------------\n"; }
}

bool Biblioteca::editarPerfilUtente(int numeroUtente, const std::string& novoNome,
                                    const std::string& novoEmail,
                                    const std::string& novoContacto) {
    Utente* u = procurarUtentePorNumero(numeroUtente);
    if (!u) { std::cout << "Utente nao encontrado.\n"; return false; }
    if (!novoNome.empty())     u->setNome(novoNome);
    if (!novoEmail.empty())    u->setEmail(novoEmail);
    if (!novoContacto.empty()) u->setContactoTelefonico(novoContacto);
    std::cout << "Perfil atualizado com sucesso.\n";
    return true;
}

bool Biblioteca::alterarPasswordUtente(int numeroUtente, const std::string& atual,
                                       const std::string& nova) {
    Utente* u = procurarUtentePorNumero(numeroUtente);
    if (!u) { std::cout << "Utente nao encontrado.\n"; return false; }
    return u->alterarPassword(atual, nova);
}

bool Biblioteca::editarUtenteAdmin(int numeroUtente, const std::string& novoNome,
                                   const std::string& novoEmail,
                                   const std::string& novoContacto) {
    Utente* u = procurarUtentePorNumero(numeroUtente);
    if (!u) { std::cout << "Utente nao encontrado.\n"; return false; }
    if (!novoNome.empty())     u->setNomeBibliotecario(novoNome);
    if (!novoEmail.empty())    u->setEmailBibliotecario(novoEmail);
    if (!novoContacto.empty()) u->setContactoBibliotecario(novoContacto);
    std::cout << "Dados do utente atualizados.\n";
    return true;
}

bool Biblioteca::resetPasswordUtenteAdmin(int numeroUtente, const std::string& nova) {
    Utente* u = procurarUtentePorNumero(numeroUtente);
    if (!u) { std::cout << "Utente nao encontrado.\n"; return false; }
    u->resetPasswordBibliotecario(nova);
    std::cout << "Password redefinida com sucesso.\n";
    return true;
}

// ─── Gestao de bibliotecários ─────────────────────────────────────────────────

bool Biblioteca::adicionarBibliotecario(const std::string& username,
                                        const std::string& password,
                                        const std::string& nome) {
    if (username.empty() || password.empty() || nome.empty()) {
        std::cout << "Username, password e nome sao obrigatorios.\n";
        return false;
    }
    if (procurarBibliotecario(username)) {
        std::cout << "Ja existe um bibliotecario com esse username.\n";
        return false;
    }
    bibliotecarios.push_back(std::make_unique<Bibliotecario>(username, password, nome, false));
    std::cout << "Bibliotecario \"" << username << "\" criado com sucesso.\n";
    return true;
}

void Biblioteca::listarBibliotecarios() const {
    std::cout << "\n=== Bibliotecarios Registados ===\n";
    for (const auto& b : bibliotecarios) {
        b->mostrar();
        std::cout << "--------------------------\n";
    }
}

bool Biblioteca::editarPerfilBibliotecario(const std::string& username,
                                           const std::string& novoNome) {
    Bibliotecario* b = procurarBibliotecario(username);
    if (!b) { std::cout << "Bibliotecario nao encontrado.\n"; return false; }
    b->setNome(novoNome);
    std::cout << "Perfil atualizado.\n";
    return true;
}

bool Biblioteca::alterarPasswordBibliotecario(const std::string& username,
                                              const std::string& atual,
                                              const std::string& nova) {
    Bibliotecario* b = procurarBibliotecario(username);
    if (!b) { std::cout << "Bibliotecario nao encontrado.\n"; return false; }
    return b->alterarPassword(atual, nova);
}

bool Biblioteca::editarBibliotecarioAdmin(const std::string& username,
                                          const std::string& novoNome) {
    Bibliotecario* b = procurarBibliotecario(username);
    if (!b) { std::cout << "Bibliotecario nao encontrado.\n"; return false; }
    b->setNomeAdmin(novoNome);
    std::cout << "Dados atualizados.\n";
    return true;
}

bool Biblioteca::resetPasswordBibliotecarioAdmin(const std::string& username,
                                                 const std::string& nova) {
    Bibliotecario* b = procurarBibliotecario(username);
    if (!b) { std::cout << "Bibliotecario nao encontrado.\n"; return false; }
    b->resetPasswordAdmin(nova);
    std::cout << "Password redefinida com sucesso.\n";
    return true;
}

// ─── Requisiçoes ──────────────────────────────────────────────────────────────

bool Biblioteca::requisitarLivro(int numeroUtente, const std::string& query) {
    Utente* utente = procurarUtentePorNumero(numeroUtente);
    Livro* livro  = procurarLivro(query);

    if (!utente) { std::cout << "Utente nao encontrado.\n"; return false; }
    if (!livro)  { std::cout << "Livro nao encontrado.\n";  return false; }

    if (!livro->requisitarCopia()) {
        std::cout << "Livro indisponivel. Nao existe stock disponivel.\n";
        return false;
    }

    requisicoes.push_back(Requisicao(proximoIdRequisicao, numeroUtente, livro->getIsbn()));
    proximoIdRequisicao++;
    return true;
}

bool Biblioteca::registarDevolucao(const std::string& query) {
    Livro* livro = procurarLivro(query);
    if (!livro) { std::cout << "Livro nao encontrado.\n"; return false; }

    for (Requisicao& r : requisicoes) {
        if (r.getIsbnLivro() == livro->getIsbn() && r.estaAtiva()) {
            r.fechar();
            if (!livro->devolverCopia()) {
                std::cout << "Erro ao atualizar stock do livro.\n";
                return false;
            }
            return true;
        }
    }
    std::cout << "Nao existe requisicao ativa para esse livro.\n";
    return false;
}

void Biblioteca::listarRequisicoesAtivas(int numeroUtente) const {
    bool encontrou = false;
    std::cout << "\n=== Requisicoes Ativas ===\n";
    for (const Requisicao& r : requisicoes) {
        if (r.getNumeroUtente() == numeroUtente && r.estaAtiva()) {
            r.mostrar(); std::cout << "--------------------------\n";
            encontrou = true;
        }
    }
    if (!encontrou) std::cout << "Nao tem requisicoes ativas de momento.\n";
}

void Biblioteca::listarTodasRequisicoes() const {
    if (requisicoes.empty()) { std::cout << "Nao existem requisicoes registadas.\n"; return; }
    std::cout << "\n=== Todas as Requisicoes ===\n";
    for (const Requisicao& r : requisicoes) { r.mostrar(); std::cout << "--------------------------\n"; }
}

void Biblioteca::listarRequisicoesAtivasAdmin() const {
    bool encontrou = false;
    std::cout << "\n=== Requisicoes Ativas ===\n";
    for (const Requisicao& r : requisicoes) {
        if (r.estaAtiva()) { r.mostrar(); std::cout << "--------------------------\n"; encontrou = true; }
    }
    if (!encontrou) std::cout << "Nao existem requisicoes ativas de momento.\n";
}

void Biblioteca::listarRequisicoesUtente(int numeroUtente) const {
    bool encontrou = false;
    std::cout << "\n=== Requisicoes do Utente " << numeroUtente << " ===\n";
    for (const Requisicao& r : requisicoes) {
        if (r.getNumeroUtente() == numeroUtente) {
            r.mostrar(); std::cout << "--------------------------\n"; encontrou = true;
        }
    }
    if (!encontrou) std::cout << "Nao existem requisicoes para este utente.\n";
}

// ─── Estatísticas ─────────────────────────────────────────────────────────────

static std::time_t tmParaTime(const std::tm& t) {
    std::tm copia = t;
    return std::mktime(&copia);
}

void Biblioteca::mostrarEstatisticasSemana() const {
    std::time_t agora = std::time(nullptr);
    std::time_t limite = agora - 7 * 24 * 60 * 60;

    int total = 0, ativas = 0, fechadas = 0;
    for (const Requisicao& r : requisicoes) {
        std::time_t dataR = tmParaTime(r.getDataRequisicaoTm());
        if (dataR >= limite) {
            total++;
            r.estaAtiva() ? ativas++ : fechadas++;
        }
    }

    std::cout << "\n=== Estatisticas da Semana ===\n";
    std::cout << "Requisicoes totais: " << total << "\n";
    std::cout << "  Ativas:           " << ativas << "\n";
    std::cout << "  Concluidas:       " << fechadas << "\n";
}

void Biblioteca::mostrarEstatisticasMes() const {
    std::time_t agora = std::time(nullptr);
    std::tm* local = std::localtime(&agora);
    int mesAtual = local->tm_mon;
    int anoAtual = local->tm_year;

    int total = 0, ativas = 0, fechadas = 0;
    for (const Requisicao& r : requisicoes) {
        const std::tm& d = r.getDataRequisicaoTm();
        if (d.tm_mon == mesAtual && d.tm_year == anoAtual) {
            total++;
            r.estaAtiva() ? ativas++ : fechadas++;
        }
    }

    std::string isbnMaisReq;
    int maxCount = 0;
    for (const auto& livro : livros) {
        int count = 0;
        for (const Requisicao& r : requisicoes) {
            const std::tm& d = r.getDataRequisicaoTm();
            if (d.tm_mon == mesAtual && d.tm_year == anoAtual &&
                r.getIsbnLivro() == livro->getIsbn()) count++;
        }
        if (count > maxCount) { maxCount = count; isbnMaisReq = livro->getIsbn(); }
    }

    std::cout << "\n=== Estatisticas do Mes ===\n";
    std::cout << "Requisicoes totais: " << total << "\n";
    std::cout << "  Ativas:           " << ativas << "\n";
    std::cout << "  Concluidas:       " << fechadas << "\n";
    if (maxCount > 0) {
        Livro* l = const_cast<Biblioteca*>(this)->procurarLivroPorIsbn(isbnMaisReq);
        std::cout << "Livro mais requisitado: "
                  << (l ? l->getTitulo() : isbnMaisReq)
                  << " (" << maxCount << " vez(es))\n";
    }
}

void Biblioteca::mostrarEstatisticasAno() const {
    std::time_t agora = std::time(nullptr);
    std::tm* local = std::localtime(&agora);
    int anoAtual = local->tm_year;

    int total = 0, ativas = 0, fechadas = 0;
    int porMes[12] = {};

    for (const Requisicao& r : requisicoes) {
        const std::tm& d = r.getDataRequisicaoTm();
        if (d.tm_year == anoAtual) {
            total++;
            r.estaAtiva() ? ativas++ : fechadas++;
            porMes[d.tm_mon]++;
        }
    }

    const char* nomesMes[] = {
            "Janeiro","Fevereiro","Marco","Abril","Maio","Junho",
            "Julho","Agosto","Setembro","Outubro","Novembro","Dezembro"
    };

    std::cout << "\n=== Estatisticas do Ano (" << (anoAtual + 1900) << ") ===\n";
    std::cout << "Requisicoes totais: " << total << "\n";
    std::cout << "  Ativas:           " << ativas << "\n";
    std::cout << "  Concluidas:       " << fechadas << "\n";
    std::cout << "\nDistribuicao mensal:\n";
    for (int i = 0; i < 12; i++) {
        if (porMes[i] > 0)
            std::cout << "  " << nomesMes[i] << ": " << porMes[i] << "\n";
    }
}