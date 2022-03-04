#include <iostream>
#include <locale.h>
#include <list>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Nodo {
    string nombre;
    struct Nodo* siguiente;
    struct Arista* adyacente;
};

struct Arista {
    struct Nodo* destino;
    struct Arista* siguiente;
};

typedef struct Nodo* TNode;
typedef struct Arista* TArista;

bool dirigido = false;
void menu();
void menu_grafo();
void agregar_grafo();
void insertar_nodo(string);
void agrega_arista(TNode&, TNode&, TArista&);
void insertar_arista();
void vaciar_aristas(TNode&);
void eliminar_nodo();
void eliminar_arista();
void mostrar_grafo();
void mostrar_aristas();
void peso();
void verificar_convexo();
void abrir_archivo();

TNode p;
list<string> nombres;

int main() {
    system("color 0b");
    setlocale(LC_ALL, "");

    agregar_grafo();
    menu_grafo();
    system("pause");
}

void menu() {
    system("cls");
    int option = 0;
    cout << "1. Agregar Grafo\n";
    cout << "2. Seleccionar Grafo\n";
    cout << "3. Borrar Grafo\n";
    cout << "\nOpción seleccionada: ";
    cin >> option;

    switch (option)
    {
    case 1: agregar_grafo();
        break;
    case 2: menu_grafo();
        break;
    case 3: cout << "Borrando grafo"; // Cambiar la opcion al menu correspondiente
        break;
    default:
        cout << "Opción no válida";
        break;
    }
}

void agregar_grafo() {
    int option = 0;
    do {
        system("cls");
        cout << "\tTipo de Grafo a utilizar:\n";

        cout << "1. Grafo dirigido\n";
        cout << "2. Grafo no dirigido\n";
        cout << "3. Abrir grafo por archivo\n";

        cout << "\nOpci�n seleccionada: ";
        cin >> option;


        switch (option)
        {
        case 1:
            dirigido = true;
            break;
        case 2:
            dirigido = false;
            break;
        case 3:
            abrir_archivo();
            break;
        default:
            cout << "Opcion no valida!\n";
            system("pause");
            break;
        }
    } while (option > 3 || option < 1);
}


#pragma region Dirigidos

void menu_grafo() {
    system("cls");
    int op = 0;
    do
    {
        if(dirigido)
            cout << "\tREPRESENTACION DE GRAFOS DIRIGIDOS\n\n";
        else
            cout << "\tREPRESENTACION DE GRAFOS NO DIRIGIDOS\n\n";

        cout << " 1. INSERTAR UN NODO                 " << endl;
        cout << " 2. INSERTAR UNA ARISTA              " << endl;
        cout << " 3. ELIMINAR UN NODO                 " << endl;
        cout << " 4. ELIMINAR UNA ARISTA              " << endl;
        cout << " 5. MOSTRAR  GRAFO                   " << endl;
        cout << " 6. MOSTRAR ARISTAS DE UN NODO       " << endl;
        cout << " 7. MOSTRAR PESO DE UN NODO          " << endl;
        cout << " 8. VERIFICAR CONVEXIDAD             " << endl;
        cout << " 9. SALIR                            " << endl;

        cout << "\n INGRESE OPCION: ";

        cin >> op;

        string _nombre;
        switch (op){
        case 1:
            cout << "INGRESE VARIABLE:";
            cin >> _nombre;
            insertar_nodo(_nombre);
            break;
        case 2: insertar_arista();
            break;
        case 3: eliminar_nodo();
            break;
        case 4: eliminar_arista();
            break;
        case 5: mostrar_grafo();
            break;
        case 6: mostrar_aristas();
            break;
        case 7: peso();
            break;
        case 8: verificar_convexo();
            break;
        case 9: continue;

        default: cout << "OPCION NO VALIDA...!!!";
                op = 0;
            break;


        }

        cout << endl << endl;
        system("pause");  system("cls");

    } while (op != 9);
    system("cls");
}

#pragma endregion

/*                      INSERTAR NODO AL GRAFO
---------------------------------------------------------------------*/
void insertar_nodo(string _nombre)
{
    TNode t, nuevo = new struct Nodo;
    nuevo->nombre = _nombre;
    nuevo->siguiente = NULL;
    nuevo->adyacente = NULL;

    if (p == NULL)
    {
        p = nuevo;
        cout << "NODO AGREGADO.\n";
    }
    else
    {
        t = p;
        while (t->siguiente != NULL)
        {
            t = t->siguiente;
        }
        t->siguiente = nuevo;
        cout << "NODO INGRESADO.\n";
    }

    nombres.push_back(nuevo->nombre);
}

