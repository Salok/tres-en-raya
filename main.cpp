#include <stdio.h>

enum ficha {
	Vacio = 0,
	X = 1,
	O = 2
};

//Esto de arriba es una enumeración lo que hace se crear un nuevo tipo de dato(como int, float, etc)
//pero que los valores que contiene son los de dentro de las llaves
//Internamente es un int y cada valor tiene un entero asociado
//En este caso creamos un tipo ficha que puede ser Vacio, X ó O

enum estado {
	No_terminado = -1,
	Empate = 0,
	X = 1,
	O = 2
};
//Otra enum para que nos devuelva el estado de la partida.

ficha tablero[3][3];
//Esto es una matriz de 3x3 de variables del tipo ficha

enum jugador {
	Humano = 0,
	Maquina = 1
};
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

void pensar() {

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
	imprimir();

	//El siguiente bucle continua mientras la partida no este terminada
	while(ganador() == Pendiente) {
		imprimir();
		puts("Le toca a usted. Escriba coordenadas [x y]");
		scanf("%i %i\n", &x, &y);
		//scanf toma la entrada escrita
		//y la guarda atendiendo al formata en que se escribe en las variables

		//En este bucle se entra si la casilla elegida esta ocupada y no se sale de el hasta que se proporcione una casilla vacia
		while(tablero[x][y] != Vacio) {
			puts("Esas coordenadas estan ocupadas");
			scanf("%i %i\n", &x, &y);
		}

		tablero[x][y] = X;	//Colocamos ficha

		//Si con este movimiento se termina la partida nos salimos del bucle
		if(ganador() != Pendiente) {
			break;
		}
		
		imprimir();
		puts("Le toca a la máquina");

		pensar(); //La maquina coloca
	}

	jugador g = ganador();

	switch(g) {
		case Empate: 
			puts('-------------');
			puts('Nadie gana!!!');
			puts('-------------');
			break;
		case X:
			puts('------------');
			puts('Enhorabuena!');
			puts('------------');
			break;
		case O:
			puts('------------');
			puts('EXTERMINATE!');
			puts('------------');
			break;
		default:
			puts('------------');
			puts('WTF!!!!!!!!!');
			puts('------------');
	}

	return 0;
}

int ganador()
{	
	//Comprobamos diagonal izquierda
	if (tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2])
	{
		if (tablero[1][1] != 0)
			return tablero[1][1];
		else
			return estado No_terminado;
	}

	//Comprobamos diagonal derecha
	if (tablero[2][0] == tablero[1][1] && tablero[1][1] == tablero[0][2])
	{
		if (tablero[1][1] != 0)
			return tablero[1][1];
		else
			return estado No_terminado;
	}
	// Comprobamos filas
	for(int i = 0; i<3; i++)
	{
		if (tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2])
		{
			if (tablero[i][1] != 0)
				return tablero[i][1];
		}

	}
	
	//Comprobamos columnas
	for(int i = 0; i<3; i++)
	{
		if (tablero[0][i] == tablero[1][i] && tablero[1][i] == tablero[2][i])
		{
			if (tablero[1][i] != 0)
				return tablero[1][i];
		}

	}

	//Comprobamos si quedan jugadas posibles
	for(int i = 0; i<3; i++)
	{
		for(int j = 0; j<3; j++)
			if (j == 0)
				return estado No_terminado;
	}

return estado Empate;
}
