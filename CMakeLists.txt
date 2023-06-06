cmake_minimum_required(VERSION 3.25)
project(personal_diary_C C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(personal_diary_C
        fonctions.c
        fonctions.h
        main.c)
