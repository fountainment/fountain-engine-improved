include_directories(../fountain)

set(FOUNTAIN_LINK_LIBRARY fountain glfw)

if(LINUX)
	set(PLATFORM_LINK_LIBRARY GLEW GL)
endif()

if(WINDOWS)
	include_directories(../deps/include)
	link_directories(../deps/lib)
	set(PLATFORM_LINK_LIBRARY gdi32 glew32s opengl32)
endif()

add_subdirectory(fountain-tests)

