cmake_minimum_required(VERSION 2.8)

project(TP2_Annotations)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES Annotations_fr_FR.ts Annotations_en_US.ts)
qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

add_executable(${PROJECT_NAME}
    main.cpp
    mainwindow.cpp
    mainwindow.h
    annotationwidget.cpp
    annotationwidget.h

    ${QM_FILES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)

