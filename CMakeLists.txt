cmake_minimum_required(VERSION 3.0)

project(Tank_Game)

set(EXECUTABLE_OUTPUT_PATH .)

include_directories(tank_game/include)
include_directories(tank_game/include/Manager)

# find Boost python
FIND_PACKAGE(PythonLibs 2.7 REQUIRED)
FIND_PACKAGE(Boost  ${BOOST_VERSION}  COMPONENTS python)
include_directories("${Boost_INCLUDE_DIR}"   "${PYTHON_INCLUDE_DIRS}")
link_directories("${PYTHON_INCLUDE_DIRS}" "${Boost_LIBRARY_DIRS}")

# find anax
set(ANAX_INCLUDE_DIR /home/guillaume/anax/include/)
set(ANAX_LIB_DIR    /home/guillaume/anax/build/lib/)
include_directories(${ANAX_INCLUDE_DIR})
include_directories(lib/)
link_directories(${ANAX_LIB_DIR})

# find SFML
list(APPEND CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules")
find_package(SFML 2.4 COMPONENTS system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})

if(CMAKE_COMPILER_IS_GNUCXX)
        add_definitions(-std=c++17 -Wall)
        # add_definitions(-O2 -s -DNDEBUG)
        add_definitions(-g -DEBUG)
        add_definitions(${GCC_COVERAGE_LINK_FLAGS}$)
endif()

file(
    GLOB_RECURSE
    source_files
        
    lib/*.hpp
    tank_game/*.cpp
    tank_game/*.hpp

)

add_executable(
  Tank_Game
  tank_game/main.cxx
  ${source_files}
)

target_link_libraries(
  Tank_Game 
  python2.7
  ${SFML_LIBRARIES} 
  anax
)

add_executable(
  Tank_Game_Test
  tank_game/test.cxx
  ${source_files}
)

target_link_libraries(
  Tank_Game_Test 
  python2.7
  ${SFML_LIBRARIES} 
  anax
)
