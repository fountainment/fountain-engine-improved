set(TEST_SRC
	main.cpp
	EditorScene.cpp
)

if(WINDOWS)
	set(TEST_RES test.rc)
endif()

add_executable(GeometryEditor ${TEST_SRC} ${TEST_RES})
target_link_libraries(GeometryEditor ${FOUNTAIN_LINK_LIBRARY} ${PLATFORM_LINK_LIBRARY})

if(WINDOWS)
	file(COPY ${PROJECT_SOURCE_DIR}/res DESTINATION ./)
endif()