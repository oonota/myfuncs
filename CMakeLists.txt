cmake_minimum_required(VERSION 2.8)
SET( CMAKE_CXX_COMPILER /usr/bin/clang++)
include_directories(Eigen)
include_directories(nmf)
add_executable(main	
	main.cpp
	nmf/nmf.cpp
)
