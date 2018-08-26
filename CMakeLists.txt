cmake_minimum_required(VERSION 3.1)

set (CMAKE_CXX_STANDARD 11)

project(Mandelbrot)

if(MSVC)
include(c:/tools/vcpkg/scripts/buildsystems/vcpkg.cmake)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(SFML_STATIC_LIBRARIES TRUE)
include_directories(c:/tools/vcpkg/installed/x64-windows-static/include)
endif(MSVC)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

set(
	SOURCES
	main.cpp
	Mandelbrot.cpp
)

add_executable(Mandelbrot ${SOURCES})
target_link_libraries(Mandelbrot sfml-graphics)

if(MSVC)
target_link_libraries(Mandelbrot c:/tools/vcpkg/installed/x64-windows-static/lib/mpir.lib)
endif(MSVC)

# Install executable
install(TARGETS Mandelbrot
		RUNTIME DESTINATION .)
