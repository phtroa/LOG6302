cmake_minimum_required(VERSION 2.8)
project(inf1010)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -pg")
set(SOURCE_FILES
	Const.h
	Main.cpp
	Infirmier.h 	Infirmier.cpp
	Medecin.h	Medecin.cpp
	Personnel.h	Personnel.cpp
	Specialite.h	Specialite.cpp
    )

#FIND_PACKAGE(Clang REQUIRED)

add_definitions(-v -D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS -D_GLIBCXX_USE_CXX11_ABI=0 -I/home/filou/Documents/Hiver2017/LOG6302/LOG6302/clang+llvm-3.3-Ubuntu-13.04-x86_64-linux-gnu/clang+llvm-3.3-Ubuntu-13.04-x86_64-linux-gnu/lib/clang/3.3/include -D__STRICT_ANSI__)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
