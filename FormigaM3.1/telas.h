#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>

#define LARGURA_TELA 1000
#define ALTURA_TELA 900

void exibe_menu_tutorial(mapa m, controle_ &c, itens_ i, armazens a);
void exibe_menu_tutorial2(mapa m, controle_ &c, itens_ i, armazens a);
void exibe_menu_tutorial3(mapa m, controle_ &c, itens_ i, armazens a);
void renderizar(mapa mapa, controle_ &c, armazens a);
void reiniciar(mapa &m, controle_ &c, itens_ &i, relogio &r, armazens &a);
void salvar(mapa m, controle_ c, itens_ i, armazens a, relogio r);
void carrega(mapa &m, controle_ &c, itens_ &i, armazens &a, relogio &r);
struct scores;

#include "SubControle.h"

//Função que cria janela dinâmica, de acordo com o tamanho desejado
void mostra_janela(int w, int h, controle_ &c) {
	al_draw_filled_rectangle(LARGURA_TELA / 2 - w / 2 - 5, ALTURA_TELA / 2 - h / 2 - 5, LARGURA_TELA / 2 + w / 2, ALTURA_TELA / 2 + h / 2, al_map_rgb(192, 192, 192));
	al_draw_filled_rectangle(LARGURA_TELA / 2 - w / 2, ALTURA_TELA / 2 - h / 2, LARGURA_TELA / 2 + w / 2 + 5, ALTURA_TELA / 2 + h / 2 + 5, al_map_rgb(64, 64, 64));
	al_draw_filled_rectangle(LARGURA_TELA / 2 - w / 2, ALTURA_TELA / 2 - h / 2, LARGURA_TELA / 2 + w / 2, ALTURA_TELA / 2 + h / 2, al_map_rgb(128, 128, 128));

	al_draw_filled_rounded_rectangle(LARGURA_TELA / 2 + w / 2 - al_get_text_width(c.fonte_10, "ESC") - 5,
		ALTURA_TELA / 2 + h / 2 - al_get_font_ascent(c.fonte_10) - 5,
		LARGURA_TELA / 2 + w / 2 - 1,
		ALTURA_TELA / 2 + h / 2 - 1, 2, 2, al_map_rgba(0, 0, 0, 100));
	al_draw_text(c.fonte_10, al_map_rgba(150, 150, 150, 50),
		LARGURA_TELA / 2 + w / 2 - al_get_text_width(c.fonte_10, "ESC") - 2,
		ALTURA_TELA / 2 + h / 2 - al_get_font_ascent(c.fonte_10) - 3, ALLEGRO_ALIGN_LEFT, "ESC");
}

//Exibe tela de creditos
void exibe_menu_creditos(mapa m, controle_ &c, itens_ i, armazens a) {
	while (c.tecla != 3) {
		controle_fun(m, c, i, a, true);
		mostra_janela(500, 100, c);
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 - 30, ALLEGRO_ALIGN_CENTRE, "Developed by Herikc Brecher, ");
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 - 5, ALLEGRO_ALIGN_CENTRE, "Alecsandra Tomasi and Wesley Martin");
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 + 20, ALLEGRO_ALIGN_CENTRE, "University of the Itajai Valley - Univali");
		al_flip_display();
	}
}

//Sequencia de 4 telas para o tutorial
void exibe_menu_tutorial4(mapa m, controle_ &c, itens_ i, armazens a) {
	c.tecla = 99;
	while (c.tecla != 3) {
		mostra_janela(850, 380, c);
		controle_fun(m, c, i, a, true);
		al_draw_text(c.fonte_30, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 - 175, ALLEGRO_ALIGN_CENTRE, "TOP MENU");
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 - 130, ALLEGRO_ALIGN_CENTRE, "When the game started, at the top ");
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 - 95, ALLEGRO_ALIGN_CENTRE, "the information menu will be located on the screen. ");
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 - 60, ALLEGRO_ALIGN_CENTRE, "In it, time will be displayed, and whether or not you have");
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 - 25, ALLEGRO_ALIGN_CENTRE, " the items.");
		al_draw_text(c.fonte_30, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 + 15, ALLEGRO_ALIGN_CENTRE, "COMMANDS");
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 + 45, ALLEGRO_ALIGN_CENTRE, "Use W / S / A / D to move around. To pick up any item / food, walk");
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 + 80, ALLEGRO_ALIGN_CENTRE, " in its direction, as if it were a path.");
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 + 115, ALLEGRO_ALIGN_CENTRE, "<----------");
		if (c.tecla == 5) {
			exibe_menu_tutorial3(m, c, i, a);
		}
		al_flip_display();
	}
}

