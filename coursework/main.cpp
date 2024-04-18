#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <locale.h>

using namespace std;

const int number_towns = 25;
const int true_length = 1711;
vector <vector <int> > graph(number_towns, vector <int>(number_towns));

// считывание графа
void ReadGraph() {
	ifstream fin;
	fin.open("dists.txt");
	for (int town_i = 0; town_i < number_towns; ++town_i) {
		for (int town_j = 0; town_j < number_towns; ++town_j) {
			fin >> graph[town_i][town_j];
		}
	}
	fin.close();
}

// подсчет длины пути
int PathLength(vector <int>& path) {
	int length = graph[path.back()][path.front()];
	for (int i = 1; i < number_towns; ++i) {
		length += graph[path[i - 1]][path[i]];
	}
	return length;
}

// вывод пути
void PrintPath(vector <int>& path) {
	cout << "Путь: ";
	for (int town : path) {
		cout << town + 1 << ' ';
	}
	cout << endl;
	int length = PathLength(path);
	cout << "Длина пути: " << length << endl;
	cout << "Лямбда: " << 1.0 * length / true_length - 1 << endl;
	cout << "---------------------------------------------------------------------" << endl;
}

// метод ближайшего соседа
vector <int> NearestNeighbour() {
	vector <int> optimal_path;
	int optimal_length = 1000000;
	vector <int> used(number_towns, 0);
	for (int start = 0; start < number_towns; ++start) {
		vector <int> path = { start };
		for (int town = 0; town < number_towns; ++town) {
			used[town] = 1 ? town == start : 0;
		}
		while (path.size() < number_towns) {
			int next = -1;
			int next_dist = 1000000;
			for (int town = 0; town < number_towns; ++town) {
				if (!used[town] && graph[path.back()][town] < next_dist) {
					next = town;
					next_dist = graph[path.back()][town];
				}
			}
			used[next] = 1;
			path.push_back(next);
		}
		if (PathLength(path) < optimal_length) {
			optimal_path = path;
			optimal_length = PathLength(path);
		}
	}
	return optimal_path;
}

// метод минимального ребра
vector <int> MinimalEdge() {
	struct edge {
		int length;
		int town_i;
		int town_j;

		edge(int l, int i, int j){
			length = l;
			town_i = i;
			town_j = j;
		}

		bool operator< (const edge& r) {
			return length < r.length;
		}
	};

	vector <edge> edges;
	for (int town_i = 0; town_i < number_towns; ++town_i) {
		for (int town_j = 0; town_j != town_i && town_j < number_towns; ++town_j) {
			if (town_i != town_j) {
				edges.emplace_back(graph[town_i][town_j], town_i, town_j);
			}
		}
	}
	sort(edges.begin(), edges.end());
	vector <int> component(number_towns);
	for (int town = 0; town < number_towns; ++town) {
		component[town] = town;
	}
	int l = 0;
	vector <int> neighbours(number_towns, 0);
	vector <edge> edges_in_path;
	for (edge e : edges) {
		if (component[e.town_i] != component[e.town_j] && neighbours[e.town_i] < 2 && neighbours[e.town_j] < 2) {
			neighbours[e.town_i]++;
			neighbours[e.town_j]++;
			int comp_j = component[e.town_j];
			for (int town = 0; town < number_towns; ++town) {
				if (component[town] == comp_j) {
					component[town] = component[e.town_i];
				}
			}
			edges_in_path.push_back(e);
		}
	}
	int start = -1, end = -1;
	for (int town = 0; town < number_towns; ++town) {
		if (neighbours[town] == 1) {
			if (start == -1) {
				start = town;
			}
			else {
				end = town;
			}
		}
	}
	vector <int> path{ start };
	while (start != end) {
		for (edge &e : edges_in_path) {
			if (e.town_i == start) {
				path.push_back(e.town_j);
				start = e.town_j;
				e = edge(-1, -1, -1);
				break;
			}
			if (e.town_j == start) {
				path.push_back(e.town_i);
				start = e.town_i;
				e = edge(-1, -1, -1);
				break;
			}
		}
	}
	return path;
}

// перестановка соседей
vector <int> SwapNeighbours(vector <int> path) {
	bool was_swap = true;
	while (was_swap) {
		was_swap = false;
		for (int i = 0; i < number_towns; ++i) {
			if (graph[path[i]][path[(i + 1) % number_towns]] + graph[path[(i + 2) % number_towns]][path[(i + 3) % number_towns]] >
				graph[path[i]][path[(i + 2) % number_towns]] + graph[path[(i + 1) % number_towns]][path[(i + 3) % number_towns]]) {
				swap(path[(i + 1) % number_towns], path[(i + 2) % number_towns]);
				was_swap = true;
			}
		}
	}
	return path;
}

// перестановка пар
vector <int> SwapPairs(vector <int> path) {
	bool was_swap = true;
	while (was_swap) {
		was_swap = false;
		for (int i = 0; i < number_towns; ++i) {
			for (int j = i + 2; (j + 2) % number_towns != i; ++j) {
				if (graph[path[i]][path[(i + 1) % number_towns]] + graph[path[j % number_towns]][path[(j + 1) % number_towns]] >
					graph[path[i]][path[j % number_towns]] + graph[path[(i + 1) % number_towns]][path[(j + 1) % number_towns]]) {
					if (j % number_towns > (i + 1) % number_towns) {
						reverse(path.begin() + (i + 1) % number_towns, path.begin() + j % number_towns + 1);
					}
					else {
						reverse(path.begin() + (j + 1) % number_towns, path.begin() + i % number_towns + 1);
					}
					was_swap = true;
				}
			}
		}
	}
	return path;
}

// перестановка соседей и пар
vector <int> SwapNeighboursAndPairs(vector <int> path) {
	return SwapPairs(SwapNeighbours(path));
}

int main() {
	setlocale(LC_ALL, "Russian");
	ReadGraph();
	vector <int> path;

	path = NearestNeighbour();
	cout << "Метод ближайшего соседа" << endl;
	PrintPath(path);

	path = SwapNeighbours(NearestNeighbour());
	cout << "Метод ближайшего соседа с перестановкой соседей" << endl;
	PrintPath(path);

	path = SwapPairs(NearestNeighbour());
	cout << "Метод ближайшего соседа с перестановкой пар" << endl;
	PrintPath(path);

	path = SwapNeighboursAndPairs(NearestNeighbour());
	cout << "Метод ближайшего соседа с перестановкой соседей и пар" << endl;
	PrintPath(path);

	path = MinimalEdge();
	cout << "Метод минимального ребра" << endl;
	PrintPath(path);

	path = SwapNeighbours(MinimalEdge());
	cout << "Метод минимального ребра с перестановкой соседей" << endl;
	PrintPath(path);

	path = SwapPairs(MinimalEdge());
	cout << "Метод минимального ребра с перестановкой пар" << endl;
	PrintPath(path);

	path = SwapNeighboursAndPairs(MinimalEdge());
	cout << "Метод минимального ребра с перестановкой соседей и пар" << endl;
	PrintPath(path);
}