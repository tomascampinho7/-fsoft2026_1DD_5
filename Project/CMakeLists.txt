cmake_minimum_required(VERSION 3.10)

project(BibliotecaApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(Include)

add_executable(BibliotecaApp
        src/main.cpp
        src/Livro.cpp
        src/Utente.cpp
        src/Requisicao.cpp
        src/Bibliotecario.cpp
        src/Biblioteca.cpp
        src/Interface.cpp
)
