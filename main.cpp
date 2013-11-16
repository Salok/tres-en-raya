#include <stdio.h>

enum ficha {
	Vacio = 0,
	X = 1,
	O = 2
}
//Esto de arriba es una enumeración lo que hace se crear un nuevo tipo de dato(como int, float, etc)
//pero que los valores que contiene son los de dentro de las llaves
//Internamente es un int y cada valor tiene un entero asociado
//En este caso creamos un tipo ficha que puede ser Vacio, X ó O

ficha tablero[3][3];
//Esto es una matriz de 3x3 de variables del tipo ficha

enum jugador {
	Humano,
	Maquina
}
//Otro enum para representar a uno de los jugadores

jugador turno;

//Esta función imprime el tablero por pantalla
void imprimir() {
	const char simbolo_ficha[3] = {'.', 'X', 'O'};
	//Esto es un array en el que aparecen las representaciones de las fichas

	int x, y;
	ficha f;
	for(x = 0; x < 3; ++x) {
		for(y = 0; y < 3; ++y) {
			//Estos bucles mueven x e y por todas las coordenadas de la matriz
			f = tablero[x][y];
			//f es la ficha en cada coordenada
			putchar(simbolo_ficha[f]);
			//putchar sirve para imprimir un solo caracter en pantalla
		}
		putchar('\n');
		//el caracter '\n' significa salto de linea
	}
}

int main() {
	//A continuación vaciamos el tablero
	int x, y;
	for(x = 0; x < 3; ++x) {
		for(y = 0; y < 3; ++y) {
			tablero[x][y] = Vacio;
		}
	}

	imprimir();

	return 0;
}