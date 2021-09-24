#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/// structures

typedef struct nodo
{
    int dato;
    struct nodo* sig;
}nodo;

/// functions

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
        mostrarLista(lista->sig);
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





/// main

int main()
{
    srand(time(NULL));

    nodo* lista;
    inicLista(&lista);

    cargarListaRand(&lista, 6);

    printf("LISTA:\n");
    mostrarLista(lista);

    printf("\n\nLISTA INVERTIDA:\n");
    mostrarListaInvertida(lista);



    return 0;
}
