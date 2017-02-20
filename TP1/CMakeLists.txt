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
    src/NamespaceNode.h src/NamespaceNode.cpp
    src/VarNode.h src/VarNode.cpp
    src/AttributeNode.h src/AttributeNode.cpp
    src/ProgramNode.h src/ProgramNode.cpp
    src/ABSASTVisitor.h
    src/MetricASTVisitor.h src/MetricASTVisitor.cpp
    src/MetaTree.h src/MetaTree.cpp
    src/PrettyPrintASTVisitor.h src/PrettyPrintASTVisitor.cpp
    src/UMLClass.h src/UMLClass.cpp
    src/UMLMethod.h src/UMLMethod.cpp
    src/UMLAttribute.h src/UMLAttribute.cpp
    src/UMLBuilder.h src/UMLBuilder.cpp
    src/UMLASTVisitor.h src/UMLASTVisitor.cpp
    src/ABSUMLRelation.h src/ABSUMLRelation.cpp
    src/CompositionRel.h src/CompositionRel.cpp
    src/InheritanceRel.h src/InheritanceRel.cpp
    src/InfoType.h src/InfoType.cpp
    )

#FIND_PACKAGE(Clang REQUIRED)

set(LLVM_PATH /home/filou/Documents/Hiver2017/LOG6302/LOG6302/clang+llvm-3.3-amd64-Ubuntu-12.04.2/ CACHE PATH "Path to LLVM installation")
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
