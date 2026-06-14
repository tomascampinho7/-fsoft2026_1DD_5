add_executable(BibliotecaTester
        tests.cpp
        ../Project/src/Livro.cpp
        ../Project/src/Utente.cpp
        ../Project/src/Requisicao.cpp
        ../Project/src/Bibliotecario.cpp
        ../Project/src/Biblioteca.cpp
        ../Project/src/Interface.cpp
)

target_include_directories(BibliotecaTester PRIVATE ../Project/Include)