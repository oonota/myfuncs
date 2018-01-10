cmake_minimum_required(VERSION 2.8)
include_directories(Eigen)
include_directories(nmf)
add_executable(main	
	main.cpp
	nmf/nmf.cpp
)
