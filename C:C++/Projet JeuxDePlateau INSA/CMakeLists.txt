cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(JeuxDePlateau CXX)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
set(GTKMM_API_VERSION 3)

include_directories(include ${GTKMM_INCLUDE_DIRS})
add_definitions(${GTKMM_CFLAGS})
link_directories(${GTKMM_LIBRARY_DIRS})

file(GLOB
     libJeuxDePlateau_HDR
     include/*.h)

file(GLOB
     libJeuxDePlateau_SRC
     src/*.cpp)

set(CMAKE_STATIC_LIBRARY_PREFIX "")
add_library(libJeuxDePlateau STATIC ${libJeuxDePlateau_SRC} ${libJeuxDePlateau_HDR})
target_compile_features(libJeuxDePlateau PUBLIC cxx_nullptr)

add_executable(JeuxDePlateau main.cpp)
target_link_libraries(JeuxDePlateau libJeuxDePlateau ${GTKMM_LIBRARIES})
