cmake_minimum_required(VERSION 3.4)

#Setting Version.
set(MAJOR 1)
set(MINOR 0)
set(PATCH 1)
set(VERSION ${MAJOR}.${MINOR}.${PATCH})

project("Logger" VERSION ${VERSION}
             DESCRIPTION "A header only c++ library that helps to log the messages at various severity level."
             HOMEPAGE_URL "https://github.com/inbangsa/Logger")

#Includes standard Project settings.
include(cmake/StandardProjectSettings.cmake)

#Add interface library.
add_library(logger_lib  INTERFACE)

#Include Directories.
target_include_directories(logger_lib INTERFACE 
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>)

#Option to build sample EXAMPLE.
option(BUILD_EXAMPLE "Turn on to build example." OFF)

if(BUILD_EXAMPLE)
add_subdirectory(sample)
endif()

#Setting installation paths.
set(_include include)
set(_lib lib)
set(_bin bin)


#Export the target of the library.
install(TARGETS logger_lib 
EXPORT logger_lib
RUNTIME       DESTINATION ${_bin}
LIBRARY       DESTINATION ${_lib}
ARCHIVE       DESTINATION ${_lib}
PUBLIC_HEADER DESTINATION ${_include}
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/logger_libConfigVersion.cmake
  VERSION ${VERSION}
  COMPATIBILITY SameMajorVersion)

configure_package_config_file(cmake/logger_lib-config.cmake.in  ${CMAKE_CURRENT_BINARY_DIR}/logger_lib-config.cmake
  INSTALL_DESTINATION  ${_lib}
  )

#Install the include files.
install(DIRECTORY include/logger DESTINATION include)

#Install the export group.
install(EXPORT logger_lib FILE logger_lib.cmake DESTINATION "${_lib}/cmake/logger_lib")

#Install the config.cmake file.
install(FILES  ${CMAKE_CURRENT_BINARY_DIR}/logger_lib-config.cmake DESTINATION "${_lib}/cmake/logger_lib")
install(FILES  ${CMAKE_CURRENT_BINARY_DIR}/logger_libConfigVersion.cmake DESTINATION "${_lib}/cmake/logger_lib")