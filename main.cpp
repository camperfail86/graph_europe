#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include <algorithm>
#include <unordered_set>

std::unordered_map<std::string, std::vector<std::string> > europeGraph;

void bronKerbosch(std::unordered_set<std::string>& R, std::unordered_set<std::string>& P, std::unordered_set<std::string>& X,
                  std::vector<std::string>& clique, std::vector<std::vector<std::string> >& allCliques) {
    if (P.empty() && X.empty()) {
        allCliques.push_back(std::vector<std::string>(R.begin(), R.end()));
        return;
    }

    std::unordered_set<std::string> P_copy = P;
    for (const std::string& v : P_copy) {
        std::unordered_set<std::string> newP, newX;
        for (const std::string& w : P) {
            if (std::find(europeGraph[v].begin(), europeGraph[v].end(), w) != europeGraph[v].end()) {
                newP.insert(w);
            }
        }
        for (const std::string& w : X) {
            if (std::find(europeGraph[v].begin(), europeGraph[v].end(), w) != europeGraph[v].end()) {
                newX.insert(w);
            }
        }

        R.insert(v);
        P.erase(v);
        X.insert(v);

        bronKerbosch(R, newP, newX, clique, allCliques);

        R.erase(v);
        P.insert(v);
        X.erase(v);
    }
}

void addEdge(std::unordered_map<std::string, std::vector<std::string> >& graph,
             const std::string& country1, const std::string& country2) {
    graph[country1].push_back(country2);
    graph[country2].push_back(country1);
}

int bfs(const std::string& start) {
    std::unordered_map<std::string, int> distances;
    std::queue<std::string> q;

    q.push(start);
    distances[start] = 0;

    int max_distance = 0;

    while (!q.empty()) {
        std::string current = q.front();
        q.pop();

        for (const std::string& neighbor : europeGraph.at(current)) {
            if (distances.find(neighbor) == distances.end()) {
                distances[neighbor] = distances[current] + 1;
                q.push(neighbor);
                if (distances[neighbor] > max_distance) {
                    max_distance = distances[neighbor];
                }
            }
        }
    }

    return max_distance;
}

