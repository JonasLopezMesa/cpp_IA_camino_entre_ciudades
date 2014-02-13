//
//  main.cpp
//  Práctica_Ciudades_IA
//
//  Created by jonas on 28/09/12.
//  Copyright (c) 2012 jonas. All rights reserved.
//

#include "Header.h"

MAPA::MAPA(char nombredefichero1[], char nombredefichero2[], char nombredefichero3[]){
    //Obtención de los datos del fichero
    Datos dato1,dato2;
    //info_ciudad info;
    int cuenta = 0;
    ifstream textfile(nombredefichero1);
    ifstream textfile2(nombredefichero2);
    ifstream textfile3(nombredefichero3);
    int a1, p,l,l1;
    int a2, k;
    int a3, predi;
    if (textfile.is_open() && textfile2.is_open() && textfile3.is_open()) {
        textfile >> (int&) a1; //lee el tamaño de la matriz1
        textfile2 >> (int&) a2; //lee el tamaño de la matriz2
        textfile3 >> (int&) a3; //lee el tamaño de la matriz3
        if (a1 == a2 && a2 == a3) {
            LISTA.resize(a1+1);
            //cout << "A:" << a1 << endl;
            numero_ciudades = a1;
            numero_caminos = 0;
            l1=1;
            for (int i = 1; i <= numero_ciudades; i++) {
                //cout << "------------NUEVA LÍNEA DE LA MATRIZ-------------" << endl;
                l = 0;
                for (int j = 0; j < numero_ciudades; j++) {
                    textfile >> (int&) p;
                    textfile2 >> (int&) k;
                    //cout << p << " ";
                    textfile3 >> (int&) predi;
                    LISTA[l1].prediccion.push_back(predi);
                    //cout << j;
                    if (p == 1) {
                        //cout <<endl << p << " = P" << endl;
                        
                        //cout << "J: " << j+1 << " " << endl;
                        LISTA[l1].a_que_ciudades_puede_ir.push_back(j+1);
                        LISTA[l1].kilometros.push_back(k);
                        LISTA[l1].posicion_en_la_matriz.push_back(j);
                        LISTA[l1].ciudad_padre = 0;
                        LISTA[l1].visitado = false;
                        cuenta++;
                        //cout << p << "  ";
                        l++;
                    }
                }
                //cout << endl;
                numero_caminos = numero_caminos + l;
                l1= l1+1;
            }
        }
        
    }
    //cout << "CUENTA: " << cuenta << endl;
    //cout << "Nº CAMINOS:  " << numero_caminos*2 << endl;
    //cout << "1.27" << endl;
    numero_caminos = numero_caminos/2;
    //cout << "1.28" << endl;
    textfile.close();
    //cout << "1.29" << endl;
    textfile2.close();
    textfile3.close();
    //cout << "1.30" << endl;
}

void MAPA::mostrar_matriz1(){
    for (int i = 0; i < numero_ciudades; i++) {
        for (int j = 0; j < numero_ciudades; j++) {
            if (j == LISTA[i].posicion_en_la_matriz[j]) {
                cout << "1" << "  ";
            } else {
                cout << "0" << "  ";
            }
        }
        cout << endl;
    }
}

void MAPA::mostrar_lista(){
    for (int i = 1; i <= numero_ciudades; i++) {
        cout << "Desde la ciudad: [" << i << "] se puede ir a la ciudad: [";
        for (int j = 0; j < LISTA[i].a_que_ciudades_puede_ir.size(); j++) {
            cout << ", " << LISTA[i].a_que_ciudades_puede_ir[j] << " {" << LISTA[i].kilometros[j] <<  ".km}";
        }
        
        cout << "]" << endl;
        cout << "Heurística: { ";
        for (int x = 0; x < LISTA[i].prediccion.size(); x++) {
            cout << LISTA[i].prediccion[x] << " - ";
        }
        cout << " }" << endl;
    }
}

