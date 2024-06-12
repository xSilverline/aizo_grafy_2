cmake_minimum_required(VERSION 3.27)
project(aizo_grafy)

set(CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
add_executable(aizo_grafy source/class/main.cpp
        source/class/GraphGenerator.cpp
        source/headers/GraphGenerator.h
        source/headers/Structures.h
        source/class/GraphReader.cpp
        source/headers/GraphReader.h
        source/class/PrimMST.cpp
        source/headers/PrimMST.h
        source/class/PriorityQueue.cpp
        source/headers/PriorityQueue.h
        source/class/Dijkstra.cpp
        source/headers/Dijkstra.h
        source/class/KruskalMST.cpp
        source/headers/KruskalMST.h
        source/class/BellmanFord.cpp
        source/headers/BellmanFord.h
        source/headers/Counters.h)
