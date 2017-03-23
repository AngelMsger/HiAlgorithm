cmake_minimum_required(VERSION 3.6)

project(HiAlgorithm)

set(CMAKE_CXX_STANDARD 14)

aux_source_directory(. SOURCE_FILES)

add_executable(HiAlgorithm ${SOURCE_FILES})
