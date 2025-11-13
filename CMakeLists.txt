cmake_minimum_required(VERSION 3.29.6)
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

FetchContent_Declare(
        tinyxml2
        GIT_REPOSITORY https://github.com/leethomason/tinyxml2.git
        GIT_TAG        11.0.0
)
FetchContent_MakeAvailable(tinyxml2)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)


# Exiv2 has dependencies which make building complicated. We turn most of these off to get the basics working
set (EXIV2_BUILD_DOC OFF CACHE INTERNAL "Add 'doc' target to generate documentation")
set (EXIV2_ENABLE_INIH OFF CACHE INTERNAL "Use inih library")
set (EXIV2_ENABLE_PNG OFF CACHE INTERNAL "Build with PNG support (requires zlib)")
set (EXIV2_ENABLE_BROTLI OFF CACHE INTERNAL "Use Brotli for JPEG XL compressed boxes (BMFF)")
set (BUILD_SHARED_LIBS OFF CACHE INTERNAL "Build exiv2lib as a shared library")
SET (EXIV2_ENABLE_XMP OFF CACHE INTERNAL "Build with XMP metadata support")
FetchContent_Declare(
        exiv2
        GIT_REPOSITORY https://github.com/Exiv2/exiv2.git
        GIT_TAG        v0.28.7
)
FetchContent_MakeAvailable(exiv2)


add_executable(MediaFileRenamer main.cpp
        Model/model.cpp
        Model/model.h
        View/view.cpp
        View/view.h
        main.h
        View/media_file_renamer.ui
)

target_link_libraries(MediaFileRenamer
        Qt::Core
        Qt::Gui
        Qt::Widgets
        spdlog
        CLI11
        tinyxml2
        nlohmann_json::nlohmann_json
        exiv2lib
)

target_include_directories(MediaFileRenamer PRIVATE include)
target_include_directories(MediaFileRenamer PRIVATE cmake-build-debug)

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
