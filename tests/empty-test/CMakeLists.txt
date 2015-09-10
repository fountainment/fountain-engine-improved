set(TEST_SRC
	main.cpp
)

if(WINDOWS)
	set(TEST_RES test.rc)
endif()

add_executable(empty-test ${TEST_SRC} ${TEST_RES})
target_link_libraries(empty-test ${FOUNTAIN_LINK_LIBRARY} ${PLATFORM_LINK_LIBRARY})
