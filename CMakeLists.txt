cmake_minimum_required(VERSION 3.4)
project(mote_vision)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

message("Configuration")
set(THIRD_PARTY_LIBRARIES "${CMAKE_SOURCE_DIR}/libs")
set(SWS_VERSION "v2.0")
set(SWS_REPO_URL "git@github.com:eidheim/Simple-Web-Server.git")

find_package(Git REQUIRED)

message("Git")
message("-- Exe at: ${GIT_EXECUTABLE}")
message("")

set(SWS_DIR "${THIRD_PARTY_LIBRARIES}/sws")
if (NOT EXISTS ${SWS_DIR})
	message("Cloning Simple-Web-Server (${SWS_REPO_URL}) into ${THIRD_PARTY_LIBRARIES}/sws")
	execute_process(
		COMMAND "${GIT_EXECUTABLE}" clone ${SWS_REPO_URL} sws
		WORKING_DIRECTORY ${THIRD_PARTY_LIBRARIES}
		ERROR_VARIABLE GIT_ERROR
		RESULT_VARIABLE GIT_RESULT
	)
	if (${GIT_RESULT} EQUAL 0)                                 # if success
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

set(JSONCPP_VERSION "1.7.3")
set(JSONCPP_REPO_URL "git@github.com:open-source-parsers/jsoncpp.git")
set(JSONCPP_DIR "${THIRD_PARTY_LIBRARIES}/jsoncpp")
if (NOT EXISTS ${JSONCPP_DIR})
	message("Clonning JSON-CPP (${JSONCPP_REPO_URL}) ... into ${JSONCPP_DIR}")
	execute_process(
		COMMAND "${GIT_EXECUTABLE}" clone ${JSONCPP_REPO_URL} jsoncpp
		WORKING_DIRECTORY ${THIRD_PARTY_LIBRARIES}
		ERROR_VARIABLE GIT_ERROR
		RESULT_VARIABLE GIT_RESULT
	)
	if (${GIT_RESULT} EQUAL 0)                                 # if success
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
			file(MAKE_DIRECTORY "${JSONCPP_DIR}/build")
			file(MAKE_DIRECTORY "${JSONCPP_DIR}/build/debug")
			file(MAKE_DIRECTORY "${JSONCPP_DIR}/build/release")
			file(MAKE_DIRECTORY "${JSONCPP_DIR}/isntall")
			file(MAKE_DIRECTORY "${JSONCPP_DIR}/isntall/debug")
			file(MAKE_DIRECTORY "${JSONCPP_DIR}/isntall/release")
			execute_process(
				COMMAND cmake -DCMAKE_INSTALL_PREFIX=../../install/debug -DBUILD_SHARED_LIBS=ON -config Debug ../..
				WORKING_DIRECTORY "${JSONCPP_DIR}/build/debug"
				RESULT_VARIABLE CMAKE_RESULT
			)
			if (${CMAKE_RESULT} EQUAL 0)
				execute_process(
					COMMAND make install
					WORKING_DIRECTORY "${JSONCPP_DIR}/build/debug"
					RESULT_VARIABLE MAKE_RESULT
				)
				if (MAKE_RESULT GREATER 0)
					file(REMOVE_RECURSE ${JSONCPP_DIR})
					message(FATAL_ERROR "Cannot make JSON-CPP.")
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

find_package(OpenCV REQUIRED)

message("OpenCV")
message("-- Libs: ${OpenCV_LIBS}")
message("")

set(SOURCE_FILES
	src/main.cpp

	src/capture/devices/device.hpp
	)

add_executable(vision ${SOURCE_FILES})

message("OpenCV: ${OpenCV_LIBS}")

target_link_libraries(vision
	opencv_videostab opencv_video opencv_ts opencv_superres opencv_stitching opencv_photo opencv_ocl
	opencv_objdetect opencv_ml opencv_legacy opencv_imgproc opencv_highgui opencv_gpu opencv_flann opencv_features2d
	opencv_core opencv_contrib opencv_calib3d

	jsoncpp
	)
