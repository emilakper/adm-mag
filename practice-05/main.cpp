// БПМ-22-4 Акперов Эмиль, Гончаровский Максим, Максимов Иван
#include <iostream>
#include <locale.h>
#include <vector>
#include <string>

using namespace std;

// связное представление дерева
class TreeLink {
public:
    // структура для хранения вершины дерева
    struct Node {
        string data;
        vector <Node*> children;  
    };

    // освобождение памяти, используемой вершиной
    void ClearNode(Node* node) {
        for (Node* child : node->children) {
            ClearNode(child);
            delete child;
            child = nullptr;
        }
        node->children.clear();
    }

    // корень дерева
    Node* root = new Node;

    // деструктор класса
    ~TreeLink() {
        ClearNode(root);
    }

    // инициализация дерева
    TreeLink(string root_data) {
        root->data = root_data;
        root->children = vector <Node*> ();
    }

    // поиск вершины дерева
    Node* FindNode(string value, Node* node = nullptr) {
        if (node == nullptr) {
            node = root;
        }
        if (node->data == value) {
            return node;
        }
        for (Node* child : node->children) {
            Node* found = FindNode(value, child);
            if (found != nullptr) {
                return found;
            }
        }
        return nullptr;
    }

    // поиск родителя вершины дерева
    Node* FindParent(string value, Node* node = nullptr) {
        if (node == nullptr) {
            node = root;
        }
        for (Node* child : node->children) {
            if (child->data == value) {
                return node;
            }
            Node* found = FindParent(value, child);
            if (found != nullptr) {
                return found;
            }
        }
        return nullptr;
    }

    // создание новой вершины с заданным значением и предком
    void AddNode() {
        cout << "Введите вершину: " << endl;
        string value;
        cin >> value;
        cout << "Введите родителя: " << endl;
        string parent_data;
        cin >> parent_data;
        Node* parent = FindNode(parent_data);
        Node* same = FindNode(value);
        if (parent == nullptr) {
            cout << "Родитель не найден" << endl;
            return;
        }
        if (same != nullptr) {
            cout << "В дереве уже существует вершина с таким значением" << endl;
            return;
        }
        Node* newNode = new Node;
        newNode->data = value;
        newNode->children = vector <Node*> ();
        parent->children.push_back(newNode);
        return;
    }

    // удаление вершины дерева
    void DeleteNode() {
        cout << "Введите вершину: " << endl;
        string value;
        cin >> value;
        Node* node = FindNode(value);
        if (node == nullptr) {
            cout << "Вершина не найдена" << endl;
            return;
        }
        if (node == root) {
            cout << "Нельзя удалять корень" << endl;
            return;
        }
        Node* parent = FindParent(node->data);
        ClearNode(node);
        for (auto child_it = parent->children.begin(); child_it != parent->children.end(); child_it++) {
            if ((*child_it)->data == value) {
                parent->children.erase(child_it);
                break;
            }
        }
    }

    // вывод информации о вершине дерева
    void GetInfo() {
        cout << "Введите вершину: " << endl;
        string value;
        cin >> value;
        Node* node = FindNode(value);
        if (node == nullptr) {
            cout << "Вершина не найдена" << endl;
            return;
        }
        if (node == root) {
            cout << "Корень дерева" << endl;
        }
        else {
            Node* parent = FindParent(node->data);
            cout << "Родитель вершины: " << parent->data << endl;
        }
        cout << "Дети вершины:";
        for (Node* child : node->children) {
            cout << " " << child->data;
        }
        cout << endl;
    }

    int prev_level = 0;

    // вывод вершины на экран
    void PrintNode(Node* node, int level) {
        prev_level = level;
        for (int i = 0; i < level; ++i) {
            if (i == level - 1) {
                cout << "|--";
            }
            else {
                cout << "|  ";
            }
        }
        cout << node->data;
        cout << endl;
        for (Node* child : node->children) {
            PrintNode(child, level + 1);
            if (level < prev_level - 1 && child != *(--(node->children.end()))) {
                for (int i = 0; i <= level; ++i) {
                    cout << "|  ";
                }
                cout << endl;
            }
        }
    }

    // вывод дерева на экран
    void PrintTree() {
        cout << "Дерево:" << endl;
        PrintNode(root, 0);
    }
};



class TreeAdj {
public:
    // ширина дерева (максимальное число детей у вершины)
    int tree_width;
    // высота дерева (число уровней в дереве)
    int tree_depth;
    // массив для хранения дерева
    vector <string> data;

