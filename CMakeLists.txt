# Project settings
cmake_minimum_required(VERSION 2.6) 
project(cobra) 

# Compiler settings
if (CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
if (CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fmessage-length=0")
endif()
if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmessage-length=0")
endif()

# Includes and libraries settings
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH}) 

include(FindPkgConfig)

find_package(SFML 2 REQUIRED system window graphics) 
if (SFML_FOUND)
    set(EXTRA_INCLUDES ${EXTRA_INCLUDES} ${SFML_INCLUDE_DIR})
    set(EXTRA_LIBS ${EXTRA_LIBS} ${SFML_LIBRARIES})
endif()

# Executable settings
include_directories(${PROJECT_SOURCE_DIR}
    ${EXTRA_INCLUDES}
) 

add_executable(${PROJECT_NAME}
    cobra/application.cpp 
    cobra/main.cpp
)

target_link_libraries(${PROJECT_NAME}
    ${EXTRA_LIBS}
)
