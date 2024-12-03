cmake_minimum_required(VERSION 3.26)
project(TP C)

set(CMAKE_C_STANDARD 11)

add_executable(TP main.c
        util.c
        util.h
        funcao.c
        funcao.h
        algoritmo.c
        algoritmo.h)
