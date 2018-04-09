cmake_minimum_required (VERSION 3.0)

#----------------------------------------------------------------------
# Set source and header files
#----------------------------------------------------------------------
set (APPLICATION_SOURCE
	Astar.cpp
	EndOfLevel.cpp
	maze3D.cpp
	Menu3D.cpp
	RMRGame3D.cpp
	RoboMazeRumble3D.cpp
	RobotClass3D.cpp
	Tutorial3D.cpp
)

set (APPLICATION_HEADERS
	Astar.h
	EndOfLevel.h
	maze3D.h
	Menu3D.h
	RMRGame3D.h
	RobotClass3D.h
	Tutorial3D.h 
)

#----------------------------------------------------------------------
# Set executable path
#----------------------------------------------------------------------
set (EXECUTABLE_OUTPUT_PATH ..)

#----------------------------------------------------------------------
# Add executable
#----------------------------------------------------------------------
if (MSVC)
	add_executable (${PROJECT_NAME} WIN32 ${APPLICATION_SOURCE} ${APPLICATION_HEADERS})
	set (DATA_COPY_DIR "${EXECUTABLE_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}")
elseif (APPLE)
	add_executable (${PROJECT_NAME} MACOSX_BUNDLE ${APPLICATION_SOURCE} ${APPLICATION_HEADERS})
	set (DATA_COPY_DIR "${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.app/Contents/Resources")
else ()
	add_executable (${PROJECT_NAME} ${APPLICATION_SOURCE} ${APPLICATION_HEADERS})
	set (DATA_COPY_DIR "${EXECUTABLE_OUTPUT_PATH}")
endif()

#----------------------------------------------------------------------
# Link libraries
#----------------------------------------------------------------------
target_link_libraries (${PROJECT_NAME} fssimplewindow)
target_link_libraries (${PROJECT_NAME} ysbitmapfont)
target_link_libraries (${PROJECT_NAME} ysbitmap)
target_include_directories(${PROJECT_NAME} PUBLIC include/ysglfont)
target_include_directories(${PROJECT_NAME} PUBLIC include/yspng)
target_include_directories(${PROJECT_NAME} PUBLIC include/fssimplewindow)

#----------------------------------------------------------------------
# Copy data post build
#----------------------------------------------------------------------
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
	COMMAND echo Copy
	COMMAND echo From: ${ONE_DATA_FILE_LOCATION}
	COMMAND echo To:   ${DATA_COPY_DIR}
	COMMAND cmake -E copy_directory "${DATA_LOCATION}" "${DATA_COPY_DIR}")

install(TARGETS ${PROJECT_NAME} DESTINATION ${${PROJECT_NAME}_SOURCE_DIR})