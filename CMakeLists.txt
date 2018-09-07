cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)

project(Mandelbrot)

if (MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(SFML_STATIC_LIBRARIES TRUE)
    set(SFGUI_STATIC_LIBRARIES TRUE)
    set(SFGUI_STATIC TRUE)
endif (MSVC)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Ofast")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/modules")

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
find_package(SFGUI REQUIRED)

include_directories(${SFGUI_INCLUDE_DIR})

set(
        SOURCES
        main.cpp
        Mandelbrot.cpp
        Application.cpp
)

add_executable(Mandelbrot ${SOURCES})
target_link_libraries(Mandelbrot sfml-graphics ${SFGUI_LIBRARY} ${SFGUI_DEPENDENCIES})

# Install executable
install(TARGETS Mandelbrot
        RUNTIME DESTINATION .)