void exibe_menu_tutorial3(mapa m, controle_ &c, itens_ i, armazens a) {
	c.tecla = 99;
	while (c.tecla != 3) {
		mostra_janela(850, 380, c);
		controle_fun(m, c, i, a, true);
		al_draw_text(c.fonte_30, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 - 175, ALLEGRO_ALIGN_CENTRE, "FOOD STORES");
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 - 130, ALLEGRO_ALIGN_CENTRE, "Food warehouses are 3.");
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 - 95, ALLEGRO_ALIGN_CENTRE, " Only one starts with food, weight");
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 - 60, ALLEGRO_ALIGN_CENTRE, " of the food, is determined by the color of the leaves.");
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 - 25, ALLEGRO_ALIGN_CENTRE, "The green leaf is the lightest, after purple, orange and ");
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 + 10, ALLEGRO_ALIGN_CENTRE, "red. The warehouses have moss green background.");
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 + 45, ALLEGRO_ALIGN_CENTRE, "If the warehouse does not have food, there will be no ");
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 + 80, ALLEGRO_ALIGN_CENTRE, "representing. The visible leaf will always be the top one. The ");
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 + 115, ALLEGRO_ALIGN_CENTRE, "food that you carry, it will always be green, disregarding the weight.");
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 + 150, ALLEGRO_ALIGN_CENTRE, "<--------->");
		if (c.tecla == 5) { 
			exibe_menu_tutorial2(m, c, i, a);
		}
		else if (c.tecla == 4) {
			exibe_menu_tutorial4(m, c, i, a);
		}
		al_flip_display();
	}
}

void exibe_menu_tutorial2(mapa m, controle_ &c, itens_ i, armazens a) {
	c.tecla = 99;
	while (c.tecla != 3) {
		mostra_janela(850, 380, c);
		controle_fun(m, c, i, a, true);
		al_draw_text(c.fonte_30, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 - 175, ALLEGRO_ALIGN_CENTRE, "HANOI TOWER CHALLENGE");
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 - 130, ALLEGRO_ALIGN_CENTRE, "The challenge of the tower of Hanoi consists ");
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 - 95, ALLEGRO_ALIGN_CENTRE, "to remove the 4 foods from a warehouse A");
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 - 60, ALLEGRO_ALIGN_CENTRE, "and transfer to a single warehouse, B or C.");
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 - 25, ALLEGRO_ALIGN_CENTRE, "The player can keep alternating meals");
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 + 10, ALLEGRO_ALIGN_CENTRE, "between the 3 warehouses. In addition, meals");
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 + 45, ALLEGRO_ALIGN_CENTRE, "have weight. The lighter one always has to");
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 + 80, ALLEGRO_ALIGN_CENTRE, "stay on top of the warehouse.");
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 + 115, ALLEGRO_ALIGN_CENTRE, "<---------->");	
		if (c.tecla == 5) {
			exibe_menu_tutorial(m, c, i, a);
		}
		else if (c.tecla == 4) {
			exibe_menu_tutorial3(m, c, i, a);
		}
		al_flip_display();
	}
}

