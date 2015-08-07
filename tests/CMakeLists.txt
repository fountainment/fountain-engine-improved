include_directories(../fountain)
link_directories(${PROJECT_BINARY_DIR}/bin)

set(FOUNTAIN_LINK_LIBRARY fountain glfw3 freetype)

if(LINUX)
	set(PLATFORM_LINK_LIBRARY openal X11 GLEW GL dl Xxf86vm pthread Xi Xrandr Xcursor Xinerama)
endif()

if(WINDOWS)
	set(PLATFORM_LINK_LIBRARY OpenAL32 gdi32 glew_static opengl32)
endif()

add_subdirectory(fountain-tests)

