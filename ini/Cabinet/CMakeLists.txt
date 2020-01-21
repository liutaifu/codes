SET(cab_SRCS Cabinet.cpp)

add_library(Cabinet SHARED ${cab_SRCS})
target_link_libraries (Cabinet Socket)
