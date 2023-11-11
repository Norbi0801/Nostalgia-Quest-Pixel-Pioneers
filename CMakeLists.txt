############################################################
##
## SFML
## https://github.com/SFML/cmake-sfml-project/blob/master/CMakeLists.txt
##
############################################################

cmake_minimum_required(VERSION 3.26)
project(ProjektPJC LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(ProjektPJC src/main.cpp)
target_link_libraries(ProjektPJC PRIVATE sfml-graphics)
target_compile_features(ProjektPJC PRIVATE cxx_std_20)

if(WIN32)
    add_custom_command(
            TARGET ProjektPJC
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:ProjektPJC>
            VERBATIM)
endif()

install(TARGETS ProjektPJC)