#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include "../inc/VariablesFrogger.h"
#include "../inc/Inicializacion.h"
#include "../inc/Teclado.h"

char Jugador1ApretoTecla( ALLEGRO_EVENT *p_ev, bool *key, ALLEGRO_TIMER **p_resting_timer, ALLEGRO_TIMER **p_sprites_timer ){
	// Seteamos flag de flechas y P
	
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
	// Reseteamos flag de flechas y P
	
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


char JugadorApretoTecla( ALLEGRO_EVENT *p_ev, bool *key, ALLEGRO_TIMER **p_resting_timer_1, ALLEGRO_TIMER **p_resting_timer_2, ALLEGRO_TIMER **p_sprites_timer_1, ALLEGRO_TIMER **p_sprites_timer_2 ){
	// Seteamos flag de flechas, W, A, S, D y P
	
	char Flag = CONTINUAR;
	
	switch(p_ev->keyboard.keycode) {
		case ALLEGRO_KEY_UP:
			key[KEY_UP] = true;
			InicializarTimers( p_resting_timer_1, p_sprites_timer_1 );							
			break;
		case ALLEGRO_KEY_DOWN:
			key[KEY_DOWN] = true;
			InicializarTimers( p_resting_timer_1, p_sprites_timer_1 );
			break;
		case ALLEGRO_KEY_LEFT:
			key[KEY_LEFT] = true;
			InicializarTimers( p_resting_timer_1, p_sprites_timer_1 );
			break;
		case ALLEGRO_KEY_RIGHT:
			key[KEY_RIGHT] = true;
			InicializarTimers( p_resting_timer_1, p_sprites_timer_1 );
			break;
			
		case ALLEGRO_KEY_W:
			key[KEY_2_UP] = true;
			InicializarTimers( p_resting_timer_2, p_sprites_timer_2 );							
			break;
		case ALLEGRO_KEY_S:
			key[KEY_2_DOWN] = true;
			InicializarTimers( p_resting_timer_2, p_sprites_timer_2 );
			break;
		case ALLEGRO_KEY_A:
			key[KEY_2_LEFT] = true;
			InicializarTimers( p_resting_timer_2, p_sprites_timer_2 );
			break;
		case ALLEGRO_KEY_D:
			key[KEY_2_RIGHT] = true;
			InicializarTimers( p_resting_timer_2, p_sprites_timer_2 );
			break;
			
		case ALLEGRO_KEY_P:
			Flag = PAUSA;
			break;
	}
	return Flag;
}

void JugadorSoltoTecla( ALLEGRO_EVENT *p_ev, bool *key, ALLEGRO_TIMER **p_resting_timer_1, ALLEGRO_TIMER **p_resting_timer_2 ){
	// Reseteamos flag de flechas, W, A, S, D y P
	
	switch(p_ev->keyboard.keycode) {
		case ALLEGRO_KEY_UP:
			key[KEY_UP] = false;
			al_stop_timer( *(p_resting_timer_1) );
			break;
		case ALLEGRO_KEY_DOWN:
			key[KEY_DOWN] = false;
			al_stop_timer( *(p_resting_timer_1) );
			break;
		case ALLEGRO_KEY_LEFT:
			key[KEY_LEFT] = false;
			al_stop_timer( *(p_resting_timer_1) );
			break;
		case ALLEGRO_KEY_RIGHT:
			key[KEY_RIGHT] = false;
			al_stop_timer( *(p_resting_timer_1) );
			break;
			
		case ALLEGRO_KEY_W:
			key[KEY_2_UP] = false;
			al_stop_timer( *(p_resting_timer_2) );							
			break;
		case ALLEGRO_KEY_S:
			key[KEY_2_DOWN] = false;
			al_stop_timer( *(p_resting_timer_2) );
			break;
		case ALLEGRO_KEY_A:
			key[KEY_2_LEFT] = false;
			al_stop_timer( *(p_resting_timer_2) );
			break;
		case ALLEGRO_KEY_D:
			key[KEY_2_RIGHT] = false;
			al_stop_timer( *(p_resting_timer_2) );
			break;
	}
}
