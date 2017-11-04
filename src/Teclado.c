#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include "../inc/VariablesFrogger.h"
#include "../inc/Teclado.h"
#include "../inc/Inicializacion.h"

char Jugador1ApretoTecla( ALLEGRO_EVENT *p_ev, bool *key, char *Direccion, ALLEGRO_TIMER **p_resting_timer, ALLEGRO_TIMER **p_sprites_timer ){
	char Flag = CONTINUAR;
	
	switch(p_ev->keyboard.keycode) {
		case ALLEGRO_KEY_UP:
			key[KEY_UP] = true;
			*(Direccion) = ARRIBA;
			InicializarTimers( p_resting_timer, p_sprites_timer );							
			break;
		case ALLEGRO_KEY_DOWN:
			key[KEY_DOWN] = true;
			*(Direccion) = ABAJO;
			InicializarTimers( p_resting_timer, p_sprites_timer );
			break;
		case ALLEGRO_KEY_LEFT:
			key[KEY_LEFT] = true;
			*(Direccion) = IZQUIERDA;
			InicializarTimers( p_resting_timer, p_sprites_timer );
			break;
		case ALLEGRO_KEY_RIGHT:
			key[KEY_RIGHT] = true;
			*(Direccion) = DERECHA;
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








/*

void TeclaPresionadaJugador1(ALLEGRO_EVENT *pev, bool **pkey, Objeto **pIni, Objeto **pObjetoFrog, ALLEGRO_BITMAP **VecFrog){
	Objeto *ObjetoFrog = *(pObjetoFrog);

	switch(pev->keyboard.keycode){
		case ALLEGRO_KEY_UP:
			if( ObjetoFrog->Pos_y >= LIM_SALTO_ARRIBA ){
				RanaSaltaArriba(pIni, pObjetoFrog, VecFrog );	
				(*pkey)[KEY_UP] = true;
				//al_start_timer(resting_timer);
			}
			break;
		case ALLEGRO_KEY_DOWN:
			if( ObjetoFrog->Pos_y <= LIM_SALTO_ABAJO ) {
				RanaSaltaAbajo( pIni, pObjetoFrog, VecFrog );			
				(*pkey)[KEY_DOWN] = true;
				//al_start_timer(resting_timer);
			}
			break;
		case ALLEGRO_KEY_LEFT:
			if( ObjetoFrog->Pos_x >= LIM_SALTO_IZQUIERDA ) {
				RanaSaltaIzquierda( pIni, pObjetoFrog, VecFrog );			
				(*pkey)[KEY_LEFT] = true;
				//al_start_timer(resting_timer);

			}
			break;
		case ALLEGRO_KEY_RIGHT:
			if( ObjetoFrog->Pos_x <= LIM_SALTO_DERECHA ) {
				RanaSaltaDerecha( pIni, pObjetoFrog, VecFrog );
				(*pkey)[KEY_RIGHT] = true;
				//al_start_timer(resting_timer);
			}*/
		/*default:
			if( ObjetoFrog->Pos_y <= LIM_SALTO_ABAJO ) {
				RanaSaltaAbajo( pIni, pObjetoFrog, VecFrog );			
				(*pkey)[KEY_DOWN] = true;	
				//al_start_timer(resting_timer);
			}*/	
/*	}
}

void TeclaSoltadaJugador1(ALLEGRO_EVENT *pev, bool **pkey){
	switch(pev->keyboard.keycode){
		case ALLEGRO_KEY_UP:
			(*pkey)[KEY_UP] = true;			
			break;
		case ALLEGRO_KEY_DOWN:
			(*pkey)[KEY_DOWN] = true;
			break;
		case ALLEGRO_KEY_LEFT:
			(*pkey)[KEY_LEFT] = true;
			break;
		case ALLEGRO_KEY_RIGHT:
			(*pkey)[KEY_RIGHT] = true;
			break;	
	}
}



*/
