#include <iostream>
#include <string.h>
#include <algorithm>
#include <list>
#include<stdio.h>
int n;
using namespace std;

int a[100] = {0};
bool graph1[10][10];

class Hamiltonian
{
	int *path,v,x;
	public:
		Hamiltonian(int n){ v = 0; x = 0; path = new int[n]; }
		bool isSafe(bool graph[][10], int pos);
		bool hamCycleUtil(bool graph[][10], int pos, int i);
		bool hamCycle(bool graph[][10]);
		void printSolution();
};
 
class Euler
{
  int V;    
  list<int> *adj;    
public:
  Euler(int V)  { this->V = V;  adj = new list<int>[V];  }
  ~Euler()      { delete [] adj;  }
 
  void addEdge(int u, int v) {  adj[u].push_back(v); adj[v].push_back(u); }
  void rmvEdge(int u, int v);
  void printEulerTour();
  void printEulerUtil(int s);
  int DFSCount(int v, bool visited[]);
  bool isValidNextEdge(int u, int v);
  int iseuler(int[]);
};

// void menu_grafo();
void agregar_grafo();
void insertar_grafo();
void inicializar_grafo();
void ingresar_vertices_manual(int,Euler);
void ingresar_vertices(int);

int main() {
    system("color 0b");
    setlocale(LC_ALL, "");

    agregar_grafo();
    // menu_grafo();
    system("pause");
}

void Euler::printEulerTour()
{
  int u = 0;
  for (int i = 0; i < V; i++)
      if (adj[i].size() & 1)
        {   u = i; break;  }
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
 
  return (count1 > count2)? false: true;
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
	for(int i=0;i<n;i++){
		if(a[i] % 2 != 0)
			count++;
	}
	if(count == 0){
		cout<<"Es un grafo Euleriano:\n";
		return 1;
	}
	else if(count == 2){
		cout<<"Es un grafo Euleriano:\n";
		return 1;
	}
	else{
		cout<<"No es un grafo Euleriano:'\n\n";
		return -1;
	}
}

bool Hamiltonian::isSafe(bool graph[][10], int pos)
{
    if (graph [ path[pos-1] ][ v ] == 0)
        return false;
 
     for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;
 
    return true;
}
 
bool Hamiltonian::hamCycleUtil(bool graph[][10], int pos, int i)
{
    if (pos == n)
    {
        if ( graph[ path[pos-1] ][ path[0] ] == 1 )
        {
        	cout<<"Ciclo Hamiltoniano:\n";
        	x = 1;
    	}
        else
        	cout<<"Camino Hamiltoniano\n";
        return true;
    }
 
    for (v = 0; v < n; v++)
    {
    	if(v == i)
    		continue;
        if (isSafe(graph, pos))
        {
            path[pos] = v;
 
            if (hamCycleUtil (graph, pos+1, i) == true)
                return true;
 
            path[pos] = -1;
        }
    }
 
    return false;
}
 
bool Hamiltonian::hamCycle(bool graph[][10])
{
    for (int i = 0; i < n; i++)
        path[i] = -1;

    for(int i=0;i < n; i++)
    {
	path[0] = i;
    if ( hamCycleUtil(graph, 1,i) == true )
    {
		printSolution();
    	return true;
    }
	}
    cout<<"\nNo es un grafo Hamiltoniano";
    return false; 

}
 
void Hamiltonian::printSolution()
{
    for (int i = 0; i < n - 1; i++)
        cout << path[i] << "-" << path[i + 1] << " ";
        
 	if(x == 1)
    	cout << path[n - 1] << "-" << path[0];
    cout<<"\n";
}

int inicializar_grafo(int numVer, int _edges)
{
	int i,j,Edges;
 	n = numVer;
 	Euler g1(n);
 	Hamiltonian g2(n);
 	
	for(i=1;i<=n;i++)
  		for(j=1;j<=n;j++)
   			graph1[i][j]=0;
 	
    ingresar_vertices_manual(_edges,g1);

 	cout<<"\n";
 	g2.hamCycle(graph1);
 	cout<<"\n";
 	if(g1.iseuler(a) == 1)
 		g1.printEulerTour();
  return 0;
}

void ingresar_vertices_manual(int Edges,Euler g1){
    int v1, v2;
    for(int i=1;i<=Edges;i++)
 	{
  		cout<<"\n Ingresa el vertice (Separado por espacio. E.g. 1 3): ";
  		cin>>v1>>v2;
  		graph1[v1][v2]=1;
  		graph1[v2][v1]=1;
  		g1.addEdge(v1, v2);
  		a[v1]++;	
		a[v2]++;
 	}
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

        int n,Edges;
        switch (option)
        {
        case 1:
            cout<<"\n Ingresa el número de nodos\n";
            cout << ">> ";
            cin>>n;
            cout<<"\n Ingresa el total de vertices: ";
            cin>>Edges;

            inicializar_grafo(n,Edges);
            break;
        case 2:
            //abrir_archivo();
            break;
        default:
            cout << "Opcion no valida!\n";
            system("pause");
            break;
        }
    } while (option > 2 || option < 1);
}

// void menu_grafo() {
//     system("cls");
//     int op = 0;
//     do
//     {
//         cout << "\tREPRESENTACION DE GRAFOS\n\n";

//         cout << " 1. INSERTAR UN NODO                 " << endl;
//         cout << " 2. INSERTAR UNA ARISTA              " << endl;
//         cout << " 3. ELIMINAR UN NODO                 " << endl;
//         cout << " 4. ELIMINAR UNA ARISTA              " << endl;
//         cout << " 5. MOSTRAR  GRAFO                   " << endl;
//         cout << " 6. MOSTRAR ARISTAS DE UN NODO       " << endl;
//         cout << " 7. MOSTRAR PESO DE UN NODO          " << endl;
//         cout << " 8. VERIFICAR CONEXIDAD              " << endl;
//         cout << " 9. VERIFICAR EULERIANO              " << endl;
//         cout << " 10. SALIR                            " << endl;

//         cout << "\n INGRESE OPCION: ";

//         cin >> op;

//         string _nombre;
//         string ini, fin;
//         string var;
//         switch (op){
//         case 1:
//             cout << "INGRESE VARIABLE:";
//             cin >> _nombre;
//             insertar_nodo(_nombre);
//             break;
//         case 2: 
//             cout << "INGRESE NODO DE INICIO:";
//             cin >> ini;
//             cout << "INGRESE NODO FINAL:";
//             cin >> fin;
//             insertar_arista(ini,fin);
//             break;
//         case 3: eliminar_nodo();
//             break;
//         case 4: eliminar_arista();
//             break;
//         case 5: mostrar_grafo();
//             break;
//         case 6: mostrar_aristas();
//             break;
//         case 7: 
//             cout << "INGRESE NODO:";
//             cin >> var;
//             peso(var,true);
//             break;
//         case 8: verificar_convexo();
//             break;
//         case 9: verificar_euleriano();
//         case 10: continue;

//         default: cout << "OPCION NO VALIDA...!!!";
//                 op = 0;
//             break;


//         }

//         cout << endl << endl;
//         system("pause");  system("cls");

//     } while (op != 10);
//     system("cls");
// }
