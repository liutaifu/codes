cmake_minimum_required (VERSION 3.16.x)
project(PAJ)

add_subdirectory(RegKeyIni)
add_subdirectory(parseIni)
add_subdirectory(Clog)
add_subdirectory(Socket)
add_subdirectory(Cabinet)


add_executable (PAJDemo main.cpp)
target_link_libraries (PAJDemo RegKeyIni)
target_link_libraries (PAJDemo parseIni)
target_link_libraries (PAJDemo Clog)
target_link_libraries (PAJDemo Socket)
target_link_libraries (PAJDemo Cabinet)
