#include <iostream>
#include <string.h>
#include <algorithm>
#include <list>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>

int n;
int nGlobal;
using namespace std;

int a[100] = { 0 };
bool graph1[10][10];

class Hamiltonian
{
    int* path, v, x;
public:
    Hamiltonian(int n) { v = 0; x = 0; path = new int[n]; }
    bool isSafe(bool graph[][10], int pos);
    bool hamCycleUtil(bool graph[][10], int pos, int i,bool msg);
    bool hamCycle(bool graph[][10],bool msg);
    void printSolution();
};

class Euler
{
    int V;
    list<int>* adj;
public:
    Euler(int V) { this->V = V;  adj = new list<int>[V]; }
    ~Euler() { delete[] adj; }

    void addEdge(int u, int v) { adj[u].push_back(v); adj[v].push_back(u); }
    void rmvEdge(int u, int v);
    void printEulerTour();
    void printEulerUtil(int s);
    int DFSCount(int v, bool visited[]);
    bool isValidNextEdge(int u, int v);
    int iseuler(int[]);
};

void agregar_grafo();
void inicializar_grafo_manual();
void abrir_archivo();

int main() {
    system("color 0b");
    setlocale(LC_ALL, "");

    agregar_grafo();
    system("pause");
}

void Euler::printEulerTour()
{
    int u = 0;
    for (int i = 0; i < V; i++)
        if (adj[i].size() & 1)
        {
            u = i; break;
        }
    printEulerUtil(u);
    cout << endl;
}

void Euler::printEulerUtil(int u)
{
    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i)
    {
        int v = *i;
        if (v != -1 && isValidNextEdge(u, v))
        {
            cout << u << "-" << v << " ";
            rmvEdge(u, v);
            printEulerUtil(v);
        }
    }
}

bool Euler::isValidNextEdge(int u, int v)
{
    int count = 0;
    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i)
        if (*i != -1)
            count++;
    if (count == 1)
        return true;

    const int _V = 60;

    bool visited[_V];
    memset(visited, false, _V);
    int count1 = DFSCount(u, visited);

    rmvEdge(u, v);
    memset(visited, false, V);
    int count2 = DFSCount(u, visited);

    addEdge(u, v);

    return (count1 > count2) ? false : true;
}

void Euler::rmvEdge(int u, int v)
{
    list<int>::iterator iv = find(adj[u].begin(), adj[u].end(), v);
    *iv = -1;

    list<int>::iterator iu = find(adj[v].begin(), adj[v].end(), u);
    *iu = -1;
}

int Euler::DFSCount(int v, bool visited[])
{
    visited[v] = true;
    int count = 1;

    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (*i != -1 && !visited[*i])
            count += DFSCount(*i, visited);

    return count;
}

int Euler::iseuler(int a[])
{
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] % 2 != 0)
            count++;
    }
    if (count == 0) {
        cout << "Es un grafo Euleriano:\n";
        return 1;
    }
    else if (count == 2) {
        cout << "Es un grafo Euleriano:\n";
        return 1;
    }
    else {
        cout << "No es un grafo Euleriano:'\n\n";
        return -1;
    }
}

bool Hamiltonian::isSafe(bool graph[][10], int pos)
{
    if (graph[path[pos - 1]][v] == 0)
        return false;

    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;

    return true;
}

bool Hamiltonian::hamCycleUtil(bool graph[][10], int pos, int i,bool msg)
{
    if (pos == n)
    {
        if (graph[path[pos - 1]][path[0]] == 1)
        {
            if(msg)
            cout << "Ciclo Hamiltoniano:\n";
            x = 1;
        }
        else if (msg)
            cout << "Camino Hamiltoniano\n";
        return true;
    }

    for (v = 0; v < n; v++)
    {
        if (v == i)
            continue;
        if (isSafe(graph, pos))
        {
            path[pos] = v;

            if (hamCycleUtil(graph, pos + 1, i,true) == true)
                return true;

            path[pos] = -1;
        }
    }

    return false;
}

