cmake_minimum_required(VERSION 3.13)
project(assignment_4_zhanggy31_master C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(assignment_4_zhanggy31_master
        dynarray.c
        dynarray.h
        pq.c
        pq.h
        test_pq.c)
