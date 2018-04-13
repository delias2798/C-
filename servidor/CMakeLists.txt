cmake_minimum_required(VERSION 3.9)
project(servidor)

set(CMAKE_CXX_STANDARD 11)

add_executable(servidor main.cpp client.cpp client.h cmake-build-debug/Generador_Datos.cpp cmake-build-debug/Generador_Datos.h)