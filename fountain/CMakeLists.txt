include(base/CMakeLists.txt)
include(math/CMakeLists.txt)
include(interface/CMakeLists.txt)
include(control/CMakeLists.txt)
include(time/CMakeLists.txt)
include(render/CMakeLists.txt)
include(font/CMakeLists.txt)
include(scene/CMakeLists.txt)
include(audio/CMakeLists.txt)
include(anime/CMakeLists.txt)
include(physics/CMakeLists.txt)
include(sprite/CMakeLists.txt)
include(ui/CMakeLists.txt)
include(network/CMakeLists.txt)
include(util/CMakeLists.txt)

set(FOUNTAIN_SRC fountain.cpp
	${FOUNTAIN_BASE_SRC}
	${FOUNTAIN_MATH_SRC}
	${FOUNTAIN_INTERFACE_SRC}
	${FOUNTAIN_CONTROL_SRC}
	${FOUNTAIN_TIME_SRC}
	${FOUNTAIN_RENDER_SRC}
	${FOUNTAIN_FONT_SRC}
	${FOUNTAIN_SCENE_SRC}
	${FOUNTAIN_AUDIO_SRC}
	${FOUNTAIN_ANIME_SRC}
	${FOUNTAIN_SPRITE_SRC}
	${FOUNTAIN_PHYSICS_SRC}
	${FOUNTAIN_UI_SRC}
	${FOUNTAIN_NETWORK_SRC}
	${FOUNTAIN_UTIL_SRC}
)

add_library(fountain STATIC ${FOUNTAIN_SRC})
