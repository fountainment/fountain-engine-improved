cmake_minimum_required(VERSION 2.8)

project(Fountain)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  if(WINRT)
    set(SYSTEM_STRING "Windows RT")
  elseif(WP8)
    set(SYSTEM_STRING "Windows Phone 8")
  else()
    set(WINDOWS TRUE)
    set(SYSTEM_STRING "Windows Desktop")
  endif()
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  if(ANDROID)
    set(SYSTEM_STRING "Android")
  else()
    set(LINUX TRUE)
    set(SYSTEM_STRING "Linux")
  endif()
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  if(IOS)
    set(SYSTEM_STRING "IOS")
  else()
    set(MACOSX TRUE)
    set(APPLE TRUE)
    set(SYSTEM_STRING "Mac OSX")
  endif()
endif()

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

if(LINUX)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -O2")
endif()

add_subdirectory(deps/proj/glfw)
add_subdirectory(deps/proj/Box2D)

add_definitions(-DGLFW_INCLUDE_NONE -DGLFW_STATIC -DGLEW_STATIC)
include_directories(fountain)
include_directories(deps/proj/glfw/include deps/proj/Box2D)
link_directories(${PROJECT_BINARY_DIR}/lib)

set(FOUNTAIN_LINK_LIBRARY fountain)

if(LINUX)
  add_definitions(-Wall -fexceptions -std=c++11)
  add_definitions(-I/usr/include/freetype2)

  set(GLFW_DEPS_LIBRARY X11 Xrandr Xinerama Xi Xxf86vm Xcursor pthread rt m dl)
  set(PLATFORM_LINK_LIBRARY glfw ${GLFW_DEPS_LIBRARY} GLEW GL freeimage openal Box2D freetype)

  file(COPY ${PROJECT_SOURCE_DIR}/res DESTINATION ${EXECUTABLE_OUTPUT_PATH})
endif()

if(WINDOWS)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)

  include_directories(${PROJECT_SOURCE_DIR}/deps/include)
  link_directories(${PROJECT_SOURCE_DIR}/deps/lib)

  set(PLATFORM_LINK_LIBRARY glfw glew32s opengl32 FreeImage OpenAL32 Box2D freetype winmm)
  if (MSVC14)
    set(PLATFORM_LINK_LIBRARY ${PLATFORM_LINK_LIBRARY} legacy_stdio_definitions)
  endif()

  file(COPY ${PROJECT_SOURCE_DIR}/deps/bin/ DESTINATION ${EXECUTABLE_OUTPUT_PATH}/Debug)
  file(COPY ${PROJECT_SOURCE_DIR}/deps/bin/ DESTINATION ${EXECUTABLE_OUTPUT_PATH}/Release)
endif()

add_subdirectory(fountain)
add_subdirectory(tools)
add_subdirectory(tests)
