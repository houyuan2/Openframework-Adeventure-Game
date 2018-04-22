cmake_minimum_required(VERSION 3.9)
project(final-project)

set(CMAKE_CXX_STANDARD 14)

add_executable(TestSuite test/tests.cpp src/Game.cpp src/Items.cpp)