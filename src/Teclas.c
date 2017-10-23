#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include "../inc/VariablesFrogger.h"
#include "../inc/SaltosFrogLib.h"
#include "../inc/Teclas.h"
#include "../inc/AlTodo.h"

void Jugador1ApretoFlecha(ALLEGRO_EVENT *ev, bool *key, bool *jump, bool *redraw, ALLEGRO_TIMER **resting_timer, Objeto **Ini){
	Objeto *ObjetoFrog;
	
	ObjetoFrog = *(Ini);
	while( ! (strstr(ObjetoFrog->Nombre, "Frog")) && ObjetoFrog->Numero == 1 ){
		ObjetoFrog = ObjetoFrog->Sig;
	}		
	switch(ev->keyboard.keycode) {
		case ALLEGRO_KEY_UP: //si es tecla arriba
			key[KEY_UP] = true; //en nuestro set de teclas, arriba es true
			if( ObjetoFrog->Pos_y >= (BOUNCE_Y+UPPER_OFFSET)) { //si se puede mover, habilitamos el movimiento
				jump[JUMP_UP] = true;
			}	
			break;
		case ALLEGRO_KEY_DOWN://si es tecla abajo
			key[KEY_DOWN] = true;  //en nuestro set de teclas, abajo es true
			if( ObjetoFrog->Pos_y <= SCREEN_H - FROG_SIZE - BOUNCE_Y) {//si se puede mover, le cambiamos la posicion
				jump[JUMP_DOWN] = true;
			}
			break;
		case ALLEGRO_KEY_LEFT: //igual que KEY_UP, pero para la izquierda
			key[KEY_LEFT] = true;
			if( ObjetoFrog->Pos_x >= BOUNCE_X) {
				jump[JUMP_LEFT] = true;
			}
			break;
		case ALLEGRO_KEY_RIGHT: //igual que  KEY_DOWN, pero para la derecha
			key[KEY_RIGHT] = true;
			if( ObjetoFrog->Pos_x <= SCREEN_W - FROG_SIZE - BOUNCE_X) {
				jump[JUMP_RIGHT] = true;
			}  
			break;
	}
	*(redraw) = true;
	al_start_timer(*(resting_timer));
}

void Jugador1SoltoFlecha(ALLEGRO_EVENT *ev, bool *key, bool *doexit, ALLEGRO_TIMER **resting_timer){	
	switch(ev->keyboard.keycode) { //detectamos la tecla y en nuestro set de teclas, queda como false
		case ALLEGRO_KEY_UP:
			key[KEY_UP] = false;
			break;	
		case ALLEGRO_KEY_DOWN:
			key[KEY_DOWN] = false;
			break;	
		case ALLEGRO_KEY_LEFT: 
			key[KEY_LEFT] = false;
			break;
			
		case ALLEGRO_KEY_RIGHT:
			key[KEY_RIGHT] = false;
			break;  
		case ALLEGRO_KEY_ESCAPE:
			*(doexit) = true;
			break;
	}
	al_stop_timer(*(resting_timer));	
}

void Jugador1SigueApretandoFlecha(ALLEGRO_EVENT *ev, bool *key, bool *jump, bool *redraw, Objeto **Ini){
	Objeto *Act;
	
	Act = *(Ini);
	while( (strstr(Act->Nombre, "Frog") == NULL) || Act->Numero != 1 || Act != NULL ){
		Act = Act->Sig;
	}
	if(key[KEY_UP] && Act->Pos_y >= BOUNCE_Y) { //si UP estaba presionada y se puede mover
		jump[JUMP_UP] = true;
	}
	if(key[KEY_DOWN] && Act->Pos_y <= SCREEN_H - FROG_SIZE - BOUNCE_Y) {
		jump[JUMP_DOWN] = true;
	}
	if(key[KEY_LEFT] && Act->Pos_x >= BOUNCE_X) {
		jump[JUMP_LEFT] = true;
	}
	if(key[KEY_RIGHT] && Act->Pos_x <= SCREEN_W - FROG_SIZE - BOUNCE_X) {
		jump[JUMP_RIGHT] = true;
	}	
	*(redraw) = true; //HAY que redibujar	
}


