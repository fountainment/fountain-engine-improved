set(TEST_SRC
	main.cpp
	TestApplication.cpp
	TestScene.cpp
)

if(WINDOWS)
	set(TEST_RES test.rc)
endif()

add_executable(toposort-test ${TEST_SRC} ${TEST_RES})
target_link_libraries(toposort-test ${FOUNTAIN_LINK_LIBRARY} ${PLATFORM_LINK_LIBRARY})

if(WINDOWS)
	file(COPY ${PROJECT_SOURCE_DIR}/res DESTINATION ./)
endif()