int main() {
    addEdge(europeGraph, "Албания", "Македония");
    addEdge(europeGraph, "Албания", "Сербия");
    addEdge(europeGraph, "Албания", "Черногория");
    addEdge(europeGraph, "Албания", "Греция");

    addEdge(europeGraph, "Андорра", "Испания");
    addEdge(europeGraph, "Андорра", "Франция");

    addEdge(europeGraph, "Австрия", "Словения");
    addEdge(europeGraph, "Австрия", "Чехия");
    addEdge(europeGraph, "Австрия", "Словакия");
    addEdge(europeGraph, "Австрия", "Германия");
    addEdge(europeGraph, "Австрия", "Венгрия");
    addEdge(europeGraph, "Австрия", "Швейцария");
    addEdge(europeGraph, "Австрия", "Германия");
    addEdge(europeGraph, "Австрия", "Лихтенштейн"); // 3

    addEdge(europeGraph, "Беларусь", "Украина");
    addEdge(europeGraph, "Беларусь", "Россия");
    addEdge(europeGraph, "Беларусь", "Латвия");
    addEdge(europeGraph, "Беларусь", "Литва");
    addEdge(europeGraph, "Беларусь", "Польша");

    addEdge(europeGraph, "Бельгия", "Люксембург");
    addEdge(europeGraph, "Бельгия", "Франция");
    addEdge(europeGraph, "Бельгия", "Нидерланды"); // 5

    addEdge(europeGraph, "Босния и Герцеговина", "Хорватия");
    addEdge(europeGraph, "Босния и Герцеговина", "Сербия");
    addEdge(europeGraph, "Босния и Герцеговина", "Черногория");

    addEdge(europeGraph, "Болгария", "Румыния");
    addEdge(europeGraph, "Болгария", "Сербия");
    addEdge(europeGraph, "Болгария", "Македония");
    addEdge(europeGraph, "Болгария", "Греция");
    addEdge(europeGraph, "Болгария", "Турция"); // 7

    addEdge(europeGraph, "Хорватия", "Босния и Герцеговина"); 
    addEdge(europeGraph, "Хорватия", "Черногория");
    addEdge(europeGraph, "Хорватия", "Сербия");
    addEdge(europeGraph, "Хорватия", "Венгрия");
    addEdge(europeGraph, "Хорватия", "Словения");

    // Кипр

    addEdge(europeGraph, "Чехия", "Словакия");
    addEdge(europeGraph, "Чехия", "Польша");
    addEdge(europeGraph, "Чехия", "Австрия");
    addEdge(europeGraph, "Чехия", "Германия"); // 10

    addEdge(europeGraph, "Дания", "Германия");

    addEdge(europeGraph, "Эстония", "Россия");
    addEdge(europeGraph, "Эстония", "Латвия");

    addEdge(europeGraph, "Финляндия", "Россия");
    addEdge(europeGraph, "Финляндия", "Швеция");
    addEdge(europeGraph, "Финляндия", "Норвегия");

    addEdge(europeGraph, "Франция", "Бельгия");
    addEdge(europeGraph, "Франция", "Германия");
    addEdge(europeGraph, "Франция", "Люксембург");
    addEdge(europeGraph, "Франция", "Швейцария");
    addEdge(europeGraph, "Франция", "Италия");
    addEdge(europeGraph, "Франция", "Андорра");
    addEdge(europeGraph, "Франция", "Испания");
    addEdge(europeGraph, "Франция", "Монако");

    addEdge(europeGraph, "Германия", "Дания");
    addEdge(europeGraph, "Германия", "Польша");
    addEdge(europeGraph, "Германия", "Чехия");
    addEdge(europeGraph, "Германия", "Австрия");
    addEdge(europeGraph, "Германия", "Люксембург");
    addEdge(europeGraph, "Германия", "Швейцария");
    addEdge(europeGraph, "Германия", "Франция");
    addEdge(europeGraph, "Германия", "Бельгия");
    addEdge(europeGraph, "Германия", "Нидерланды"); // 15

    addEdge(europeGraph, "Греция", "Македония"); 
    addEdge(europeGraph, "Греция", "Албания"); 
    addEdge(europeGraph, "Греция", "Турция"); 
    addEdge(europeGraph, "Греция", "Болгария"); 

    addEdge(europeGraph, "Венгрия", "Словения");
    addEdge(europeGraph, "Венгрия", "Словакия");
    addEdge(europeGraph, "Венгрия", "Украина");
    addEdge(europeGraph, "Венгрия", "Румыния");
    addEdge(europeGraph, "Венгрия", "Сербия");
    addEdge(europeGraph, "Венгрия", "Хорватия");
    addEdge(europeGraph, "Венгрия", "Австрия");

    // Исландия

    // addEdge(europeGraph, "Ирландия", "Великобритания");

    addEdge(europeGraph, "Италия", "Сан-Марино");
    addEdge(europeGraph, "Италия", "Ватикан");
    addEdge(europeGraph, "Италия", "Австрия");
    addEdge(europeGraph, "Италия", "Словения");
    addEdge(europeGraph, "Италия", "Швейцария");
    addEdge(europeGraph, "Италия", "Франция"); // 20

    addEdge(europeGraph, "Латвия", "Россия");
    addEdge(europeGraph, "Латвия", "Эстония");
    addEdge(europeGraph, "Латвия", "Белорусь");
    addEdge(europeGraph, "Латвия", "Литва");

    addEdge(europeGraph, "Лихтенштейн", "Австрия");
    addEdge(europeGraph, "Лихтенштейн", "Швейцария");

    addEdge(europeGraph, "Литва", "Латвия");
    addEdge(europeGraph, "Литва", "Польша");
    addEdge(europeGraph, "Литва", "Россия");
    addEdge(europeGraph, "Литва", "Белорусь");

    addEdge(europeGraph, "Люксембург", "Германия");
    addEdge(europeGraph, "Люксембург", "Бельгия");
    addEdge(europeGraph, "Люксембург", "Франция");

    // Мальта

    addEdge(europeGraph, "Молдова", "Украина");
    addEdge(europeGraph, "Молдова", "Румыния");

    addEdge(europeGraph, "Монако", "Франция");

    addEdge(europeGraph, "Черногория", "Хорватия");
    addEdge(europeGraph, "Черногория", "Босния и Герцеговина");
    addEdge(europeGraph, "Черногория", "Сербия");
    addEdge(europeGraph, "Черногория", "Албания"); // 28

    addEdge(europeGraph, "Нидерланды", "Германия");
    addEdge(europeGraph, "Нидерланды", "Бельгия");

    addEdge(europeGraph, "Македония", "Болгария");
    addEdge(europeGraph, "Македония", "Греция");
    addEdge(europeGraph, "Македония", "Албания");
    addEdge(europeGraph, "Македония", "Сербия");

    addEdge(europeGraph, "Норвегия", "Швеция");
    addEdge(europeGraph, "Норвегия", "Финляндия");
    addEdge(europeGraph, "Норвегия", "Россия");

    addEdge(europeGraph, "Польша", "Германия");
    addEdge(europeGraph, "Польша", "Чехия");
    addEdge(europeGraph, "Польша", "Белорусь");
    addEdge(europeGraph, "Польша", "Словакия");
    addEdge(europeGraph, "Польша", "Литва");
    addEdge(europeGraph, "Польша", "Россия");
    addEdge(europeGraph, "Польша", "Украина");

    addEdge(europeGraph, "Португалия", "Испания");

    addEdge(europeGraph, "Румыния", "Украина");
    addEdge(europeGraph, "Румыния", "Молдова");
    addEdge(europeGraph, "Румыния", "Болгария");
    addEdge(europeGraph, "Румыния", "Сербия");
    addEdge(europeGraph, "Румыния", "Венгрия"); // 34

    addEdge(europeGraph, "Россия", "Украина");
    addEdge(europeGraph, "Россия", "Белорусь");
    addEdge(europeGraph, "Россия", "Литва");
    addEdge(europeGraph, "Россия", "Латвия");
    addEdge(europeGraph, "Россия", "Эстония");
    addEdge(europeGraph, "Россия", "Норвегия");
    addEdge(europeGraph, "Россия", "Финляндия");
    addEdge(europeGraph, "Россия", "Польша");

    addEdge(europeGraph, "Сан-Марино", "Италия");

    addEdge(europeGraph, "Сербия", "Румыния");
    addEdge(europeGraph, "Сербия", "Болгария");
    addEdge(europeGraph, "Сербия", "Македония");
    addEdge(europeGraph, "Сербия", "Албания");
    addEdge(europeGraph, "Сербия", "Черногория");
    addEdge(europeGraph, "Сербия", "Босния и Герцеговина");
    addEdge(europeGraph, "Сербия", "Хорватия");
    addEdge(europeGraph, "Сербия", "Венгрия");

    addEdge(europeGraph, "Словакия", "Венгрия");
    addEdge(europeGraph, "Словакия", "Австрия");
    addEdge(europeGraph, "Словакия", "Чехия");
    addEdge(europeGraph, "Словакия", "Польша");
    addEdge(europeGraph, "Словакия", "Украина");

    addEdge(europeGraph, "Словения", "Италия");
    addEdge(europeGraph, "Словения", "Австрия");
    addEdge(europeGraph, "Словения", "Хорватия");
    addEdge(europeGraph, "Словения", "Венгрия"); // 39

    addEdge(europeGraph, "Испания", "Андорра");
    addEdge(europeGraph, "Испания", "Португалия");
    addEdge(europeGraph, "Испания", "Франция");

    addEdge(europeGraph, "Швеция", "Финляндия");
    addEdge(europeGraph, "Швеция", "Норвегия");

    addEdge(europeGraph, "Швейцария", "Германия");
    addEdge(europeGraph, "Швейцария", "Франция");
    addEdge(europeGraph, "Швейцария", "Италия");
    addEdge(europeGraph, "Швейцария", "Австрия");
    addEdge(europeGraph, "Швейцария", "Лихтенштейн"); // 42


    addEdge(europeGraph, "Турция", "Болгария");
    addEdge(europeGraph, "Турция", "Греция");

    addEdge(europeGraph, "Украина", "Молдова");
    addEdge(europeGraph, "Украина", "Румыния");
    addEdge(europeGraph, "Украина", "Венгрия");
    addEdge(europeGraph, "Украина", "Словакия");
    addEdge(europeGraph, "Украина", "Белорусь");
    addEdge(europeGraph, "Украина", "Польша");
    addEdge(europeGraph, "Украина", "Россия");

    // addEdge(europeGraph, "Великобритания", "Ирландия");

    addEdge(europeGraph, "Ватикан", "Италия"); // 46

    std::unordered_map<std::string, int> eccentricities;

    for (const auto& pair : europeGraph) {
        const std::string& country = pair.first;
        eccentricities[country] = bfs(country);
    }

    int rad = 10000;
    std::string rad_str;
    int diam = 0;
    std::string diam_str;
    for (const auto& pair : eccentricities) {
        if (pair.second <= rad) {
            rad = pair.second;
            rad_str = pair.first;
        }
        if (pair.second >= diam) {
            diam = pair.second;
            diam_str = pair.first;
        }
    }

    std::cout << "Радиус: " << rad << " " << rad_str << std::endl;
    std::cout << "Диаметр: " << diam << " " << diam_str << std::endl;

        std::unordered_set<std::string> R, P, X;
    for (const auto& pair : europeGraph) {
        P.insert(pair.first);
    }

    std::vector<std::string> clique;
    std::vector<std::vector<std::string> > allCliques;
    bronKerbosch(R, P, X, clique, allCliques);

    std::vector<std::string> maxClique;
    for (const auto& clique : allCliques) {
        if (clique.size() > maxClique.size()) {
            maxClique = clique;
        }
    }

    std::cout << "Максимальная клика: ";
    for (const std::string& country : maxClique) {
        std::cout << country << " ";
    }
    std::cout << std::endl;

    return 0;
}