void exibe_menu_tutorial(mapa m, controle_ &c, itens_ i, armazens a) {
	c.tecla = 99;
	while (c.tecla != 3) {
		mostra_janela(850, 380, c);
		controle_fun(m, c, i, a, true);
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 - 165, ALLEGRO_ALIGN_CENTRE, "You should get the food in the warehouses");
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 - 130, ALLEGRO_ALIGN_CENTRE, "and complete the challenge of the Tower of Hanoi.");
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 - 95, ALLEGRO_ALIGN_CENTRE, "Move using the W / S / A / D keys.");
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 - 60, ALLEGRO_ALIGN_CENTRE, "In the middle of the path may have items or traps");
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 - 25, ALLEGRO_ALIGN_CENTRE, "Boot will make you faster. Pa");
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 + 10, ALLEGRO_ALIGN_CENTRE, "will allow you to break walls. ");
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 + 45, ALLEGRO_ALIGN_CENTRE, "The kit will increase the time that earthquakes occur.");
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 + 80, ALLEGRO_ALIGN_CENTRE, "And the torch will increase your field of view.");
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 + 115, ALLEGRO_ALIGN_CENTRE, "Press P to pause.");
		al_draw_text(c.fonte_20, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 + 150, ALLEGRO_ALIGN_CENTRE, "---------->");		
		if (c.tecla == 4) {
			exibe_menu_tutorial2(m, c, i, a);
		}
		al_flip_display();
	}
}

//Define o status das opções, de acordo com as escolhidas
void status_options(controle_ &c) {
	if (c.music_status) {
		al_set_audio_stream_gain(c.musica_menu, 1.0);
		al_set_audio_stream_gain(c.game, 1.0);
		al_set_audio_stream_gain(c.win, 1.0);
	}
	else {
		al_set_audio_stream_gain(c.musica_menu, 0.0);
		al_set_audio_stream_gain(c.game, 0.0);
		al_set_audio_stream_gain(c.win, 0.0);
	}		
}

//Exibe as opções de jogo
void exibe_opcoes(mapa m, controle_ &c, itens_ i, armazens a, bool aux) {
	c.tecla = 0;
	int tam_menu = 2;
	int imenu = -1;
	char op_menu[2][50] = { "Music: ","Sound Effects: " }; //texto das opcoes do menu
	float y_menu = (3 * ALTURA_TELA / (tam_menu + 3)) - 150;
	float x_menu = LARGURA_TELA / 2;
	float menu_inc = (ALTURA_TELA - y_menu) / tam_menu;
	ALLEGRO_COLOR cor_menu;
	while (c.tecla != 3) {
		if (aux == true) {
			renderizar(m, c, a);
		}
		mostra_janela(400, 180, c);
		controle_fun(m, c, i, a, true);
		status_options(c);
		if (c.tecla == 0) {
			imenu++;
			if (c.sfx) 
				al_play_sample(c.scroll, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);		
			if (imenu == 2)
				imenu = 0;
			c.tecla = 99;
		}
		else if (c.tecla == 1) {
			imenu--;
			if (c.sfx) 
				al_play_sample(c.scroll, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);		
			if (imenu == -1)
				imenu = 1;

			c.tecla = 99;
		}
		else if (c.tecla == 2) {
			if (c.sfx) 
				al_play_sample(c.click, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);	
			if (imenu == 0) {
				if (c.music_status) 
					c.music_status = false;			
				else 
					c.music_status = true;			
			}
			else if (imenu == 1) {
				if (c.sfx)
					c.sfx = false;
				else
					c.sfx = true;
			}
			c.tecla = 99;
		}

		for (int i = 0; i <= tam_menu; i++) {
			if (i == imenu) 
				cor_menu = al_map_rgb(0, 255, 0);	
			else
				cor_menu = al_map_rgb(255, 255, 255);
			al_draw_text(c.fonte_30, cor_menu, x_menu - 190, y_menu + i * menu_inc * 0.3, ALLEGRO_ALIGN_LEFT, op_menu[i]);
			if (i == 0) {
				if (c.music_status==true) 
					al_draw_text(c.fonte_30, cor_menu, x_menu - 100, y_menu + i * menu_inc * 0.3, ALLEGRO_ALIGN_LEFT, "On");				
				else 
					al_draw_text(c.fonte_30, cor_menu, x_menu - 100, y_menu + i * menu_inc * 0.3, ALLEGRO_ALIGN_LEFT, "Off");						
			}
			if (i == 1) {
				if (c.sfx == true)
					al_draw_text(c.fonte_30, cor_menu, x_menu + 5, y_menu + i * menu_inc * 0.3, ALLEGRO_ALIGN_LEFT, "On");
				else
					al_draw_text(c.fonte_30, cor_menu, x_menu + 5, y_menu + i * menu_inc * 0.3, ALLEGRO_ALIGN_LEFT, "Off");
			}
		}
		al_flip_display();
	}
	al_clear_to_color(al_map_rgb(0, 0, 0));
	renderizar(m, c, a);
}

