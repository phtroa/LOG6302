cmake_minimum_required(VERSION 2.8)
project(anticipeeWithAtt)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -pg")
set(SOURCE_FILES
	main.cpp
	dummy_Class.h
	test.h
    )

#FIND_PACKAGE(Clang REQUIRED)

add_definitions(-D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS
-D_GLIBCXX_USE_CXX11_ABI=0)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