    // инициализация дерева
    TreeAdj(int width, int depth, string root_data) {
        tree_width = width;
        tree_depth = depth;
        int size = 0;
        int width_pow = 1;
        for (int i = 0; i < depth; ++i) {
            size += width_pow;
            width_pow *= width;
        }
        data = vector <string>(size, "");
        data[0] = root_data;
    }

    // освобождение памяти, используемой вершиной
    void ClearNode(int node) {
        if (node >= data.size()) {
            return;
        }
        for (int child = node * tree_width + 1; child <= (node + 1) * tree_width; child++) {
            if (child >= data.size()) {
                break;
            }
            if (data[child] != "") {
                ClearNode(child);
            }
        }
        data[node] = "";
    }

    // поиск вершины дерева
    int FindNode(string value, int node = 0) {
        if (node >= data.size()) {
            return -1;
        }
        if (data[node] == value) {
            return node;
        }
        for (int child = node * tree_width + 1; child <= (node + 1) * tree_width; child++) {
            int found = FindNode(value, child);
            if (found != -1) {
                return found;
            }
        }
        return -1;
    }

    // поиск родителя вершины дерева
    int FindParent(string value) {
        int node = FindNode(value);
        if (node == 0) {
            return -1;
        }
        return (node - 1) / tree_width;
    }

    // создание новой вершины с заданным значением и предком
    void AddNode() {
        cout << "Введите вершину: " << endl;
        string value;
        cin >> value;
        cout << "Введите родителя: " << endl;
        string parent_data;
        cin >> parent_data;
        int parent = FindNode(parent_data);
        int same = FindNode(value);
        if (parent == -1) {
            cout << "Родитель не найден" << endl;
            return;
        }
        if (same != -1) {
            cout << "В дереве уже существует вершина с таким значением" << endl;
            return;
        }
        if (parent * tree_width + 1 >= data.size()) {
            cout << "Достигнут лимит глубины дерева (" << tree_depth << ")" << endl;
            return;
        }
        for (int child = parent * tree_width + 1; child <= (parent + 1) * tree_width; child++) {
            if (data[child] == "") {
                data[child] = value;
                return;
            }
        }
        cout << "У данного родителя достигнут лимит детей (" << tree_width << ")" << endl;
    }

    // удаление вершины дерева
    void DeleteNode() {
        cout << "Введите вершину: " << endl;
        string value;
        cin >> value;
        int node = FindNode(value);
        if (node == -1) {
            cout << "Вершина не найдена" << endl;
            return;
        }
        if (node == 0) {
            cout << "Нельзя удалять корень" << endl;
            return;
        }
        ClearNode(node);

    }

    // вывод информации о вершине дерева
    void GetInfo() {
        cout << "Введите вершину: " << endl;
        string value;
        cin >> value;
        int node = FindNode(value);
        if (node == -1) {
            cout << "Вершина не найдена" << endl;
            return;
        }
        if (node == 0) {
            cout << "Корень дерева" << endl;
        }
        else {
            int parent = FindParent(value);
            cout << "Родитель вершины: " << data[parent] << endl;
        }
        cout << "Дети вершины:";
        for (int child = node * tree_width + 1; child <= (node + 1) * tree_width; child++) {
            if (child >= data.size()) {
                break;
            }
            if (data[child] != "") {
                cout << " " << data[child];
            }
        }
        cout << endl;
    }

    int prev_level = 0;

    // вывод вершины на экран
    void PrintNode(int node, int level) {
        if (node >= data.size()) {
            return;
        }
        prev_level = level;
        for (int i = 0; i < level; ++i) {
            if (i == level - 1) {
                cout << "|--";
            }
            else {
                cout << "|  ";
            }
        }
        cout << data[node];
        cout << endl;
        for (int child = node * tree_width + 1; child <= (node + 1) * tree_width; child++) {
            if (child >= data.size()) {
                return;
            }
            if (data[child] != "") {
                PrintNode(child, level + 1);
                bool is_last_child = true;
                for (int next = child + 1; next <= (node + 1) * tree_width; next++) {
                    if (data[next] != "") {
                        is_last_child = false;
                        break;
                    }
                }
                if (level < prev_level - 1 && child != 0) {
                    for (int i = 0; i <= level; ++i) {
                        cout << "|  ";
                    }
                    cout << endl;
                }
            }
        }
    }

