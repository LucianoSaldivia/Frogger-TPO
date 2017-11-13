#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include "../inc/VariablesFrogger.h"
#include "../inc/Inicializacion.h"
#include "../inc/Teclado.h"

char Jugador1ApretoTecla( ALLEGRO_EVENT *p_ev, bool *key, ALLEGRO_TIMER **p_resting_timer, ALLEGRO_TIMER **p_sprites_timer ){
	char Flag = CONTINUAR;
	
	switch(p_ev->keyboard.keycode) {
		case ALLEGRO_KEY_UP:
			key[KEY_UP] = true;
			InicializarTimers( p_resting_timer, p_sprites_timer );							
			break;
		case ALLEGRO_KEY_DOWN:
			key[KEY_DOWN] = true;
			InicializarTimers( p_resting_timer, p_sprites_timer );
			break;
		case ALLEGRO_KEY_LEFT:
			key[KEY_LEFT] = true;
			InicializarTimers( p_resting_timer, p_sprites_timer );
			break;
		case ALLEGRO_KEY_RIGHT:
			key[KEY_RIGHT] = true;
			InicializarTimers( p_resting_timer, p_sprites_timer );
			break;
		case ALLEGRO_KEY_P:
			Flag = PAUSA;
			break;
	}
	return Flag;
}

void Jugador1SoltoTecla( ALLEGRO_EVENT *p_ev, bool *key, ALLEGRO_TIMER **p_resting_timer ){
	switch(p_ev->keyboard.keycode) {
		case ALLEGRO_KEY_UP:
			key[KEY_UP] = false;
			al_stop_timer( *(p_resting_timer) );
			break;
		case ALLEGRO_KEY_DOWN:
			key[KEY_DOWN] = false;
			al_stop_timer( *(p_resting_timer) );
			break;
		case ALLEGRO_KEY_LEFT:
			key[KEY_LEFT] = false;
			al_stop_timer( *(p_resting_timer) );
			break;
		case ALLEGRO_KEY_RIGHT:
			key[KEY_RIGHT] = false;
			al_stop_timer( *(p_resting_timer) );
			break;
	}
}

