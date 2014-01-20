cmake_minimum_required(VERSION 2.6)

set(the_target "cvcmd-sample-per-image")
project(${the_target})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include/)
file(
	GLOB sources "*.cpp"
	)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror -Weffc++")

find_package(OpenCV REQUIRED)
find_package(Boost COMPONENTS
	program_options
	REQUIRED)

add_executable(${the_target} ${sources})
target_link_libraries(
	${the_target} stdc++ cvcmd ${OpenCV_LIBS} ${Boost_LIBRARIES})

install(TARGETS ${the_target} DESTINATION bin)

