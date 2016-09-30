set(TEST_SRC
	main.cc
	editor.cc
)

if(WINDOWS)
	set(TEST_RES test.rc)
endif()

add_executable(collision_editor ${TEST_SRC} ${TEST_RES})
target_link_libraries(collision_editor ${FOUNTAIN_LINK_LIBRARY} ${PLATFORM_LINK_LIBRARY})

if(WINDOWS)
	file(COPY ${PROJECT_SOURCE_DIR}/res DESTINATION ./)
endif()
