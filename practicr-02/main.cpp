#include <iostream>
#include <locale.h>
#include <vector>
#include <string>

using namespace std;



// Функция подсчета мощности суммы множеств по правилу суммы
// Пользователь вводит мощности отдельных множеств, а функция выводит мощность суммы
void sum() {
	cout << "Введите мощности множеств через пробел: ";
	string first, sizes;
	cin >> first;
	getline(cin, sizes);
	sizes = first + sizes;
	long long size = 0, ans = 0;
	for (char c : sizes) {
		if (c == ' ') {
			ans += size;
			size = 0;
		}
		else if (c >= '0' && c <= '9') {
			size = size * 10 + c - '0';
		}
		else {
			cout << "Ошибка во вводе" << endl;
			return;
		}
	}
	ans += size;
	cout << "Мощность суммы множеств: " << ans << endl;
}


// Функция подсчета мощности произведения множеств по правилу произведения
// Пользователь вводит мощности отдельных множеств, а функция выводит мощность произведения
void mul() {
	cout << "Введите мощности множеств через пробел: ";
	string first, sizes;
	cin >> first;
	getline(cin, sizes);
	sizes = first + sizes;
	long long size = 0, ans = 1;
	for (char c : sizes) {
		if (c == ' ') {
			ans *= size;
			size = 0;
		}
		else if (c >= '0' && c <= '9') {
			size = size * 10 + c - '0';
		}
		else {
			cout << "Ошибка во вводе" << endl;
			return;
		}
	}
	ans *= size;
	cout << "Мощность произведения множеств: " << ans << endl;
}


// Функция подсчета количесвта размещений с повторениями длины k из элементов множества мощностью n
// Пользователь вводит мощность множества n и длину размещений k, а функция выводит количество размещений
void acc_with() {
	int n, k;
	cout << "Введите мощность множества (число предметов, n): ";
	cin >> n;
	cout << "Введите длину размещения (k): ";
	cin >> k;
	long long ans = 1;
	for (int i = 0; i < k; ++i) {
		ans *= n;
	}
	cout << "Количество размещений с повторениями: " << ans << endl;
}


// Функция подсчета количесвта размещений без повторений длины k из элементов множества мощностью n
// Пользователь вводит мощность множества n и длину размещений k, а функция выводит количество размещений
void acc_without() {
	int n, k;
	cout << "Введите мощность множества (число предметов, n): ";
	cin >> n;
	cout << "Введите длину размещения (k): ";
	cin >> k;
	long long ans = 1;
	for (int i = n - k + 1; i <= n; ++i) {
		ans *= i;
	}
	cout << "Количество размещений без повторений: " << ans << endl;
}


// Функция подсчета количесвта сочетаний с повторениями длины k из элементов множества мощностью n
// Пользователь вводит мощность множества n и длину сочетаний k, а функция выводит количество сочетаний
void comb_with() {
	int n, k;
	cout << "Введите мощность множества (число предметов, n): ";
	cin >> n;
	cout << "Введите длину расстановки (k): ";
	cin >> k;
	long long ans = 1;
	for (int i = max(k, n - 1) + 1; i <= n + k - 1; ++i) {
		ans *= i;
	}
	for (int i = 1; i <= min(k, n - 1); ++i) {
		ans /= i;
	}
	cout << "Количество сочетаний с повторениями: " << ans << endl;
}


// Функция подсчета количесвта сочетаний без повторений длины k из элементов множества мощностью n
// Пользователь вводит мощность множества n и длину сочетаний k, а функция выводит количество сочетаний
void comb_without() {
	int n, k;
	cout << "Введите мощность множества (число предметов, n): ";
	cin >> n;
	cout << "Введите длину расстановки (k): ";
	cin >> k;
	long long ans = 1;
	for (int i = max(k, n - k) + 1; i <= n; ++i) {
		ans *= i;
	}
	for (int i = 1; i <= min(k, n - k); ++i) {
		ans /= i;
	}
	cout << "Количество сочетаний без повторений: " << ans << endl;
}


// Функция подсчета количесвта перестановок с повторениями, состоящих из k типов элементов численностью n_i
// Пользователь вводит количество типов k и число элементов каждого типа n_i, а функция выводит количество перестановок
void perm_with() {
	int k;
	cout << "Введите количество типов (k): ";
	cin >> k;
	cout << "Введите число элементов каждого типа через пробел: ";
	vector <int> ns(k);
	int n = 0;
	for (int i = 0; i < k; ++i) {
		cin >> ns[i];
		n += ns[i];
	}
	long long ans = 1;
	for (int i = 1; i <= n; ++i) {
		ans *= i;
	}
	for (int i = 0; i < k; ++i) {
		for (int j = 1; j <= ns[i]; ++j) {
			ans /= j;
		}
	}
	cout << "Количество перестановок с повторениями: " << ans << endl;
}


// Функция подсчета количесвта перестановок без повторений длины n
// Пользователь вводит длину перестановки n, а функция выводит количество перестановок
void perm_without() {
	int n;
	cout << "Введите длину перестановки (n): ";
	cin >> n;
	long long ans = 1;
	for (int i = 1; i <= n; ++i) {
		ans *= i;
	}
	cout << "Количество перестановок без повторений: " << ans << endl;
}


// Функция взаимодействия с пользователем
// Функция предлагает 8 вариантов рассчета различных комбинаторных схем, пользователь выбирает один из них
// После этого работа передается функции для выбранной комбинаторной схемы
// По окончании выполнения пользователь может выбрать еще одну комбинаторную схему или завершить работу
bool choose() {
	cout << "Выберите комбинаторную схему:" << endl;
	cout << "    1 - правило суммы" << endl;
	cout << "    2 - правило произведения" << endl;
	cout << "    3 - размещения с повторениями" << endl;
	cout << "    4 - размещения без повторениий" << endl;
	cout << "    5 - сочетания с повторениями" << endl;
	cout << "    6 - сочетания без повторениий" << endl;
	cout << "    7 - перестановки с повторениями" << endl;
	cout << "    8 - перестановки без повторениий" << endl;
	cout << "Комбинаторная схема: ";
	bool fl = true;
	while (fl) {
		int input;
		cin >> input;
		cout << "---------------------------------------------------------------------" << endl;
		switch (input) {
		case 1: sum(); fl = false; break;
		case 2: mul(); fl = false; break;
		case 3: acc_with(); fl = false; break;
		case 4: acc_without(); fl = false; break;
		case 5: comb_with(); fl = false; break;
		case 6: comb_without(); fl = false; break;
		case 7: perm_with(); fl = false; break;
		case 8: perm_without(); fl = false; break;
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


int main() {
	setlocale(LC_ALL, "Russian"); 
	bool go = choose();
	while (go) {
		go = choose();
	}
	return 0;
}
