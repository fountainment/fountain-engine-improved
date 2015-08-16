set(FOUNTAIN_LINK_LIBRARY fountain)

if(LINUX)
	set(PLATFORM_LINK_LIBRARY glfw GLEW GL freeimage)
endif()

if(WINDOWS)
	link_directories(${PROJECT_SOURCE_DIR}/deps/lib ${PROJECT_BINARY_DIR}/bin)
	set(PLATFORM_LINK_LIBRARY glfw3 glew32s opengl32 FreeImage)
endif()

add_subdirectory(fountain-tests)
