cmake_minimum_required(VERSION 3.11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 11)

project(FayEngineProj VERSION 0.9 DESCRIPTION "Game Engine lib")

# just glob the include files...
file(GLOB FE_HEADER ${CMAKE_SOURCE_DIR}/include/*.h*)
file(GLOB FE_SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*/*.cpp)

add_library(FayEngine STATIC
    ${FE_SOURCES}
    ${FE_HEADER}
)

set_target_properties(FayEngine PROPERTIES
	VERSION ${PROJECT_VERSION}
)

target_include_directories(FayEngine PUBLIC
	$<INSTALL_INTERFACE:include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# sdl for target
find_package(SDL2 REQUIRED)
find_package(SDL2_net REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(sdl2_mixer REQUIRED)
find_package(sdl2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_NET_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
include_directories(${SDL2_MIXER_INCLUDE_DIR})
include_directories(${SDL2_TTF_INCLUDE_DIR})

add_library(SDL2 SHARED IMPORTED)
add_library(SDL2_net SHARED IMPORTED)
add_library(SDL2_ttf SHARED IMPORTED)
add_library(SDL2_mixer SHARED IMPORTED)
add_library(SDL2_image SHARED IMPORTED)

set_property(TARGET SDL2 PROPERTY IMPORTED_LOCATION ${SDL2_LIBRARY})
set_property(TARGET SDL2_net PROPERTY IMPORTED_LOCATION ${SDL2_NET_LIBRARY})
set_property(TARGET SDL2_ttf PROPERTY IMPORTED_LOCATION ${SDL2_TTF_LIBRARY})
set_property(TARGET SDL2_mixer PROPERTY IMPORTED_LOCATION ${SDL2_MIXER_LIBRARY})
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

add_test(FayEngine testlib)

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION include/FayEngine
    FILES_MATCHING PATTERN "*.h*"
)

install(TARGETS FayEngine
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)
