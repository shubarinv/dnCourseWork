cmake_minimum_required(VERSION 3.15)
project(dnCourseWork)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/ ${CMAKE_MODULE_PATH})
find_package(SDL2 REQUIRED)
find_package(SDL2_TTF REQUIRED)
find_package(SDL2_image REQUIRED)
find_library(SDL2TTF_LIBRARIES SDL_ttf)

include_directories(${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_MIXER_INCLUDE_DIR}
        ${SDL2TFF_LIBRARY}
        )

# Workaround for the non-working REQUIRED flag
if (NOT SDL2_FOUND)
    message(FATAL_ERROR "SDL not found!")
endif (NOT SDL2_FOUND)


link_libraries(
        ${SDL2_LIBRARY}
        ${SDL2TTF_LIBRARY}
        ${SDL2_IMAGE_LIBRARY}
        SDLmain # Sadly not included in SDL_LIBRARY variable
)
set(CMAKE_CXX_STANDARD 17)
#add_executable(progOnHLang ex1main.cpp)
add_executable(dnCourseWork driver.cpp game/game.hpp game/UI/ui_base.hpp game/UI/ui_manager.hpp game/UI/ui_main_menu.hpp game/UI/ui_button.hpp game/input_manager.hpp game/windows_manager.hpp game/line.hpp game/graph.hpp game/graph_builder.hpp Lib/tinyexpr.c Lib/tinyexpr.h game/UI/ui_text_field.hpp game/UI/ui_functions.hpp)
include_directories(${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_MIXER_INCLUDE_DIR}
        ${SDL2TFF_LIBRARY}
        )
target_link_libraries(dnCourseWork ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARY}
        ${SDL2_MIXER_LIBRARY}
        ${SDL2TFF_LIBRARY}
        )