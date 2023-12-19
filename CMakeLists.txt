cmake_minimum_required(VERSION 3.16)

project(CellularAutomata)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(WIN32)
  set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake) #module mode for windows
endif()

find_package(SFML REQUIRED COMPONENTS graphics) #config mode for unix is fine

file(GLOB SOURCES "src/*.cpp")

OPTION(LOGGING "Enable Logging" OFF) #logging disabled by default
if(LOGGING)
  add_definitions(-DLOGGING)
endif()

include_directories(${SFML_INCLUDE_DIR} include)
add_executable(automata ${SOURCES})
target_link_libraries(automata sfml-graphics)
