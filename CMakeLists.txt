cmake_minimum_required(VERSION 3.14)
project(
    SnakeGame
    VERSION 1.0.0
    DESCRIPTION "Skillbox Snake Game"
    LANGUAGES CXX
)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем AUTOMOC для сборки сигналов, слотов и таймеров Qt
set(CMAKE_AUTOMOC ON)

# Список всех исходных файлов игры в папке src
set(sources
    src/main.cpp
    src/snake.h
    src/snake.cpp
)

# Поиск графической библиотеки Qt5Widgets
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Создание исполняемого файла
add_executable(snake_game ${sources})

# Подключение папки src для заголовочных файлов
target_include_directories(snake_game PRIVATE src)

# Линковка с Qt5::Widgets
target_link_libraries(snake_game PRIVATE Qt5::Widgets)
