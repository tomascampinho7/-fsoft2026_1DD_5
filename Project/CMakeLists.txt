cmake_minimum_required(VERSION 3.10)

project(BibliotecaApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(BibliotecaApp
    main.cpp
    Livro.cpp
    Utente.cpp
    Requisicao.cpp
    Biblioteca.cpp
)
