#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <sstream>
#include <stack>

using namespace std;

// Estructura que representa un estado del juego de pancakes
struct Estado {
    vector<char> pancakes;
    int costo; // cantidad de volteos realizados
    vector<int> camino; // lista de los índices de los pancakes volteados

    Estado(vector<char> p, int c, vector<int> cam) {
        pancakes = p;
        costo = c;
        camino = cam;
    }
};

// Función que imprime el camino de volteos de pancakes para llegar a la solución
void imprimir_camino(vector<int> camino) {
    for (int i = 0; i < camino.size(); i++) {
        cout << camino[i] << " ";
    }
    cout << endl;
}

// Función que verifica si el estado actual es la solución (pancakes ordenados de forma ascendente)
bool es_solucion(vector<char> pancakes) {
    vector<char> pancakes_ordenados = pancakes;
    sort(pancakes_ordenados.begin(), pancakes_ordenados.end());
    return pancakes == pancakes_ordenados;
}

// Función que realiza el volteo de los pancakes
void voltear_pancakes(vector<char>& pancakes, int desde, int hasta) {
    while (desde < hasta) {
        char temp = pancakes[desde];
        pancakes[desde] = pancakes[hasta];
        pancakes[hasta] = temp;
        desde++;
        hasta--;
    }
}

// Función que imprime el arreglo de pancakes
void imprimir_pancakes(vector<char> pancakes) {
    for (int i = 0; i < pancakes.size(); i++) {
        cout << pancakes[i] << " ";
    }
    cout << endl;
}


// Función heurística para estimar la distancia a la solución
int heuristica(vector<char> pancakes) {
    int distancia = 0;
    for (int i = 0; i < pancakes.size(); i++) {
        if (pancakes[i] != i + '1') {
            distancia++;
        }
    }
    return distancia;
}


// Función que realiza la búsqueda en IDA
void busqueda_en_ida(vector<char>& pancakes) {
    int limite = heuristica(pancakes); // límite inicial de la búsqueda
    bool encontrado = false;

    while (!encontrado) {
        int nuevo_limite = INT_MAX; // límite para la siguiente iteración
        stack<Estado> pila;
        pila.push(Estado(pancakes, 0, vector<int>()));

        while (!pila.empty()) {
            Estado actual = pila.top();
            pila.pop();

            if (es_solucion(actual.pancakes)) {
                cout << "Voltear pancakes: ";
                imprimir_camino(actual.camino);
                cout << " "<< endl;
                cout << "Arreglo ordenado: ";
                imprimir_pancakes(actual.pancakes);
                cout << " "<< endl;
                cout << "Nodos visitados: " << actual.costo  << endl;
                encontrado = true;


                break;
            }

            if (actual.costo + heuristica(actual.pancakes) <= limite) {
                for (int i = 2; i <= actual.pancakes.size(); i++) {
                    vector<char> nuevos_pancakes = actual.pancakes;
                    voltear_pancakes(nuevos_pancakes, 0, i-1);

                    vector<int> nuevos_camino = actual.camino;
                    nuevos_camino.push_back(i-1);

                    pila.push(Estado(nuevos_pancakes, actual.costo+1, nuevos_camino));
                }
            } else {
                nuevo_limite = min(nuevo_limite, actual.costo + heuristica(actual.pancakes));
            }
        }

        limite = nuevo_limite;
    }
}


// Función principal
int main() {
    string entrada;
    vector<char> pancakes;

    cout << "Pancakes con busqueda en IDA";
    cout << " "<< endl;
    cout << "Ingrese los caracteres a ordenar(letras) Ejemplo( flrpmend ) caracteres: ";
    getline(cin, entrada);
    istringstream iss(entrada);

    char c;
    while (iss >> c) {
        pancakes.push_back(c);
    }

    cout << "Arreglo de pancakes: ";
    imprimir_pancakes(pancakes);

    busqueda_en_ida(pancakes);
    return 0;
}

