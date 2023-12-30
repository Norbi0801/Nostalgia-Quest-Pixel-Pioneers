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
        src/Core/Event/Event.cpp
        src/Core/State/State.cpp
        src/Core/Window/Window.cpp
        src/Core/Texture/Texture.cpp
        src/Core/SpriteSheet/SpriteSheet.cpp
        src/Core/Tile/Tile.cpp
        src/Core/Map/Map.cpp
        src/Utilities/MessageHandler.hpp
        src/Core/System/System.hpp
        src/Utilities/Observer.hpp
        src/Utilities/EventQueue.hpp
        src/Utilities/Communicator.hpp
        src/Utilities/Bitmask.hpp
        src/Systems/Base/SystemBase.hpp
        src/Systems/Base/SystemBase.cpp
        src/Components/Position/Position.hpp
        src/Core/System/System.cpp
        src/Components/Drawable/Drawable.hpp
        src/Components/SpriteSheet/SpriteSheet.hpp
        src/Components/SpriteSheet/SpriteSheet.hpp
        src/Systems/Renderer/Renderer.hpp
        src/Systems/Renderer/Renderer.cpp
        src/Systems/Renderer/Renderer.cpp
        src/Game/Game.hpp
        src/Game/Game.cpp
        src/Core/Entity/Entity.cpp
        src/States/State_Game/State_Game.hpp
        src/States/State_Game/State_Game.cpp
        src/States/State_Game/State_Game.cpp
        src/States/State_Intro/State_Intro.hpp
        src/States/State_Intro/State_Intro.cpp
        src/States/State_MainMenu/State_MainMenu.cpp
        src/States/State_Paused/State_Paused.cpp
        src/Components/Movable/Movable.hpp
        src/Utilities/Direction.hpp
        src/Components/Movable/Movable.cpp
        src/Utilities/Axis.hpp
        src/Systems/Movement/Movement.hpp
        src/Systems/Movement/Movement.cpp
        src/Components/State/State.hpp
        src/Systems/State/State.cpp
        src/Systems/Control/Control.cpp
        src/Systems/SheetAnimation/SheetAnimation.cpp
        src/Systems/SheetAnimation/SheetAnimation.hpp
        src/Components/Collidable/Collidable.hpp)

    target_link_libraries(PixelPioneers PRIVATE sfml-graphics fmt::fmt)
    target_compile_features(PixelPioneers PRIVATE cxx_std_20)
    target_include_directories(PixelPioneers PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

if(WIN32)
    add_custom_command(
            TARGET PixelPioneers
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:PixelPioneers>
            VERBATIM)
endif()

install(TARGETS PixelPioneers)
