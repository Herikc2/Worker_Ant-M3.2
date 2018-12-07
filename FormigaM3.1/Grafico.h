#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>

#define TAMANHO 30
#define LARGURA_TELA 1000
#define ALTURA_TELA 900
#define FPS 60.0

#define CAMINHO_PAREDE 0
#define CAMINHO_LIVRE 1
#define FORMIGA_ 2
#define FORMIGA_COM_ALIMENTO 3
#define PAREDE_INDESTRUTIVEL 4
#define ARMAZEM_CORROMPIDO 5
#define ARMAZEM_1 6
#define ARMAZEM_2 7
#define ITEM_PA 20
#define ITEM_BOTA 21
#define ITEM_TOCHA 22
#define ITEM_KIT 23

//Struct principal de controle do jogo
struct controle_ {
	ALLEGRO_DISPLAY *janela = NULL;
	ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
	ALLEGRO_FONT *fonte_10 = NULL;
	ALLEGRO_FONT *fonte_14 = NULL;
	ALLEGRO_FONT *fonte_16 = NULL;
	ALLEGRO_FONT *fonte_18 = NULL;
	ALLEGRO_FONT *fonte_20 = NULL;
	ALLEGRO_FONT *fonte_30 = NULL;
	ALLEGRO_FONT *fonte_40 = NULL;
	ALLEGRO_BITMAP *MENU = NULL;
	ALLEGRO_BITMAP *MENU_SUPERIOR = NULL;
	ALLEGRO_BITMAP *MENU_SCORE = NULL;
	ALLEGRO_BITMAP *BACKGROUND = NULL;
	ALLEGRO_BITMAP *CAMINHO = NULL;
	ALLEGRO_BITMAP *PAREDE = NULL;
	ALLEGRO_BITMAP *FORMIGA_CIMA = NULL;
	ALLEGRO_BITMAP *FORMIGA_BAIXO = NULL;
	ALLEGRO_BITMAP *FORMIGA_ESQUERDA = NULL;
	ALLEGRO_BITMAP *FORMIGA_DIREITA = NULL;
	ALLEGRO_BITMAP *FORMIGA_ALIMENTO_CIMA = NULL;
	ALLEGRO_BITMAP *FORMIGA_ALIMENTO_BAIXO = NULL;
	ALLEGRO_BITMAP *FORMIGA_ALIMENTO_ESQUERDA = NULL;
	ALLEGRO_BITMAP *FORMIGA_ALIMENTO_DIREITA = NULL;
	ALLEGRO_BITMAP *FOLHA_SETA = NULL;
	ALLEGRO_BITMAP *PA = NULL;
	ALLEGRO_BITMAP *BOTA = NULL;
	ALLEGRO_BITMAP *TOCHA = NULL;
	ALLEGRO_BITMAP *KIT = NULL;
	ALLEGRO_BITMAP *COMIDA_PESO0 = NULL;
	ALLEGRO_BITMAP *COMIDA_PESO1 = NULL;
	ALLEGRO_BITMAP *COMIDA_PESO2 = NULL;
	ALLEGRO_BITMAP *COMIDA_PESO3 = NULL;
	ALLEGRO_BITMAP *COMIDA_PESO4 = NULL;
	ALLEGRO_BITMAP *COMIDA_PESO0_CORROMPIDO = NULL;
	ALLEGRO_BITMAP *COMIDA_PESO1_CORROMPIDO = NULL;
	ALLEGRO_BITMAP *COMIDA_PESO2_CORROMPIDO = NULL;
	ALLEGRO_BITMAP *COMIDA_PESO3_CORROMPIDO = NULL;
	ALLEGRO_BITMAP *COMIDA_PESO4_CORROMPIDO = NULL;
	ALLEGRO_BITMAP *PENUMBRA_150 = NULL;
	ALLEGRO_BITMAP *PENUMBRA_250 = NULL;
	ALLEGRO_AUDIO_STREAM *musica_menu = NULL;
	ALLEGRO_AUDIO_STREAM *game = NULL;
	ALLEGRO_AUDIO_STREAM *win = NULL;
	ALLEGRO_SAMPLE *scroll = NULL;
	ALLEGRO_SAMPLE *click = NULL;
	ALLEGRO_SAMPLE *pa = NULL;
	ALLEGRO_SAMPLE *pa_pegando = NULL;
	ALLEGRO_SAMPLE *tocha = NULL;
	ALLEGRO_SAMPLE *kit = NULL;
	ALLEGRO_SAMPLE *bota = NULL;
	ALLEGRO_SAMPLE *pega_entrega_armazem = NULL;
	ALLEGRO_SAMPLE *evento = NULL;
	clock_t decorrido = 0;
	clock_t inicial = 0;
	int tecla = 0;
	int x_formiga;
	int y_formiga;
	int modo = 0;
	int USOS_TOCHA = 0;
	int sair = 0;
	int lado = 1;
	bool music_status = true;
	bool sfx = true;
	float musica_volume_jogo = 1.0;
	bool carregou = false;
	char texto[20] = "";
	int tam_score = 0;
};

