cmake_minimum_required(VERSION 3.9)

project(elysium-server)
set(CMAKE_CXX_STANDARD 14)

link_libraries(pthread)
add_executable(elysium-server main.cpp Server.cpp Server.h SignalManager.cpp SignalManager.h ConnectionManager.cpp
        ConnectionManager.h ClientConnection.cpp ClientConnection.h Logger.cpp Logger.h
        ../core/CoreSettings.cpp ../core/CoreSettings.h CommandManager.cpp CommandManager.h DatabaseManager.cpp DatabaseManager.h)
