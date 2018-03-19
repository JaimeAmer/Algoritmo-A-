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
			for (auto it = camino.cbegin(); it != camino.cend(); it++) {
				tablero[**it].tipo = 'O';
				tablero.imprimirMatriz();
				system("pause");
			}
		}
		system("pause");
	}

	~ModoInteractivo() {}

private:

};

#endif MODOINTERACTIVO_H_
