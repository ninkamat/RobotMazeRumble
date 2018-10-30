cmake_minimum_required (VERSION 3.0)

#----------------------------------------------------------------------
#	PROJECT NAME
#----------------------------------------------------------------------
project(RobotMazeRumble)

#----------------------------------------------------------------------
#	Setup CMake Flags
#----------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 11)
if (MSVC)
	set (MSVC_CXX_FLAGS "/MP /MT /wd4996")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MSVC_CXX_FLAGS}")
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${MSVC_C_FLAGS}")
	string (REGEX REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
	string (REGEX REPLACE "/MD" "/MT" CMAKE_C_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE})
	string (REGEX REPLACE "/MDd" "/MTd" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
	string (REGEX REPLACE "/MDd" "/MTd" CMAKE_C_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
elseif (APPLE)
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mmacosx-version-min=10.9")
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
add_subdirectory(include/yspng)

#----------------------------------------------------------------------
# Add fssimplewindow framework subdirectory
#----------------------------------------------------------------------
add_subdirectory(include/fssimplewindow)

#----------------------------------------------------------------------
# Add source subdirectory
#----------------------------------------------------------------------
add_subdirectory(src)

set(CMAKE_INSTALL_PREFIX "${${PROJECT_NAME}_SOURCE_DIR}/")

# Disable in-source builds to prevent source tree corruption
if (" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "
FATAL: In-source builds are not allowed.
You should create a separate directory for build files.
")
endif()