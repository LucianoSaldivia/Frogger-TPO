#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include "../inc/VariablesFrogger.h"
#include "../inc/SaltosFrogLib.h"
#include "../inc/Teclas.h"
#include "../inc/AlTodo.h"


enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};
enum MYJUMPS {
	JUMP_UP, JUMP_DOWN, JUMP_LEFT, JUMP_RIGHT
};

int HayQueRedibujar(bool *redraw, bool *jump, ALLEGRO_TIMER **resting_timer, ALLEGRO_TIMER **frames_timer, ALLEGRO_DISPLAY **display, ALLEGRO_EVENT_QUEUE **event_queue, Objeto **Ini){
	int aux;
	
	*(redraw) = false; //dejamos redraw en false, para que no entre infinitas veces					  
			  
	if(jump[JUMP_UP]){
		aux = (FrogSaltaArriba(Ini));			   
		jump[JUMP_UP] = false;
	}
	
	if(jump[JUMP_DOWN]){
		aux = (FrogSaltaAbajo(Ini));
		jump[JUMP_DOWN] = false;
	}
	if(jump[JUMP_LEFT]){
		aux = (FrogSaltaIzquierda(Ini));
		jump[JUMP_LEFT] = false;
	}
	if(jump[JUMP_RIGHT]){
		aux = (FrogSaltaDerecha(Ini));
		jump[JUMP_RIGHT] = false;
	}	
	
	if(aux == -5) {
		AlDestroyTodo(resting_timer, frames_timer, display, event_queue, Ini);
		return -5;
	}
	else return 0;
}


void Jugador1ApretoFlecha(ALLEGRO_EVENT *ev, bool *key, bool *jump, bool *redraw, ALLEGRO_TIMER **resting_timer, Objeto **Ini){
	Objeto *Act, *ObjetoFrog;
	
	Act = *(Ini);
	while( Act != NULL ){
		if( (strstr(Act->Nombre, "Frog") != NULL) && Act->Numero == 1 ){
			ObjetoFrog = Act;
		}
		Act = Act->Sig;
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
			if(key[KEY_DOWN] && ObjetoFrog->Pos_y <= SCREEN_H - FROG_SIZE - BOUNCE_Y) {//si se puede mover, le cambiamos la posicion
				jump[JUMP_DOWN] = true;
			}
			break;
	
		case ALLEGRO_KEY_LEFT: //igual que KEY_UP, pero para la izquierda
			key[KEY_LEFT] = true;
			if(key[KEY_LEFT] && ObjetoFrog->Pos_x >= BOUNCE_X) {
				jump[JUMP_LEFT] = true;
			}
			break;
	
		case ALLEGRO_KEY_RIGHT: //igual que  KEY_DOWN, pero para la derecha
			key[KEY_RIGHT] = true;
			if(key[KEY_RIGHT] && ObjetoFrog->Pos_x <= SCREEN_W - FROG_SIZE - BOUNCE_X) {
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


