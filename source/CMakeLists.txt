cmake_minimum_required(VERSION 2.6)

set(the_target "cvcmd")
project (${the_target})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
file(
	GLOB sources "*.cpp"
	)

set(CMAKE_CXX_FLAGS "-std=c++11")

find_package(OpenCV REQUIRED)
find_package(Boost COMPONENTS
	filesystem
	program_options
	REQUIRED)

add_library(${the_target} SHARED ${sources})
target_link_libraries(${the_target} stdc++  ${OpenCV_LIBS} ${Boost_LIBRARIES})
install(TARGETS ${the_target} DESTINATION lib)

