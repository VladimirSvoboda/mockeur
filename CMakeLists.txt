########################################################################
# mockeur CMake configuration file
#
# Example of a user CMake-based project using mockeur:
#
# project(FOO CXX)
# include(path/to/mockeur/root)
# include_directories(path/to/mockeur/include/dir)
# add_executable(foo foo.cpp)
# target_link_libraries(foo mockeur)
########################################################################
project(mockeur CXX)
cmake_minimum_required(VERSION 2.8.6)

########################################################################
# Directories
########################################################################
set(MOCKEUR_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(MOCKEUR_INCLUDE_DIR ${MOCKEUR_DIR}/include)
set(MOCKEUR_SRC_DIR ${MOCKEUR_DIR}/src)
set(MOCKEUR_TEST_SRC_DIR ${MOCKEUR_DIR}/test)

########################################################################
# Compiler flags
########################################################################

#-----------------------------------
# Add C++11 flag
#-----------------------------------
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(ENABLE_CXX11 "-std=c++11")

    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.7)
        set(ENABLE_CXX11 "-std=c++0x")
    else()
        set(ENABLE_CXX11 "-std=c++11")
    endif()

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ENABLE_CXX11}")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

#-----------------------------------
# Add warning flags
#-----------------------------------
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS
      "${CMAKE_CXX_FLAGS} -pipe -Wall -Wextra -pedantic -Wshadow -Wundef -Wcast-qual -Wwrite-strings -Werror=implicit-function-declaration"
  )
endif()

########################################################################
# Source files registration
########################################################################

# Where Mockeur's .h files can be found.
include_directories(${MOCKEUR_INCLUDE_DIR})

set(MOCKEUR_SRCS
    ${MOCKEUR_SRC_DIR}/ArgumentMatcher/ArgumentMatcher.cpp
)

########################################################################
# Unit tests
########################################################################

if (MOCKEUR_TEST)
    set(MOCKEUR_TEST_SRCS
        ${MOCKEUR_TEST_SRC_DIR}/MockTest.cpp
    )
    
    add_executable(mockeur-test ${MOCKEUR_TEST_SRCS})
    target_link_libraries(mockeur-test mockeur)
endif()

########################################################################
# Define the target.
# User application should link with it.
########################################################################
add_library(mockeur STATIC ${MOCKEUR_SRCS})
