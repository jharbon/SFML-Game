cmake_minimum_required(VERSION 3.10)
project(SFMLGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define function for enforcing existence of specified directories
function(enforce_dir_existence dir_path must_already_exist)
    if(NOT EXISTS ${dir_path})
        if (must_already_exist)
            message(FATAL_ERROR "Required directory which must already exist is missing: ${dir_path}")
        else() 
            file(MAKE_DIRECTORY ${dir_path})
            message(STATUS "Created required directory: ${dir_path}")
        endif()
    endif()
endfunction()

# Ensure that some of the required directories already exist in the project root  
enforce_dir_existence(${CMAKE_SOURCE_DIR}/assets ON)
enforce_dir_existence(${CMAKE_SOURCE_DIR}/config ON)
enforce_dir_existence(${CMAKE_SOURCE_DIR}/include ON)
enforce_dir_existence(${CMAKE_SOURCE_DIR}/src ON)
enforce_dir_existence(${CMAKE_SOURCE_DIR}/tests ON)
# Create the remaining required directories if they do not already exist
enforce_dir_existence(${CMAKE_SOURCE_DIR}/bin OFF)
enforce_dir_existence(${CMAKE_SOURCE_DIR}/logs OFF)

if (NOT DEFINED LIB_DIR_PATH)
    set(LIB_DIR_PATH ${CMAKE_SOURCE_DIR}/lib)
endif()
if (NOT EXISTS ${LIB_DIR_PATH})
    message(WARNING "Optional lib directory missing. If you want to manually add one or more external dependencies, add them to either '${CMAKE_SOURCE_DIR}/lib' or a custom specified lib directory")
else()
    # Search for dependencies in lib directory
    list(APPEND CMAKE_PREFIX_PATH ${LIB_DIR_PATH})
endif()

# Find dependencies - search in both <project root>/lib (if it exists) and system-wide paths
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system) 

# Compile a game executable
add_executable(game src/main.cpp)

# Install game executable in bin/
install(TARGETS game DESTINATION ${CMAKE_SOURCE_DIR}/bin)

# Link required libraries
target_link_libraries(game PRIVATE spdlog fmt sfml-graphics sfml-window sfml-system)