/*                      AGREGAR ARISTA
    funcion que utilizada para agregar la arista a dos nodos
---------------------------------------------------------------------*/
void agrega_arista(TNode& aux, TNode& aux2, TArista& nuevo)
{
    TArista q;
    if (aux->adyacente == NULL){
        aux->adyacente = nuevo;
        nuevo->destino = aux2;
        cout << "PRIMERA ARISTA....!";
    } else {
        q = aux->adyacente;
        if(q->destino != aux2){
            while (q->siguiente != NULL)
                q = q->siguiente;
            nuevo->destino = aux2;
            q->siguiente = nuevo;
            cout << "ARISTA AGREGADA...!!!!";
        }
        else
            cout << "ARISTA EXISTENTE";
    }
}

/*                      INSERTAR ARISTA
    funcion que busca las posiciones de memoria de los nodos
    y hace llamado a agregar_arista para insertar la arista
---------------------------------------------------------------------*/
void insertar_arista()
{
    string ini, fin;
    TArista nuevo = new struct Arista;
    TArista nuevo2 = new struct Arista;
        
    TNode aux, aux2;

    if (p == NULL)
    {
        cout << "GRAFO VACIO...!!!!";
        return;
    }
    nuevo->siguiente = NULL;
    if(!dirigido)
        nuevo2->siguiente = NULL;

    cout << "INGRESE NODO DE INICIO:";
    cin >> ini;
    cout << "INGRESE NODO FINAL:";
    cin >> fin;
    aux = p;
    aux2 = p;
    while (aux2 != NULL)
    {
        if (aux2->nombre == fin)
        {
            break;
        }

        aux2 = aux2->siguiente;
    }
    while (aux != NULL)
    {
        if (aux->nombre == ini)
        {
            agrega_arista(aux, aux2, nuevo);
            if(!dirigido)
                agrega_arista(aux2, aux, nuevo2);
                
            return;
        }

        aux = aux->siguiente;
    }
}

/*          FUNCION PARA BORRAR TODAS LAS ARISTAS DE UN NODO
    esta funcion es utilizada al borrar un nodo pues si tiene aristas
    es nesesario borrarlas tambien y dejar libre la memoria
---------------------------------------------------------------------*/
void vaciar_aristas(TNode& aux)
{
    TArista q, r;
    q = aux->adyacente;
    while (q->siguiente != NULL)
    {
        r = q;
        q = q->siguiente;
        delete(r);
    }
}
/*                      ELIMINAR NODO
    funcion utilizada para eliminar un nodo del grafo
    pero para eso tambien tiene que eliminar sus aristas por lo cual
    llama a la funcion vaciar_aristas para borrarlas
---------------------------------------------------------------------*/
void eliminar_nodo()
{
    string var;
    TNode aux, ant;
    ant = nullptr;
    aux = p;
    cout << "ELIMINAR UN NODO\n";
    if (p == NULL)
    {
        cout << "GRAFO VACIO...!!!!";
        return;
    }
    cout << "INGRESE NOMBRE DE VARIABLE:";
    cin >> var;

    while (aux != NULL)
    {
        if (aux->nombre == var)
        {
            if (aux->adyacente != NULL)
                vaciar_aristas(aux);

            if (aux == p)
            {

                p = p->siguiente;
                delete(aux);
                cout << "NODO ELIMINADO...!!!!";
                return;



            }
            else
            {
                ant->siguiente = aux->siguiente;
                delete(aux);
                cout << "NODO ELIMINADO...!!!!";
                return;
            }
        }
        else
        {
            ant = aux;
            aux = aux->siguiente;
        }
    }

}

/*                      ELIMINAR ARISTA
    funcion utilizada para eliminar una arista
---------------------------------------------------------------------*/
void eliminar_arista()
{
    string ini, fin;
    TNode aux, aux2;
    TArista q, r;
    r = nullptr;
    cout << "\n ELIMINAR ARISTA\n";
    cout << "INGRESE NODO DE INICIO:";
    cin >> ini;
    cout << "INGRESE NODO FINAL:";
    cin >> fin;
    aux = p;
    aux2 = p;
    while (aux2 != NULL)
    {
        if (aux2->nombre == fin)
        {
            break;
        }
        else
            aux2 = aux2->siguiente;
    }
    while (aux != NULL)
    {
        if (aux->nombre == ini)
        {
            q = aux->adyacente;
            while (q != NULL)
            {
                if (q->destino == aux2)
                {
                    if (q == aux->adyacente)
                        aux->adyacente = aux->adyacente->siguiente;
                    else
                        r->siguiente = q->siguiente;
                    delete(q);
                    cout << "ARISTA  " << aux->nombre << "----->" << aux2->nombre << " ELIMINADA.....!!!!";
                    return;
                }
            }
            r = q;
            q = q->siguiente;
        }
        aux = aux->siguiente;
    }
}

