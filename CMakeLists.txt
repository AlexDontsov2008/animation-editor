cmake_minimum_required(VERSION 3.2)


project(AnimationEditor)

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake/;${CMAKE_MODULE_PATH}")

find_package(SFML 2 COMPONENTS audio graphics window system network)

include_directories(${SFML_INCLUDE_DIR})



# Specific compiler options
if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -stdlib=libc++")
endif()

set (SRC
	Source/Application.cpp
	Source/Button.cpp
	Source/FontStorage.cpp
	Source/InputWindow.cpp
	Source/Label.cpp
	Source/Line.cpp
	Source/Main.cpp
	Source/Point.cpp
	Source/Rectangle.cpp
	Source/SceneNode.cpp
	Source/UserInput.cpp
	Source/Utility.cpp
	Source/WorkFlow.cpp)


include_directories("Include/")
add_executable(AnimationEditor ${SRC})

target_link_libraries(AnimationEditor ${SFML_LIBRARIES})

install(DIRECTORY ${CHAPTER_DIR}/Resources
		DESTINATION ${PROJECT_NAME}
		PATTERN "CMakeLists.txt" EXCLUDE)











