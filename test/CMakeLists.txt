project(mockeur CXX)
cmake_minimum_required(VERSION 2.8)

########################################################################
# Directories
########################################################################

set(MOCKEUR_TEST_DIR ${MOCKEUR_DIR}/test)
set(MOCKEUR_TEST_INCLUDE_DIR ${MOCKEUR_TEST_DIR}/include)
set(MOCKEUR_TEST_SRC_DIR ${MOCKEUR_TEST_DIR}/src)

include_directories(${MOCKEUR_TEST_INCLUDE_DIR})

set(MOCKEUR_TEST_SRCS
    ${MOCKEUR_TEST_SRC_DIR}/MockTest.cpp
)

add_executable(mockeur-test ${MOCKEUR_TEST_SRCS})
target_link_libraries(mockeur-test mockeur)
