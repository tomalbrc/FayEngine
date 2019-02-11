cmake_minimum_required(VERSION 3.9)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 14)

project(rawketProj VERSION 0.9 DESCRIPTION "Game Engine lib")

# just glob the include files...
file(GLOB RKT_HEADER ${CMAKE_SOURCE_DIR}/include/*.h*)
file(GLOB RKT_SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*/*.cpp)

add_library(rawket STATIC
    ${RKT_SOURCES}
    ${RKT_HEADER}
)

set_target_properties(rawket PROPERTIES
	VERSION ${PROJECT_VERSION}
)

# sdl for target
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(sdl2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
include_directories(${SDL2_TTF_INCLUDE_DIR})

add_library(SDL2 SHARED IMPORTED)
add_library(SDL2_ttf SHARED IMPORTED)
add_library(SDL2_image SHARED IMPORTED)

set_property(TARGET SDL2 PROPERTY IMPORTED_LOCATION ${SDL2_LIBRARY})
set_property(TARGET SDL2_ttf PROPERTY IMPORTED_LOCATION ${SDL2_TTF_LIBRARY})
set_property(TARGET SDL2_image PROPERTY IMPORTED_LOCATION ${SDL2_IMAGE_LIBRARY})

add_executable(testlib
    tests/main.cpp
    tests/sprite.cpp
    tests/matrix.cpp
)

include_directories(include)

target_link_libraries(testlib rawket
	SDL2
	SDL2_image
	SDL2_ttf
)

add_test(rawket testlib)

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION include/rawket
    FILES_MATCHING PATTERN "*.h*"
)

install(TARGETS rawket
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)
