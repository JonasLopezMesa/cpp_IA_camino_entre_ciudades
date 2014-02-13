//
//  Header.h
//  Práctica_Ciudades_IA
//
//  Created by jonas on 28/09/12.
//  Copyright (c) 2012 jonas. All rights reserved.
//

#ifndef Pra_ctica_Ciudades_IA_Header_h
#define Pra_ctica_Ciudades_IA_Header_h

#include <list>
#include "math.h"
#include <vector>
#include <deque>
#include <stdio.h>
#include <stdlib.h>
#include <iostream> //biblioteca para el uso de la entrada y salida por defecto
#include <fstream> //biblioteca para el uso de ficheros como entrada y salida
using namespace std;

typedef struct
{
	deque<unsigned short int>   a_que_ciudades_puede_ir; // nodo
	deque<int>                  kilometros; // peso, longitud, etc...
    deque<int>                  posicion_en_la_matriz;
    int                         ciudad_padre;
    bool                        visitado;
    deque<int>                  prediccion;
    deque<int>                  lista_predecesores;
} Datos;

typedef struct {
    int nodo;
    deque<int> aqueciudadespuedeir;
    deque<int> listadepredecesores;
    deque<int> listadepredecesores2;
    int ciudadpadre;
    bool visitado;
    int funcion;
    int distanciapadre;
} elementos;

typedef elementos datos;
typedef deque<elementos> GRAFO;
typedef deque<int> auxiliar;

int f(int g, int h) {
    return g + h;
}
int partir(GRAFO& v, int primero, int ultimo){
    int i,d;
    int val_pivote;
    val_pivote = v[primero].funcion;
    i = primero + 1;
    d = ultimo;
    do {
        while ((i <= d)&&(v[d].funcion <= val_pivote)) {
            i++;
        }
        while ((i <= d)&&(v[d].funcion > val_pivote)) {
            d--;
        }
        if (i < d) {
            swap(v[i], v[d]);
            i++;
            d--;
        }
    } while (i <= d);
    swap(v[primero], v[d]);
    return d;
}
void OR(GRAFO& v, int i, int d) {
    int pos_pivote;
    if (i < d) {
        pos_pivote = partir(v, i, d);
        OR(v, i, pos_pivote -1);
        OR(v, pos_pivote +1, d);
    }
}


//typedef vector<Datos> info_ciudad; //información de cada ciudad, con que ciudad conecta y cuantos kilómetros hay

class MAPA
{
	unsigned            numero_ciudades;         /* n˙mero de NODOS */
	unsigned            numero_caminos;         /* n˙mero de ARCOS */
	deque<Datos>       LISTA;
public:
	MAPA(char nombredefichero[], char nombrefichero2[], char nombrefichero3[]);
    void mostrar_matriz1();
    void mostrar_lista();
    void Amplitud(int ciudad_inicial, int ciudad_final);
    void Profundidad(int ciudad_inicial, int ciudad_final);
    void A_estrella(int ciudad_inicial, int ciudad_final);
	~MAPA() {};
};

#endif
