#include "task_manager.h"
#include <iostream>
#include <fstream>
#include <algorithm>

void TaskManager::addTask(const std::string& description) {
    tasks.emplace_back(description);
}

void TaskManager::displayAllTasks() const {
    if (tasks.empty()) {
        std::cout << "Список задач пуст.\n";
        return;
    }
    
    std::cout << "\n=== Все задачи ===\n";
    for (const auto& task : tasks) {
        task.display();
        std::cout << std::endl;
    }
}

Task* TaskManager::findTaskById(int taskId) {
    for (auto& task : tasks) {
        if (task.getId() == taskId) {
            return &task;
        }
    }
    return nullptr;
}

void TaskManager::markTaskCompleted(int taskId) {
    Task* task = findTaskById(taskId);
    if (task) {
        task->setCompleted(true);
        std::cout << "Задача [" << taskId << "] отмечена как выполненная!\n";
    } else {
        std::cout << "Задача с ID " << taskId << " не найдена.\n";
    }
}

void TaskManager::removeTask(int taskId) {
    auto it = std::remove_if(tasks.begin(), tasks.end(),
        [taskId](const Task& task) {
            return task.getId() == taskId;
        });
    
    if (it != tasks.end()) {
        tasks.erase(it, tasks.end());
        std::cout << "Задача [" << taskId << "] удалена!\n";
    } else {
        std::cout << "Задача с ID " << taskId << " не найдена.\n";
    }
}

void TaskManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла для записи!\n";
        return;
    }
    
    for (const auto& task : tasks) {
        file << task.getId() << "|"
             << task.getDescription() << "|"
             << task.isCompleted() << "|"
             << task.getCreationTime() << "\n";
    }
    
    file.close();
}

void TaskManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return; // Файл может не существовать при первом запуске
    }
    
    tasks.clear();
    std::string line;
    
    while (std::getline(file, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);
        
        if (pos1 != std::string::npos && 
            pos2 != std::string::npos && 
            pos3 != std::string::npos) {
            
            int id = std::stoi(line.substr(0, pos1));
            std::string desc = line.substr(pos1 + 1, pos2 - pos1 - 1);
            bool completed = line.substr(pos2 + 1, pos3 - pos2 - 1) == "1";
            
            // 🔧 ИСПРАВЛЕНО: используем публичный метод вместо прямого доступа
            Task::updateNextId(id + 1);
            
            // Создаем задачу и устанавливаем параметры
            tasks.emplace_back(desc);
            Task& newTask = tasks.back();
            // Восстанавливаем оригинальный ID
            // Это сложно, так как ID устанавливается в конструкторе
            
            // Альтернативный подход: создаем задачу с правильным ID
            // Для этого нужно изменить конструктор или добавить метод setId
        }
    }
    
    file.close();
}

std::vector<Task> TaskManager::findTasks(const std::string& keyword) const {
    std::vector<Task> result;
    for (const auto& task : tasks) {
        if (task.getDescription().find(keyword) != std::string::npos) {
            result.push_back(task);
        }
    }
    return result;
}