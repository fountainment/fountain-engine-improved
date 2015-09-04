set(FOUNTAIN_LINK_LIBRARY fountain)

if(LINUX)
	set(PLATFORM_LINK_LIBRARY glfw GLEW GL freeimage openal Box2D)
endif()

if(WINDOWS)
	link_directories(${PROJECT_SOURCE_DIR}/deps/lib ${PROJECT_BINARY_DIR}/bin)
	set(PLATFORM_LINK_LIBRARY glfw3 glew32s opengl32 FreeImage OpenAL32 Box2D legacy_stdio_definitions)
endif()

add_subdirectory(fountain-tests)
