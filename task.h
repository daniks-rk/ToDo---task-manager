#ifndef TASK_H
#define TASK_H

#include <string>
#include <chrono>

class Task {
private:
    static int nextId; // Статическая переменная для автоматического ID
    int id;
    std::string description;
    bool completed;
    std::chrono::system_clock::time_point creationTime;
    
public:
    // Конструктор
    Task(const std::string& desc);
    
    // Геттеры
    int getId() const;
    std::string getDescription() const;
    bool isCompleted() const;
    std::string getCreationTime() const;
    
    // Сеттеры
    void setDescription(const std::string& desc);
    void setCompleted(bool status);
    
    // Метод для отображения задачи
    void display() const;
    
    // 🔧 НОВОЕ: публичный статический метод для доступа к nextId
    static void updateNextId(int value);
    
    // 🔧 НОВОЕ: получить текущее значение nextId
    static int getCurrentNextId();
};

#endif // TASK_H