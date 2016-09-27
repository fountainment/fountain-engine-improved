set(TOOL_SRC
	main.cc
	tool.cc
)

if(WINDOWS)
	set(TOOL_RES normaltool.rc)
endif()

add_executable(normal_tool ${TOOL_SRC} ${TOOL_RES})
target_link_libraries(normal_tool  ${FOUNTAIN_LINK_LIBRARY} ${PLATFORM_LINK_LIBRARY})

if(WINDOWS)
	file(COPY ${PROJECT_SOURCE_DIR}/res DESTINATION ./)
endif()
