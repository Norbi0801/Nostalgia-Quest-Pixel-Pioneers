############################################################
##
## SFML
## https://github.com/SFML/cmake-sfml-project/blob/master/CMakeLists.txt
##
############################################################

cmake_minimum_required(VERSION 3.26)
project(PixelPioneers LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)

    FetchContent_Declare(fmt
            GIT_REPOSITORY https://github.com/fmtlib/fmt.git
            GIT_TAG 8.1.1)
    FetchContent_MakeAvailable(fmt)

    FetchContent_Declare(SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG 2.6.x)
    FetchContent_MakeAvailable(SFML)

add_executable(PixelPioneers src/main.cpp
        src/Core/Event/EventM.cpp
        src/Core/State/StateM.cpp
        src/Utilities/Utilities.hpp
        src/Core/Window/Window.cpp
        src/Core/Window/Window.hpp)

    target_link_libraries(PixelPioneers PRIVATE sfml-graphics fmt::fmt)
    target_compile_features(PixelPioneers PRIVATE cxx_std_20)

if(WIN32)
    add_custom_command(
            TARGET PixelPioneers
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:PixelPioneers>
            VERBATIM)
endif()

install(TARGETS PixelPioneers)
