// Максимов Иван, Акперов Эмиль, Гончаровский Максим   БПМ-22-4

#include <iostream>
#include <locale.h>
#include <vector>
#include <string>

using namespace std;

// инициализация
void Init(int &n, vector <int> &a) {
    cout << "Введите размер массива: ";
    cin >> n;
    a.resize(n);
    cout << "Введите элементы массива (целые числа): " << endl;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
}

// сортировка слиянием
vector <int> MergeSort(vector <int> a) {
    int n = a.size();
    if (a.size() == 1) {
        return a;
    }
    int m = n / 2;
    vector <int> l(m);
    vector <int> r(n - m);
    for (int i = 0; i < m; ++i) {
        l[i] = a[i];
    }
    for (int i = 0; i < n - m; ++i) {
        r[i] = a[i + m];
    }
    l = MergeSort(l);
    r = MergeSort(r);
    int i_l = 0, i_r = 0;
    while (i_l < m && i_r < n - m) {
        if (l[i_l] < r[i_r]) {
            a[i_l + i_r] = l[i_l];
            i_l++;
        }
        else {
            a[i_l + i_r] = r[i_r];
            i_r++;
        }
    }
    for (; i_l < m; ++i_l) {
        a[i_l + i_r] = l[i_l];
    }
    for (; i_r < n - m; ++i_r) {
        a[i_l + i_r] = r[i_r];
    }
    return a;
}

// вывод
void Print(int& n, vector <int>& a) {
    cout << "Отсортированный массив: " << endl;
    for (int i = 0; i < n; ++i) {
        cout << a[i] << ' ';
    }
    cout << endl;
}



// взаимодействие с пользователем
bool choose() {
    cout << "---------------------------------------------------------------------" << endl;
    int n;
    vector <int> a;
    Init(n, a);
    a = MergeSort(a);
    Print(n, a);
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

int main() {
    setlocale(LC_ALL, "Russian");
    bool go = choose();
    while (go) {
        go = choose();
    }
    return 0;
}
