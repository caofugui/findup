cmake_minimum_required(VERSION 3.16)

project(Findup VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt6 COMPONENTS SvgWidgets REQUIRED)

add_executable(findup
    DirListWidget.cpp
    DirOperationWidget.cpp
    FileNameWidget.cpp
    IconButton.cpp
    ListItem.cpp
    main.cpp
    MainWindow.cpp
    ResultItem.cpp
    ResultList.cpp
    ResultWidget.cpp
    SearchThread.cpp
    findup.qrc
)

target_link_libraries(findup PRIVATE Qt6::Widgets)
target_link_libraries(findup PRIVATE Qt6::SvgWidgets)