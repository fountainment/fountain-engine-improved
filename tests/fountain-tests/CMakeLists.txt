set(TEST_SRC
	main.cpp
	Charactor.cpp
	TestApplication.cpp
	TestScene.cpp
)

if(WINDOWS)
	set(TEST_RES test.rc)
endif()

add_executable(fountain-tests ${TEST_SRC} ${TEST_RES})
target_link_libraries(fountain-tests ${FOUNTAIN_LINK_LIBRARY} ${PLATFORM_LINK_LIBRARY})

if(WINDOWS)
	file(COPY ${PROJECT_SOURCE_DIR}/res DESTINATION ./)
endif()