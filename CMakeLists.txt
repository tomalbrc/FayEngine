cmake_minimum_required(VERSION 3.11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 11)

project(FayEngineProj VERSION 0.9 DESCRIPTION "Game Engine lib")

add_library(FayEngine STATIC
	${CMAKE_SOURCE_DIR}/src/Types.cpp
	${CMAKE_SOURCE_DIR}/src/tinyxml2.cpp
	${CMAKE_SOURCE_DIR}/src/nodes/TiledMapNode.cpp
	${CMAKE_SOURCE_DIR}/src/nodes/Scene.cpp
	${CMAKE_SOURCE_DIR}/src/nodes/Sprite.cpp
	${CMAKE_SOURCE_DIR}/src/nodes/Node.cpp
	${CMAKE_SOURCE_DIR}/src/nodes/LabelNode.cpp
	${CMAKE_SOURCE_DIR}/src/nodes/ButtonNode.cpp
	${CMAKE_SOURCE_DIR}/src/Window.cpp
	${CMAKE_SOURCE_DIR}/src/DrawTexture.cpp
	${CMAKE_SOURCE_DIR}/src/Texture.cpp
	${CMAKE_SOURCE_DIR}/src/actions/RepeatAction.cpp
	${CMAKE_SOURCE_DIR}/src/actions/SpriteAnimationAction.cpp
	${CMAKE_SOURCE_DIR}/src/actions/MoveByAction.cpp
	${CMAKE_SOURCE_DIR}/src/actions/RotateByAction.cpp
	${CMAKE_SOURCE_DIR}/src/actions/CallbackAction.cpp
	${CMAKE_SOURCE_DIR}/src/actions/RemoveFromParent.cpp
	${CMAKE_SOURCE_DIR}/src/actions/JumpByAction.cpp
	${CMAKE_SOURCE_DIR}/src/actions/WaitAction.cpp
	${CMAKE_SOURCE_DIR}/src/actions/ScaleToAction.cpp
	${CMAKE_SOURCE_DIR}/src/actions/SequenceAction.cpp
	${CMAKE_SOURCE_DIR}/src/actions/RotateToAction.cpp
	${CMAKE_SOURCE_DIR}/src/actions/EasingFunctions.cpp
	${CMAKE_SOURCE_DIR}/src/actions/FadeAlphaToAction.cpp
	${CMAKE_SOURCE_DIR}/src/actions/Action.cpp
	${CMAKE_SOURCE_DIR}/src/tmxparser.cpp
	${CMAKE_SOURCE_DIR}/src/EngineHelper.cpp
)

# props for target, not project...
set_target_properties(FayEngine PROPERTIES
	VERSION ${PROJECT_VERSION}
)

# only for project, not installation
target_include_directories(FayEngine PUBLIC
	$<INSTALL_INTERFACE:include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# sdl for target
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(SDL2_net REQUIRED)
include_directories(${SDL2_NET_INCLUDE_DIR})

find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

find_package(sdl2_mixer REQUIRED)
include_directories(${SDL2_MIXER_INCLUDE_DIR})

find_package(sdl2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIR})

add_library(SDL2 SHARED IMPORTED)
set_property(TARGET SDL2 PROPERTY IMPORTED_LOCATION ${SDL2_LIBRARY})

add_library(SDL2_net SHARED IMPORTED)
set_property(TARGET SDL2_net PROPERTY IMPORTED_LOCATION ${SDL2_NET_LIBRARY})

add_library(SDL2_ttf SHARED IMPORTED)
set_property(TARGET SDL2_ttf PROPERTY IMPORTED_LOCATION ${SDL2_TTF_LIBRARY})

add_library(SDL2_mixer SHARED IMPORTED)
set_property(TARGET SDL2_mixer PROPERTY IMPORTED_LOCATION ${SDL2_MIXER_LIBRARY})

add_library(SDL2_image SHARED IMPORTED)
set_property(TARGET SDL2_image PROPERTY IMPORTED_LOCATION ${SDL2_IMAGE_LIBRARY})

add_executable(testlib
    tests/main.cpp
    tests/sprite.cpp
    tests/matrix.cpp
)
target_include_directories(testlib PRIVATE
	${CMAKE_INSTALL_PREFIX}/include
)
target_link_libraries(testlib FayEngine
	SDL2
	SDL2_image
	SDL2_net
	SDL2_ttf
	SDL2_mixer
)

add_test(testlib testlib)




# too cumbersome
# set_target_properties(FayEngine PROPERTIES PUBLIC_HEADER PATTERN "include/*.h*")
# This is easier.
# only installs headers
install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION include/FayEngine
    FILES_MATCHING PATTERN "*.h*"
)

# installs static/dynamic lib
install(TARGETS FayEngine
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)

