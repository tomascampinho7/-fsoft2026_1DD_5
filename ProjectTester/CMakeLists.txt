add_executable(BibliotecaTester
        tests.cpp
        ../Project/Livro.cpp
        ../Project/Utente.cpp
        ../Project/Requisicao.cpp
        ../Project/Bibliotecario.cpp
        ../Project/Biblioteca.cpp
)

target_include_directories(BibliotecaTester PRIVATE ../Project)