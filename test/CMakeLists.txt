enable_testing()

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

file(GLOB_RECURSE Test_src "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

foreach( test ${Test_src} )
	get_filename_component( file_name ${test} NAME_WE )
	add_executable(${file_name} ${test})

	target_link_libraries(${file_name} Boost::unit_test_framework)

	set_target_properties( ${file_name} PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

	add_test(NAME ${file_name}
		WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
		COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/bin")
endforeach()