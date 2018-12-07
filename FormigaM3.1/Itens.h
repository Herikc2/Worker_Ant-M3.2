#pragma once

struct itens_ {
	int pa = 0;
	int bota = 0;
	int tocha = 0;
	int kit = 0;
	int USOS_PA = 0;
	int VELOCIDADE_FORMIGA = 100;
	int USOS_BOTA = 0;
	int VELOCIDADE_EVENTO = 40000;
	int USOS_KIT = 0;
	int dificuldade = 1;
	int verificador = 0;
};

//Função onde todos os itens serão sorteados
void sorteador_itens(itens_ i, mapa &mapa) {
	srand(time(NULL));
	int contador = 20, x = 0, y = 0;
	while (contador < 24) {
		x = rand() % mapa.linha;
		y = rand() % mapa.coluna;
		if (mapa.matriz[x][y] == 1) {
			mapa.matriz[x][y] = contador;
			contador++;
		}
	}
}

//Abaixo segue as funções individuais de cada um dos itens
void pa(itens_ &i, int aux) {
	if (aux == 0) {
		i.pa = 1;
		i.USOS_PA = 30;
	}
	else if (aux == 1) {
		i.USOS_PA--;
		if (i.USOS_PA == 0) 
			i.pa = 0;
	}
}

void velocidade(itens_ &i, int aux) {
	if (aux == 0) {
		i.USOS_BOTA++;
		i.VELOCIDADE_FORMIGA = 50;
	}
	else if (aux == 1) {
		i.USOS_BOTA--;
		i.VELOCIDADE_FORMIGA = 100;
	}
}

void luz(itens_ &i, int aux, controle_ c) {
	if (aux == 0) 
		c.USOS_TOCHA++;
	else if (aux == 1) 
		c.USOS_TOCHA--;
}

void kit(itens_ &i, int aux) {
	if (aux == 0) {
		i.verificador = 1;
		i.USOS_KIT++;
		if (i.dificuldade == 0)
			i.VELOCIDADE_EVENTO = 120000;
		else if (i.dificuldade == 1)
			i.VELOCIDADE_EVENTO = 80000;
		else if (i.dificuldade == 2)
			i.VELOCIDADE_EVENTO = 40000;
	}
	else if (aux == 1) {
		i.USOS_KIT--;
		if (i.dificuldade == 0)
			i.VELOCIDADE_EVENTO = 60000;
		else if (i.dificuldade == 1)
			i.VELOCIDADE_EVENTO = 40000;
		else if (i.dificuldade == 2)
			i.VELOCIDADE_EVENTO = 20000;
	}
}