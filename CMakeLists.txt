cmake_minimum_required(VERSION 4.0)
project(MediaFileRenamer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

Include(FetchContent)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG        v1.16.0 # or a later release
)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(
        CLI11
        GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
        GIT_TAG        v2.5.0 # or a later release
)
FetchContent_MakeAvailable(CLI11)

add_executable(MediaFileRenamer main.cpp
        Model/model.cpp
        Model/model.h
        View/view.cpp
        View/view.h
        main.h
        View/media_file_renamer.ui
        Controller/controller.cpp
        Controller/controller.h
)

target_link_libraries(MediaFileRenamer
        Qt::Core
        Qt::Gui
        Qt::Widgets
        spdlog
        CLI11
)

target_include_directories(MediaFileRenamer PRIVATE include)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.11.0 # or a later release
)
FetchContent_MakeAvailable(Catch2)

add_executable(tests test.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)


if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
