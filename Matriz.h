//
//  Matriz.h
//
//  Implementación de matrices (arrays bidimensionales)
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Created by Alberto Verdejo on 26/6/15.
//  Copyright (c) 2015 Alberto Verdejo. All rights reserved.
//

#ifndef MATRIZ_H
#define MATRIZ_H

#include <cstddef>  // size_t
#include <vector>
#include <iostream>
#include "termcolor.hpp"
#include "Nodo.h"

template <typename Object>
class Matriz {
public:
    // crea una matriz con fils filas y cols columnas,
    // con todas sus celdas inicializadas al valor e
    Matriz(size_t fils, size_t cols, Object e = Object()) : datos(fils, std::vector<Object>(cols, e)) {}
    
    // operadores para poder utilizar notación M[i][j]
    std::vector<Object> const& operator[](size_t f) const {
        return datos[f];
    }
    std::vector<Object> & operator[](size_t f) {
        return datos[f];
    }

	Object &operator[](Nodo n) {
		return datos[n.posX][n.posY];
	}
    
    // métodos que lanzan una excepción si la posición no existe
    Object const& at(size_t f, size_t c) const {
        return datos.at(f).at(c);
    }
    Object & at(size_t f, size_t c) { // este método da problemas cuando Object == bool
        return datos.at(f).at(c);
    }
    
    size_t numfils() const { return datos.size(); }
    size_t numcols() const { return numfils() > 0 ? datos[0].size() : 0; }
    
    bool posCorrecta(int f, int c) const {
        return 0 <= f && f < numfils() && 0 <= c && c < numcols();
    }

	bool posCorrecta(const Nodo &n) {
		return 0 <= n.posX && n.posX < numfils() && 0 <= n.posY && n.posY < numcols();
	}

	void imprimirMatriz() {
		for (size_t i = 0; i < numfils(); i++) {
			std::cout << termcolor::cyan << i << " ";
			for (size_t j = 0; j < numcols(); j++) {
				std::cout << termcolor::reset << datos[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << "  ";
		for (size_t i = 0; i < numfils(); i++) {
			std::cout << termcolor::cyan << i << " ";
		}
		std::cout << termcolor::reset << std::endl;
	}
    
private:
    std::vector<std::vector<Object>> datos;
};

#endif