void MAPA::Amplitud(int ciudad_inicial, int ciudad_final){
    int rama, rama2, contador, final;
    bool se_pone;
    GRAFO grafo;
    datos datosiniciales;
    datosiniciales.nodo = ciudad_inicial;
    datosiniciales.listadepredecesores.push_back(-1);
    datosiniciales.aqueciudadespuedeir.push_back(0);
    datosiniciales.ciudadpadre = 0;
    grafo.push_front(datosiniciales);
    int encontrado = 0;
    for (int i = 0; encontrado == 0; i++) {
        if (grafo[i].nodo != ciudad_final) {
            for (int j = 0; j < LISTA[grafo[i].nodo].a_que_ciudades_puede_ir.size(); j++) {
                datos aux;
                se_pone = true;
                rama = LISTA[grafo[i].nodo].a_que_ciudades_puede_ir[j];
                rama2 = i;
                if (rama == ciudad_inicial) {
                    se_pone = false;
                } else {
                    aux.listadepredecesores.push_back(grafo[rama2].nodo);
                    while (rama2 != grafo[0].ciudadpadre) {
                        rama2 = grafo[rama2].ciudadpadre;
                        if (rama == grafo[rama2].nodo) {
                            se_pone = false;
                        }
                        aux.listadepredecesores.push_back(grafo[rama2].nodo);
                    }
                }
                if (se_pone == true) {
                    aux.nodo = LISTA[grafo[i].nodo].a_que_ciudades_puede_ir[j];
                    aux.ciudadpadre = i;
                    grafo.push_back(aux);
                    grafo[i].aqueciudadespuedeir.push_back(LISTA[grafo[i].nodo].a_que_ciudades_puede_ir[j]);
                }
            }
        } else {
            final = i;
            encontrado = 1;
        }
    }
    if (encontrado == 1) {
        deque<int> lista;
        int iterador = 0, kilometross = 0, este = 0;
        grafo[final].listadepredecesores.push_front(grafo[final].nodo);
        while (iterador < grafo[final].listadepredecesores.size()) {
            lista.push_front(grafo[final].listadepredecesores[iterador]);
            iterador++;
        } iterador = 0;
        while (iterador < lista.size()) {
            cout << lista[iterador] << " - ";
            iterador++;
        }
        unsigned long contador1 = 0;
        for (int i = 0; i < grafo.size(); i++) {
            contador1 = contador1 + grafo[i].aqueciudadespuedeir.size();
        }
        for (int w = 0; w < grafo[final].listadepredecesores.size()-1; w++) {
            este = 0;
            for (int x = 0; x < LISTA[grafo[final].listadepredecesores[w+1]].a_que_ciudades_puede_ir.size(); x++) {
                if (grafo[final].listadepredecesores[w] == LISTA[grafo[final].listadepredecesores[w+1]].a_que_ciudades_puede_ir[x]) {
                    este = x;
                }
            }
                kilometross = kilometross + LISTA[grafo[final].listadepredecesores[w+1]].kilometros[este];
        }
        cout << " || Costo: " << kilometross << " .Nodos Generados: " << contador1 << "  .Nodos analizados: " << final+1 << endl;
    } else {
        cout << "ERROR: NO SE HA ENCONTRADO EL NODO!!!" << endl;
    }
}

