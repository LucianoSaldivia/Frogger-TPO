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
 
int main(void)
{
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *resting_timer = NULL, *frames_timer = NULL;	
	ALLEGRO_BITMAP **VecFrog = NULL;
	Objeto *Act = NULL, *ObjetoFrog = NULL, *Ini = NULL;
	char FlagDeSalida = 0; // Flag de salida
	bool *key = NULL;
	
	if( AlInitTodo(&resting_timer, &frames_timer, &display, &event_queue, &VecFrog, &key) == -5 ){
		AlDestroyTodo(&resting_timer, &frames_timer, &display, &event_queue, &VecFrog, &key);
		return -1;	
	}
	
	if( IniciarLista(&Ini, &ObjetoFrog) == -5 ){
		AlDestroyTodo(&resting_timer, &frames_timer, &display, &event_queue, &VecFrog, &key);
		LiberarTodo(&Ini);	
		return -1;
	}
	/*aaa*/
	fprintf(stderr, "\n \n ");
	Act = Ini;
	while(Act != NULL){
		fprintf(stderr, "\n %s %d %s %s %f %f %f ", Act->Nombre, Act->Numero, Act->DirImagen, Act->DirMov, Act->Velocidad, Act->Dif_x, Act->Pos_y);
		Act = Act->Sig;
	}
	fprintf(stderr, "\n %f", BOUNCE_Y);	
	/*aaa*/

	al_start_timer(frames_timer);
	al_start_timer(resting_timer);
	al_flush_event_queue(event_queue);
	while( /*FlagDeSalida == 0*/ 1 ){ //Loop del juego
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		
		if( ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE || ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE ) /*FlagDeSalida = 5*/ break;
		else switch(ev.type){
			case ALLEGRO_EVENT_TIMER:
				if(ev.timer.source == frames_timer) MoverAmbiente(&Ini);
				else if(ev.timer.source == resting_timer) TeclaPresionadaJugador1( &ev, &key, &Ini, &ObjetoFrog, VecFrog );
				break;
			case ALLEGRO_EVENT_KEY_DOWN:
				fprintf(stderr, "\n \n \t\t Apretaste algo... \n");
				TeclaPresionadaJugador1( &ev, &key, &Ini, &ObjetoFrog, VecFrog );
				//Jugador1ApretoFlecha(&ev, &key, &resting_timer, &ObjetoFrog, &Ini, VecFrog);
				break;
			case ALLEGRO_EVENT_KEY_UP:
				TeclaSoltadaJugador1( &ev, &key );
				//Jugador1SoltoFlecha(&ev, &key, &doexit, &resting_timer);
				break;
		}
	} //Fin del Loop 	
	AlDestroyTodo(&resting_timer, &frames_timer, &display, &event_queue, &VecFrog, &key);
	LiberarTodo(&Ini);
		
	return 0;
}
