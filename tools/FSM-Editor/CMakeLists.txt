set(TEST_SRC
	main.cpp
	ButtonArrow.cpp
	FSMEditorScene.cpp
)

if(WINDOWS)
	set(TEST_RES test.rc)
endif()

add_executable(FSM-Editor ${TEST_SRC} ${TEST_RES})
target_link_libraries(FSM-Editor ${FOUNTAIN_LINK_LIBRARY} ${PLATFORM_LINK_LIBRARY})

if(WINDOWS)
	file(COPY ${PROJECT_SOURCE_DIR}/res DESTINATION ./)
endif()
