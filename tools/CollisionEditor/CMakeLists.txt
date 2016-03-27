set(TEST_SRC
	main.cc
	editor.cc
)

if(WINDOWS)
	set(TEST_RES test.rc)
endif()

add_executable(CollisionEditor ${TEST_SRC} ${TEST_RES})
target_link_libraries(CollisionEditor ${FOUNTAIN_LINK_LIBRARY} ${PLATFORM_LINK_LIBRARY})

if(WINDOWS)
	file(COPY ${PROJECT_SOURCE_DIR}/res DESTINATION ./)
endif()
