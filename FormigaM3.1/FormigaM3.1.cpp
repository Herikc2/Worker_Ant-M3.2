/*
Integrantes: Herikc Brecher, Alecsandra Tomasi e Wesley Martins

Instituição: Universidade do Vale do Itajaí

Link Repositório GitHub: https://github.com/Herikc2/FormigaM3.1.git

TRABALHO M3.1
*/

#pragma once

#include <stdio.h>
#include <iostream>
#include "sstream"
#include "string"
#include "time.h"
#include "stdlib.h"
#include <windows.h>
#include <fstream>
#include "libMapa.h"
#include "Grafico.h"
#include "Tempo.h"
#include "Armazem.h"
#include "Formiga.h"
#include "Itens.h"
#include "SubControle.h"
#include "telas.h"

#define MODO_MENU 0
#define MODO_JOGAR 1
#define MODO_PAUSE 2
#define MODO_VITORIA 3

int main() {
	mapa m;
	controle_ c;
	itens_ i;
	relogio r;
	armazens a;
	scores s[10];

	//Inicialização Básica de Comandos 
	pre(m, c, a);
	prePontos(s, c, true);

	//Motor do Jogo
	while (!c.sair) {
		al_clear_to_color(al_map_rgb(0, 0, 0));
		if (c.modo == MODO_MENU)
			preMenu(m, c, i, a, r, s);
		if (c.modo == MODO_JOGAR) 	
			if (preJogar(m, c, i, a, r)) 
				c.modo = 3;
		if (c.modo == MODO_PAUSE) 
			prePause(m, c, i, a, r);
		if (c.modo == MODO_VITORIA) { 
			preVitoria(m, c, i, a, r, s);
			break;
		}
		al_flip_display();
	}

	finalizacao(m, c, i, a, r);
	return 0;
}