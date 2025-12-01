cmake_minimum_required(VERSION 3.10)
project(TodoManager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем исполняемый файл
add_executable(todo_manager 
    main.cpp 
    task.cpp 
    task_manager.cpp
)

# Устанавливаем имя выходного файла
set_target_properties(todo_manager PROPERTIES OUTPUT_NAME "todo")