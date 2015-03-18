cmake_minimum_required(VERSION 3.1)
project(tp_multitache)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#repetoire des includes et repertoires
include_directories( /share/public/tp/tp-multitache/)
LINK_DIRECTORIES( /share/public/tp/tp-multitache/)


set(SOURCE_FILES GestionMenu.cpp
                 GestionMenu.h
                 Mere.cpp
                 Voie.h
                 Voie.cpp
                 )
add_executable(tp_multitache ${SOURCE_FILES})

target_link_libraries(tp_multitache -ltp -ltcl -lncurses)