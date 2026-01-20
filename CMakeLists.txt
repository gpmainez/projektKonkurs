cmake_minimum_required(VERSION 4.0)
project(projekt)

set(CMAKE_CXX_STANDARD 20)

add_executable(projekt Evaluator.cpp Evaluator.h
        Individual.cpp
        Individual.h
        main.cpp
        Algorythm.cpp
        Algorythm.h
        LoadBalancer.cpp
        LoadBalancer.h
        REunner.cpp
        REunner.h)
