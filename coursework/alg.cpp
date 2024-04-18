#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <locale.h>
#include <numeric>
#include <limits>

const int number_towns = 25;
const int true_length = 1711;
std::vector<std::vector<int>> graph(number_towns, std::vector<int>(number_towns));
const double alpha = 1.0; // влияние длины пути
const double beta = 3.0;  // влияние феромона
const double evaporation = 0.4; // коэффициент испарения
const double Q = 5.0; // константа для расчета феромона
const int number_ants = 100; // количество муравьев
const int max_iter = 50;   // количество итераций

std::vector<std::vector<double>> pheromone_map(number_towns, std::vector<double>(number_towns, 1.0)); // матрица феромонов

void ReadGraph() {
    std::ifstream fin;
    fin.open("dists.txt");
    for (int town_i = 0; town_i < number_towns; ++town_i) {
        for (int town_j = 0; town_j < number_towns; ++town_j) {
            fin >> graph[town_i][town_j];
        }
    }
    fin.close();
}

int PathLength(std::vector<int>& path) {
    int length = graph[path.back()][path.front()];
    for (int i = 1; i < number_towns; ++i) {
        length += graph[path[i - 1]][path[i]];
    }
    return length;
}

void UpdatePheromone(std::vector<std::vector<int>>& all_paths) {
    for (auto& row : pheromone_map) {
        for (auto& p : row) {
            p *= (1 - evaporation);
        }
    }

    for (auto& path : all_paths) {
        double contribution = Q / PathLength(path);
        for (int i = 0; i < path.size(); i++) {
            int from = i;
            int to = (i + 1) % path.size();
            pheromone_map[path[from]][path[to]] += contribution;
            pheromone_map[path[to]][path[from]] += contribution;
        }
    }
}

std::vector<int> AntAlgorithm() {
    std::vector<int> best_path;
    int shortest_path_length = std::numeric_limits<int>::max();
    srand(static_cast<unsigned int>(time(nullptr)));

    for (int iter = 0; iter < max_iter; ++iter) {
        std::vector<std::vector<int>> all_paths(number_ants);
        for (int ant_k = 0; ant_k < number_ants; ++ant_k) {
            std::vector<int> path(1, rand() % number_towns);
            std::vector<int> allowed_towns(number_towns);
            std::iota(allowed_towns.begin(), allowed_towns.end(), 0);
            allowed_towns.erase(find(allowed_towns.begin(), allowed_towns.end(), path[0]));

            while (path.size() < number_towns) {
                std::vector<double> probabilities;
                double sum_probabilities = 0.0;

                for (int& allowed_town : allowed_towns) {
                    double pheromone = pow(pheromone_map[path.back()][allowed_town], alpha);
                    double distance = pow(1.0 / graph[path.back()][allowed_town], beta);
                    double probability = pheromone * distance;
                    probabilities.push_back(probability);
                    sum_probabilities += probability;
                }

                double select_random = (double)rand() / RAND_MAX;
                double cumulative = 0.0;
                for (int i = 0; i < allowed_towns.size(); i++) {
                    cumulative += probabilities[i] / sum_probabilities;
                    if (select_random < cumulative) {
                        path.push_back(allowed_towns[i]);
                        allowed_towns.erase(allowed_towns.begin() + i);
                        break;
                    }
                }
            }

            int path_length = PathLength(path);
            if (path_length < shortest_path_length) {
                best_path = path;
                shortest_path_length = path_length;
            }
            all_paths[ant_k] = path;
        }
        UpdatePheromone(all_paths);
    }
    return best_path;
}

void PrintPath(std::vector<int>& path) {
    std::cout << "Путь: ";
    for (int town : path) {
        std::cout << town + 1 << ' ';
    }
    std::cout << std::endl;
    int length = PathLength(path);
    std::cout << "Длина пути: " << length << std::endl;
    std::cout << "Лямбда: " << 1.0 * length / true_length - 1 << std::endl;
    std::cout << "---------------------------------------------------------------------" << std::endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    ReadGraph();

    std::vector<int> path = AntAlgorithm();
    std::cout << "Муравьиный алгоритм" << std::endl;
    PrintPath(path);

    return 0;
}