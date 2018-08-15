cmake_minimum_required(VERSION 3.1)

set (CMAKE_CXX_STANDARD 11)

project(Mandelbrot)

if(MSVC)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(SFML_STATIC_LIBRARIES TRUE)
endif(MSVC)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

set(
	SOURCES
	main.cpp
	Mandelbrot.cpp
	Application.cpp
	Menu.cpp
	Bouton.cpp
)

add_executable(Mandelbrot ${SOURCES})
target_link_libraries(Mandelbrot sfml-graphics)

# Install executable
install(TARGETS Mandelbrot
		RUNTIME DESTINATION .)