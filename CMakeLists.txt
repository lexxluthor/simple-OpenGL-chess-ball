cmake_minimum_required(VERSION 3.16)
project(anime)

set(OpenGlLinkers -lglut -lGLU -lGL)

add_executable(OpenGLLinuxTest1 anime.cpp anim.cpp anim.h checker.h) #common to all clion project
target_link_libraries(OpenGLLinuxTest1 ${OpenGlLinkers})