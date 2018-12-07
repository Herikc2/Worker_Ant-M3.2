#pragma once
#include "Itens.h"

//Struct usada para exibição de tempo
struct relogio {
	char minuto_principal_char[256];
	char segundo_principal_char[256];
	int minuto_principal = 0;
	int segundo_principal = 0;
	clock_t tempo_inicial_principal = 0;
	clock_t tempo_final_principal = 0;
	double tempo_exe_principal = 0;
	int tempo_terremoto = 0;
};


//Função de tempo
void tempo_converte(int tempo_total_segundos, relogio &r) {
	int minuto = tempo_total_segundos / 60;
	int segundo = tempo_total_segundos % 60;

	r.minuto_principal = minuto;
	r.segundo_principal = segundo;
}

//Função que controla o tempo e informações do menu superior
void controle_de_tempo_principal(relogio &r, controle_ c, itens_ i, bool aux) {
	if (aux == true) 
		r.tempo_inicial_principal = clock();
	else {
		r.tempo_final_principal = clock();
		r.tempo_exe_principal += ((r.tempo_final_principal - r.tempo_inicial_principal) / (double)CLOCKS_PER_SEC);
		r.tempo_terremoto -= (r.tempo_final_principal - r.tempo_inicial_principal) / (double)CLOCKS_PER_SEC;
		tempo_converte(r.tempo_exe_principal, r);
	}
}