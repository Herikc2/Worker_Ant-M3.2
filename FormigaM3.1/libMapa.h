#pragma once
#include <fstream>
#include "time.h"
#include "thread"
#include "string"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include "string"
#include "vector"
#include "unordered_map"
#include "queue"
#include "cstdlib"
#include "ctime"
#include "algorithm"
#include "stack"
#include <list>

#define TAMANHO_MINIMO_LINHA 15
#define TAMANHO_LIMITE_LINHA 33
#define TAMANHO_MINIMO_COLUNA 12
#define TAMANHO_LIMITE_COLUNA 22

using namespace std;

//Struct do mapa
typedef struct mapa {
	int **matriz = NULL;
	int coluna = 0, linha = 0;
};

//Função que irá gerar mapa dinâmico, com tamanho também dinâmico
void gerador_mapa(mapa &mapa, bool aux)
{
	//0 É PAREDE E 1 CAMINHO
	if (aux == true) {
		srand(time(NULL));
		do {
			mapa.coluna = (rand() % 20) + 10;
			mapa.linha = (rand() % 15) + 10;
		} while (mapa.coluna > TAMANHO_LIMITE_COLUNA or mapa.linha > TAMANHO_LIMITE_LINHA or mapa.coluna < TAMANHO_MINIMO_COLUNA or mapa.linha < TAMANHO_MINIMO_LINHA);
	}
	list < pair < int, int> > drillers;
	mapa.matriz = new int *[mapa.linha];

	for (size_t y = 0; y < mapa.linha; y++)
		mapa.matriz[y] = new int[mapa.coluna];

	for (size_t x = 0; x < mapa.coluna; x++)
		for (size_t y = 0; y < mapa.linha; y++)
			mapa.matriz[y][x] = false;

	if (aux == true) {
		drillers.push_back(make_pair(mapa.coluna / 2, mapa.linha / 2));
		while (drillers.size() > 0)
		{
			list < pair < int, int> >::iterator m, _m, temp;
			m = drillers.begin();
			_m = drillers.end();
			while (m != _m)
			{
				bool remove_driller = false;
				switch (rand() % 4)
				{
				case 0:
					(*m).second -= 2;
					if ((*m).second < 0 || mapa.matriz[(*m).second][(*m).first])
					{
						remove_driller = true;
						break;
					}
					mapa.matriz[(*m).second + 1][(*m).first] = true;
					break;
				case 1:
					(*m).second += 2;
					if ((*m).second >= mapa.linha || mapa.matriz[(*m).second][(*m).first])
					{
						remove_driller = true;
						break;
					}
					mapa.matriz[(*m).second - 1][(*m).first] = true;
					break;
				case 2:
					(*m).first -= 2;
					if ((*m).first < 0 || mapa.matriz[(*m).second][(*m).first])
					{
						remove_driller = true;
						break;
					}
					mapa.matriz[(*m).second][(*m).first + 1] = true;
					break;
				case 3:
					(*m).first += 2;
					if ((*m).first >= mapa.coluna || mapa.matriz[(*m).second][(*m).first])
					{
						remove_driller = true;
						break;
					}
					mapa.matriz[(*m).second][(*m).first - 1] = true;
					break;
				}
				if (remove_driller)
					m = drillers.erase(m);
				else
				{
					drillers.push_back(make_pair((*m).first, (*m).second));
					// uncomment the line below to make the maze easier 
					// if (rand()%2) 
					drillers.push_back(make_pair((*m).first, (*m).second));

					mapa.matriz[(*m).second][(*m).first] = true;
					++m;
				}
			}
		}
		//BORDA INQUEBRAVEL E INACESSIVEL
		for (int i = 0; i < mapa.linha; i++) {
			for (int j = 0; j < mapa.coluna; j++) {
				if (i == 0 || j == 0)
					mapa.matriz[i][j] = 99;
				if (i == mapa.linha - 1 || j == mapa.coluna - 1)
					mapa.matriz[i][j] = 99;
			}
		}
	}
}