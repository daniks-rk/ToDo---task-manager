#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <vector>
#include <string>
#include "task.h"

class TaskManager {
private:
    std::vector<Task> tasks;
    
public:
    // Основные операции с задачами
    void addTask(const std::string& description);
    void displayAllTasks() const;
    void markTaskCompleted(int taskId);
    void removeTask(int taskId);
    
    // Работа с файлами
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    
    // Поиск задач
    std::vector<Task> findTasks(const std::string& keyword) const;
    
private:
    Task* findTaskById(int taskId);
};

#endif // TASK_MANAGER_H