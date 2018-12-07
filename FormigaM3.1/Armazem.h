#pragma once
#define CAMINHO_PAREDE 0
#define CAMINHO_LIVRE 1


#define TAMANHO_ARMAZEM_LINHA 4
#define TAMANHO_ARMAZEM_COLUNA 3

//Struct principal dos armazens
struct armazens {
	int armazens_comida[4][3] = { 13,0,0,12,0,0,11,0,0,10,0,0 };
	bool status = false;
	int Comida = 0;
	int indice_comida_i = 0;
	int indice_comida_j = 0;
	int comida_encontrada = 0;
	int menorComida = 100;
};

//Sorteio da posição de cada um dos armazens
void sorteia_armazem(mapa &mapa, armazens &a) {
	int contador = 5, x = 0, y = 0;
	srand(time(NULL));
	while (contador < 8) {
		x = rand() % mapa.linha;
		y = rand() % mapa.coluna;
		if ((contador == 6 and mapa.matriz[x][y] == CAMINHO_PAREDE) && (mapa.matriz[x + 1][y] == CAMINHO_LIVRE or mapa.matriz[x - 1][y] == CAMINHO_LIVRE or mapa.matriz[x][y + 1] == CAMINHO_LIVRE or mapa.matriz[x][y -1 ] == CAMINHO_LIVRE)) {
			mapa.matriz[x][y] = contador;
			contador++;
		}
		else if ((mapa.matriz[x][y] == CAMINHO_PAREDE) && (mapa.matriz[x + 1][y] == CAMINHO_LIVRE or mapa.matriz[x - 1][y] == CAMINHO_LIVRE or mapa.matriz[x][y + 1] == CAMINHO_LIVRE or mapa.matriz[x][y - 1] == CAMINHO_LIVRE)) {
			mapa.matriz[x][y] = contador;
			contador++;
		}
	}
}

//Captura o indice da comida pegue ou entregue
bool indiceComida(armazens &a, int pino, controle_ &c) {
	for (int i = TAMANHO_ARMAZEM_LINHA - 1; i >= 0; i--) {
		if (a.armazens_comida[i][pino] != 0) {
			a.comida_encontrada = a.armazens_comida[i][pino];
			a.indice_comida_i = i;
			a.indice_comida_j = pino;
			return true;
		}
	}
	return false;
}

//Função executada para pegar a comida
bool pegarComida(armazens &a, int pino, controle_ c) {
	pino -= 5;
	if (indiceComida(a, pino, c) == true) {
		a.Comida = a.armazens_comida[a.indice_comida_i][a.indice_comida_j];
		a.status = true;
		a.armazens_comida[a.indice_comida_i][a.indice_comida_j] = 0;
		return true;
	}
	return false;
}

//Função executada para entregar a comida
bool entregarComida(armazens &a, int pino, controle_ c) {
	pino -= 5;
	if (a.armazens_comida[0][pino] == 0) {
		a.armazens_comida[0][pino] = a.Comida;
		a.Comida = 0;
		a.status = false;
		return true;
	}
	else {
		if (indiceComida(a, pino, c) == true) {
			if (a.comida_encontrada > a.Comida) {
				a.armazens_comida[a.indice_comida_i + 1][a.indice_comida_j] = a.Comida;
				a.Comida = 0;
				a.status = false;
				return true;
			}
		}
	}
	return false;
}

//Verifica se o jogo esta apto a ser encerrado
bool checkFimGame(armazens a){
	if (a.armazens_comida[0][1] != 0 and a.armazens_comida[1][1] != 0 and a.armazens_comida[2][1] != 0 and a.armazens_comida[3][1] != 0) 
		return true;
	else if (a.armazens_comida[0][2] != 0 and a.armazens_comida[1][2] != 0 and a.armazens_comida[2][2] != 0 and a.armazens_comida[3][2] != 0) 
		return true;
	else 
		return false;
}

//Verifica qual a menor comida do armazem em questão
void menorComida(armazens &a, int pino) {
	a.menorComida = 100;
	for (int i = 0; i < TAMANHO_ARMAZEM_LINHA; i++) {
		if (a.armazens_comida[i][pino] <= a.menorComida and a.armazens_comida[i][pino] != 0) {
			a.menorComida = a.armazens_comida[i][pino];
		}
	}
}