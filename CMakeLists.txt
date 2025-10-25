cmake_minimum_required(VERSION 4.0)
project(MediaFileRenamer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(MediaFileRenamer main.cpp
        spdlog/async.cpp
        spdlog/bundled_fmtlib_format.cpp
        spdlog/cfg.cpp
        spdlog/color_sinks.cpp
        spdlog/file_sinks.cpp
        spdlog/spdlog.cpp
        spdlog/stdout_sinks.cpp
        Model/model.cpp
        Model/model.h
        View/view.cpp
        View/view.h
        main.h
        Controller/controller.cpp
        Controller/controller.h
        CLI11/App.hpp
        CLI11/Argv.hpp
        CLI11/CLI.hpp
        CLI11/Config.hpp
        CLI11/ConfigFwd.hpp
        CLI11/Encoding.hpp
        CLI11/Error.hpp
        CLI11/ExtraValidators.hpp
        CLI11/Formatter.hpp
        CLI11/FormatterFwd.hpp
        CLI11/Macros.hpp
        CLI11/Option.hpp
        CLI11/Split.hpp
        CLI11/StringTools.hpp
        CLI11/Timer.hpp
        CLI11/TypeTools.hpp
        CLI11/Validators.hpp
        CLI11/Version.hpp
)

target_link_libraries(MediaFileRenamer
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

target_compile_definitions(MediaFileRenamer PUBLIC SPDLOG_COMPILED_LIB)

Include(FetchContent)
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
