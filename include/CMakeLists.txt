cmake_minimum_required(VERSION 2.6)

file(GLOB headers "cvcmd/*.hpp")
install(FILES ${headers} DESTINATION "include/cvcmd")

