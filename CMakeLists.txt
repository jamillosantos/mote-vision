cmake_minimum_required(VERSION 3.4)
project(mote_vision)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# Configuration
set(THIRD_PARTY_LIBRARIES "${CMAKE_SOURCE_DIR}/libs" CACHE FILEPATH "Third party libraries directory")

# Simple-Web-Server
set(SWS_VERSION "v2.0"
	CACHE STRING "Simple-Web-Server version")
set(SWS_REPO_URL "git@github.com:eidheim/Simple-Web-Server.git"
	CACHE STRING "Simple-Web-Server git repository URL")
set(SWS_DIR "${THIRD_PARTY_LIBRARIES}/sws"
	CACHE STRING "Simple-Web-Server destiny folder")

# JSONCPP
set(JSONCPP_VERSION "1.7.3"
	CACHE STRING "JSON-CPP library's version")
set(JSONCPP_REPO_URL "git@github.com:open-source-parsers/jsoncpp.git"
	CACHE STRING "JSON-CPP library's git repository URL")
set(JSONCPP_DIR "${THIRD_PARTY_LIBRARIES}/jsoncpp"
	CACHE STRING "JSON-CPP destiny folder")

# GTest
set(GTEST_VERSION "release-1.7.0"
	CACHE STRING "GTest library's version")
set(GTEST_REPO_URL "git@github.com:google/googletest.git"
	CACHE STRING "GTest library's git repository URL")
set(GTEST_DIR "${THIRD_PARTY_LIBRARIES}/googletest"
	CACHE STRING "GTest destiny folder")

message("")

message("Git")
find_package(Git REQUIRED)
message("-- Exe at: ${GIT_EXECUTABLE}")
message("")

message("Simple-Web-Server")
if (NOT EXISTS ${SWS_DIR})
	message("-- Cloning Simple-Web-Server (${SWS_REPO_URL}) into ${THIRD_PARTY_LIBRARIES}/sws")
	execute_process(
		COMMAND "${GIT_EXECUTABLE}" clone ${SWS_REPO_URL} sws
		WORKING_DIRECTORY ${THIRD_PARTY_LIBRARIES}
		ERROR_VARIABLE GIT_ERROR
		RESULT_VARIABLE GIT_RESULT
	)
	if (${GIT_RESULT} EQUAL 0)                                 # if success
		message("-- Checking Simple-Web-Server out to '${SWS_VERSION}'")
		execute_process(                                       # checkout to v2.0
			COMMAND "${GIT_EXECUTABLE}" checkout ${SWS_VERSION}
			WORKING_DIRECTORY ${SWS_DIR}
			RESULT_VARIABLE GIT_RESULT
			ERROR_VARIABLE GIT_ERROR
		)
		if (${GIT_RESULT} GREATER 0)
			file(REMOVE_RECURSE ${SWS_DIR})
			message(FATAL_ERROR "Cannot checkout Simple-Web-Server to ${SWS_VERSION}: ${GIT_ERROR}.")
		endif()
	else()
		message(FATAL_ERROR "Cannot clone Simple-Web-Server: ${GIT_ERROR}")
	endif()
endif()
set(SWS_INCLUDE_DIR ${SWS_DIR})
message("-- Include dir: ${SWS_INCLUDE_DIR}")
include_directories(${SWS_INCLUDE_DIR})
message("")

message("JSONCPP")
if (NOT EXISTS ${JSONCPP_DIR})
	message("-- Clonning JSON-CPP (${JSONCPP_REPO_URL}) ... into ${JSONCPP_DIR}")
	execute_process(
		COMMAND "${GIT_EXECUTABLE}" clone ${JSONCPP_REPO_URL} jsoncpp
		WORKING_DIRECTORY ${THIRD_PARTY_LIBRARIES}
		ERROR_VARIABLE GIT_ERROR
		RESULT_VARIABLE GIT_RESULT
	)
	if (${GIT_RESULT} EQUAL 0)                                 # if success
		message("-- Checking JSON-CPP to ${JSONCPP_VERSION}")
		execute_process(                                       # checkout to v2.0
			COMMAND "${GIT_EXECUTABLE}" checkout ${JSONCPP_VERSION}
			WORKING_DIRECTORY ${JSONCPP_DIR}
			RESULT_VARIABLE GIT_RESULT
			ERROR_VARIABLE GIT_ERROR
			)
		if (${GIT_RESULT} GREATER 0)                           # git checkout failed
			file(REMOVE_RECURSE ${JSONCPP_DIR})
			message(FATAL_ERROR "Cannot checkout JSON-CPP to ${JSONCPP_VERSION}: ${GIT_ERROR}.")
		else()                                                 # git checkout success
			message("-- CMaking ...")
			file(MAKE_DIRECTORY "${JSONCPP_DIR}/build")
			file(MAKE_DIRECTORY "${JSONCPP_DIR}/build/debug")
			file(MAKE_DIRECTORY "${JSONCPP_DIR}/install")
			file(MAKE_DIRECTORY "${JSONCPP_DIR}/install/debug")
			execute_process(
				COMMAND cmake -DCMAKE_INSTALL_PREFIX=../../install/debug -DBUILD_SHARED_LIBS=ON -config Debug ../..
				WORKING_DIRECTORY "${JSONCPP_DIR}/build/debug"
				OUTPUT_VARIABLE CMAKE_OUTPUT
				RESULT_VARIABLE CMAKE_RESULT
			)
			if (${CMAKE_RESULT} EQUAL 0)
				message("-- Making ...")
				execute_process(
					COMMAND make install
					WORKING_DIRECTORY "${JSONCPP_DIR}/build/debug"
					OUTPUT_VARIABLE MAKE_OUTPUT
					RESULT_VARIABLE MAKE_RESULT
				)
				if (MAKE_RESULT GREATER 0)
					file(REMOVE_RECURSE ${JSONCPP_DIR})
					message(FATAL_ERROR "Cannot make JSON-CPP.")
				else()
					message("-- Success!")
				endif()
			else()
				file(REMOVE_RECURSE ${JSONCPP_DIR})
				message(FATAL_ERROR "Cannot cmake JSON-CPP.")
			endif()
		endif()
	else()
		message(FATAL_ERROR "Cannot clone JSON-CPP: ${GIT_ERROR}")
	endif()
