#include <stdio.h>

enum ficha {
	No_terminado = -1,
	Vacio = 0,
	X = 1,
	O = 2
};

//Esto de arriba es una enumeración lo que hace se crear un nuevo tipo de dato(como int, float, etc)
//pero que los valores que contiene son los de dentro de las llaves
//Internamente es un int y cada valor tiene un entero asociado
//En este caso creamos un tipo ficha que puede ser Vacio, X ó O

/*
enum estado {
	Empate = 0,
	X = 1,
	O = 2
};
//Otra enum para que nos devuelva el estado de la partida.
*/

ficha tablero[3][3];
//Esto es una matriz de 3x3 de variables del tipo ficha

void imprimir();
int min();
int max();
void pensar();
int main();
ficha ganador();

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

int min() {
	ficha e = ganador();
	switch(e) {
		case X:
			return -1;
		case O:
			return 1;
		case Vacio:
			return 0;
	}

	int worst_val = 2;

	int x, y, val;
	for(x = 0; x < 3; ++x) {
		for(y = 0; y < 3; ++y) {
			if(tablero[x][y] == Vacio) {
				tablero[x][y] = X;

				val = max();
				if(val < worst_val) {
					worst_val = val;
				}

				tablero[x][y] = Vacio;
			}
		}
	}

	return worst_val;
}

int max() {
	ficha e = ganador();
	switch(e) {
		case X:
			return -1;
		case O:
			return 1;
		case Vacio:
			return 0;
	}

	int best_val = -2;

	int x, y, val;
	for(x = 0; x < 3; ++x) {
		for(y = 0; y < 3; ++y) {
			if(tablero[x][y] == Vacio) {
				tablero[x][y] = O;

				val = min();
				if(val > best_val) {
					best_val = val;
				}

				tablero[x][y] = Vacio;
			}
		}
	}

	return best_val;
}

void pensar() {
	int best_val = -2;
	int best_x, best_y;

	int x, y, val;
	for(x = 0; x < 3; ++x) {
		for(y = 0; y < 3; ++y) {
			if(tablero[x][y] == Vacio) {
				tablero[x][y] = O;

				val = min();
				if(val > best_val) {
					best_val = val;
					best_x = x;
					best_y = y;
				}

				tablero[x][y] = Vacio;
			}
		}
	}

	tablero[best_x][best_y] = O;
}

int main() {
	//A continuación vaciamos el tablero
	int x, y;
	for(x = 0; x < 3; ++x) {
		for(y = 0; y < 3; ++y) {
			tablero[x][y] = Vacio;
		}
	}

	puts("Tres en Raya");

	//El siguiente bucle continua mientras la partida no este terminada
	while(ganador() == No_terminado) {
		imprimir();
		puts("Le toca a usted. Escriba coordenadas [x y]");
		scanf("%i %i", &x, &y);
		//scanf toma la entrada escrita
		//y la guarda atendiendo al formata en que se escribe en las variables

		//En este bucle se entra si la casilla elegida esta ocupada y no se sale de el hasta que se proporcione una casilla vacia

		while((x < 0 || x > 2 || y < 0 || y > 2) || tablero[x][y] != Vacio))
		{
			puts("Esas coordenadas no son validas");
			scanf("%i %i", &x, &y);
		}


		tablero[x][y] = X;	//Colocamos ficha

		//Si con este movimiento se termina la partida nos salimos del bucle
		if(ganador() != No_terminado) {
			break;
		}
		
		imprimir();
		puts("Le toca a la máquina");

		pensar(); //La maquina coloca
	}

	ficha g = ganador();

	puts("---");
	imprimir();
	puts("---");

	switch(g) {
		case Vacio: 
			puts("-------------");
			puts("Nadie gana!!!");
			puts("-------------");
			break;
		case X:
			puts("------------");
			puts("Enhorabuena!");
			puts("------------");
			break;
		case O:
			puts("------------");
			puts("EXTERMINATE!");
			puts("------------");
			break;
		default:
			puts("------------");
			puts("WTF!!!!!!!!!");
			puts("------------");
	}

	return 0;
}

ficha ganador()
{	
	//Comprobamos diagonal izquierda
	if (tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2])
	{
		if (tablero[1][1] != Vacio)
			return tablero[1][1];
		else
			return No_terminado;
	}

	//Comprobamos diagonal derecha
	if (tablero[2][0] == tablero[1][1] && tablero[1][1] == tablero[0][2])
	{
		if (tablero[1][1] != Vacio)
			return tablero[1][1];
		else
			return No_terminado;
	}
	// Comprobamos filas
	for(int i = 0; i<3; i++)
	{
		if (tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2])
		{
			if (tablero[i][1] != Vacio)
				return tablero[i][1];
		}

	}
	
	//Comprobamos columnas
	for(int i = 0; i<3; i++)
	{
		if (tablero[0][i] == tablero[1][i] && tablero[1][i] == tablero[2][i])
		{
			if (tablero[1][i] != Vacio)
				return tablero[1][i];
		}

	}

	//Comprobamos si quedan jugadas posibles
	for(int i = 0; i<3; i++)
	{
		for(int j = 0; j<3; j++)
			if (j == 0)
				return No_terminado;
	}

	return Vacio; //Significa empate
}
