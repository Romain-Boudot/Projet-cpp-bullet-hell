cmake_minimum_required(VERSION 3.9)
project(Projet_cpp_bullet_hell)

set(CMAKE_CXX_STANDARD 11)

add_executable(Projet_cpp_bullet_hell
        apps
        Bullet.hpp
        Bullet_hell.hpp
        Enemy.hpp
        main.cpp
        Player.hpp
        README.md
        Roboto-Regular.ttf menu/Menu.cpp menu/Menu.h)
