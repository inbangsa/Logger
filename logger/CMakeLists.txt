#Interface target for logger lib.
add_library(logger_lib_target INTERFACE )

#Include Directories for logger lib target.
target_include_directories(logger_lib_target INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
  $<INSTALL_INTERFACE:include/>  
)
