#include <iostream>
#include <fstream>
#include <string>
#include "termcolor.hpp"
#include "ModoInteractivo.h"
#include "ModoAutomatico.h"

using namespace std;

void initApplication() {
	int opcion = -1;
	string rutaFichero = "";

	while (opcion != 0) {
		system("cls");
		cout << termcolor::red << "   Bienvenido al Algoritmo A*" << endl;
		cout << "-------------------------------------" << endl;
		cout << termcolor::cyan << "1. Modo Interactivo" << endl;
		cout << "2. Modo Automatico" << endl;
		cout << "0. Salir" << endl;
		cout << termcolor::reset << "Seleccione modo: ";
		cin >> opcion;
		switch (opcion) {
		case 0:
			break;
		case 1:
			ModoInteractivo();
			opcion = -1;
			break;
		case 2:
			system("cls");
			cout << termcolor::red << "   Algoritmo A* - Modo Automatico" << endl;
			cout << "-------------------------------------" << endl;
			cout << termcolor::reset << "Introduce nombre o ruta del fichero: ";
			cin >> rutaFichero;
			ModoAutomatico MA(rutaFichero);
			rutaFichero = "";
			break;
		}
	}

}


int main(int argc, char **argv) {

	if (argc == 2) {
		ModoAutomatico MA(argv[1]);
	}
	else initApplication();

	return 0;
}