void MAPA::Profundidad(int ciudad_inicial, int ciudad_final){
    int rama, rama2, contador, final, actual, analizados = 0;
    bool se_pone, sinhijos, pusoalmenosuno;
    GRAFO grafo;
    datos datosiniciales;
    datosiniciales.nodo = ciudad_inicial;
    datosiniciales.listadepredecesores.push_back(-1);
    datosiniciales.aqueciudadespuedeir.push_back(0);
    datosiniciales.ciudadpadre = 0;
    grafo.push_front(datosiniciales);
    int encontrado = 0;
    for (int i = 0; encontrado == 0; i++) {
        actual = i;
        if (grafo[i].nodo != ciudad_final) {
            grafo[actual].visitado = true;
            sinhijos = true;
            contador = 0;
            for (int j = 0; j < LISTA[grafo[actual].nodo].a_que_ciudades_puede_ir.size(); j++) {
                datos aux;
                se_pone = true;
                rama = LISTA[grafo[actual].nodo].a_que_ciudades_puede_ir[j];
                rama2 = actual;
                if (rama == ciudad_inicial) {
                    se_pone = false;
                } else {
                    aux.listadepredecesores.push_back(grafo[rama2].nodo);
                    while (rama2 != grafo[0].ciudadpadre) {
                        rama2 = grafo[rama2].ciudadpadre;
                        if (rama == grafo[rama2].nodo) {
                            se_pone = false;
                        }
                        aux.listadepredecesores.push_back(grafo[rama2].nodo);
                    }
                }
                if (se_pone == true) {
                    contador++;
                    aux.visitado = false;
                    aux.nodo = LISTA[grafo[actual].nodo].a_que_ciudades_puede_ir[j];
                    aux.ciudadpadre = actual;
                    grafo.push_back(aux);
                    grafo[actual].aqueciudadespuedeir.push_back(LISTA[grafo[actual].nodo].a_que_ciudades_puede_ir[j]);
                    i = grafo.size() - contador;
                    sinhijos = false;
                }
            }
            if (sinhijos == true) {
                int aqui;
                for (int f = 0; f < grafo.size()-1; f++) {
                    if (grafo[f].visitado == false) {
                        aqui = f;
                    } else{
                    }
                }
                i = aqui-1;
            }else {
                i--;
            }
            analizados++;
        } else {
            final = i;
            encontrado = 1;
        }
    }
    if (encontrado == 1) {
        deque<int> lista;
        int iterador = 0, kilometross = 0, este = 0;
        grafo[final].listadepredecesores.push_front(grafo[final].nodo);
        while (iterador < grafo[final].listadepredecesores.size()) {
            lista.push_front(grafo[final].listadepredecesores[iterador]);
            iterador++;
        } iterador = 0;
        while (iterador < lista.size()) {
            cout << lista[iterador] << " - ";
            iterador++;
        }
        unsigned long contador1 = 0;
        for (int i = 0; i < grafo.size(); i++) {
            contador1 = contador1 + grafo[i].aqueciudadespuedeir.size();
        }
        for (int w = 0; w < grafo[final].listadepredecesores.size()-1; w++) {
            este = 0;
            for (int x = 0; x < LISTA[grafo[final].listadepredecesores[w+1]].a_que_ciudades_puede_ir[x]; x++) {
                if (grafo[final].listadepredecesores[w] == LISTA[grafo[final].listadepredecesores[w+1]].a_que_ciudades_puede_ir[x]) {
                    este = x;
                }
            }
            kilometross = kilometross + LISTA[grafo[final].listadepredecesores[w+1]].kilometros[este];
        }
        cout << " || Costo: " << kilometross << " .Nodos Generados: " << contador1 << "  .Nodos analizados: " << analizados+1 << endl;
    } else {
        cout << "ERROR: NO SE HA ENCONTRADO EL NODO!!!" << endl;
    }
}

