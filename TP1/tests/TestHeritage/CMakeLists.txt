cmake_minimum_required(VERSION 2.8)
project(testHeritageTableau)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -pg")
set(SOURCE_FILES
	Main.cpp
	Echiquier.h Echiquier.cpp
	Piece.h Piece.cpp
	Pion.h Pion.cpp
	Roi.h Roi.cpp
	Tour.h Tour.cpp
    )

#FIND_PACKAGE(Clang REQUIRED)

add_definitions(-v -D__STDC_LIMIT_MACROS
-D__STDC_CONSTANT_MACROS -D_GLIBCXX_USE_CXX11_ABI=0
-I/home/filou/Documents/Hiver2017/LOG6302/LOG6302/clang+llvm-3.3-amd64-Ubuntu-12.04.2/lib/clang/3.3/include/ -D__STRICT_ANSI__)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
