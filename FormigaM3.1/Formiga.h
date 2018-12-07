#pragma once
#include "Itens.h"

#define CAMINHO_LIVRE 1
#define CAMINHO_PAREDE 0
#define FORMIGA_ 2
#define ITEM_PA 20
#define ITEM_BOTA 21
#define ITEM_TOCHA 22
#define ITEM_KIT 23
#define ARMAZEM_CORROMPIDO 5
#define ARMAZEM_1 6
#define ARMAZEM_2 7

//Função a formiga irá sortear onde aparecer
void sorteia_formiga(mapa &mapa, controle_ &c) {
	int x = 0, y = 0, aux = 0;
	srand(time(NULL));

	while (aux == 0) {
		x = rand() % mapa.linha;
		y = rand() % mapa.coluna;
		if ((mapa.matriz[x][y] == CAMINHO_PAREDE) && (mapa.matriz[x + 1][y] == CAMINHO_LIVRE or mapa.matriz[x - 1][y] == CAMINHO_LIVRE or mapa.matriz[x][y + 1] == CAMINHO_LIVRE or mapa.matriz[x][y - 1] == CAMINHO_LIVRE)) {
			mapa.matriz[x][y] = 2;
			aux++;
			c.x_formiga = x;
			c.y_formiga = y;
		}
	}
}