bool Hamiltonian::hamCycle(bool graph[][10],bool msg)
{
    for (int i = 0; i < n; i++)
        path[i] = -1;

    for (int i = 0; i < n; i++)
    {
        path[0] = i;
        if (hamCycleUtil(graph, 1, i,true) == true)
        {
            if (msg)
                printSolution();
            else
                cout << "Es un grafo conexo\n";
            return true;
        }
    }
    if(msg)
        cout << "\nNo es un grafo Hamiltoniano";
    return false;

}

void Hamiltonian::printSolution()
{
    for (int i = 0; i < n - 1; i++)
        cout << path[i] << "-" << path[i + 1] << " ";

    if (x == 1)
        cout << path[n - 1] << "-" << path[0];
    cout << "\n";
}

void inicializar_grafo_manual()
{
    int i, j, v1, v2, Edges;
    cout << "\n Ingresa el número de nodos\n";
    cout << ">> ";
    cin >> n;
    
    Euler g1(n);
    Hamiltonian g2(n);
    int a[10] = { 0 };
    bool graph1[10][10];
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            graph1[i][j] = 0;
    cout << "\n Ingresa el total de vertices\n";
    cout << ">> ";
    cin >> Edges;
    for (i = 1; i <= Edges; i++)
    {
        cout << "\n Ingresa el vertice (Separado por espacio. E.g. 1 3): ";
        cin >> v1 >> v2;
        graph1[v1][v2] = 1;
        graph1[v2][v1] = 1;
        g1.addEdge(v1, v2);
        a[v1]++;
        a[v2]++;
    }    

    system("cls");
    int op = 0;
    do
    {
        cout << "\tREPRESENTACION DE GRAFOS\n\n";

        cout << " 1. MOSTRAR  GRAFO                   " << endl;
        cout << " 2. MOSTRAR ARISTAS DE UN NODO       " << endl;
        cout << " 3. MOSTRAR PESO DE UN NODO          " << endl;
        cout << " 4. VERIFICAR CONEXIDAD              " << endl;
        cout << " 5. VERIFICAR TIPO DE GRAFO          " << endl;
        cout << " 6. SALIR                           " << endl;

        cout << "\n INGRESE OPCION: ";

        cin >> op;

        int peso = 0;
        switch (op) {
        case 1:
            cout << "    ";
            for (j = 0; j < n; j++) {
                cout << j << " ";
            }
            cout << endl;
            cout << "   -";
            for (j = 0; j < n; j++) {
                cout << "--";
            }
            cout << endl;
            for (i = 1; i <= n; i++) {
                cout << i - 1 << " | ";
                for (j = 1; j <= n; j++) {
                    cout << graph1[i][j] << " ";
                }
                cout << endl;
            }
            break;
        case 2:
            cout << "Ingresa el nodo a escoger: ";
            cin >> i;

            cout << "    ";
            for (j = 0; j < n; j++) {
                cout << j << " ";
            }
            cout << endl;
            cout << "   -";
            for (j = 0; j < n; j++) {
                cout << "--";
            }
            cout << endl;
            cout << i << " | ";
            for (j = 1; j <= n; j++) {
                cout << graph1[i + 1][j] << " ";
            }
            cout << endl;
            break;
        case 3:
            cout << "Ingresa el nodo a escoger: ";
            cin >> i;
            cout << "Nodo | Peso" << endl;
            for (j = 1; j <= n; j++) {
                if (graph1[i + 1][j] == 1)
                    peso++;
            }
            cout << i << " | " << peso;
            break;
        case 4:
            break;
        case 5:
            g2.hamCycle(graph1,true);
            cout << "\n";
            if (g1.iseuler(a) == 1)
                g1.printEulerTour();
            break;
        case 6: continue;

        default: cout << "OPCION NO VALIDA...!!!";
            op = 0;
            break;


        }

        cout << endl << endl;
        system("pause");  system("cls");

    } while (op != 6);
    system("cls");

    system("pause");
}

