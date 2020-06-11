cmake_minimum_required(VERSION 3.4)

project("Logger" VERSION 1.0.1
             DESCRIPTION "A header only c++ library that helps to log the messages at various severity level."
             HOMEPAGE_URL "https://github.com/inbangsa/Logger")

#Includes standard Project settings.
include(cmake/StandardProjectSettings.cmake)

#Add interface library.
add_library(logger_lib_target INTERFACE)

target_include_directories(logger_lib_target INTERFACE 
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>)

option(BUILD_EXAMPLE "Turn on to build example." ON)

if(BUILD_EXAMPLE)
add_subdirectory(sample)
endif()

#Install the required files and folder.
install(DIRECTORY include DESTINATION ${CMAKE_INSTALL_PREFIX})