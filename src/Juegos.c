#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "../inc/VariablesFrogger.h"
#include "../inc/Inicializacion.h"
#include "../inc/MovimientoAmbiente.h"
#include "../inc/Teclado.h"
#include "../inc/Saltos.h"
#include "../inc/Dibujos.h"
#include "../inc/Menu.h"

char Juego1vsC( ALLEGRO_DISPLAY **p_display, ALLEGRO_EVENT_QUEUE **p_event_queue ){
	ALLEGRO_TIMER *resting_timer = NULL, *frames_timer = NULL, *sprites_timer = NULL;
	ALLEGRO_BITMAP **VecFrog = NULL;
	Objeto *Ini = NULL, *ObjetoFrog = NULL, /*aaaaaaa*/*Act = NULL;
	bool *key;
	char Flag = CONTINUAR, Direccion = NO_HAY_DIRECCION, ContadorSprites = 0;
	//char EstadoFrog, *PosicionesFinales /*( malloc 4*sizeof char)*/;
	
	if( Inicializar1vsC( p_event_queue, &resting_timer, &frames_timer, &sprites_timer, &VecFrog, &key ) == ERROR ){
		Finalizar1vsC( p_event_queue, &resting_timer, &frames_timer, &sprites_timer, &VecFrog, &key );
		return ERROR;		
	}
	
	if( AlistarObjetos( &Ini, &ObjetoFrog, "Archivos/Objetos1vsC.txt" ) == ERROR ){
		Finalizar1vsC( p_event_queue, &resting_timer, &frames_timer, &sprites_timer, &VecFrog, &key );
		LiberarMemoria( &Ini );
		return ERROR;
	}
	
	/*aaaaaaaaaaaaaaaaaaaaaaaa*/
	Act = Ini;
	while( Act != NULL){
		fprintf(stderr, "\n%s %d %s %f %f", Act->Nombre, Act->Numero, Act->DirImagen, Act->Pos_y, Act->Dif_x);
		Act = Act->Sig;
	}
	/*aaaaaaaaaaaaaaaaaaaaaaaa*/
	
	al_start_timer( frames_timer );
		
	while( Flag != SALIR && Flag != VOLVER /*&& FinDelJuego == TODAVIA_NO*/){							// VOLVER = VOLVER AL MENU PRINCIPAL
		while( Flag != PAUSA ){											//Juego
			ALLEGRO_EVENT ev;
			al_wait_for_event( *(p_event_queue), &ev);
			
			if( ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE ) return SALIR;
			
			else if( ev.type == ALLEGRO_EVENT_KEY_DOWN ){
				Flag = Jugador1ApretoTecla( &ev, key, &Direccion, &resting_timer, &sprites_timer );
			}
			
			else if( ev.type == ALLEGRO_EVENT_KEY_UP ){
				Jugador1SoltoTecla( &ev, key, &resting_timer );
			}
			
			else if( ev.type == ALLEGRO_EVENT_TIMER ){
				if( ev.timer.source == frames_timer ){
					MoverTodo( &Ini, &ObjetoFrog );
					RedibujarDesde( &Ini );
					DetectarColision( &Ini, &ObjetoFrog, VecFrog );
				}
				else if( ev.timer.source == resting_timer ){
					al_start_timer( sprites_timer );
					if( key[KEY_UP] == true ) Direccion = ARRIBA;
					if( key[KEY_DOWN] == true ) Direccion = ABAJO;
					if( key[KEY_LEFT] == true ) Direccion = IZQUIERDA;
					if( key[KEY_RIGHT] == true ) Direccion = DERECHA;
				}
				else if( ev.timer.source == sprites_timer && Direccion != NO_HAY_DIRECCION ){
					if( ContadorSprites < CANT_SPRITES ){
						switch( Direccion ){
							case ARRIBA:
								if( ObjetoFrog->Pos_y > LIM_SALTO_ARRIBA ) RanaSaltaArriba( &ObjetoFrog, VecFrog, &ContadorSprites );
								break;
							case ABAJO:
								if( ObjetoFrog->Pos_y < LIM_SALTO_ABAJO ) RanaSaltaAbajo( &ObjetoFrog, VecFrog, &ContadorSprites );
								break;
							case IZQUIERDA:
								if( ObjetoFrog->Pos_x > LIM_SALTO_IZQUIERDA ) RanaSaltaIzquierda( &ObjetoFrog, VecFrog, &ContadorSprites );
								break;
							case DERECHA:
								if( ObjetoFrog->Pos_x < LIM_SALTO_DERECHA ) RanaSaltaDerecha( &ObjetoFrog, VecFrog, &ContadorSprites );
								break;
						}
					}
					else{
						al_stop_timer( sprites_timer );
						ContadorSprites = 0;
						Direccion = NO_HAY_DIRECCION;
						fprintf(stdout, "\n\t PosFrog X : %f\t\t PosFrog Y : %f", ObjetoFrog->Pos_x, ObjetoFrog->Pos_y);
					}
				}
			}
		}
		
		Flag = MenuPausa( p_display );												// Devuelve CONTINUAR, VOLVER o SALIR	LIMPIAR EVENT QUEUE ANTES DE SALIR DE PAUSA
		al_flush_event_queue( *(p_event_queue) );
	}
		
	/* Menu para agregar puntaje obtenido */
	
	Finalizar1vsC( p_event_queue, &resting_timer, &frames_timer, &sprites_timer, &VecFrog, &key );
	LiberarMemoria( &Ini );
	
	return Flag;
}

