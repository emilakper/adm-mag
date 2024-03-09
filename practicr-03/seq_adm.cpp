#include <iostream>

class Sequence {
public:
    struct Node {
        int data;
        Node* next;
    };

    Node* first = nullptr;

    // Инициализация нового узла с заданным значением
    Node* InitNode(int value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = nullptr;
        return newNode;
    }

    // Добавление нового элемента в конец списка
    void AppendNode(int value) {
        Node* newNode = InitNode(value);
        if (first == nullptr) {
            first = newNode;
        } else {
            Node* current = first;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    // Вставка нового элемента на указанную позицию
    void InsertNode(int position, int value) {
        if (position < 0) {
            std::cout << "Position out of range" << std::endl;
            return;
        }
    
        Node* newNode = InitNode(value);
        if (position == 0) {
            newNode->next = first;
            first = newNode;
        } else {
            Node* current = first;
            for (int i = 0; i < position - 1 && current != nullptr; i++) {
                current = current->next;
            }
            if (current == nullptr) {
                std::cout << "Position out of range" << std::endl;
            } else {
                newNode->next = current->next;
                current->next = newNode;
            }
        }
    }

    // Сдвиг элементов списка на указанное количество шагов влево
    void ShiftNode(int steps) {
        if (first == nullptr || first->next == nullptr) {
            return;
        }

        Node* current = first;
        int count = 1;
        while (count < steps && current->next != nullptr) {
            current = current->next;
            count++;
        }

        Node* newLast = current;
        while (current->next != nullptr) {
            current = current->next;
        }

        current->next = first;
        first = newLast->next;
        newLast->next = nullptr;
    }

    // Удаление элемента по указанной позиции
    void DeleteNode(int k) {
        if (first == nullptr) {
            return;
        }
    
        if (k < 0) {
            std::cout << "Position out of range" << std::endl;
            return;
        }
    
        if (k == 0) {
            Node* temp = first;
            first = first->next;
            delete temp;
        } else {
            Node* prev = nullptr;
            Node* current = first;
            int i = 0;
            while (current != nullptr && i < k) {
                i++;
                prev = current;
                current = current->next;
            }
            if (current == nullptr) {
                std::cout << "Position out of range" << std::endl;
            } else {
                prev->next = current->next;
                delete current;
            }
        }
    }

    // Вывод списка на экран
    void PrintNodeList() {
        Node* p = first;
        while (p != nullptr) {
            std::cout << p->data << " ";
            p = p->next;
        }
    }
};

int main() {
    Sequence sequence;
    int mode = -1;
    while (mode != 0) {
        std::cout << "Choose mode (0 - Exit, 1 - Adjacency representation (not implemented yet), 2 - Linked representation): ";
        std::cin >> mode;
        if (mode == 2) {
            int action = -1;
            while (action != 0) {
                std::cout << "Choose action (0 - Back to mode selection, 1 - Append, 2 - Insert, 3 - Shift, 4 - Delete, 5 - Print): ";
                std::cin >> action;
                if (action == 1) {
                    int value;
                    std::cout << "Enter value to append: ";
                    std::cin >> value;
                    sequence.AppendNode(value);
                } else if (action == 2) {
                    int position, insertValue;
                    std::cout << "Enter position to insert: ";
                    std::cin >> position;
                    std::cout << "Enter value to insert: ";
                    std::cin >> insertValue;
                    sequence.InsertNode(position, insertValue);
                } else if (action == 3) {
                    int steps;
                    std::cout << "Enter number of steps to shift to the right: ";
                    std::cin >> steps;
                    sequence.ShiftNode(steps);
                } else if (action == 4) {
                    int deletePosition;
                    std::cout << "Enter position to delete: ";
                    std::cin >> deletePosition;
                    sequence.DeleteNode(deletePosition);
                } else if (action == 5) {
                    std::cout << "List: ";
                    sequence.PrintNodeList();
                    std::cout << std::endl;
                }
            }
        }
    }

    return 0;
}
