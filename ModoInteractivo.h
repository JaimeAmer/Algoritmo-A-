#ifndef MODOINTERACTIVO_H_
#define MODOINTERACTIVO_H_

#include <iostream>
#include <string>
#include "Algoritmo_A.h"
#include "Matriz.h"
#include "termcolor.hpp"
#include "Nodo.h"

using namespace std;

class ModoInteractivo {
public:
	ModoInteractivo() {
		iniciar();
	}

	void iniciar() {
		string dimensionTablero = "";
		while (dimensionTablero.size() != 3) {
			system("cls");
			cout << termcolor::red << "   Algoritmo A* - Modo Interactivo" << endl;
			cout << "-------------------------------------" << endl;
			cout << termcolor::reset << "Inserte dimensiones de la tabla (AxB): ";
			cin >> dimensionTablero;

		}
		int X = dimensionTablero[0] - '0';
		int Y = dimensionTablero[2] - '0';
		Matriz<Nodo> tablero(X, Y);
		for (size_t i = 0; i < tablero.numfils(); i++) {
			for (size_t j = 0; j < tablero.numcols(); j++) {
				tablero[i][j] = Nodo(i, j);
			}
		}
		
		X = Y = -1;
		while (!tablero.posCorrecta(X,Y)) {
			system("cls");
			cout << termcolor::red << "   Algoritmo A* - Modo Interactivo" << endl;
			cout << "-------------------------------------" << endl;
			tablero.imprimirMatriz();
			cout << termcolor::reset << "Inserte posición de origen (A B): ";
			cin >> X >> Y;
		}
		Nodo origen(X, Y, 'A');
		tablero[origen] = origen;
		tablero.imprimirMatriz();
		
		X = Y = -1;
		while (!tablero.posCorrecta(X, Y) && origen != Nodo(X,Y)) {
			system("cls");
			cout << termcolor::red << "   Algoritmo A* - Modo Interactivo" << endl;
			cout << "-------------------------------------" << endl;
			tablero.imprimirMatriz();
			cout << termcolor::reset << "Inserte posición de destino (A B): ";
			cin >> X >> Y;
		}

		Nodo destino(X, Y, 'B');
		tablero[destino] = destino;
		tablero.imprimirMatriz();

		bool pedirObstaculos = true;

		while (pedirObstaculos) {
			system("cls");
			cout << termcolor::red << "   Algoritmo A* - Modo Interactivo" << endl;
			cout << "-------------------------------------" << endl;
			tablero.imprimirMatriz();
			cout << termcolor::reset << "Inserte posición del obstáculo (" << destino.posX << " " << destino.posY << " para terminar): ";
			cin >> X >> Y;

			if (Nodo(X, Y) == destino) {
				pedirObstaculos = false;
			}
			else if (Nodo(X, Y) != origen) {
				Nodo obs(X, Y, 'X');
				tablero[obs] = obs;
			}

		}

		Algoritmo_A alg(tablero, origen, destino);
		

		if (alg.existeSolucion()){
			list<Nodo*> camino = alg.mejorCamino();
			double tiempoEjecucion = alg.tiempoEjecucion();
			int i = 0;
			string rutaFichero = "";
			int op = -1;
			while (op != 0) {
				system("cls");
				cout << termcolor::red << "   Algoritmo A* - Modo Interactivo" << endl;
				cout << "-------------------------------------" << endl;
				cout << termcolor::green << "Existe solucion. Tiempo de ejecucion: " << tiempoEjecucion << " s" << endl;
				cout << termcolor::cyan << "1. Mostrar solucion" << endl
					<< "2. Mostrar solucion paso a paso" << endl
					<< "3. Exportar fichero del tablero" << endl
					<< "0. Salir al menu principal" << endl
					<< termcolor::reset << "Opcion: ";
				cin >> op;

				switch (op) {
				case 1: 
					for (auto it = camino.cbegin(); it != camino.cend(); it++) {
						tablero[**it].tipo = 'O';
					}
					system("cls");
					cout << termcolor::red << "   Algoritmo A* - Modo Interactivo" << endl;
					cout << "-------------------------------------" << endl;
					tablero.imprimirMatriz();
					system("pause");
					for (auto it = camino.cbegin(); it != camino.cend(); it++) {
						tablero[**it].tipo = '\0';
					}
					break;
				case 2:
					system("cls");
					cout << termcolor::red << "   Algoritmo A* - Modo Interactivo" << endl;
					cout << "-------------------------------------" << endl;
					tablero.imprimirMatriz();
					cout << termcolor::cyan << "Num. Iteracion: " << i << termcolor::reset << endl;
					system("pause");
					i++;
					for (auto it = camino.cbegin(); it != camino.cend(); it++) {
						tablero[**it].tipo = 'O';
						system("cls");
						cout << termcolor::red << "   Algoritmo A* - Modo Interactivo" << endl;
						cout << "-------------------------------------" << endl;
						tablero.imprimirMatriz();
						cout << termcolor::cyan << "Num. Iteracion: " << i << termcolor::reset << endl;
						system("pause");
						i++;
					}
					for (auto it = camino.cbegin(); it != camino.cend(); it++) {
						tablero[**it].tipo = '\0';
					}
					break;
				case 3:
					system("cls");
					cout << termcolor::red << "   Algoritmo A* - Modo Interactivo" << endl;
					cout << "-------------------------------------" << endl;
					cout << termcolor::reset << "Introduce nombre o ruta del fichero: ";
					cin >> rutaFichero;
					if (alg.exportarFichero(rutaFichero))
						cout << termcolor::green << "Fichero exportado correctamente." << termcolor::reset << endl;
					else cout << termcolor::red << "Ha habido un error al exportar el fichero" << termcolor::reset << endl;
					system("pause");
					break;
				default:
					break;
				}
			}
			return;
		}
		else {
			system("cls");
			cout << termcolor::red << "   Algoritmo A* - Modo Interactivo" << endl;
			cout << "-------------------------------------" << endl;
			cout << termcolor::reset << "No es posible alcanzar ninguna solución." << endl;
			system("pause");
			return;
		}
	}

	~ModoInteractivo() {}

};

#endif MODOINTERACTIVO_H_
