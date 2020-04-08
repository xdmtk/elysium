cmake_minimum_required(VERSION 3.9)
project(Elysium)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(SOURCE_FILES
        chatwindow.cpp
        chatwindow.h
	connectionprogresswindow.cpp
	connectionprogresswindow.h
        commandmanager.cpp
        commandmanager.h
        loginwindow.cpp
        loginwindow.h
	portInfo.h
	../core/CoreSettings.cpp
	../core/CoreSettings.h
        main.cpp
        socketmanager.cpp
        socketmanager.h
	soundmanager.cpp
	soundmanager.h
        notificationmanager.cpp notificationmanager.h)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
#find_package(Qt5Quick REQUIRED)
#find_package(Qt5QuickWidgets REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5MultimediaWidgets REQUIRED)
set(CMAKE_AUTOUIC_SEARCH_PATHS .)

#core gui widgets multimedia multimediawidgets quick quickwidgets
add_executable(Elysium ${SOURCE_FILES})
target_link_libraries(Elysium Qt5::Widgets)
target_link_libraries(Elysium Qt5::Gui)
target_link_libraries(Elysium Qt5::Multimedia)
target_link_libraries(Elysium Qt5::MultimediaWidgets)
#target_link_libraries(Elysium Qt5::Quick)
target_link_libraries(Elysium Qt5::Core)
#target_link_libraries(Elysium Qt5::QuickWidgets)