#include "Grafico.h"
#include "Tempo.h"
#include "Armazem.h"
#include "Formiga.h"
#include "Itens.h"
#include "telas.h"

//Função que carrega arquivos externos
void carrega_arquivos(controle_ &c) {
	c.MENU = al_load_bitmap("imgs/menu.png");
	c.MENU_SUPERIOR = al_load_bitmap("imgs/menu_superior.png");
	c.MENU_SCORE = al_load_bitmap("imgs/menu_score.png");
	c.BACKGROUND = al_load_bitmap("imgs/arenito_background.png");
	c.CAMINHO = al_load_bitmap("imgs/areia.png");
	c.PAREDE = al_load_bitmap("imgs/arenito.png");
	c.PA = al_load_bitmap("imgs/pa_caminho.png");
	c.BOTA = al_load_bitmap("imgs/bota_caminho.png");
	c.TOCHA = al_load_bitmap("imgs/tocha_caminho.png");
	c.KIT = al_load_bitmap("imgs/kit_caminho.png");
	c.COMIDA_PESO0 = al_load_bitmap("imgs/armazem_vazio.png");
	c.COMIDA_PESO1 = al_load_bitmap("imgs/folha_muito_leve.png");
	c.COMIDA_PESO2 = al_load_bitmap("imgs/folha_leve.png");
	c.COMIDA_PESO3 = al_load_bitmap("imgs/folha_media.png");
	c.COMIDA_PESO4 = al_load_bitmap("imgs/folha_pesada.png");
	c.COMIDA_PESO0_CORROMPIDO = al_load_bitmap("imgs/armazem_vazio_corrompido.png");
	c.COMIDA_PESO1_CORROMPIDO = al_load_bitmap("imgs/folha_muito_leve_corrompido.png");
	c.COMIDA_PESO2_CORROMPIDO = al_load_bitmap("imgs/folha_leve_corrompido.png");
	c.COMIDA_PESO3_CORROMPIDO = al_load_bitmap("imgs/folha_media_corrompido.png");
	c.COMIDA_PESO4_CORROMPIDO = al_load_bitmap("imgs/folha_pesada_corrompido.png");
	c.FOLHA_SETA = al_load_bitmap("imgs/folha_seta.png");
	c.FORMIGA_CIMA = al_load_bitmap("imgs/formiga_cima.png");
	c.FORMIGA_BAIXO = al_load_bitmap("imgs/formiga_baixo.png");
	c.FORMIGA_ESQUERDA = al_load_bitmap("imgs/formiga_esquerda.png");
	c.FORMIGA_DIREITA = al_load_bitmap("imgs/formiga_direita.png");
	c.FORMIGA_ALIMENTO_CIMA = al_load_bitmap("imgs/formiga_cima_alimento.png");
	c.FORMIGA_ALIMENTO_BAIXO = al_load_bitmap("imgs/formiga_baixo_alimento.png");
	c.FORMIGA_ALIMENTO_ESQUERDA = al_load_bitmap("imgs/formiga_esquerda_alimento.png");
	c.FORMIGA_ALIMENTO_DIREITA = al_load_bitmap("imgs/formiga_direita_alimento.png");
	c.PENUMBRA_150 = al_load_bitmap("imgs/penumbra_150.png");
	c.PENUMBRA_250 = al_load_bitmap("imgs/penumbra_250.png");
	al_reserve_samples(15);
	c.musica_menu = al_load_audio_stream("som/Netherplace.ogg", 4, 1024);
	c.game = al_load_audio_stream("som/game.ogg", 4, 1024);
	c.win = al_load_audio_stream("som/win_music.ogg", 4, 1024);
	c.scroll = al_load_sample("som/scroll.ogg");
	c.click = al_load_sample("som/click.ogg");
	c.pa = al_load_sample("som/pa.ogg");
	c.pa_pegando = al_load_sample("som/pa_pegando.ogg");
	c.tocha = al_load_sample("som/tocha.ogg");
	c.kit = al_load_sample("som/kit.ogg");
	c.bota = al_load_sample("som/bota.ogg");
	c.pega_entrega_armazem = al_load_sample("som/pega_entrega_armazem.ogg");
	c.evento = al_load_sample("som/evento.ogg");
	c.fonte_10 = al_load_font("fonte/arial.ttf", 10, 0);
	c.fonte_14 = al_load_font("fonte/arial.ttf", 14, 0);
	c.fonte_16 = al_load_font("fonte/arial.ttf", 16, 0);
	c.fonte_18 = al_load_font("fonte/arial.ttf", 18, 0);
	c.fonte_20 = al_load_font("fonte/arial.ttf", 20, 0);
	c.fonte_30 = al_load_font("fonte/arial.ttf", 30, 0);
	c.fonte_40 = al_load_font("fonte/arial.ttf", 40, 0);
}

