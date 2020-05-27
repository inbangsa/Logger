cmake_minimum_required(VERSION 3.4)

project("Logger" VERSION 1.0.1
             DESCRIPTION "A header only c++ library that helps to log the messages at various severity level."
             HOMEPAGE_URL "https://github.com/inbangsa/Logger")

include(cmake/StandardProjectSettings.cmake)

#Add interface library.
add_library(logger_lib_target INTERFACE)

target_include_directories(logger_lib_target INTERFACE 
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include/>)

#testing options.
option(BUILD_TEST "Build tests" ON)
if(BUILD_TEST)
enable_testing()
add_subdirectory(test)
endif()

#Install the required files and folder.
install(DIRECTORY include DESTINATION ${CMAKE_INSTALL_PREFIX})
