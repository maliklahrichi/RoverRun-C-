cmake_minimum_required(VERSION 3.27)
project(RoverRun C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(RoverRun
        loc.c
        loc.h
        main.c
        map.c
        map.h
        moves.c
        moves.h
        queue.c
        queue.h
        stack.c
        stack.h
        tree.c
        tree.h
        draw.c
        draw.h
        node.c
        node.h)