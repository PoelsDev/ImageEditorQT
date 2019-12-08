cmake_minimum_required(VERSION 3.8)
project(ImageEditor)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

#=====================================================
# TODO: Change directory QT for windows/mac/linux
# Uncomment correct directory, and comment other directories
#=====================================================

#=====================================================
#Linux (tested in classroom):
#=====================================================
#For other linux variants locate local installation directory Qt5.
#For example on ubuntu search for installation directory using
#>>dpkg --listfiles qtbase5-dev
#Then find path witch contains "lib" and "cmake" and "Qt5Core")
#=====================================================
set(Qt5Core_DIR "/home/thibaultpoels/Qt5.9.7/5.9.7/gcc_64/lib/cmake/Qt5Core")
set(Qt5Widgets_DIR "/home/thibaultpoels/Qt5.9.7/5.9.7/gcc_64/lib/cmake/Qt5Widgets")
set(Qt5Gui_DIR "/home/thibaultpoels/Qt5.9.7/5.9.7/gcc_64/lib/cmake/Qt5Gui")

#=====================================================
# Mac
#=====================================================
#set(Qt5Core_DIR "~/Qt/5.9.2/clang_64/lib/cmake/Qt5Core")
#set(Qt5Widgets_DIR "~/Qt/5.9.2/clang_64/lib/cmake/Qt5Widgets")
#set(Qt5Gui_DIR "~/Qt/5.9.2/clang_64/lib/cmake/Qt5Gui")

#=====================================================
# Windows
#=====================================================
#set(Qt5Core_DIR "C:\\Qt\\5.9.3\\mingw53_32\\lib\\cmake\\Qt5Core")
#set(Qt5Widgets_DIR "C:\\Qt\\5.9.3\\mingw53_32\\lib\\cmake\\Qt5Widgets")
#set(Qt5Gui_DIR "C:\\Qt\\5.9.3\\mingw53_32\\lib\\cmake\\Qt5Gui")

find_package( Qt5Core REQUIRED )
find_package( Qt5Widgets REQUIRED )
find_package( Qt5Gui REQUIRED )
set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.cpp MyMainWindow.cpp MyMainWindow.h)

#ImageEditor == ProjectName
add_executable(ImageEditor_base ${SOURCE_FILES})
qt5_use_modules( ImageEditor_base Core Widgets Gui )