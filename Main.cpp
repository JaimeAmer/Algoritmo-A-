#include <iostream>
#include <fstream>
#include "termcolor.hpp"
#include "ModoInteractivo.h"

using namespace std;

void initApplication() {
	int opcion = -1;
	

	while (opcion != 0) {
		system("cls");
		cout << termcolor::red << "   Bienvenido al Algoritmo A*" << endl;
		cout << "-------------------------------------" << endl;
		cout << termcolor::blue << "1. Modo Interactivo" << endl;
		cout << "2. Modo Autom�tico" << endl;
		cout << "0. Salir" << endl;
		cout << termcolor::reset << "Seleccione modo: ";
		cin >> opcion;
		switch (opcion) {
		case 0:
			break;
		case 1:
			ModoInteractivo().iniciar();
			break;
		case 2:
			//ModoAutomatico().iniciar();
			break;
		default:
			opcion = -1;
			break;
		}
	}

}


int main() {

	initApplication();

	return 0;
}

