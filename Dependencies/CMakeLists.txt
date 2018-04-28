CMAKE_MINIMUM_REQUIRED(VERSION 2.8.3)

#==============================Overwrite LIBZMQ settings==============================
option(BUILD_SHARED "Whether or not to build the shared object"  OFF)
set (ZMQ_BUILD_TESTS OFF CACHE BOOL "Build the tests for ZeroMQ")

#==============================Overwrite Protobuf settings===========================
#Before processing protobuf dependency it's necessary to overwrite this option, otherwise gmock needs to be installed
option(protobuf_BUILD_TESTS "Build tests" OFF)
option(protobuf_BUILD_SHARED_LIBS OFF)

#==============================Overwrite zmqpp settings============================== 
set( ZMQPP_BUILD_SHARED   false   CACHE BOOL "Build the ZMQPP dynamic library" )
set( IS_TRAVIS_CI_BUILD   false    CACHE bool "Defines TRAVIS_CI_BUILD - Should the tests avoid running cases where memory is scarce." )
set( ZMQPP_INCLUDE_DIR ${ZMQPP_INCLUDE_DIR}
						${CMAKE_CURRENT_BINARY_DIR}/zmqpp
						PARENT_SCOPE)
						

						
ADD_SUBDIRECTORY(libzmq)

#option(protobuf_MSVC_STATIC_RUNTINE "Static runtime" OFF)


SET(ZEROMQ_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/libzmq/include)
SET(ZEROMQ_LIBRARY_SHARED "libzmq-shared")
SET(ZEROMQ_LIBRARY_STATIC "libzmq-static")

option (IS_TRAVIS_CI_BUILD "false")
option(ZMQPP_LIBZMQ_CMAKE "true")


ADD_SUBDIRECTORY(protobuf/cmake)
ADD_SUBDIRECTORY(zmqpp)

option (IS_TRAVIS_CI_BUILD "false")
SET(ZMQPP_LIBZMQ_CMAKE OFF)
SET(ZMQ_BUILD_TESTS OFF)

