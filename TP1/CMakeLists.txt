cmake_minimum_required(VERSION 2.8)
project(LOG6302)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
set(SOURCE_FILES src/main.cpp src/Visitor.cpp src/Visitor.h)

#FIND_PACKAGE(Clang REQUIRED)

set(LLVM_PATH /home/local/cours/INF6603/clang+llvm-3.3-x86_64-fedora18 CACHE PATH "Path to LLVM installation")
include_directories(${LLVM_PATH}/include)
link_directories(${LLVM_PATH}/lib)
add_definitions(-DLLVM_PATH=\"${LLVM_PATH}\")

add_definitions(-D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS -D_GLIBCXX_USE_CXX11_ABI=0)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(
        ${PROJECT_NAME}

        clangTooling
        clangFrontend
        clangFrontendTool
        clangSerialization
        clangParse
        clangSema
        clangAnalysis
        clangDriver
        clangAST
        clangASTMatchers
        clangEdit
        clangLex
        clangBasic
        LLVMSupport
        LLVMMC
        LLVMMCParser
        LLVMBitReader
        pthread
        dl
)