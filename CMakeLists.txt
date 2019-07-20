cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)

project(Mandelbrot)

if (MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(SFML_STATIC_LIBRARIES TRUE)
endif (MSVC)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Ofast")

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
find_package(Threads)

set(
        SOURCES
        main.cpp
        Mandelbrot.cpp
        Application.cpp
)

add_executable(Mandelbrot ${SOURCES})
target_link_libraries(Mandelbrot sfml-graphics ${CMAKE_THREAD_LIBS_INIT})

# Install executable
install(TARGETS Mandelbrot
        RUNTIME DESTINATION .)
