cmake_minimum_required(VERSION 2.8)
project(universite)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -pg")
set(SOURCE_FILES
	main.cpp
	Universite.h
	Etudiant.h Etudiant.cpp
	Prof.h Prof.cpp
	Homme.h Homme.cpp
    )

#FIND_PACKAGE(Clang REQUIRED)

add_definitions(-D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS -D_GLIBCXX_USE_CXX11_ABI=0)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