endif()
find_library(jsoncpp jsoncpp
	HINTS "${JSONCPP_DIR}/install/debug/lib"
	NO_DEFAULT_PATH
	)
if (${jsoncpp} STREQUAL "jsoncpp-NOTFOUND")
	message(FATAL_ERROR "Cannot find jsoncpp at '${JSONCPP_DIR}/install/debug/lib'.")
else()
	message("-- JSONCPP found at ${jsoncpp}")
	set(JSONCPP_INCLUDE_DIR "${JSONCPP_DIR}/install/debug/include")
	message("-- Include directory: ${JSONCPP_INCLUDE_DIR}")
	include_directories(${JSONCPP_INCLUDE_DIR})
endif()
message("")

message("GTest")
if (NOT EXISTS ${GTEST_DIR})
	message("-- Clonning GTest (${GTEST_REPO_URL}) ... into ${GTEST_DIR}")
	execute_process(
		COMMAND "${GIT_EXECUTABLE}" clone ${GTEST_REPO_URL} googletest
		WORKING_DIRECTORY ${THIRD_PARTY_LIBRARIES}
		ERROR_VARIABLE GIT_ERROR
		RESULT_VARIABLE GIT_RESULT
	)
	if (${GIT_RESULT} EQUAL 0)                                 # if success
		message("-- Checking out to ${GTEST_VERSION} ...")
		execute_process(                                       # checkout to v2.0
			COMMAND "${GIT_EXECUTABLE}" checkout ${GTEST_VERSION}
			WORKING_DIRECTORY ${GTEST_DIR}
			RESULT_VARIABLE GIT_RESULT
			ERROR_VARIABLE GIT_ERROR
			)
		if (${GIT_RESULT} GREATER 0)                           # git checkout failed
			file(REMOVE_RECURSE ${GTEST_DIR})
			message(FATAL_ERROR "Cannot checkout GTest to ${GTEST_VERSION}: ${GIT_ERROR}.")
		else()                                                 # git checkout success
			file(MAKE_DIRECTORY "${GTEST_DIR}/build")
			file(MAKE_DIRECTORY "${GTEST_DIR}/build/debug")
			message("-- CMaking ...")
			execute_process(
				COMMAND cmake -config Debug ../..
				WORKING_DIRECTORY "${GTEST_DIR}/build/debug"
				OUTPUT_VARIABLE CMAKE_OUTPUT
				RESULT_VARIABLE CMAKE_RESULT
			)
			if (${CMAKE_RESULT} EQUAL 0)
				message("-- Making ...")
				execute_process(
					COMMAND make
					WORKING_DIRECTORY "${GTEST_DIR}/build/debug"
					OUTPUT_VARIABLE MAKE_OUTPUT
					RESULT_VARIABLE MAKE_RESULT
				)
				if (MAKE_RESULT GREATER 0)
					file(REMOVE_RECURSE ${GTEST_DIR})
					message(FATAL_ERROR "Cannot make GTest.")
				else()
					message("-- Success!")
				endif()
			else()
				file(REMOVE_RECURSE ${GTEST_DIR})
				message(FATAL_ERROR "Cannot cmake GTest.")
			endif()
		endif()
	else()
		message(FATAL_ERROR "Cannot clone GTest: ${GIT_ERROR}")
	endif()
endif()
find_library(gtest gtest
	HINTS "${GTEST_DIR}/build/debug"
	NO_DEFAULT_PATH
	)
if (${gtest} STREQUAL "gtest-NOTFOUND")
	message(FATAL_ERROR "Cannot find gtest.")
else()
	message("-- GTest found at ${gtest}")
	set(GTEST_INCLUDE_DIR "${GTEST_DIR}/include")
	message("-- Include directory: ${GTEST_INCLUDE_DIR}")
	include_directories(${GTEST_INCLUDE_DIR})
endif()
message("")

message("OpenCV")
find_package(OpenCV REQUIRED)
message("-- Libs: ${OpenCV_LIBS}")
message("")

set(SOURCE_FILES
	src/main.cpp

	src/capture/devices/device.hpp
	src/capture/devices/image.hpp
	)

add_executable(vision ${SOURCE_FILES})

target_link_libraries(vision
	${OpenCV_LIBS}

	jsoncpp
	)
