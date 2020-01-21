SET(Reg_SRCS RegKeyIni.cpp)

add_library(RegKeyIni SHARED ${Reg_SRCS})

target_link_libraries(RegKeyIni parseIni)
#target_link_libraries(RegKeyIni Clog)
