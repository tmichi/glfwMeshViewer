CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

PROJECT(glfwMeshViewer)


if(UNIX)

ADD_DEFINITIONS(-g -O3 -Wall)

endif(UNIX)

if(APPLE)
	LINK_DIRECTORIES(/usr/local/lib)
	INCLUDE_DIRECTORIES(/usr/local/include /usr/local/include/eigen3)
elseif(WIN32)
	INCLUDE_DIRECTORIES(include )
	if(CMAKE_SIZEOF_VOID_P EQUAL 8) # 64bit system
		LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib/x64)
	else()
		LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)
	endif()
endif()

ADD_EXECUTABLE(glfwMeshViewer Mesh.hpp Tokenizer.hpp Camera.cpp Camera.hpp Window.cpp Window.hpp main.cpp)

if(APPLE)
TARGET_LINK_LIBRARIES(glfwMeshViewer  glfw3 "-framework OpenGL")
endif()

