#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include "../inc/VariablesFrogger.h"
#include "../inc/Inicializacion.h"
#include "../inc/CreadorDeArchivos.h"
#include "../inc/Teclado.h"
#include "../inc/Saltos.h"
#include "../inc/MovimientoAmbiente.h"
	
int main(int argc, char *argv[])
{
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *resting_timer = NULL, *frames_timer;
	ALLEGRO_BITMAP **VecFrog = NULL;
	Objeto *Ini = NULL, *ObjetoFrog = NULL;
	bool *key, doexit = false; //Flags de teclas apretadas y de salida

	/*aaaaa*/
	/*int aux;*/
	Objeto *Act;
	/*aaaaa*/
	
	
	if( InicializarALLEGRO( &display, &event_queue, &resting_timer, &frames_timer, &VecFrog, &key ) == -5 ){
		FinalizarALLEGRO( &display, &event_queue, &resting_timer, &frames_timer, &VecFrog, &key );
		return -1;		
	}
	if( argc == 2 && strstr(argv[1], "Crear") != NULL ){
		if ( CrearArchivo( 0 ) == -5 ){
			FinalizarALLEGRO( &display, &event_queue, &resting_timer, &frames_timer, &VecFrog, &key );
			return -1;
		}
	}

	if( EnlistarObjetos( &Ini, &ObjetoFrog ) == -5 ){
		FinalizarALLEGRO( &display, &event_queue, &resting_timer, &frames_timer, &VecFrog, &key );
		LiberarMemoria( &Ini );
		return -1;
	}

	Act = Ini;
	while( Act != NULL){
		fprintf(stderr, "\n%s %d %s %f %f", Act->Nombre, Act->Numero, Act->DirImagen, Act->Pos_y, Act->Dif_x);
		Act = Act->Sig;
	}
	
	InicializarTimers( &resting_timer, &frames_timer );
	if( al_get_timer_started( resting_timer ) == true ) fprintf(stderr, "\n\t REST_TIMER INICIALIZADO \n");
	if( al_get_timer_started( frames_timer ) == true ) fprintf(stderr, "\n\t FRAMES_TIMER INICIALIZADO \n");
	
	while( doexit == false ){ 					//Loop del juego
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		
		if( ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE || ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE ) /*FlagDeSalida = 5*/ break;
		else switch(ev.type){
			case ALLEGRO_EVENT_TIMER:
				if(ev.timer.source == frames_timer) MoverCosas( &Ini );
				//else if(ev.timer.source == resting_timer) TeclaPresionadaJugador1( &ev, &key, &Ini, &ObjetoFrog, VecFrog );
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
	}
	
	al_rest(1);
	fprintf(stderr, "\n Hasta antes de finalizar TODO BIEN");
	FinalizarALLEGRO( &display, &event_queue, &resting_timer, &frames_timer, &VecFrog, &key );
	
	fprintf(stderr, "\n Hasta antes de liberar TODO BIEN\n");
	LiberarMemoria( &Ini );
	fprintf(stderr, "\n Hasta el final TODO BIEN\n");
	return 0;
}
