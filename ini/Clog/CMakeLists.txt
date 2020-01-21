SET(Clog_SRCS Clog.cpp)

add_library(Clog SHARED ${Clog_SRCS})

target_link_libraries (Clog parseIni)
target_link_libraries (Clog RegKeyIni)
