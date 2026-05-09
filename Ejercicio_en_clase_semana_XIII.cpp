#include <iostream>
#include <algorithm>

using namespace std;

struct Student {
    int student_id;
    string full_name;
    string career;
    int semester;
    float gpa;
    int skill_score;
};

struct Nodo {
    Student data;
    Nodo* izquierda;
    Nodo* derecha;
    int altura;

    Nodo(Student s) {
        data = s;
        izquierda = nullptr;
        derecha = nullptr;
        altura = 1;
    }
};

int totalNodos = 0;

int obtenerAltura(Nodo* n) {
    return (n == nullptr) ? 0 : n->altura;
}

int obtenerBalance(Nodo* n) {
    return (n == nullptr) ? 0 :
           obtenerAltura(n->izquierda) - obtenerAltura(n->derecha);
}

bool menor(Student a, Student b) {

    if (a.skill_score == b.skill_score) {

        return a.student_id < b.student_id;
    }

    return a.skill_score < b.skill_score;
}

Nodo* rotarDerecha(Nodo* y) {

    Nodo* x = y->izquierda;
    Nodo* T2 = x->derecha;

    x->derecha = y;
    y->izquierda = T2;

    y->altura = max(obtenerAltura(y->izquierda),
                    obtenerAltura(y->derecha)) + 1;

    x->altura = max(obtenerAltura(x->izquierda),
                    obtenerAltura(x->derecha)) + 1;

    return x;
}

Nodo* rotarIzquierda(Nodo* x) {

    Nodo* y = x->derecha;
    Nodo* T2 = y->izquierda;

    y->izquierda = x;
    x->derecha = T2;

    x->altura = max(obtenerAltura(x->izquierda),
                    obtenerAltura(x->derecha)) + 1;

    y->altura = max(obtenerAltura(y->izquierda),
                    obtenerAltura(y->derecha)) + 1;

    return y;
}

Nodo* insertar(Nodo* nodo, Student s) {

    if (nodo == nullptr) {
        totalNodos++;
        return new Nodo(s);
    }

    if (menor(s, nodo->data)) {

        nodo->izquierda = insertar(nodo->izquierda, s);

    } else if (menor(nodo->data, s)) {

        nodo->derecha = insertar(nodo->derecha, s);

    } else {

        cout << "\nEstudiante duplicado.\n";
        return nodo;
    }

    nodo->altura = 1 +
                   max(obtenerAltura(nodo->izquierda),
                       obtenerAltura(nodo->derecha));

    int balance = obtenerBalance(nodo);

    if (balance > 1 &&
        menor(s, nodo->izquierda->data)) {

        return rotarDerecha(nodo);
    }

    if (balance < -1 &&
        menor(nodo->derecha->data, s)) {

        return rotarIzquierda(nodo);
    }

    if (balance > 1 &&
        menor(nodo->izquierda->data, s)) {

        nodo->izquierda = rotarIzquierda(nodo->izquierda);

        return rotarDerecha(nodo);
    }

    if (balance < -1 &&
        menor(s, nodo->derecha->data)) {

        nodo->derecha = rotarDerecha(nodo->derecha);

        return rotarIzquierda(nodo);
    }

    return nodo;
}

void mostrarStudent(Student s, int posicion) {

    cout << posicion << ". "
         << s.full_name
         << " - Score: "
         << s.skill_score
         << " | ID: "
         << s.student_id
         << endl;
}

void inOrden(Nodo* raiz, int& contador) {

    if (raiz != nullptr) {

        inOrden(raiz->izquierda, contador);

        contador++;
        mostrarStudent(raiz->data, contador);

        inOrden(raiz->derecha, contador);
    }
}

void preOrden(Nodo* raiz) {

    if (raiz != nullptr) {

        cout << raiz->data.full_name
             << " (" << raiz->data.skill_score << ")\n";

        preOrden(raiz->izquierda);
        preOrden(raiz->derecha);
    }
}

void postOrden(Nodo* raiz) {

    if (raiz != nullptr) {

        postOrden(raiz->izquierda);
        postOrden(raiz->derecha);

        cout << raiz->data.full_name
             << " (" << raiz->data.skill_score << ")\n";
    }
}

bool encontrado = false;