void agregar_grafo() {
    int option = 0;
    do {
        system("cls");
        cout << "\tTipo de Grafo a utilizar:\n";

        cout << "1. Agregar grafo manual\n";
        cout << "2. Abrir grafo por archivo\n";

        cout << "\nOpcion seleccionada: ";
        cin >> option;

        int n, Edges;
        switch (option)
        {
        case 1:
            inicializar_grafo_manual();
            break;
        case 2:
            abrir_archivo();
            break;
        default:
            cout << "Opcion no valida!\n";
            system("pause");
            break;
        }
    } while (option > 2 || option < 1);
}

 void abrir_archivo() {
     string nombre_archivo;
     string mensaje;

     cout << "Ingresa el nombre/ruta del archivo: ";
     cin >> nombre_archivo;

     ifstream fe(nombre_archivo);
     int i, j, v1, v2;
     getline(fe, mensaje);
     list<int> pareja;

     string lectura;
     stringstream input_stringstream(mensaje);
     while (getline(input_stringstream, lectura, ' '))
     {
         pareja.push_back(stoi(lectura));
     }

     n = pareja.front();
     Euler g1(n);
     Hamiltonian g2(n);
     int a[10] = { 0 };
     bool graph1[10][10];
     for (i = 1; i <= n; i++)
         for (j = 1; j <= n; j++)
             graph1[i][j] = 0;
   
     while (!fe.eof()) {
        pareja.clear();
         getline(fe, mensaje);
         string lectura;
         stringstream input_stringstream(mensaje);
         while (getline(input_stringstream, lectura, ' '))
         {
             pareja.push_back(stoi(lectura));
         }
         v1 = pareja.front();
         v2 = pareja.back();

        graph1[v1][v2] = 1;
        graph1[v2][v1] = 1;
        g1.addEdge(v1, v2);
        a[v1]++;
        a[v2]++;
     }

     system("cls");
     int op = 0;
     do
     {
         cout << "\tREPRESENTACION DE GRAFOS\n\n";

         cout << " 1. MOSTRAR  GRAFO                   " << endl;
         cout << " 2. MOSTRAR ARISTAS DE UN NODO       " << endl;
         cout << " 3. MOSTRAR PESO DE UN NODO          " << endl;
         cout << " 4. VERIFICAR CONEXIDAD              " << endl;
         cout << " 5. VERIFICAR TIPO DE GRAFO          " << endl;
         cout << " 6. SALIR                           " << endl;

         cout << "\n INGRESE OPCION: ";

         cin >> op;

         int peso = 0;
         switch (op) {
         case 1:
             cout << "    ";
             for (j = 0; j < n; j++) {
                 cout << j << " ";
             }
             cout << endl;
             cout << "   -";
             for (j = 0; j < n; j++) {
                 cout << "--";
             }
             cout << endl;
             for (i = 1; i <= n; i++) {
                 cout << i - 1 << " | ";
                 for (j = 1; j <= n; j++) {
                     cout << graph1[i][j] << " ";
                 }
                 cout << endl;
             }
             break;
         case 2:
             cout << "Ingresa el nodo a escoger: ";
             cin >> i;

             cout << "    ";
             for (j = 0; j < n; j++) {
                 cout << j << " ";
             }
             cout << endl;
             cout << "   -";
             for (j = 0; j < n; j++) {
                 cout << "--";
             }
             cout << endl;
            cout << i << " | ";
            for (j = 1; j <= n; j++) {
                cout << graph1[i+1][j] << " ";
            }
            cout << endl;
             break;
         case 3:
             cout << "Ingresa el nodo a escoger: ";
             cin >> i;
             cout << "Nodo | Peso" << endl;
             for (j = 1; j <= n; j++) {
                 if (graph1[i + 1][j] == 1)
                     peso++;
             }
             cout << i << " | " << peso;
             break;
         case 4:
             if (g1.iseuler(a) == 1)
                 cout << "Es conexo\n";
             else
                 cout << "No es conexo\n";
             break;
         case 5:
             g2.hamCycle(graph1,true);
             cout << "\n";
             if (g1.iseuler(a) == 1)
                 g1.printEulerTour();
             break;
         case 6: continue;

         default: cout << "OPCION NO VALIDA...!!!";
             op = 0;
             break;


         }

         cout << endl << endl;
         system("pause");  system("cls");

     } while (op != 6);
     system("cls");

     system("pause");
 }