/*                      MOSTRAR GRAFO
    funcion que imprime un grafo en su forma enlazada
---------------------------------------------------------------------*/
void mostrar_grafo()
{
    TNode ptr;
    TArista ar;
    ptr = p;
    cout << "NODO|LISTA DE ADYACENCIA\n";

    while (ptr != NULL)
    {
        cout << "   " << ptr->nombre << "|";
        if (ptr->adyacente != NULL)
        {
            ar = ptr->adyacente;
            while (ar != NULL)
            {
                cout << " " << ar->destino->nombre;
                ar = ar->siguiente;
            }

        }
        ptr = ptr->siguiente;
        cout << endl;
    }
}

/*                      MOSTRAR ARISTAS
    funcion que muestra todas las aristas de un nodo seleccionado
---------------------------------------------------------------------*/
void mostrar_aristas()
{
    TNode aux;
    TArista ar;
    string var;
    cout << "MOSTRAR ARISTAS DE NODO\n";
    cout << "INGRESE NODO:";
    cin >> var;
    aux = p;
    while (aux != NULL)
    {
        if (aux->nombre == var)
        {
            if (aux->adyacente == NULL)
            {
                cout << "EL NODO NO TIENE ARISTAS...!!!!";
                return;
            }
            else
            {
                cout << "NODO|LISTA DE ADYACENCIA\n";
                cout << "   " << aux->nombre << "|";
                ar = aux->adyacente;

                while (ar != NULL)
                {
                    cout << ar->destino->nombre << " ";
                    ar = ar->siguiente;
                }
                cout << endl;
                return;
            }
        }
        else
            aux = aux->siguiente;
    }
}

void peso() {
    TNode aux;
    TArista ar;
    string var;
    cout << "GRADO NODO\n";
    cout << "INGRESE NODO:";
    cin >> var;
    aux = p;
    while (aux != NULL)
    {
        if (aux->nombre == var)
        {
            if (aux->adyacente == NULL){
                cout << "NODO|Grado\n";
                cout << "   " << aux->nombre << "|";
                cout << "0";
                return;
            }
            else
            {
                cout << "NODO|Grado\n";
                cout << "   " << aux->nombre << "|";
                ar = aux->adyacente;
                int peso = 0;

                while (ar != NULL){
                    peso++;
                    ar = ar->siguiente;
                }
                cout << peso << endl;
                //! Aquí esta el tercer commit
                return ;
            }
        }
        else
            aux = aux->siguiente;
    }
}

void verificar_convexo(){
    
    bool convexo = true;
    TNode ptr;
    TArista ar;
    ptr = p;

    while (ptr != NULL)
    {
        if (ptr->adyacente != NULL)
        {
            ar = ptr->adyacente;
            while (ar != NULL) {
                list<string>::iterator it = nombres.begin();
                while (*it != ar->destino->nombre && it != nombres.end() ) it++;
                if(*it != ar->destino->nombre)
                    convexo = false;

                ar = ar->siguiente;
            }

        }
        ptr = ptr->siguiente;
    }

    if(convexo)
        cout << "Si lo es" << endl;
    else
        cout << "No lo es" << endl;
}

void abrir_archivo(){
    string nombre_archivo;
    string mensaje;

    cout << "Ingresa el nombre/ruta del archivo: ";
    cin >> nombre_archivo;

    ifstream fe(nombre_archivo);
    string space_delimiter = " ";
    while (!fe.eof()) {
        fe >> mensaje;

        string nodoInicial(1,mensaje[0]);
        insertar_nodo(nodoInicial);
        mensaje.erase(0,4);

        string lectura;
        stringstream input_stringstream(mensaje);  
        while (getline(input_stringstream, lectura, ' '))
        {
            cout << lectura << ",";
        }

        cout << endl;

        // A | B D C S D A A
    }
    fe.close();

    system("pause");
}

//! Hola este es el segundo commit