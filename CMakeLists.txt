cmake_minimum_required(VERSION 3.10)

project(CompactorDrive)

find_package(fmt CONFIG REQUIRED)

add_executable(CompactorDrive main.cpp)

target_link_libraries(CompactorDrive PRIVATE fmt::fmt)
