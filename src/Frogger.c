#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include "../inc/VariablesFrogger.h"
#include "../inc/AlTodo.h"
#include "../inc/Teclas.h"
#include "../inc/SaltosFrogLib.h"
#include "../inc/MovimientoAmbiente.h"

enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};
enum MYJUMPS {
	JUMP_UP, JUMP_DOWN, JUMP_LEFT, JUMP_RIGHT
};
 
int main(int argc, char **argv)
{
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *resting_timer = NULL, *frames_timer;
	
	Objeto *Ini = NULL;
	/*aaaaa*/
	/*int aux;
	Objeto *Act;*/
	/*aaaaa*/
	bool key[4] = { false, false, false, false };
	bool redraw = false; //Identifica si hay que redibujar o no
	bool jump[4] = { false, false, false, false };
	bool doexit = false; //Identifica si hay que salir o no
	
	if( AlInitTodo(&resting_timer, &frames_timer, &display, &event_queue, &Ini) == -5 ) return -1;
	
	while(!doexit){ //Loop del juego
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//if( al_get_timer_started(frames_timer) == true ) fprintf(stderr, "\n\t frame_timer INICIALIZADO \n");
		/*aaaaa*/
		/*MoverAlgo(&Ini);*/
		/*aaaaa*/
		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { //si recibe esto, cierra la ventana
			break;
		}
		else if(ev.timer.source == frames_timer) {
			MoverCosas(&Ini);			
		}
		else if(ev.timer.source == resting_timer) { //evento de timer de descanso
			Jugador1SigueApretandoFlecha(&ev, key, jump, &redraw, &Ini);
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) { //evento de tecla presionada
			Jugador1ApretoFlecha(&ev, key, jump, &redraw, &resting_timer, &Ini);
		} 
		else if(ev.type == ALLEGRO_EVENT_KEY_UP) { //evento de tecla soltada
			Jugador1SoltoFlecha(&ev, key, &doexit, &resting_timer);
		}
		if(redraw) { //si al llegar acá, hay que redibujar
			if ( HayQueRedibujar(&redraw, jump, &Ini) == -5){
				AlDestroyTodo(&resting_timer, &frames_timer, &display, &event_queue, &Ini);
				return -1;
			}	
		}
	} //FIN DEL LOOP
	
	AlDestroyTodo(&resting_timer, &frames_timer, &display, &event_queue, &Ini);
	LiberarTodo(&Ini);
	
	return 0;
}