void MAPA::A_estrella(int ciudad_inicial, int ciudad_final){
    int rama, rama2, g, h, optimo = 4500,optimo_iter, iteradormenor, siguiente = 0, analizados = 0;
    bool se_pone, hay_menor, sigue_buscando = true;
    GRAFO grafo;
    datos datosiniciales, final;
    datosiniciales.nodo = ciudad_inicial;
    datosiniciales.listadepredecesores.push_back(-1);
    datosiniciales.listadepredecesores2.push_back(-1);
    datosiniciales.aqueciudadespuedeir.push_back(0);
    datosiniciales.ciudadpadre = 0;
    datosiniciales.funcion = f(0, LISTA[ciudad_inicial].prediccion[ciudad_final-1]);
    datosiniciales.visitado = true;
    grafo.push_front(datosiniciales);
    int encontrado = 0;
    for (int i = 0; encontrado == 0; i++) {
        int menos = 4500;
        grafo[i].visitado = true;
        cout << "I:" << i << " NODO: " << grafo[i].nodo << endl;
        
        
        
        if (grafo[i].nodo == ciudad_final) {
            sigue_buscando = false;
            if (grafo[i].funcion < optimo) {
                optimo = grafo[i].funcion;
                optimo_iter = i;
            }
                int minimo = optimo, xx;
                for (int x = 0; x < grafo.size(); x++) {
                    if (grafo[x].visitado == false) {
                        cout << grafo[x].funcion << " ---- " << minimo << endl;
                    }
                    
                    if (grafo[x].funcion < minimo && grafo[x].visitado == false) {
                        cout << "COSTE DE: " << grafo[x].funcion << " es menor que " << minimo << endl;
                        minimo = grafo[x].funcion;
                        i = x;
                        xx = x;
                        sigue_buscando = true;
                        grafo[i].visitado = true;
                        cout << "TE MANDO AL NODO: " << grafo[x].nodo << endl;
                        //analizados++;
                    }
                }
        }
        
        
        
        
        
        
        
       /* if (grafo[i].nodo != ciudad_final && optimo != 4500) {
            if (grafo[i].funcion > grafo[optimo_iter].funcion) {
                sigue_buscando = false;
                cout << "ENTRÓ" << endl;
                //if (grafo[i].funcion < optimo) {
                    int minimo = optimo, xx;
                    for (int x = 0; x < grafo.size(); x++) {
                        if (grafo[x].funcion < minimo && grafo[x].visitado == false) {
                            cout << "2. TE MANDO AL NODO: " << grafo[x].nodo << endl;
                            minimo = grafo[x].funcion;
                            i = x;
                            xx = x;
                            sigue_buscando = true;
                            grafo[i].visitado = true;
                            //analizados++;
                        }
                    }
                //}
            }
        }*/
        
        
        
        
        
        
        if (sigue_buscando == true) {
            analizados++;
            for (int j = 0; j < LISTA[grafo[i].nodo].a_que_ciudades_puede_ir.size(); j++) {
                datos aux;
                g = 0;
                aux.funcion = 0;
                se_pone = true;
                rama = LISTA[grafo[i].nodo].a_que_ciudades_puede_ir[j];
                rama2 = i;
                if (rama == ciudad_inicial) {
                    se_pone = false;
                } else {
                    aux.listadepredecesores.push_back(grafo[rama2].nodo);
                    while (rama2 != grafo[0].ciudadpadre) {
                        rama2 = grafo[rama2].ciudadpadre;
                        if (rama == grafo[rama2].nodo) {
                            se_pone = false;
                        }
                        aux.listadepredecesores.push_back(grafo[rama2].nodo);
                    }
                }
                if (se_pone == true) {
                    h = LISTA[LISTA[grafo[i].nodo].a_que_ciudades_puede_ir[j]].prediccion[ciudad_final-1];
                    int rec = i, rec2 = i;
                    g = g + LISTA[grafo[i].nodo].kilometros[j];
                    while (rec != 0) {
                        rec = grafo[rec].ciudadpadre;
                        for (int k = 0; k < LISTA[grafo[rec].nodo].a_que_ciudades_puede_ir.size(); k++) {
                            if (LISTA[grafo[rec].nodo].a_que_ciudades_puede_ir[k] == grafo[rec2].nodo) {
                                g = g + LISTA[grafo[rec].nodo].kilometros[k];
                            }
                        }
                        rec2 = grafo[rec2].ciudadpadre;
                    }
                    aux.funcion = f(g, h);
                    aux.visitado = false;
                    aux.ciudadpadre = i;
                    aux.nodo = LISTA[grafo[i].nodo].a_que_ciudades_puede_ir[j];
                    grafo.push_back(aux);
                    grafo[i].aqueciudadespuedeir.push_back(LISTA[grafo[i].nodo].a_que_ciudades_puede_ir[j]);
                    if (aux.funcion < menos) {
                        menos = aux.funcion;
                        siguiente = grafo.size()-1;
                    }
                }
            }
            i = siguiente;
            i--;
        } else{
            encontrado = 1;
            final.nodo = grafo[optimo_iter].nodo;
            final.listadepredecesores = grafo[optimo_iter].listadepredecesores;
            final.aqueciudadespuedeir = grafo[optimo_iter].aqueciudadespuedeir;
            final.funcion = grafo[optimo_iter].funcion;
        }
    }
    if (encontrado == 1) {
        deque<int> mostrar;
        mostrar.push_front(final.nodo);
        for (int i = 0; i < final.listadepredecesores.size(); i++) {
            mostrar.push_front(final.listadepredecesores[i]);
        }
        for (int i = 0; i < mostrar.size(); i++) {
            cout << mostrar[i] << " - ";
        }
        cout << " || Costo: " << final.funcion << " .Nodos Generados: " << grafo.size() << "  .Nodos analizados: " <<  analizados+1 << endl;
        cout << endl;
    } else {
        cout << " ERROR: NO SE HA ENCONTRADO EL NODO!!!!!" << endl;
    }
}

int main()
{
    int inicial, final;
    char nombredefichero1[]= "MatrizAdyacencia.txt";
    char nombredefichero2[]= "MatrizCostos.txt";
    char nombredefichero3[]= "MatrizEvaluacionHeuristica.txt";
    MAPA mapa(nombredefichero1, nombredefichero2, nombredefichero3);
    cout << "Introduce el nodo inicial: " << endl;
    cin >> inicial;
    cout << "Introduce el nodo final: " << endl;
    cin >> final;
    cout << "AMPLITUD:*********************************************** " << endl;
    mapa.Amplitud(inicial, final);
    MAPA mapa1(nombredefichero1, nombredefichero2, nombredefichero3);
    cout << "PROFUNDIDAD: *******************************************" << endl;
    mapa1.Profundidad(inicial, final);
    MAPA mapa2(nombredefichero1, nombredefichero2, nombredefichero3);
    cout << "A ESTRELLA: ********************************************" << endl;
    mapa2.A_estrella(inicial, final);
}

