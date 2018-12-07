#pragma once

struct scores {
	char nome[20];
	int tempo;
};

void exibe_menu_principal(mapa &m, controle_ &c, itens_ &i, armazens &a, relogio &r, scores s[]);
void iniciar(controle_ &c);
void carrega_arquivos(controle_ &c);
void pause_mode(mapa &m, controle_ &c, itens_ &i, armazens &a, relogio &r, bool aux);
void prePontos(scores s[], controle_ &con, bool aux);
void pontos(controle_ &c, scores s[], relogio r);
void exibe_placar(controle_ &c, mapa m, itens_ i, armazens a, scores sc[]);

//Oculta Console
void Stealth()
{
	HWND Stealth;
	AllocConsole();
	Stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Stealth, 0);
}

//Pré loading de informações básicas
void pre(mapa &m, controle_ &c, armazens &a) {
	Stealth();
	iniciar(c);
	carrega_arquivos(c);
}

//Carregamento do menu
void preMenu(mapa &m, controle_ &c, itens_ &i, armazens &a, relogio &r, scores s[]) {
	al_attach_audio_stream_to_mixer(c.musica_menu, al_get_default_mixer());
	al_set_audio_stream_playmode(c.musica_menu, ALLEGRO_PLAYMODE_LOOP);
	exibe_menu_principal(m, c, i, a, r, s);
	al_set_audio_stream_playing(c.musica_menu, 0);
	if (c.carregou == false) {
		gerador_mapa(m, true);
		sorteia_formiga(m, c);
		sorteia_armazem(m, a);
		sorteador_itens(i, m);
	}
	al_attach_audio_stream_to_mixer(c.game, al_get_default_mixer());
	al_set_audio_stream_playmode(c.game, ALLEGRO_PLAYMODE_LOOP);
}

//Carregamento e exibição do menu-superior durante o jogo
void menuSup(relogio r, controle_ c, itens_ i) {
	char usos_pa[256], usos_tocha[256], usos_bota[256], tempo_terremoto[256];

	sprintf_s(r.minuto_principal_char, "%d", r.minuto_principal);
	sprintf_s(r.segundo_principal_char, "%d", r.segundo_principal);
	sprintf_s(usos_pa, "%d", i.USOS_PA);
	sprintf_s(usos_tocha, "%d", c.USOS_TOCHA);
	sprintf_s(usos_bota, "%d", i.USOS_BOTA);
	sprintf_s(tempo_terremoto, "%d", (r.tempo_terremoto / 1000) + 1);
	al_draw_text(c.fonte_14, al_map_rgb(0, 0, 0), LARGURA_TELA - 300, 40, ALLEGRO_ALIGN_RIGHT, "TIME: ");
	al_draw_text(c.fonte_14, al_map_rgb(0, 0, 0), LARGURA_TELA - 280, 40, ALLEGRO_ALIGN_RIGHT, r.minuto_principal_char);
	al_draw_text(c.fonte_14, al_map_rgb(0, 0, 0), LARGURA_TELA - 270, 40, ALLEGRO_ALIGN_RIGHT, ":");
	al_draw_text(c.fonte_14, al_map_rgb(0, 0, 0), LARGURA_TELA - 252, 40, ALLEGRO_ALIGN_RIGHT, r.segundo_principal_char);

	al_draw_text(c.fonte_14, al_map_rgb(0, 0, 0), LARGURA_TELA - 210, 55, ALLEGRO_ALIGN_RIGHT, "Time to earthquake: ");
	al_draw_text(c.fonte_14, al_map_rgb(0, 0, 0), LARGURA_TELA - 185, 55, ALLEGRO_ALIGN_RIGHT, tempo_terremoto);

	al_draw_text(c.fonte_14, al_map_rgb(0, 0, 0), LARGURA_TELA - 255, 70, ALLEGRO_ALIGN_RIGHT, "Uses Shovel: ");
	al_draw_text(c.fonte_14, al_map_rgb(0, 0, 0), LARGURA_TELA - 240, 70, ALLEGRO_ALIGN_RIGHT, usos_pa);

	al_draw_text(c.fonte_14, al_map_rgb(0, 0, 0), LARGURA_TELA - 261, 85, ALLEGRO_ALIGN_RIGHT, "Uses Torch: ");
	al_draw_text(c.fonte_14, al_map_rgb(0, 0, 0), LARGURA_TELA - 251, 85, ALLEGRO_ALIGN_RIGHT, usos_tocha);

	al_draw_text(c.fonte_14, al_map_rgb(0, 0, 0), LARGURA_TELA - 268, 100, ALLEGRO_ALIGN_RIGHT, "Uses Boot: ");
	al_draw_text(c.fonte_14, al_map_rgb(0, 0, 0), LARGURA_TELA - 258, 100, ALLEGRO_ALIGN_RIGHT, usos_bota);
}

