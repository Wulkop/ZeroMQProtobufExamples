CMAKE_MINIMUM_REQUIRED(VERSION 2.8.3)

PROJECT(Examples)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

SET(ZeroMQ_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/libzmq/include)
SET(PROTOBUF_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/protobuf/src)
SET(PROTOBUF_MESSAGE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Messages/c++)
SET(ZMQPP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/zmqpp/src/zmqpp)

file(GLOB ZMQ_HPP_FILES "${ZMQPP_INCLUDE_DIR}/*.hpp")


#============================Overwrite linker flags for msvc========================
if(MSVC)
        foreach(flag_var
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
			if(${flag_var} MATCHES "/MD")
				string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
			endif(${flag_var} MATCHES "/MD")
		endforeach(flag_var)
endif()

ADD_SUBDIRECTORY(Dependencies)
ADD_SUBDIRECTORY(Source)