//Altera a dificuldade do jogo
void status_dificuldade(itens_ &i, int aux) {
	if (aux == 0) {
		i.VELOCIDADE_EVENTO = 60000;
		i.dificuldade = 0;
	}
	else if (aux == 1) {
		i.VELOCIDADE_EVENTO = 40000;
		i.dificuldade = 1;
	}
	else if (aux == 2) {
		i.VELOCIDADE_EVENTO = 20000;
		i.dificuldade = 2;
	}
}

//Exibe a tela de dificuldade
void exibe_dificuldade(mapa m, controle_ &c, itens_ &i, armazens a) {
	c.tecla = 0;
	int tam_menu = 3;
	int imenu = -1;
	char op_menu[3][50] = { "EASY","NORMAL","HARD" }; //texto das opcoes do menu
	float y_menu = (3 * ALTURA_TELA / (tam_menu + 3)) - 100;
	float x_menu = LARGURA_TELA / 2;
	float menu_inc = (ALTURA_TELA - y_menu) / tam_menu;
	ALLEGRO_COLOR cor_menu;

	while (c.tecla != 3) {
		mostra_janela(400, 250, c);
		controle_fun(m, c, i, a, true);
		if (c.tecla == 0) {
			imenu++;
			if (c.sfx)
				al_play_sample(c.scroll, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			if (imenu == 3)
				imenu = 0;

			c.tecla = 99;
		}
		else if (c.tecla == 1) {
			imenu--;
			if (c.sfx)
				al_play_sample(c.scroll, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			if (imenu == -1)
				imenu = 2;

			c.tecla = 99;
		}
		else if (c.tecla == 2) {
			if (c.sfx)
				al_play_sample(c.click, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			if (imenu == 0) {
				status_dificuldade(i, 0);
				c.tecla = 3;
			}
			else if (imenu == 1) {
				status_dificuldade(i, 1);
				c.tecla = 3;
			}
			else if (imenu == 2) {
				status_dificuldade(i, 2);
				c.tecla = 3;
			}
		}

		for (int i = 0; i <= tam_menu; i++) {
			if (i == imenu) {
				cor_menu = al_map_rgb(0, 255, 0);
			}
			else
				cor_menu = al_map_rgb(255, 255, 255);
			al_draw_text(c.fonte_30, cor_menu, x_menu, y_menu + i * menu_inc * 0.3, ALLEGRO_ALIGN_CENTRE, op_menu[i]);
			if (imenu == 0) {
				al_draw_text(c.fonte_30, al_map_rgb(0, 0, 0), x_menu, y_menu + 170, ALLEGRO_ALIGN_CENTRE, "Map change: 60 seconds");
			}
			else if (imenu == 1) {
				al_draw_text(c.fonte_30, al_map_rgb(0, 0, 0), x_menu, y_menu + 170, ALLEGRO_ALIGN_CENTRE, "Map change: 40 seconds");
			}
			else if (imenu == 2) {
				al_draw_text(c.fonte_30, al_map_rgb(0, 0, 0), x_menu, y_menu + 170, ALLEGRO_ALIGN_CENTRE, "Map change: 20 seconds");
			}
		}
		al_flip_display();
	}
}

//Exibição do placar do jogo
void exibe_placar(controle_ &c, mapa m, itens_ i, armazens a, scores sc[]) {
	c.tecla = 99;
	char aux[256];
	float y_menu = 3 * ALTURA_TELA / (c.tam_score + 3);
	float x_menu = LARGURA_TELA / 2;
	float menu_inc = (ALTURA_TELA - y_menu) / c.tam_score;
	ALLEGRO_COLOR cor_score;
	cor_score = al_map_rgb(255, 255, 255);
	while (c.tecla != 3) {
		mostra_janela(400, 700, c);
		controle_fun(m, c, i, a, true);
		al_draw_text(c.fonte_30, al_map_rgb(255, 0, 0), LARGURA_TELA / 2 - 100, ALTURA_TELA / 2 - 330, ALLEGRO_ALIGN_CENTRE, "NAME");
		al_draw_text(c.fonte_30, al_map_rgb(255, 0, 0), LARGURA_TELA / 2 + 100, ALTURA_TELA / 2 - 330, ALLEGRO_ALIGN_CENTRE, "TIME (SEC)");
		for (int i = 0; i < c.tam_score; i++) {
			sprintf_s(aux, "%d", sc[i].tempo);
			al_draw_text(c.fonte_30, cor_score, x_menu - 100, 160 + (i * 40), ALLEGRO_ALIGN_CENTRE, sc[i].nome);
			al_draw_text(c.fonte_30, cor_score, x_menu + 100, 160 + (i * 40), ALLEGRO_ALIGN_CENTRE, aux);
		}
		al_flip_display();
	}
}

//Função do menu
void exibe_menu_principal(mapa &m, controle_ &c, itens_ &i, armazens &a, relogio &r, scores s[]) {
	int tam_menu = 8;
	int imenu = -1;
	char op_menu[8][50] = { "NEW GAME","INTRODUCTION","DIFFICULTY","SCOREBOARD","LOAD GAME","OPTIONS","CREDITS","EXIT" };
	float y_menu = 3 * ALTURA_TELA / (tam_menu + 3);
	float x_menu = LARGURA_TELA / 2;
	float menu_inc = (ALTURA_TELA - y_menu) / tam_menu;
	float largura_flecha = 125; 
	float altura_flecha = largura_flecha * al_get_bitmap_height(c.FOLHA_SETA) / al_get_bitmap_width(c.FOLHA_SETA);
	float y_flecha = al_get_font_ascent(c.fonte_40) / 2 - altura_flecha / 2;
	float x_flecha = al_get_text_width(c.fonte_40, op_menu[imenu]) / 2 + 20;
	ALLEGRO_COLOR cor_menu;
	ALLEGRO_EVENT evento;
	while (!c.sair) {
		al_draw_bitmap(c.MENU, 0, 0, 0);
		controle_fun(m, c, i, a, true);
		if (c.tecla == 0) {
			if (c.sfx)
				al_play_sample(c.scroll, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			imenu++;
			if (imenu == 8)
				imenu = 0;

			c.tecla = 99;
		}
		else if (c.tecla == 1) {
			if (c.sfx)
				al_play_sample(c.scroll, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			imenu--;
			if (imenu == -1)
				imenu = 7;

			c.tecla = 99;
		}
		else if (c.tecla == 2) {
			if (c.sfx)
				al_play_sample(c.click, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			if (imenu == 0) {
				c.tecla = 0;
				c.modo = 1;
				break;
			}
			else if (imenu == 1) {
				exibe_menu_tutorial(m, c, i, a);
			}
			else if (imenu == 2) {
				exibe_dificuldade(m, c, i, a);
			}
			else if (imenu == 3) {
				exibe_placar(c, m, i, a, s);
			}
			else if (imenu == 4) {
				c.carregou = true;
				carrega(m, c, i, a, r);
				c.modo = 1;
				break;
			}
			else if (imenu == 5) {
				exibe_opcoes(m, c, i, a, false);
			}
			else if (imenu == 6) {
				exibe_menu_creditos(m, c, i, a);
			}
			if (imenu == 7) {
				c.sair = 1;
				break;
			}
			c.tecla = 99;
		}

		//flecha do menu
		al_draw_scaled_bitmap(c.FOLHA_SETA, 0, 0, al_get_bitmap_width(c.FOLHA_SETA), al_get_bitmap_height(c.FOLHA_SETA),
			x_menu - x_flecha - largura_flecha - 85, y_menu + imenu * menu_inc + y_flecha, largura_flecha, altura_flecha, 0);
		al_draw_scaled_bitmap(c.FOLHA_SETA, 0, 0, al_get_bitmap_width(c.FOLHA_SETA), al_get_bitmap_height(c.FOLHA_SETA),
			x_menu + x_flecha + 85, y_menu + imenu * menu_inc + y_flecha, largura_flecha, altura_flecha, ALLEGRO_FLIP_HORIZONTAL);

		for (int i = 0; i <= tam_menu; i++) {
			if (i == imenu) 
				cor_menu = al_map_rgb(0, 255, 0);
			else
				cor_menu = al_map_rgb(255, 255, 255);
			al_draw_text(c.fonte_30, cor_menu, x_menu, y_menu + i * menu_inc, ALLEGRO_ALIGN_CENTRE, op_menu[i]);
		}
		al_flip_display();
	}
}

//Exibe a tela de pause, realizando todas suas sub-rotinas necessárias
void pause_mode(mapa &m, controle_ &c, itens_ &i, armazens &a, relogio &r, bool aux) {
	int tam_menu = 5;
	int imenu = -1;
	char op_menu[5][50] = { "CONTINUE","SAVE","OPTIONS","RESTART","EXIT" }; //texto das opcoes do menu
	float y_menu = (3 * ALTURA_TELA / (tam_menu + 3)) + 10;
	float x_menu = LARGURA_TELA / 2;
	float menu_inc = (ALTURA_TELA - y_menu) / tam_menu;
	ALLEGRO_COLOR cor_menu;

	while (!c.sair) {
		mostra_janela(250, 250, c);
		controle_fun(m, c, i, a, true);
		if (c.tecla == 0) {
			imenu++;
			if (c.sfx)
				al_play_sample(c.scroll, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			if (imenu == 5)
				imenu = 0;

			c.tecla = 99;
		}
		else if (c.tecla == 1) {
			imenu--;
			if (c.sfx)
				al_play_sample(c.scroll, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			if (imenu == -1)
				imenu = 4;

			c.tecla = 99;
		}
		else if (c.tecla == 2) {
			if (c.sfx)
				al_play_sample(c.click, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			if (imenu == 0) {
				c.modo = 1;
				break;
			}
			else if (imenu == 1) {
				salvar(m, c, i, a, r);
				c.sair = 1;
				break;
			}
			else if (imenu == 2) {
				exibe_opcoes(m, c, i, a, true); 
			}
			else if (imenu == 3) {
				reiniciar(m, c, i, r, a);
				break;
			}
			else if (imenu == 4) {
				c.sair = 1;
				break;
			}
		}

		for (int i = 0; i <= tam_menu; i++) {
			if (i == imenu) {
				cor_menu = al_map_rgb(0, 255, 0);
			}				
			else
				cor_menu = al_map_rgb(255, 255, 255);
			al_draw_text(c.fonte_30, cor_menu, x_menu, y_menu + i * menu_inc * 0.4, ALLEGRO_ALIGN_CENTRE, op_menu[i]);
		}
		al_flip_display();
	}
	c.modo = 1;
}

//Reinicia as variaveis necessarias para o jogo voltar a acontecer novamente
void reiniciar(mapa &m, controle_ &c, itens_ &i, relogio &r, armazens &a) {
	int comida = 13;
	for (int i = 0; i < TAMANHO_ARMAZEM_LINHA; i++) {
		a.armazens_comida[i][0] = comida;
		comida--;
	}
	for (int i = 0; i < TAMANHO_ARMAZEM_LINHA; i++) 
		for (int j = 1; j < TAMANHO_ARMAZEM_COLUNA; j++) 
			a.armazens_comida[i][j] = 0;
		

	if (i.dificuldade == 0)
		i.VELOCIDADE_EVENTO = 60000;
	else if (i.dificuldade == 1) 
		i.VELOCIDADE_EVENTO = 40000;
	else if (i.dificuldade == 2) 
		i.VELOCIDADE_EVENTO = 20000;
	r.tempo_terremoto = i.VELOCIDADE_EVENTO;

	i.pa = 0;
	i.bota = 0;
	i.tocha = 0;
	i.kit = 0;
	i.USOS_PA = 0;
	i.VELOCIDADE_FORMIGA = 200;
	i.USOS_BOTA = 0;
	i.USOS_KIT = 0;
	r.minuto_principal = 0;
	r.segundo_principal = 0;
	r.tempo_inicial_principal = 0;
	r.tempo_final_principal = 0;
	r.tempo_exe_principal = 0;
	gerador_mapa(m, true);
	sorteia_formiga(m, c);
	sorteador_itens(i, m);
	sorteia_armazem(m, a);
	c.USOS_TOCHA = 0;
	c.modo = 1;
}