//Registro de eventos, a cada intervalo determinado pela dificuldade
void terremoto_evento(controle_ &c, mapa &m, itens_ &i, relogio &r, armazens &a) {
	if (c.sfx)
		al_play_sample(c.evento, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	i.USOS_BOTA = 0;
	c.USOS_TOCHA = 0;
	if (i.USOS_KIT == 1) {
		kit(i, 1);
	}
	i.USOS_KIT = 0;
	gerador_mapa(m, true);
	sorteia_formiga(m, c);
	sorteador_itens(i, m);
	sorteia_armazem(m, a);
	i.verificador = 0;
	r.tempo_terremoto = i.VELOCIDADE_EVENTO;
}

//Carregamento das operações do jogo
bool preJogar(mapa &m, controle_ &c, itens_ &i, armazens &a, relogio &r) {
	controle_de_tempo_principal(r, c, i, true);
	controle_fun(m, c, i, a, false);
	renderizar(m, c, a);
	menuSup(r, c, i);
	if (i.verificador == 1) {
		if (i.dificuldade == 0) 
			r.tempo_terremoto += 60000;
		else if (i.dificuldade == 1) 
			r.tempo_terremoto += 40000;
		else if (i.dificuldade == 2) 
			r.tempo_terremoto += 20000;
		i.verificador--;
	}
	if (r.tempo_terremoto <= 0) {
		terremoto_evento(c, m, i, r, a);
	}
	controle_de_tempo_principal(r, c, i, false);
	if (checkFimGame(a) == true) {
		return true;
	}
	return false;
}

//Carregamento da tela de pause 
void prePause(mapa &m, controle_ &c, itens_ &i, armazens &a, relogio &r) {
	al_set_audio_stream_playing(c.game, 0);
	pause_mode(m, c, i, a, r, false);
	al_set_audio_stream_playing(c.game, 1);
	c.tecla = 0;
}

//Carregamento da tela de vitória
void preVitoria(mapa m, controle_ &c, itens_ &i, armazens &a, relogio r, scores s[]) {
	char tempo_score[256];
	al_set_audio_stream_playing(c.game, 0);
	al_attach_audio_stream_to_mixer(c.win, al_get_default_mixer());
	al_set_audio_stream_playmode(c.win, ALLEGRO_PLAYMODE_LOOP);
	sprintf_s(tempo_score, "%d", r.segundo_principal);
	while (c.tecla != 3) {
		prePontos(s, c, false);
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_bitmap(c.MENU_SCORE, 0, 0, 0);
		al_draw_text(c.fonte_40, al_map_rgb(255, 255, 255), LARGURA_TELA - 420, 550, ALLEGRO_ALIGN_RIGHT, "GAME TIME: ");
		al_draw_text(c.fonte_40, al_map_rgb(255, 255, 255), LARGURA_TELA - 340, 550, ALLEGRO_ALIGN_RIGHT, tempo_score);
		al_draw_text(c.fonte_40, al_map_rgb(255, 255, 255), LARGURA_TELA - 120, 550, ALLEGRO_ALIGN_RIGHT, "SECONDS");
		al_draw_text(c.fonte_30, al_map_rgb(0, 0, 0), LARGURA_TELA - 400, 620, ALLEGRO_ALIGN_RIGHT, c.texto);
		al_draw_text(c.fonte_40, al_map_rgb(255, 255, 255), LARGURA_TELA - 280, 700, ALLEGRO_ALIGN_RIGHT, "PRESS ESC TO EXIT");
		al_flip_display();
	}
	pontos(c, s, r);
	exibe_placar(c, m, i, a, s);
}

//Salva informações do jogo
void salvar(mapa m, controle_ c, itens_ i, armazens a, relogio r) {
	ofstream save;
	save.open("save.txt");

	//Salva lib Armazens.h
	for (int i = 0; i < TAMANHO_ARMAZEM_LINHA; i++) {
		for (int j = 0; j < TAMANHO_ARMAZEM_COLUNA; j++) {
			save << a.armazens_comida[i][j] << endl;
		}
	}
	save << a.status << endl << a.Comida << endl << a.comida_encontrada << endl;
	//Salva lib Grafico.h
	save << c.x_formiga << endl << c.y_formiga << endl << c.USOS_TOCHA << endl;
	//Salva lib Itens.h
	save << i.pa << endl << i.tocha << endl << i.bota << endl << i.kit << endl;
	save << i.USOS_PA << endl << i.VELOCIDADE_FORMIGA << endl << i.USOS_BOTA << endl;
	save << i.VELOCIDADE_EVENTO << endl << i.USOS_KIT << endl << i.dificuldade << endl << i.verificador << endl;
	//Salva lib Tempo.h
	save << r.tempo_exe_principal << endl << r.tempo_terremoto << endl;
	//Salva lib libMapa.h
	save << m.linha << endl << m.coluna << endl;
	for (int i = 0; i < m.linha; i++) {
		for (int j = 0; j < m.coluna; j++) {
			save << m.matriz[i][j] << endl;
		}
	}
	save.close();
}

//Conversão de elementos carregados
int carrega_converte(mapa m, controle_ c, itens_ i, armazens a, relogio r, ifstream carrega) {
	char aux_char[256];
	int aux_int;
	carrega.getline(aux_char, 256);
	aux_int = atoi(aux_char);
	return aux_int;
}

//Carrega os elementos essenciais do jogo
void carrega(mapa &m, controle_ &c, itens_ &i, armazens &a, relogio &r) {
	char aux_char[256];
	int aux_int;
	ifstream carrega;
	carrega.open("save.txt");

	for (int i = 0; i < TAMANHO_ARMAZEM_LINHA; i++) {
		for (int j = 0; j < TAMANHO_ARMAZEM_COLUNA; j++) {
			carrega.getline(aux_char, 256);
			aux_int = atoi(aux_char);
			a.armazens_comida[i][j] = aux_int;
		}
	}

	//Carrega lib Armazem
	carrega.getline(aux_char, 256);
	a.status = atoi(aux_char);
	carrega.getline(aux_char, 256);
	a.Comida = atoi(aux_char);
	carrega.getline(aux_char, 256);
	a.comida_encontrada = atoi(aux_char);
	//Carrega lib Controle
	carrega.getline(aux_char, 256);
	c.x_formiga = atoi(aux_char);
	carrega.getline(aux_char, 256);
	c.y_formiga = atoi(aux_char);
	carrega.getline(aux_char, 256);
	c.USOS_TOCHA = atoi(aux_char);
	//Carrega lib itens
	carrega.getline(aux_char, 256);
	i.pa = atoi(aux_char);
	carrega.getline(aux_char, 256);
	i.tocha = atoi(aux_char);
	carrega.getline(aux_char, 256);
	i.bota = atoi(aux_char);
	carrega.getline(aux_char, 256);
	i.kit = atoi(aux_char);
	carrega.getline(aux_char, 256);
	i.USOS_PA = atoi(aux_char);
	carrega.getline(aux_char, 256);
	i.VELOCIDADE_FORMIGA = atoi(aux_char);
	carrega.getline(aux_char, 256);
	i.USOS_BOTA = atoi(aux_char);
	carrega.getline(aux_char, 256);
	i.VELOCIDADE_EVENTO = atoi(aux_char);
	carrega.getline(aux_char, 256);
	i.USOS_KIT = atoi(aux_char);
	carrega.getline(aux_char, 256);
	i.dificuldade = atoi(aux_char);
	carrega.getline(aux_char, 256);
	i.verificador = atoi(aux_char);
	//Carrega lib Relogio
	carrega.getline(aux_char, 256);
	r.tempo_exe_principal = atoi(aux_char);
	carrega.getline(aux_char, 256);
	r.tempo_terremoto = atoi(aux_char);
	//Carrega Mapa
	carrega.getline(aux_char, 256);
	m.linha = atoi(aux_char);
	carrega.getline(aux_char, 256);
	m.coluna = atoi(aux_char);
	gerador_mapa(m, false);
	for (int i = 0; i < m.linha; i++) {
		for (int j = 0; j < m.coluna; j++) {
			carrega.getline(aux_char, 256);
			aux_int = atoi(aux_char);
			m.matriz[i][j] = aux_int;
		}
	}
	c.tecla = 99;
}

//Preparação para exibição dos pontos
void prePontos(scores s[], controle_ &con, bool aux) {
	char c[2] = "";
	int aux_int = 0;
	char aux_char[256];
	ifstream carrega_score;
	carrega_score.open("score.txt");
	if (aux == true) {
		carrega_score.getline(aux_char, 256);
		aux_int = atoi(aux_char);
		con.tam_score = aux_int;
		for (int i = 0; i < 10; i++) {
			carrega_score.getline(aux_char, 256);
			strcpy_s(s[i].nome, aux_char);
			carrega_score.getline(aux_char, 256);
			aux_int = atoi(aux_char);
			s[i].tempo = aux_int;
		}
		for (int i = con.tam_score; i < 10; i++) {
			if (s[i].tempo == 0) {
				s[i].tempo = 9999999999;
			}
		}
	}
	else 
		if (!al_is_event_queue_empty(con.fila_eventos)) {
			ALLEGRO_EVENT evento;
			al_wait_for_event(con.fila_eventos, &evento);
			if (evento.type == ALLEGRO_EVENT_KEY_CHAR) { //ao digitar os caracteres do nome
				*c = evento.keyboard.unichar; //captura caractere
				if (evento.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) //backspace, volta uma posicao no texto
					con.texto[strlen(con.texto) - 1] = '\0';
				//se for letras ou numeros, insere no texto
				else if (((*c >= 'a' && *c <= 'z') || (*c >= 'A' && *c <= 'Z') || (*c >= '0' && *c <= '9') || (*c == ' ')) && strlen(con.texto) < 10)
					strcat_s(con.texto, c);
				else if(evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
					con.tecla = 3;
			}
		}
}

//Salva o novo placar
void pontos(controle_ &c, scores s[], relogio r) {
	int indice_top = 0;
	ofstream salva_score;
	salva_score.open("score.txt");

	for (int i = 0; i < 10; i++) {
		if (r.tempo_exe_principal < s[i].tempo) {
			indice_top = i;
			for (int j = 9; j > i; j--)
				s[j] = s[j - 1];
			s[indice_top].tempo = r.tempo_exe_principal;
			strcpy_s(s[indice_top].nome, c.texto);
			if (c.tam_score < 10) {
				c.tam_score++;
			}
			break;
		}
	}
	salva_score << c.tam_score << endl;
	for (int i = 0; i < c.tam_score; i++) {
		salva_score << s[i].nome << endl;
		salva_score << s[i].tempo << endl;
	}
}

//Destruição de todos vestigios do jogo
void finalizacao(mapa m, controle_ c, itens_ i, armazens a, relogio r) {
	al_destroy_display(c.janela);
	al_destroy_event_queue(c.fila_eventos);
	al_destroy_font(c.fonte_10);
	al_destroy_font(c.fonte_14);
	al_destroy_font(c.fonte_16);
	al_destroy_font(c.fonte_18);
	al_destroy_font(c.fonte_20);
	al_destroy_font(c.fonte_30);
	al_destroy_font(c.fonte_40);
	al_destroy_bitmap(c.MENU);
	al_destroy_bitmap(c.MENU_SUPERIOR);
	al_destroy_bitmap(c.MENU_SCORE);
	al_destroy_bitmap(c.BACKGROUND);
	al_destroy_bitmap(c.CAMINHO);
	al_destroy_bitmap(c.PAREDE);
	al_destroy_bitmap(c.FORMIGA_CIMA);
	al_destroy_bitmap(c.FORMIGA_BAIXO);
	al_destroy_bitmap(c.FORMIGA_ESQUERDA);
	al_destroy_bitmap(c.FORMIGA_DIREITA);
	al_destroy_bitmap(c.FORMIGA_ALIMENTO_CIMA);
	al_destroy_bitmap(c.FORMIGA_ALIMENTO_BAIXO);
	al_destroy_bitmap(c.FORMIGA_ALIMENTO_ESQUERDA);
	al_destroy_bitmap(c.FORMIGA_ALIMENTO_DIREITA);
	al_destroy_bitmap(c.FOLHA_SETA);
	al_destroy_bitmap(c.PA);
	al_destroy_bitmap(c.BOTA);
	al_destroy_bitmap(c.TOCHA);
	al_destroy_bitmap(c.KIT);
	al_destroy_bitmap(c.COMIDA_PESO0);
	al_destroy_bitmap(c.COMIDA_PESO1);
	al_destroy_bitmap(c.COMIDA_PESO2);
	al_destroy_bitmap(c.COMIDA_PESO3);
	al_destroy_bitmap(c.COMIDA_PESO4);
	al_destroy_bitmap(c.COMIDA_PESO0_CORROMPIDO);
	al_destroy_bitmap(c.COMIDA_PESO1_CORROMPIDO);
	al_destroy_bitmap(c.COMIDA_PESO2_CORROMPIDO);
	al_destroy_bitmap(c.COMIDA_PESO3_CORROMPIDO);
	al_destroy_bitmap(c.COMIDA_PESO4_CORROMPIDO);
	al_destroy_bitmap(c.PENUMBRA_150);
	al_destroy_bitmap(c.PENUMBRA_250);
	al_destroy_audio_stream(c.musica_menu);
	al_destroy_audio_stream(c.game);
	al_destroy_audio_stream(c.win);
	al_destroy_sample(c.scroll);
	al_destroy_sample(c.click);
	al_destroy_sample(c.pa);
	al_destroy_sample(c.pa_pegando);
	al_destroy_sample(c.tocha);
	al_destroy_sample(c.kit);
	al_destroy_sample(c.bota);
	al_destroy_sample(c.pega_entrega_armazem);
	al_destroy_sample(c.evento);
}