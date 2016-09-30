set(TEST_SRC
	main.cpp
	EditorScene.cpp
)

if(WINDOWS)
	set(TEST_RES test.rc)
endif()

add_executable(geometry_editor ${TEST_SRC} ${TEST_RES})
target_link_libraries(geometry_editor ${FOUNTAIN_LINK_LIBRARY} ${PLATFORM_LINK_LIBRARY})

if(WINDOWS)
	file(COPY ${PROJECT_SOURCE_DIR}/res DESTINATION ./)
endif()
