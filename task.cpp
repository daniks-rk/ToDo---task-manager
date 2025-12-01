#include "task.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <algorithm>

// Инициализация статической переменной
int Task::nextId = 1;

Task::Task(const std::string& desc) 
    : id(nextId++), description(desc), completed(false), 
      creationTime(std::chrono::system_clock::now()) {}

int Task::getId() const {
    return id;
}

std::string Task::getDescription() const {
    return description;
}

bool Task::isCompleted() const {
    return completed;
}

void Task::setDescription(const std::string& desc) {
    description = desc;
}

void Task::setCompleted(bool status) {
    completed = status;
}

std::string Task::getCreationTime() const {
    auto time = std::chrono::system_clock::to_time_t(creationTime);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&time));
    return std::string(buffer);
}

void Task::display() const {
    std::cout << "[" << id << "] ";
    if (completed) {
        std::cout << "[✓] ";
    } else {
        std::cout << "[ ] ";
    }
    std::cout << description;
    std::cout << " (Создано: " << getCreationTime() << ")";
}

// 🔧 НОВОЕ: реализация публичных статических методов
void Task::updateNextId(int value) {
    nextId = std::max(nextId, value);
}

int Task::getCurrentNextId() {
    return nextId;
}