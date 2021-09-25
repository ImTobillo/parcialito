#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/// structures

typedef struct nodoD
{
    int dato;
    struct nodoD* sig;
    struct nodoD* ant;
}nodoD;

typedef struct nodo
{
    int dato;
    struct nodo* sig;
} nodo;

/// functions

// nodos dobles
void inicListaD (nodoD** listaD)
{
    *listaD = NULL;
}

nodoD* crearNodoD (int dato)
{
    nodoD* aux = (nodoD*)malloc(sizeof(nodoD));
    aux->dato = dato;
    aux->ant = NULL;
    aux->sig = NULL;
    return aux;
}

void mostrarListaD (nodoD* listaD)
{
    while (listaD)
    {
        printf("%i\t", listaD->dato);
        listaD = listaD->sig;
    }
}

void insertarOrdenadoNodoD (nodoD** listaD, int dato)
{
    nodoD* aux = crearNodoD(dato);

    if (*listaD)
    {
        if (dato < (*listaD)->dato)
        {
            aux->sig = *listaD;
            (*listaD)->ant = aux;
            *listaD = aux;
        }
        else
        {
            nodoD* ant = *listaD, *act = ant->sig;

            while (act && act->dato < dato)
            {
                ant = act;
                act = act->sig;
            }

            ant->sig = aux;
            aux->ant = ant;
            aux->sig = act;
            if (act)
                act->ant = aux;
        }
    }
    else
        *listaD = aux;
}



// nodo simple
void inicLista(nodo** lista)
{
    *lista = NULL;
}

nodo* crearNodo(int dato)
{
    nodo* aux = (nodo*)malloc(sizeof(nodo));
    aux->dato = dato;
    aux->sig = NULL;
    return aux;
}

void mostrarLista (nodo* lista)
{
    if (lista)
    {
        printf("%i\t", lista->dato);
        mostrarLista(lista->sig); /// llamada recursiva y acercamiento
    }
}

void mostrarListaInvertida (nodo* lista)
{
    if (lista)
    {
        mostrarListaInvertida(lista->sig);
        printf("%i\t", lista->dato);
    }
}

void ingresarAlFinal (nodo** lista, nodo* agreg)
{
    if (*lista)
    {
        nodo* aux = *lista;

        while (aux->sig)
            aux = aux->sig;

        aux->sig = agreg;
    }
    else
        *lista = agreg;
}

void cargarListaRand(nodo** lista, int cant)
{
    for (int i = 0; i < cant; i++)
        ingresarAlFinal(lista, crearNodo(rand() % 10 + 1));
}

int retCantNodos (nodo* lista)
{
    int c = 0;

    while (lista)
    {
        c++;
        lista = lista->sig;
    }

    return c;
}

void eliminarNodoEnPosX (nodo** lista)
{
    int cantNodos = retCantNodos(*lista);

    if (*lista)
    {
        nodo* ant = *lista;
        int pos;

        do
        {
            printf("\nINGRESE UNA POSICION A PARTIR DE 1 Y MENOR A %i: ", cantNodos);
            scanf("%i", &pos);
        }
        while (pos < 1 || pos > retCantNodos(*lista));

        if (pos == 1)
        {
            *lista = (*lista)->sig;
            free(ant);
        }
        else
        {
            nodo* act = ant->sig;
            int c = 2; /// contador desde pos 2, porque pos 1 ya se verificó

            while (c != pos)
            {
                ant = act;
                act = act->sig;
                c++;
            }

            ant->sig = act->sig;
            free(act);
        }
    }
}

void eliminarMayoresAValorX (nodo** lista, int valor)
{
    nodo* aux;

    if (*lista)
    {
        if ((*lista)->dato > valor)
        {
            aux = *lista;
            *lista = (*lista)->sig;
            free(aux);

            eliminarMayoresAValorX(lista, valor);
        }
        else
            eliminarMayoresAValorX(&(*lista)->sig, valor);
    }
}

void pasarNodosAListaD (nodo** lista, nodoD** listaD)
{
    nodo* aux;

    while (*lista)
    {
        insertarOrdenadoNodoD(listaD, (*lista)->dato);
        aux = *lista;
        *lista = (*lista)->sig;
        free(aux);
    }
}

/// main

int main()
{
    srand(time(NULL));

    nodo* lista;
    inicLista(&lista);

    cargarListaRand(&lista, 6);

    printf("LISTA SIMPLE:\n");
    mostrarLista(lista);

    /*printf("\n\nLISTA INVERTIDA:\n");
    mostrarListaInvertida(lista);

    printf("\n\nCANTIDAD DE NODOS: %i\n", retCantNodos(lista));

    eliminarNodoEnPosX(&lista);

    printf("\nLISTA CON NODO POS X BORRADO:\n");
    mostrarLista(lista);*/


    /*eliminarMayoresAValorX(&lista, 2);

    printf("\nLISTA CON NODOS MAYORES A 2 BORRADOS:\n");
    mostrarLista(lista);*/

    nodoD* listaD;
    inicListaD(&listaD);

    pasarNodosAListaD(&lista, &listaD);

    printf("\nLISTA DOBLE CON DATOS DE LISTA SIMPLE:\n");
    mostrarListaD(listaD);

    printf("\n\nLISTA SIMPLE:\n");
    mostrarLista(lista);

    return 0;
}
