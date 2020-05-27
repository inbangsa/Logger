add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/third_party/include/>
  $<INSTALL_INTERFACE:include> 
)

enable_testing()

function(test_lib test_target SOURCE1 SOURCE2)

	add_executable(${test_target} ${SOURCE1} ${SOURCE2})
    
	#test file location.
	target_include_directories(${test_target} PUBLIC
	    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/test/include>    
        $<INSTALL_INTERFACE:include>)
	
	#source file location. 
	target_include_directories(${test_target} PRIVATE
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/logger/>
        $<INSTALL_INTERFACE:include>)
	
	#link test with lib.
	target_link_libraries(${test_target} Catch logger_lib_target)
	add_test(NAME ${test_target} COMMAND ${test_target})
	set_tests_properties(${test_target} PROPERTIES RUN_SERIAL OFF)
endfunction()

test_lib(test_common src/test_main.cpp src/test_common.cpp)

test_lib(test_formatter src/test_main.cpp src/test_formatter.cpp)

test_lib(test_sink src/test_main.cpp src/test_sink.cpp)
