#ifndef MODOAUTOMATICO_H_
#define MODOAUTOMATICO_H_

#include <fstream>
#include <string>
#include "Matriz.h"
#include "Nodo.h"
#include "Algoritmo_A.h"

using namespace std;

class ModoAutomatico
{
public:

	ModoAutomatico(string rutaFichero) : _rutaFichero(rutaFichero){
		iniciar();
	}
	~ModoAutomatico(){}

	void iniciar() {
		ifstream fichero;
		fichero.open(_rutaFichero);
		if (fichero.is_open()) {
			size_t X, Y;
			fichero >> X >> Y;
			Matriz<Nodo> tablero(X, Y);
			for (size_t i = 0; i < tablero.numfils(); i++) {
				for (size_t j = 0; j < tablero.numcols(); j++) {
					tablero[i][j] = Nodo(i, j);
				}
			}
			fichero >> X >> Y;
			Nodo origen(X, Y, 'A');
			tablero[origen] = origen;
			fichero >> X >> Y;
			Nodo destino(X, Y, 'B');
			tablero[destino] = destino;

			while (!fichero.eof()) {
				fichero >> X >> Y;
				Nodo obs(X, Y, 'X');
				tablero[obs] = obs;
			}
			fichero.close();
			cout << termcolor::green << "Fichero importado correctamente." << termcolor::reset << endl;
			system("pause");

			Algoritmo_A alg(tablero, origen, destino);

			if (alg.existeSolucion()) {
				list<Nodo*> camino = alg.mejorCamino();
				double tiempoEjecucion = alg.tiempoEjecucion();
				int i = 0;
				string rutaFichero = "";
				int op = -1;
				while (op != 0) {
					system("cls");
					cout << termcolor::red << "   Algoritmo A* - Modo Automatico" << endl;
					cout << "-------------------------------------" << endl;
					cout << termcolor::green << "Existe solucion. Tiempo de ejecucion: " << tiempoEjecucion << " s" << endl;
					cout << termcolor::cyan << "1. Mostrar solucion" << endl
						<< "2. Mostrar solucion paso a paso" << endl
						<< "0. Salir" << endl
						<< termcolor::reset << "Opcion: ";
					cin >> op;

					switch (op) {
					case 1:
						for (auto it = camino.cbegin(); it != camino.cend(); it++) {
							tablero[**it].tipo = 'O';
						}
						system("cls");
						cout << termcolor::red << "   Algoritmo A* - Modo Automatico" << endl;
						cout << "-------------------------------------" << endl;
						tablero.imprimirMatriz();
						system("pause");
						for (auto it = camino.cbegin(); it != camino.cend(); it++) {
							tablero[**it].tipo = '\0';
						}
						break;
					case 2:
						system("cls");
						cout << termcolor::red << "   Algoritmo A* - Modo Automatico" << endl;
						cout << "-------------------------------------" << endl;
						tablero.imprimirMatriz();
						cout << termcolor::cyan << "Num. Iteracion: " << i << termcolor::reset << endl;
						system("pause");
						i++;
						for (auto it = camino.cbegin(); it != camino.cend(); it++) {
							tablero[**it].tipo = 'O';
							system("cls");
							cout << termcolor::red << "   Algoritmo A* - Modo Automatico" << endl;
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
					default:
						break;
					}
				}
				return;
			}
			else {
				system("cls");
				cout << termcolor::red << "   Algoritmo A* - Modo Automatico" << endl;
				cout << "-------------------------------------" << endl;
				cout << termcolor::reset << "No es posible alcanzar ninguna solución." << endl;
				system("pause");
			}

		}
		else {
			system("cls");
			cout << termcolor::red << "   Algoritmo A* - Modo Automatico" << endl;
			cout << "-------------------------------------" << endl;
			cout << termcolor::green << "ERROR DE LECTURA. El fichero no se ha podido abrir o no existe." << termcolor::reset << endl;
			system("pause");
		}
	}

private:

	string _rutaFichero;

};


#endif MODOAUTOMATICO_H_