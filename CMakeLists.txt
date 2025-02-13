cmake_minimum_required(VERSION 3.10)
project(SFMLGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compile a game executable
add_executable(game src/main.cpp)

# Find required packages
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system) 

# Install game executable in bin/
install(TARGETS game DESTINATION ${CMAKE_SOURCE_DIR}/bin)

# Link required libraries
target_link_libraries(game PRIVATE spdlog fmt sfml-graphics sfml-window sfml-system)