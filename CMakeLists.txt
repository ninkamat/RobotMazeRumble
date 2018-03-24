cmake_minimum_required (VERSION 3.0)

#----------------------------------------------------------------------
#	PROJECT NAME
#----------------------------------------------------------------------
project(RobotMazeRumble)
set (PROJECT_NAME RobotMazeRumble)

#----------------------------------------------------------------------
#	Setup CMake Flags
#----------------------------------------------------------------------
if (MSVC)
	set (MSVC_CXX_FLAGS "/MP /MT /wd4996")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MSVC_CXX_FLAGS}")
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${MSVC_C_FLAGS}")
	string (REGEX REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
	string (REGEX REPLACE "/MD" "/MT" CMAKE_C_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE})
	string (REGEX REPLACE "/MDd" "/MTd" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
	string (REGEX REPLACE "/MDd" "/MTd" CMAKE_C_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
elseif (APPLE)
	set (CLANG_CXX_FLAGS "-std=c++11")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CLANG_CXX_FLAGS} -mmacosx-version-min=10.9")
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mmacosx-version-min=10.9")
else ()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif ()

#----------------------------------------------------------------------
# Set data directory
#----------------------------------------------------------------------
set (DATA_LOCATION "${${PROJECT_NAME}_SOURCE_DIR}/data")

#----------------------------------------------------------------------
# Add font and png bitmap files to include directory
#----------------------------------------------------------------------
add_subdirectory(include/ysgl)
add_subdirectory(include/ysglfont)
include_directories(include/ysglfont)
add_subdirectory(include/yspng)
include_directories(include/yspng)

#----------------------------------------------------------------------
# Add fssimplewindow framework subdirectory
#----------------------------------------------------------------------
add_subdirectory(include/fssimplewindow)
include_directories(include/fssimplewindow)

#----------------------------------------------------------------------
# Add source subdirectory
#----------------------------------------------------------------------
add_subdirectory(src)

set(CMAKE_INSTALL_PREFIX "${${PROJECT_NAME}_SOURCE_DIR}/")