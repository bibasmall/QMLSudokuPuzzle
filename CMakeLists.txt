cmake_minimum_required(VERSION 3.16)

project(QMLSudokuPuzzle VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(appQMLSudokuPuzzle
    main.cpp
)

qt_add_qml_module(appQMLSudokuPuzzle
    URI QMLSudokuPuzzle
    VERSION 1.0
    QML_FILES Main.qml Cell.qml
    SOURCES sudoku.h sudoku.cpp  
)

set_target_properties(appQMLSudokuPuzzle PROPERTIES
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appQMLSudokuPuzzle
    PRIVATE Qt6::Quick
)

#include(GNUInstallDirs)
#install(TARGETS appQMLSudokuPuzzle
#    BUNDLE DESTINATION .
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#)
