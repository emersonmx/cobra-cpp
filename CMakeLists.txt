# Base
cmake_minimum_required(VERSION 2.6) 
project(cobra) 

# Basic build environment
if (CMAKE_BUILD_TYPE STREQUAL "")
     set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING 
         "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." 
         FORCE)
endif ()

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
if (CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fmessage-length=0")
endif (CMAKE_COMPILER_IS_GNUCC)
if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmessage-length=0")
endif (CMAKE_COMPILER_IS_GNUCXX)

include(FindPkgConfig)

find_package(SFML 2 REQUIRED system window graphics) 

# Targets
add_executable(${PROJECT_NAME}
    cobra/application.cpp 
    cobra/main.cpp
)

include_directories(${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}/lib/
)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif () 

target_link_libraries(${PROJECT_NAME}
    ${EXTRA_LIBS}
)