    // вывод дерева на экран
    void PrintTree() {
        cout << "Дерево:" << endl;
        PrintNode(0, 0);
    }
};



// Функция работы со связными деревьями
// В начале работы пользователь вводит корень дерева
// После этого на выбор предлагаются различные способы для дальнейшей работы с деревом:
//   добавлять или удалять вершину, вывести информацию о вершине или все дерево целиком
// Пользователь может вводить операции несколько раз
void WorkWithLinkTree() {
    cout << "Введите корень дерева: " << endl;
    string root;
    cin >> root;
    TreeLink tree(root);
    cout << "Выберите операцию на связном дереве:" << endl;
    cout << "    1 - добавить вершину в дерево" << endl;
    cout << "    2 - удалить вершину из дерева" << endl;
    cout << "    3 - узнать информацио о вершине в дереве" << endl;
    cout << "    4 - вывести дерево" << endl;
    cout << "    5 - завершить работу с деревом" << endl;
    bool fl = true;
    while (fl) {
        cout << "Операция: ";
        int input;
        cin >> input;
        switch (input) {
        case 1: cout << endl; tree.AddNode(); cout << endl; break;
        case 2: cout << endl; tree.DeleteNode(); cout << endl; break;
        case 3: cout << endl; tree.GetInfo(); cout << endl; break;
        case 4: cout << endl; tree.PrintTree(); cout << endl; break;
        case 5: fl = false; break;
        default: cout << "Введите допустимый вариант" << endl;
        }
    }
}

// Функция работы со смежными деревьями
// В начале работы пользователь вводит ширину, высоту и корень дерева
// После этого на выбор предлагаются различные способы для дальнейшей работы с деревом:
//   добавлять или удалять вершину, вывести информацию о вершине или все дерево целиком
// Пользователь может вводить операции несколько раз
void WorkWithAdjTree() {
    cout << "Введите ширину дерева (максимальное число детей у вершины, целое число): " << endl;
    int width;
    cin >> width;
    cout << "Введите высоту дерева (количество уровней, целое число): " << endl;
    int depth;
    cin >> depth;
    cout << "Введите корень дерева: " << endl;
    string root;
    cin >> root;
    TreeAdj tree(width, depth, root);
    cout << "Выберите операцию на смежном дереве:" << endl;
    cout << "    1 - добавить вершину в дерево" << endl;
    cout << "    2 - удалить вершину из дерева" << endl;
    cout << "    3 - узнать информацио о вершине в дереве" << endl;
    cout << "    4 - вывести дерево" << endl;
    cout << "    5 - завершить работу с деревом" << endl;
    bool fl = true;
    while (fl) {
        cout << "Операция: ";
        int input;
        cin >> input;
        switch (input) {
        case 1: cout << endl; tree.AddNode(); cout << endl; break;
        case 2: cout << endl; tree.DeleteNode(); cout << endl; break;
        case 3: cout << endl; tree.GetInfo(); cout << endl; break;
        case 4: cout << endl; tree.PrintTree(); cout << endl; break;
        case 5: fl = false; break;
        default: cout << "Введите допустимый вариант" << endl;
        }
    }
}

// Функция взаимодействия с пользователем
// Функция предлагает 2 варианта работы с ралзичными представлениями деревьев, пользователь выбирает один из них
// После этого работа передается функции для выбранного представления дерева
// По окончании выполнения пользователь может выбрать новое представление дерева или завершить работу
bool choose() {
    cout << "Выберите представление дерева:" << endl;
    cout << "    1 - связное представление" << endl;
    cout << "    2 - смежное преставление" << endl;
    cout << "Представление дерева: ";
    bool fl = true;
    while (fl) {
        int input;
        cin >> input;
        cout << "---------------------------------------------------------------------" << endl;
        switch (input) {
        case 1: WorkWithLinkTree(); fl = false; break;
        case 2: WorkWithAdjTree(); fl = false; break;
        default: cout << "Введите допустимый вариант" << endl;
        }
    }
    cout << "---------------------------------------------------------------------" << endl;
    cout << "Выбрать заново?" << endl;
    cout << "    yes - да" << endl;
    cout << "    no - нет" << endl;
    string again;
    cin >> again;
    if (again == "yes") {
        return true;
    }
    return false;
}

//
int main() {
    setlocale(LC_ALL, "Russian");
    bool go = choose();
    while (go) {
        go = choose();
    }
    return 0;
}
