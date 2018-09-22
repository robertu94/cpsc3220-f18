cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(virtual_memory VERSION 1.0 LANGUAGES CXX)

add_executable(virtual_memory_test
	CommandLineOptions.cc 
	Paging.cc 
	Segmentation.cc 
	VirtualMemory.cc 
	virtual_memory_test.cc
	)

target_include_directories(virtual_memory_test
	PUBLIC 
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	)

set_property(TARGET virtual_memory_test PROPERTY CXX_STANDARD 14)

