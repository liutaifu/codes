SET(sock_SRCS Socket.cpp)

add_library(Socket SHARED ${sock_SRCS})
#target_link_libraries (Cabinet Socket)
