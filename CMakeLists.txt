cmake_minimum_required(VERSION 3.10)
project(SFMLGame)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compile a game executable
add_executable(game src/main.cpp)

# Find SFML
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system) 
# Install game executable in bin/
install(TARGETS game DESTINATION ${CMAKE_SOURCE_DIR}/bin)

# Link SFML
target_link_libraries(game PRIVATE sfml-graphics sfml-window sfml-system)