void buscarSkill(Nodo* raiz, int skill) {

    if (raiz == nullptr) return;

    if (raiz->data.skill_score == skill) {

        cout << "\nEstudiante encontrado:\n";

        cout << "Nombre: "
             << raiz->data.full_name << endl;

        cout << "ID: "
             << raiz->data.student_id << endl;

        cout << "Carrera: "
             << raiz->data.career << endl;

        cout << "Semestre: "
             << raiz->data.semester << endl;

        cout << "GPA: "
             << raiz->data.gpa << endl;

        cout << "Skill Score: "
             << raiz->data.skill_score << endl;

        encontrado = true;
    }

    buscarSkill(raiz->izquierda, skill);
    buscarSkill(raiz->derecha, skill);
}

void mostrarEstadisticas(Nodo* raiz) {

    cout << "\n===== ESTADISTICAS AVL =====\n";

    cout << "Altura actual del arbol: "
         << obtenerAltura(raiz) << endl;

    cout << "Factor de balance de la raiz: "
         << obtenerBalance(raiz) << endl;

    cout << "Cantidad de nodos insertados: "
         << totalNodos << endl;
}

void liberarMemoria(Nodo* raiz) {

    if (raiz != nullptr) {

        liberarMemoria(raiz->izquierda);
        liberarMemoria(raiz->derecha);

        delete raiz;
    }
}

int main() {

    Nodo* raiz = nullptr;

    int opcion;

    do {

        cout << "\n========== MENU AVL ==========\n";
        cout << "Nombre: Jimy Aroldo Morales Carranza\n\n";

        cout << "1. Insertar estudiante\n";
        cout << "2. Mostrar ranking academico\n";
        cout << "3. Buscar por skill_score\n";
        cout << "4. Mostrar estadisticas AVL\n";
        cout << "5. Mostrar PreOrden\n";
        cout << "6. Mostrar PostOrden\n";
        cout << "0. Salir\n";

        cout << "\nSeleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {

            case 1: {

                Student s;

                cout << "\n===== NUEVO ESTUDIANTE =====\n";

                cout << "ID: ";
                cin >> s.student_id;

                cin.ignore();

                cout << "Nombre completo: ";
                getline(cin, s.full_name);

                cout << "Carrera: ";
                getline(cin, s.career);

                cout << "Semestre (numero): ";

                while (!(cin >> s.semester)) {

                    cin.clear();
                    cin.ignore(1000, '\n');

                    cout << "Ingrese un numero valido: ";
                }

                cout << "GPA: ";

                while (!(cin >> s.gpa)) {

                    cin.clear();
                    cin.ignore(1000, '\n');

                    cout << "Ingrese un GPA valido: ";
                }

                cout << "Skill score: ";

                while (!(cin >> s.skill_score)) {

                    cin.clear();
                    cin.ignore(1000, '\n');

                    cout << "Ingrese un score valido: ";
                }

                raiz = insertar(raiz, s);

                cout << "\nEstudiante insertado correctamente.\n";

                break;
            }

            case 2: {

                if (raiz == nullptr) {

                    cout << "\nEl arbol esta vacio.\n";

                } else {

                    cout << "\n===== RANKING ACADEMICO =====\n";

                    int contador = 0;

                    inOrden(raiz, contador);
                }

                break;
            }

            case 3: {

                if (raiz == nullptr) {

                    cout << "\nEl arbol esta vacio.\n";
                    break;
                }

                int skill;

                cout << "\nIngrese skill_score a buscar: ";
                cin >> skill;

                encontrado = false;

                buscarSkill(raiz, skill);

                if (!encontrado) {

                    cout << "\nNo se encontro ningun estudiante.\n";
                }

                break;
            }

            case 4: {

                if (raiz == nullptr) {

                    cout << "\nEl arbol esta vacio.\n";

                } else {

                    mostrarEstadisticas(raiz);
                }

                break;
            }

            case 5: {

                if (raiz == nullptr) {

                    cout << "\nEl arbol esta vacio.\n";

                } else {

                    cout << "\n===== PREORDEN =====\n";

                    preOrden(raiz);
                }

                break;
            }

            case 6: {

                if (raiz == nullptr) {

                    cout << "\nEl arbol esta vacio.\n";

                } else {

                    cout << "\n===== POSTORDEN =====\n";

                    postOrden(raiz);
                }

                break;
            }

            case 0:

                cout << "\nSaliendo del programa...\n";
                break;

            default:

                cout << "\nOpcion invalida.\n";
        }

    } while(opcion != 0);

    liberarMemoria(raiz);

    return 0;
}