//Função que contém toda lógica de movimentação, provavelmente você terá que inserir a lógica da movimentação do armazém junto aqui
void Movimentacao(mapa &mapa, controle_ &c, int aux_x, int aux_y, itens_ &i, armazens &a) {
	if (mapa.matriz[(c.x_formiga) + aux_x][(c.y_formiga) + aux_y] == CAMINHO_LIVRE) {
		mapa.matriz[(c.x_formiga)][c.y_formiga] = CAMINHO_LIVRE;
		if (a.status == false) {
			mapa.matriz[(c.x_formiga) + aux_x][(c.y_formiga) + aux_y] = FORMIGA_;
		}
		else if (a.status == true) {
			mapa.matriz[(c.x_formiga) + aux_x][(c.y_formiga) + aux_y] = FORMIGA_COM_ALIMENTO;
		}
		c.x_formiga += aux_x;
		c.y_formiga += aux_y;
	}
	else if ((i.pa = 1 and i.USOS_PA > 0) and mapa.matriz[(c.x_formiga) + aux_x][(c.y_formiga) + aux_y] == 0) {
		mapa.matriz[(c.x_formiga)][c.y_formiga] = CAMINHO_LIVRE;
		if (a.status == false) {
			mapa.matriz[(c.x_formiga) + aux_x][(c.y_formiga) + aux_y] = FORMIGA_;
		}
		else if (a.status == true) {
			mapa.matriz[(c.x_formiga) + aux_x][(c.y_formiga) + aux_y] = FORMIGA_COM_ALIMENTO;
		}
		c.x_formiga += aux_x;
		c.y_formiga += aux_y;
		if (c.sfx) 
			al_play_sample(c.pa, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		pa(i, 1);
	}
	else if (mapa.matriz[(c.x_formiga) + aux_x][(c.y_formiga) + aux_y] == ITEM_PA) {
		mapa.matriz[(c.x_formiga)][c.y_formiga] = CAMINHO_LIVRE;
		if (a.status == false) {
			mapa.matriz[(c.x_formiga) + aux_x][(c.y_formiga) + aux_y] = FORMIGA_;
		}
		else if (a.status == true) {
			mapa.matriz[(c.x_formiga) + aux_x][(c.y_formiga) + aux_y] = FORMIGA_COM_ALIMENTO;
		}
		c.x_formiga += aux_x;
		c.y_formiga += aux_y;
		if (c.sfx) 
			al_play_sample(c.pa_pegando, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);	
		pa(i, 0);
	}
	else if (mapa.matriz[(c.x_formiga) + aux_x][(c.y_formiga) + aux_y] == ITEM_BOTA) {
		mapa.matriz[(c.x_formiga)][c.y_formiga] = CAMINHO_LIVRE;
		if (a.status == false) {
			mapa.matriz[(c.x_formiga) + aux_x][(c.y_formiga) + aux_y] = FORMIGA_;
		}
		else if (a.status == true) {
			mapa.matriz[(c.x_formiga) + aux_x][(c.y_formiga) + aux_y] = FORMIGA_COM_ALIMENTO;
		}
		c.x_formiga += aux_x;
		c.y_formiga += aux_y;
		if (c.sfx) 
			al_play_sample(c.bota, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);		
		velocidade(i, 0);
	}
	else if (mapa.matriz[(c.x_formiga) + aux_x][(c.y_formiga) + aux_y] == ITEM_TOCHA) {
		mapa.matriz[(c.x_formiga)][c.y_formiga] = CAMINHO_LIVRE;
		if (a.status == false) {
			mapa.matriz[(c.x_formiga) + aux_x][(c.y_formiga) + aux_y] = FORMIGA_;
		}
		else if (a.status == true) {
			mapa.matriz[(c.x_formiga) + aux_x][(c.y_formiga) + aux_y] = FORMIGA_COM_ALIMENTO;
		}
		c.x_formiga += aux_x;
		c.y_formiga += aux_y;
		if (c.sfx) 
			al_play_sample(c.tocha, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		c.USOS_TOCHA++;
		luz(i, 0, c);
	}
	else if (mapa.matriz[(c.x_formiga) + aux_x][(c.y_formiga) + aux_y] == ITEM_KIT) {
		mapa.matriz[(c.x_formiga)][c.y_formiga] = CAMINHO_LIVRE;
		if (a.status == false) {
			mapa.matriz[(c.x_formiga) + aux_x][(c.y_formiga) + aux_y] = FORMIGA_;
		}
		else if (a.status == true) {
			mapa.matriz[(c.x_formiga) + aux_x][(c.y_formiga) + aux_y] = FORMIGA_COM_ALIMENTO;
		}
		c.x_formiga += aux_x;
		c.y_formiga += aux_y;
		if (c.sfx) 
			al_play_sample(c.kit, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		kit(i, 0);
	}
	else if (mapa.matriz[(c.x_formiga) + aux_x][(c.y_formiga) + aux_y] == ARMAZEM_CORROMPIDO or mapa.matriz[(c.x_formiga) + aux_x][(c.y_formiga) + aux_y] == ARMAZEM_1 or mapa.matriz[(c.x_formiga) + aux_x][(c.y_formiga) + aux_y] == ARMAZEM_2) {
		if (a.status == false) {
			if (pegarComida(a, mapa.matriz[(c.x_formiga) + aux_x][(c.y_formiga) + aux_y], c) == true) {
				if(c.sfx)
					al_play_sample(c.pega_entrega_armazem, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				mapa.matriz[(c.x_formiga)][c.y_formiga] = FORMIGA_COM_ALIMENTO;
				a.status = true;
			}
		}
		else if (a.status == true) {
			if (entregarComida(a, mapa.matriz[(c.x_formiga) + aux_x][(c.y_formiga) + aux_y], c) == true) {
				if(c.sfx)
					al_play_sample(c.pega_entrega_armazem, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				mapa.matriz[(c.x_formiga)][c.y_formiga] = FORMIGA_;
				a.status = false;
			}				
		}
	}
}

//Função que captura as teclas pressionadas, e passa para a função de movimentação validar
void controle_fun(mapa mapa, controle_ &con, itens_ &it, armazens &a, bool aux) {
	con.decorrido = clock();
	while (!al_is_event_queue_empty(con.fila_eventos)) {
		ALLEGRO_EVENT evento;
		//espera ate que algum evento esteja na fila
		al_wait_for_event(con.fila_eventos, &evento);

		//se o evento for pressionar uma tecla
		if (evento.type == ALLEGRO_EVENT_KEY_CHAR) {
			//verifica qual tecla foi pressionada
			switch (evento.keyboard.keycode) {
				//seta para cima
			case ALLEGRO_KEY_UP:
				if (aux == false) {
					if (con.decorrido - con.inicial > it.VELOCIDADE_FORMIGA) {
						Movimentacao(mapa, con, -1, 0, it, a);
						con.lado = 1;
						con.inicial = con.decorrido;
					}
				}
				if (aux == true) {
					con.tecla = 1;
				}
				break;
				//seta para baixo
			case ALLEGRO_KEY_DOWN:
				if (aux == false) {
					if (con.decorrido - con.inicial > it.VELOCIDADE_FORMIGA) {
						Movimentacao(mapa, con, 1, 0, it, a);
						con.lado = 2;
						con.inicial = con.decorrido;
					}
				}
				if (aux == true) {
					con.tecla = 0;
				}
				break;
				//seta para esquerda
			case ALLEGRO_KEY_LEFT:
				if (aux == false) {
					if (con.decorrido - con.inicial > it.VELOCIDADE_FORMIGA) {
						Movimentacao(mapa, con, 0, -1, it, a);
						con.lado = 3;
						con.inicial = con.decorrido;
					}
				}
				if (aux == true) {
					con.tecla = 5;
				}
				break;
				//seta para direita.
			case ALLEGRO_KEY_RIGHT:
				if (aux == false) {
					if (con.decorrido - con.inicial > it.VELOCIDADE_FORMIGA) {
						Movimentacao(mapa, con, 0, 1, it, a);
						con.lado = 4;
						con.inicial = con.decorrido;
					}
				}
				if (aux == true) {
					con.tecla = 4;
				}
				break;
			case ALLEGRO_KEY_ESCAPE:
				if (aux == true) {
					con.tecla = 3;
				}
				break;
			case ALLEGRO_KEY_ENTER:
				if (aux == true) {
					con.tecla = 2;
				}
				break;
			case ALLEGRO_KEY_P:
				con.modo = 2;
			}
		}
	}
}