//Função que inicia toda biblioteca gráfica e teclado
void iniciar(controle_ &c) {
	al_init();
	c.janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
	al_set_window_title(c.janela, "Formiga");
	al_clear_to_color(al_map_rgb(255, 255, 255));
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_init_primitives_addon();
	al_install_audio();
	al_init_acodec_addon();

	//Teclado
	al_install_keyboard();
	c.fila_eventos = al_create_event_queue();
	al_register_event_source(c.fila_eventos, al_get_keyboard_event_source());
	al_register_event_source(c.fila_eventos, al_get_display_event_source(c.janela));

	al_flip_display();
	al_rest(true);
}

//Função onde é renderizado todos os dados na tela 
void renderizar(mapa mapa, controle_ &c, armazens a) {
	int x = (LARGURA_TELA - (mapa.coluna * 30)) / 2, y = 150, xForm = 0, yform = 0;
	al_draw_bitmap(c.BACKGROUND, 0, 0, 0); //Carrega plano de fundo, para não ficar preto
	for (int i = 0; i < mapa.linha; i++) {
		for (int j = 0; j < mapa.coluna; j++) {
			if (mapa.matriz[i][j] == CAMINHO_PAREDE) {
				al_draw_bitmap(c.PAREDE, x, y, 0);
			}
			else if (mapa.matriz[i][j] == CAMINHO_LIVRE) {
				al_draw_bitmap(c.CAMINHO, x, y, 0);
			}
			else if (mapa.matriz[i][j] == FORMIGA_) {
				if (c.lado == 1) {
					al_draw_bitmap(c.FORMIGA_CIMA, x, y, 0);
				}
				else if (c.lado == 2) {
					al_draw_bitmap(c.FORMIGA_BAIXO, x, y, 0);
				}
				else if (c.lado == 3) {
					al_draw_bitmap(c.FORMIGA_ESQUERDA, x, y, 0);
				}
				else if (c.lado == 4) {
					al_draw_bitmap(c.FORMIGA_DIREITA, x, y, 0);
				}
				xForm = x;
				yform = y;
			}
			else if (mapa.matriz[i][j] == FORMIGA_COM_ALIMENTO) {
				if (c.lado == 1) {
					al_draw_bitmap(c.FORMIGA_ALIMENTO_CIMA, x, y, 0);
				}
				else if (c.lado == 2) {
					al_draw_bitmap(c.FORMIGA_ALIMENTO_BAIXO, x, y, 0);
				}
				else if (c.lado == 3) {
					al_draw_bitmap(c.FORMIGA_ALIMENTO_ESQUERDA, x, y, 0);
				}
				else if (c.lado == 4) {
					al_draw_bitmap(c.FORMIGA_ALIMENTO_DIREITA, x, y, 0);
				}
				xForm = x;
				yform = y;
			}
			else if (mapa.matriz[i][j] == PAREDE_INDESTRUTIVEL) {
				al_draw_bitmap(c.PAREDE, x, y, 0);
			}
			else if (mapa.matriz[i][j] == ARMAZEM_CORROMPIDO) {
				menorComida(a, 0);
				if (a.menorComida == 10)
					al_draw_bitmap(c.COMIDA_PESO1_CORROMPIDO, x, y, 0);
				else if (a.menorComida == 11)
					al_draw_bitmap(c.COMIDA_PESO2_CORROMPIDO, x, y, 0);
				else if (a.menorComida == 12)
					al_draw_bitmap(c.COMIDA_PESO3_CORROMPIDO, x, y, 0);
				else if (a.menorComida == 13)
					al_draw_bitmap(c.COMIDA_PESO4_CORROMPIDO, x, y, 0);
				else if (a.menorComida == 100)
					al_draw_bitmap(c.COMIDA_PESO0_CORROMPIDO, x, y, 0);
			}
			else if (mapa.matriz[i][j] == ARMAZEM_1) {
				menorComida(a, 1);
				if (a.menorComida == 10)
					al_draw_bitmap(c.COMIDA_PESO1, x, y, 0);
				else if (a.menorComida == 11)
					al_draw_bitmap(c.COMIDA_PESO2, x, y, 0);
				else if (a.menorComida == 12)
					al_draw_bitmap(c.COMIDA_PESO3, x, y, 0);
				else if (a.menorComida == 13)
					al_draw_bitmap(c.COMIDA_PESO4, x, y, 0);
				else if (a.menorComida == 100)
					al_draw_bitmap(c.COMIDA_PESO0, x, y, 0);
			}
			else if (mapa.matriz[i][j] == ARMAZEM_2) {
				menorComida(a, 2);
				if (a.menorComida == 10)
					al_draw_bitmap(c.COMIDA_PESO1, x, y, 0);
				else if (a.menorComida == 11)
					al_draw_bitmap(c.COMIDA_PESO2, x, y, 0);
				else if (a.menorComida == 12)
					al_draw_bitmap(c.COMIDA_PESO3, x, y, 0);
				else if (a.menorComida == 13)
					al_draw_bitmap(c.COMIDA_PESO4, x, y, 0);
				else if (a.menorComida == 100)
					al_draw_bitmap(c.COMIDA_PESO0, x, y, 0);
			}
			else if (mapa.matriz[i][j] == ITEM_PA) {
				al_draw_bitmap(c.PA, x, y, 0);
			}
			else if (mapa.matriz[i][j] == ITEM_BOTA) {
				al_draw_bitmap(c.BOTA, x, y, 0);
			}
			else if (mapa.matriz[i][j] == ITEM_TOCHA) {
				al_draw_bitmap(c.TOCHA, x, y, 0);
			}
			else if (mapa.matriz[i][j] == ITEM_KIT) {
				al_draw_bitmap(c.KIT, x, y, 0);
			}
			x += TAMANHO;
		}
		y += TAMANHO;
		x = (LARGURA_TELA - (mapa.coluna * 30)) / 2;
	}
	if (c.USOS_TOCHA == 0)  //Verifica se possui ou não o item tocha
		al_draw_bitmap(c.PENUMBRA_150, xForm - LARGURA_TELA, yform - ALTURA_TELA + 80, 0);
	else 
		al_draw_bitmap(c.PENUMBRA_250, xForm - LARGURA_TELA, yform - ALTURA_TELA + 80, 0);
	al_draw_bitmap(c.MENU_SUPERIOR, 0, 0, 0); 
}