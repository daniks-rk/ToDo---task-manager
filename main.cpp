#include <iostream>
#include <vector>
#include <string>
#include "task.h"
#include "task_manager.h"

using namespace std;

void displayMenu() {
    cout << "\n=== Менеджер задач ===\n";
    cout << "1. Добавить задачу\n";
    cout << "2. Показать все задачи\n";
    cout << "3. Отметить задачу как выполненную\n";
    cout << "4. Удалить задачу\n";
    cout << "5. Сохранить задачи в файл\n";
    cout << "6. Загрузить задачи из файла\n";
    cout << "0. Выход\n";
    cout << "Выберите действие: ";
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    TaskManager manager;
    int choice;
    
    // Загрузка задач при старте
    manager.loadFromFile("tasks.txt");
    
    do {
        displayMenu();
        cin >> choice;
        cin.ignore(); // Очистка буфера
        
        switch(choice) {
            case 1: {
                string description;
                cout << "Введите описание задачи: ";
                getline(cin, description);
                manager.addTask(description);
                cout << "Задача добавлена!\n";
                break;
            }
            case 2:
                manager.displayAllTasks();
                break;
            case 3: {
                int id;
                cout << "Введите ID задачи для отметки как выполненной: ";
                cin >> id;
                manager.markTaskCompleted(id);
                break;
            }
            case 4: {
                int id;
                cout << "Введите ID задачи для удаления: ";
                cin >> id;
                manager.removeTask(id);
                break;
            }
            case 5:
                manager.saveToFile("tasks.txt");
                cout << "Задачи сохранены в файл!\n";
                break;
            case 6:
                manager.loadFromFile("tasks.txt");
                cout << "Задачи загружены из файла!\n";
                break;
            case 0:
                // Автосохранение при выходе
                manager.saveToFile("tasks.txt");
                cout << "Задачи сохранены. Выход...\n";
                break;
            default:
                cout << "Неверный выбор!\n";
        }
    } while(choice != 0);
    
    return 0;
}