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
		Matriz<char> tablero(X, Y);
		
		X = Y = -1;
		while (!tablero.posCorrecta(X,Y)) {
			system("cls");
			cout << termcolor::red << "   Algoritmo A* - Modo Interactivo" << endl;
			cout << "-------------------------------------" << endl;
			tablero.imprimirMatriz();
			cout << termcolor::reset << "Inserte posición de origen (A B): ";
			cin >> X >> Y;
		}
		Nodo origen(X, Y);
		tablero[X][Y] = 'A';
		tablero.imprimirMatriz();

		//Nodo destino(X, Y);
		
		X = Y = -1;
		while (!tablero.posCorrecta(X, Y) && origen != Nodo(X,Y)) {
			system("cls");
			cout << termcolor::red << "   Algoritmo A* - Modo Interactivo" << endl;
			cout << "-------------------------------------" << endl;
			tablero.imprimirMatriz();
			cout << termcolor::reset << "Inserte posición de destino (A B): ";
			cin >> X >> Y;
		}

		Nodo destino(X, Y);
		tablero[X][Y] = 'B';
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
				tablero[X][Y] = 'X';
			}

		}

		Algoritmo_A alg(tablero, origen, destino);
		
		if (alg.existeSolucion()){
			list<Nodo> camino = alg.mejorCamino();
			for (list<Nodo>::const_iterator cit = camino.cbegin(); cit != camino.cend(); cit++){
				tablero[cit->posX][cit->posY] = '·';
			}
		}
		tablero.imprimirMatriz();
		system("pause");






		
		

	}

	~ModoInteractivo() {}

private:

	void ejecutarAlgoritmo() {

	}


};

#endif MODOINTERACTIVO_H_
