cmake_minimum_required(VERSION 3.27)
project(DA_Project1)

set(CMAKE_CXX_STANDARD 14)

add_executable(DA_Project1
        src/structs/cities.cpp
        src/structs/pipes.cpp
        src/structs/reservoirs.cpp
        src/structs/stations.cpp
        src/structs/cities.h
        src/structs/stations.h
        src/structs/reservoirs.h
        src/structs/pipes.h
        src/main.cpp
        src/structs/Graph.h
        src/structs/data_structures/UFDS.cpp
        src/structs/data_structures/MutablePriorityQueue.h
        src/menu.cpp
        src/menu.h
        src/menu.cpp
        src/menu.cpp
        src/menu.cpp)
