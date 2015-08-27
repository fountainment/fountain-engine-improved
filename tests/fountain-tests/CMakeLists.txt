add_executable(fountain-tests main.cpp Charactor.cpp TestApplication.cpp TestScene.cpp)
target_link_libraries(fountain-tests ${FOUNTAIN_LINK_LIBRARY} ${PLATFORM_LINK_LIBRARY})
