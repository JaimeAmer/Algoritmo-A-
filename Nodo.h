#ifndef NODO_H_
#define NODO_H_

class Nodo {
public:
	size_t posX, posY;
	Nodo* padre;

	Nodo() : posX(0), posY(0), padre(NULL){}
	Nodo(size_t x, size_t y) : posX(x), posY(y), padre(NULL){}
	~Nodo(){}

	

	bool operator==(const Nodo b) {
		return posX == b.posX && posY == b.posY;
	}

	bool operator!=(const Nodo b) {
		return !(*this == b);
	}

};

#endif NODO_H_