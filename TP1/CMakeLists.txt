cmake_minimum_required(VERSION 2.8)
project(LOG6302)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -pg")
set(SOURCE_FILES
    src/main.cpp
    src/Visitor.h src/Visitor.cpp
    src/ABSNode.h src/ABSNode.cpp
    src/ASTTree.h src/ASTTree.cpp
    src/CondNode.h src/CondNode.cpp
    src/ClassNode.h src/ClassNode.cpp
    src/JumpNode.h src/JumpNode.cpp
    src/LoopNode.h src/LoopNode.cpp
    src/MethodNode.h src/MethodNode.cpp
    src/VarNode.h src/VarNode.cpp
    src/ProgramNode.h src/ProgramNode.cpp
    src/ABSASTVisitor.h
    src/MetricASTVisitor.h src/MetricASTVisitor.cpp
    )

#FIND_PACKAGE(Clang REQUIRED)

set(LLVM_PATH /home/filou/Documents/Hiver2017/LOG6302/LOG6302/clang+llvm-3.3-Ubuntu-13.04-x86_64-linux-gnu/clang+llvm-3.3-Ubuntu-13.04-x86_64-linux-gnu CACHE PATH "Path to LLVM installation")
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
