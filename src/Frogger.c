#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include "../inc/VariablesFrogger.h"
#include "../inc/SaltosFrogLib.h"
#include "../inc/Teclas.h"
#include "../inc/AlInitTodo.h"

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
	ALLEGRO_TIMER *resting_timer = NULL, *refresh_timer = NULL;
	Objeto *Ini, *Act, *Ant;

	
	bool key[4] = { false, false, false, false };
	bool redraw = false; //Identifica si hay que redibujar o no
	bool jump[4] = { false, false, false, false };
	bool doexit = false; //Identifica si hay que salir o no
	
	if(AlInitTodo(&resting_timer, &refresh_timer, &display, &event_queue, &Ini) == -5) return -1;	

	while(!doexit){ //Loop del juego
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		
		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { //si recibe esto, cierra la ventana
			break;
		}	
		
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) { //evento de tecla presionada
			/*aaaaa*/
			fprintf(stderr, "\n\t Apretaste una tecla, yo te vi \n");
			/*aaaaa*/
			Jugador1ApretoFlecha(&ev, key, jump, &redraw, &resting_timer, &Ini);
		}
		  
		else if(ev.type == ALLEGRO_EVENT_KEY_UP) { //evento de tecla soltada
			Jugador1SoltoFlecha(&ev, key, &doexit, &resting_timer);
		}
		  
		else if(ev.timer.source == resting_timer) { //evento de timer de descanso
			Jugador1SigueApretandoFlecha(&ev, key, jump, &redraw, &Ini);
		}  
		
		if(redraw) { //si al llegar acá, hay que redibujar
			
			if ( HayQueRedibujar(&redraw, jump, &Ini) == -5){
				Act = Ini;
				while(Act != NULL){
					al_destroy_bitmap(Act->Imagen);
					Act = Act->Sig;
				}
				al_destroy_event_queue(event_queue);
				al_destroy_display(display);
				al_destroy_timer(resting_timer);
				al_destroy_timer(refresh_timer);
				return -1;
			}	
		}
	} //FIN DEL LOOP
	
	
	
	
		//AL DESTROY A TODO
		Act = Ini;
		while(Act != NULL){
			al_destroy_bitmap(Act->Imagen);
			Act = Act->Sig;
		}
		al_destroy_timer(resting_timer);
		al_destroy_timer(refresh_timer);
		al_destroy_display(display);
		al_destroy_event_queue(event_queue);
		
		
		// FREE A TODO
		Act = Ini;
		while(Act != NULL){
			Ant = Act;
			Act = Act->Sig;
			free(Ant);
		}	
		return 0;
}
